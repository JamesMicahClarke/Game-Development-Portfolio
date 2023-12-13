// minimalistic code to draw a single triangle, this is not part of the API.
// required for compiling shaders on the fly, consider pre-compiling instead
#include <d3dcompiler.h>
#include "FSLogo.h"

#pragma comment(lib, "d3dcompiler.lib")
#include "d3dx12.h" // official helper file provided by microsoft
// TODO: Part 1b
// Simple Vertex Shader
const char* vertexShaderSource = R"(
// an ultra simple hlsl vertex shader
// TODO: Part 2i
#pragma pack_matrix(row_major)
// TODO: Part 2b

struct Scene_Data
{
	float4 lightDirection;
	float4 lightColor; 
	float4 ambience;
	float4 camVec;
	float4x4 view;
	float4x4 projection;
	float4 padding[4];
};

struct OBJ_ATT
{
	float3  Kd;		// diffuse reflectivity
	float	  d; 	// dissolve (transparency)
	float3  Ks;		// specular reflectivity
	float	  Ns;	// specular exponent
	float3  Ka;		// ambient reflectivity
	float sharpness;  // local reflection map sharpness
	float3	Tf;		// transmission filter
	float	  Ni;	// optical density (index of refraction)
	float3  Ke;		// emissive reflectivity
	unsigned int illum; // illumination model
};

struct Mesh_Data
{
	float4x4 world;
	OBJ_ATT material;
	unsigned int padding[28];
};

struct VOutput
{
	float4 posH : SV_POSITION; // homogoneous projection space
	float3 nrmW : NORMALS; //normal in world space (lighting)
	float3 posW : WORLD; // position in world space (lighting)
};

ConstantBuffer<Scene_Data> cameraAndLights : register(b0, Space0);
ConstantBuffer<Mesh_Data> meshInfo : register(b1, Space0);
// TODO: Part 4f
// TODO: Part 4a
// TODO: Part 1f

// TODO: Part 4b
VOutput main(float3 inputVertex : POSITION,  float3 inputUV : UV, float3 inputNormals : NORMALS)
{
	// TODO: Part 1h
	VOutput ouputs;
	float4 pos = float4(inputVertex,1); //float3(0.0f, -0.75f, 0.75), 1);
	// TODO: Part 2i
	pos = mul(pos, meshInfo.world);
	ouputs.posW = pos.xyz;

	pos = mul(pos, cameraAndLights.view);
	pos = mul(pos, cameraAndLights.projection);
	// TODO: Part 4b
	ouputs.posH = pos;
	ouputs.nrmW = mul(inputNormals, meshInfo.world);
	return ouputs;
}
)";
// Simple Pixel Shader
const char* pixelShaderSource = R"(
// an ultra simple hlsl pixel shader
// TODO: Part 2b

struct Scene_Data
{
	float4 lightDirection;
	float4 lightColor; 
	float4 ambience;
	float4 camVec;
	float4x4 view;
	float4x4 projection;
	float4 padding[4];
};

struct OBJ_ATT
{
	float3  Kd;		// diffuse reflectivity
	float	  d; 	// dissolve (transparency)
	float3  Ks;		// specular reflectivity
	float	  Ns;	// specular exponent
	float3  Ka;		// ambient reflectivity
	float sharpness;  // local reflection map sharpness
	float3	Tf;		// transmission filter
	float	  Ni;	// optical density (index of refraction)
	float3  Ke;		// emissive reflectivity
	unsigned int illum; //illumination model
};

struct Mesh_Data
{
	float4x4 world;
	OBJ_ATT material;
	unsigned int padding[28];
};

struct VOutput
{
	float4 posH : SV_POSITION; // homogoneous projection space
	float3 nrmW : NORMALS; //normal in world space (lighting)
	float3 posW : WORLD; // position in world space (lighting)
};

ConstantBuffer<Scene_Data> cameraAndLights : register(b0, Space0);
ConstantBuffer<Mesh_Data> meshInfo : register(b1, Space0);

 //TODO: Part 4f
 //TODO: Part 4b
float4 main(VOutput input) :SV_Target
{	
	input.nrmW = normalize(input.nrmW);
	float3 lightDir = normalize(cameraAndLights.lightDirection.xyz);
	
	// TODO: Part 3a	   //(0.3f,0.2f,0.5f,0); // TODO: Part 1a
	float4 surfColor = float4(meshInfo.material.Kd,0);

	float lightRatio = clamp(dot(-lightDir, input.nrmW.xyz),0,1);
	lightRatio = clamp(lightRatio + cameraAndLights.ambience,0,1);
	float4 result = lightRatio * cameraAndLights.lightColor * surfColor + (surfColor * cameraAndLights.ambience);
	

	 //TODO: Part 4c
	 //TODO: Part 4g
	float3 viewDirec = normalize(cameraAndLights.camVec.xyz - input.posW.xyz);
	float3 halfVec = normalize((-lightDir) + viewDirec);
	float intensity = max(clamp(dot(input.nrmW,halfVec),0,1),0);
	intensity = pow(intensity, meshInfo.material.Ns);
	
	result = result+(cameraAndLights.lightColor * float4(meshInfo.material.Ks,0) * intensity);
	return result;
}
)";

using namespace GW::MATH;
struct Scene_Data
{
	GVECTORF lightDirection;
	GVECTORF lightColor;
	GVECTORF ambience;
	GVECTORF camVec;
	GMATRIXF view;
	GMATRIXF projection;
	GVECTORF padding[4];
};

struct Mesh_Data
{
	GMATRIXF world;
	OBJ_ATTRIBUTES material;
	unsigned padding[28];
};

int indexCount = 8532;

// Creation, Rendering & Cleanup
class Renderer
{
	// proxy handles
	GW::SYSTEM::GWindow win;
	GW::GRAPHICS::GDirectX12Surface d3d;
	// what we need at a minimum to draw a triangle
	D3D12_VERTEX_BUFFER_VIEW					vertexView;
	D3D12_INDEX_BUFFER_VIEW						indexView;
	Microsoft::WRL::ComPtr<ID3D12Resource>		vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource>		indexBuffer;
	// TODO: Part 1g
	// TODO: Part 2c
	Microsoft::WRL::ComPtr<ID3D12Resource> ConstantBuffer;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapper;
	DXGI_SWAP_CHAIN_DESC swapDesc;

	// TODO: Part 2e
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	Microsoft::WRL::ComPtr<ID3D12RootSignature>	rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState>	pipeline;
	//2f
	D3D12_CONSTANT_BUFFER_VIEW_DESC constBufferDesc = { 0 };
	D3D12_CPU_DESCRIPTOR_HANDLE descHandle;
	CD3DX12_ROOT_PARAMETER rootParam[2];
	// TODO: Part 2a
	Scene_Data scene;
	Mesh_Data mesh[2];

	GMatrix math;
	GVector vector;

	// TODO: Part 2b
	// TODO: Part 4f
	GVECTORF ambience;
	GVECTORF camVec;
public:

	/*void Normalize(GVECTORF& vector)
	{
		GVECTORF normal;
		float magnitude = sqrt(powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2));
		for (int i = 0; i < 3; i++)
		{
			normal.data[i] = vector.data[i] / magnitude;
		}
	}*/
	Renderer(GW::SYSTEM::GWindow _win, GW::GRAPHICS::GDirectX12Surface _d3d)
	{
		win = _win;
		d3d = _d3d;
		ID3D12Device* creator;
		d3d.GetDevice((void**)&creator);
		// TODO: part 2a
		math.Create();
		//mesh.world = GIdentityMatrixF;

		GVECTORF viewVec = { .75f,.25f,-1.5,1 };
		//scene.view = GIdentityMatrixF;
		//math.TranslateGlobalF(scene.view, viewVec, scene.view);
		//math.TranslateGlobalF(scene.view, viewVec, scene.view);

		//math.RotateXGlobalF(scene.view, 0.15, scene.view);
		//math.RotateYGlobalF(scene.view, 0.75, scene.view);
		//math.RotateZGlobalF(scene.view, 0, scene.view);
		mesh[0].world = GIdentityMatrixF;
		mesh[1].world = GIdentityMatrixF;
		mesh[0].material = FSLogo_materials[0].attrib;
		mesh[1].material = FSLogo_materials[1].attrib;

		

		GVECTORF eye = { 0.75, 0.25, -1.5, 1 };
		GVECTORF at = { .15, .75, 0, 1 };
		GVECTORF up = { 0, 1, 0, 0 };
		math.LookAtLHF(eye, at, up, scene.view);

		float fov = G2D_DEGREE_TO_RADIAN_F(65);
		float screenHeight = 600;
		float screenWidth = 800;
		float nPlane = 0.1;
		float fPlane = 100;
		math.ProjectionDirectXLHF(fov, screenWidth / screenHeight, nPlane, fPlane, scene.projection);

		scene.lightDirection = { -1,-1,2,1 };
		scene.lightColor = { .9,.9,1,1 };

		//vector.NormalizeF(scene.lightDirection, scene.lightDirection);
		vector.NormalizeF(scene.lightDirection, scene.lightDirection);


		// TODO: part 2b
		// TODO: Part 4f
		scene.camVec = eye;
		scene.ambience = { .25,.25,.35 };
		/*for (int i = 0; i < 4; i++)
		{
			scene.lightColor.data[i] = scene.lightColor.data[i] + ambience.data[i];

		}*/
		// TODO: Part 1c
		// Create Vertex Buffer
		//vertex stuff
		creator->CreateCommittedResource( // using UPLOAD heap for simplicity
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // DEFAULT recommend  
			D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(FSLogo_vertices)),
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexBuffer));
		// Transfer triangle data to the vertex buffer.
		UINT8* transferMemoryLocation;
		vertexBuffer->Map(0, &CD3DX12_RANGE(0, 0),
			reinterpret_cast<void**>(&transferMemoryLocation));
		memcpy(transferMemoryLocation, FSLogo_vertices, sizeof(FSLogo_vertices));
		vertexBuffer->Unmap(0, nullptr);
		// Create a vertex View to send to a Draw() call.
		vertexView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
		vertexView.StrideInBytes = sizeof(OBJ_VERT); // TODO: Part 1e
		vertexView.SizeInBytes = sizeof(FSLogo_vertices); // TODO: Part 1d
		// TODO: Part 1g
		//Create Index Buffer

		//index stuff
		creator->CreateCommittedResource( // using UPLOAD heap for simplicity
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // DEFAULT recommend  
			D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(FSLogo_indices)),
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexBuffer));
		// Transfer triangle data to the vertex buffer.
		UINT8* transferMemoryLocation2;
		indexBuffer->Map(0, &CD3DX12_RANGE(0, 0),
			reinterpret_cast<void**>(&transferMemoryLocation2));
		memcpy(transferMemoryLocation2, FSLogo_indices, sizeof(FSLogo_indices));
		indexBuffer->Unmap(0, nullptr);
		// Create a vertex View to send to a Draw() call.
		indexView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
		indexView.Format = DXGI_FORMAT_R32_UINT; // TODO: Part 1e
		indexView.SizeInBytes = sizeof(FSLogo_indices); // TODO: Part 1d
		// TODO: Part 2d
		d3d.GetSwapchain4((void**)swapper.GetAddressOf());
		swapper->GetDesc(&swapDesc);
		unsigned int constantData = (sizeof(Scene_Data) + sizeof(Mesh_Data) + sizeof(Mesh_Data)) * swapDesc.BufferCount;

		creator->CreateCommittedResource( // using UPLOAD heap for simplicity
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // DEFAULT recommend  
			D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(constantData),
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&ConstantBuffer));

		UINT8* transferMemoryLocation3;
		ConstantBuffer->Map(0, &CD3DX12_RANGE(0, 0),
			reinterpret_cast<void**>(&transferMemoryLocation3));
		memcpy(transferMemoryLocation3, &scene, sizeof(Scene_Data));
		memcpy(transferMemoryLocation3 + sizeof(Scene_Data), &mesh[0], sizeof(Mesh_Data));

		memcpy(transferMemoryLocation3 + sizeof(Scene_Data) + sizeof(Mesh_Data), &mesh[1], sizeof(Mesh_Data));
		memcpy(transferMemoryLocation3 + sizeof(Scene_Data) + (swapDesc.BufferCount * sizeof(Mesh_Data)), &scene, sizeof(Scene_Data));
		ConstantBuffer->Unmap(0, nullptr);

		// TODO: Part 2e
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		heapDesc.NodeMask = 0;
		heapDesc.NumDescriptors = 1;
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		creator->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descHeap));

		// TODO: Part 2f
		constBufferDesc.BufferLocation = ConstantBuffer->GetGPUVirtualAddress();
		constBufferDesc.SizeInBytes = constantData;
		descHandle = descHeap->GetCPUDescriptorHandleForHeapStart();
		creator->CreateConstantBufferView(&constBufferDesc, descHandle);
		// Create Vertex Shader
		UINT compilerFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if _DEBUG
		compilerFlags |= D3DCOMPILE_DEBUG;
#endif
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob, errors;
		if (FAILED(D3DCompile(vertexShaderSource, strlen(vertexShaderSource),
			nullptr, nullptr, nullptr, "main", "vs_5_1", compilerFlags, 0,
			vsBlob.GetAddressOf(), errors.GetAddressOf())))
		{
			std::cout << (char*)errors->GetBufferPointer() << std::endl;
			abort();
		}
		// Create Pixel Shader
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob; errors.Reset();
		if (FAILED(D3DCompile(pixelShaderSource, strlen(pixelShaderSource),
			nullptr, nullptr, nullptr, "main", "ps_5_1", compilerFlags, 0,
			psBlob.GetAddressOf(), errors.GetAddressOf())))
		{
			std::cout << (char*)errors->GetBufferPointer() << std::endl;
			abort();
		}
		// TODO: Part 1e
		// Create Input Layout
		D3D12_INPUT_ELEMENT_DESC format[] = {
			{
				"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
			},
			{
				"UV", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
			},
			{
				"NORMALS", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
			}
		};
		// TODO: Part 2g

		rootParam[0].InitAsConstantBufferView(0, 0);
		rootParam[1].InitAsConstantBufferView(1, 0);

		// create root signature
		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init(ARRAYSIZE(rootParam), rootParam, 0, nullptr,
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
		Microsoft::WRL::ComPtr<ID3DBlob> signature;
		D3D12SerializeRootSignature(&rootSignatureDesc,
			D3D_ROOT_SIGNATURE_VERSION_1, &signature, &errors);
		creator->CreateRootSignature(0, signature->GetBufferPointer(),
			signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
		// create pipeline state
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psDesc;
		ZeroMemory(&psDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
		psDesc.InputLayout = { format, ARRAYSIZE(format) };
		psDesc.pRootSignature = rootSignature.Get();
		psDesc.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
		psDesc.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
		psDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
		psDesc.SampleMask = UINT_MAX;
		psDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psDesc.NumRenderTargets = 1;
		psDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
		psDesc.SampleDesc.Count = 1;
		creator->CreateGraphicsPipelineState(&psDesc, IID_PPV_ARGS(&pipeline));
		// free temporary handle
		creator->Release();
	}
	void Render()
	{
		// TODO: Part 2a
		GVECTORF scaler = { .2,.2,.2,.2 };
		///GVECTORF descaler = { -1,-1,-1,-1};

		math.RotateYLocalF(mesh[1].world, G2D_DEGREE_TO_RADIAN_F(1), mesh[1].world);
		//math.RotateZLocalF(mesh[0].world, G2D_DEGREE_TO_RADIAN_F(100), mesh[0].world);
		//math.ScaleLocalF(mesh[1].world, scaler, mesh[1].world);
		//math.ScaleLocalF(mesh[1].world, descaler, mesh[1].world);
		//math.ScaleLocalF(mesh[0].world, mesh[0].world.row2, mesh[0].world);
		//math.ScaleLocalF(mesh[0].world, mesh[0].world.row3, mesh[0].world);
		//math.RotateXLocalF(mesh[0].world, G2D_DEGREE_TO_RADIAN_F(100), mesh[0].world);
		// TODO: Part 4d
		UINT8* transferRotationLocation;
		ConstantBuffer->Map(0, &CD3DX12_RANGE(0, 0),
			reinterpret_cast<void**>(&transferRotationLocation));
		memcpy(transferRotationLocation + sizeof(Scene_Data) + sizeof(Mesh_Data), &mesh[1], sizeof(Mesh_Data));
		//memcpy(transferRotationLocation + sizeof(Scene_Data), &mesh[0], sizeof(Mesh_Data));

		ConstantBuffer->Unmap(0, nullptr);

		// grab the context & render target
		ID3D12GraphicsCommandList* cmd;
		D3D12_CPU_DESCRIPTOR_HANDLE rtv;
		D3D12_CPU_DESCRIPTOR_HANDLE dsv;
		d3d.GetCommandList((void**)&cmd);
		d3d.GetCurrentRenderTargetView((void**)&rtv);
		d3d.GetDepthStencilView((void**)&dsv);
		// setup the pipeline
		cmd->SetGraphicsRootSignature(rootSignature.Get());
		// TODO: Part 2h
		cmd->SetDescriptorHeaps(1, descHeap.GetAddressOf());

		/*unsigned int bufferIndex;
		unsigned int sizeCount;
		d3d.GetSwapChainBufferIndex(bufferIndex);
		sizeCount = sizeof(Scene_Data) + sizeof(Mesh_Data) * 2;
		unsigned int combination = bufferIndex * sizeCount;*/

		// TODO: Part 4e
		unsigned int frame2 = 0;
		cmd->OMSetRenderTargets(1, &rtv, FALSE, &dsv);
		cmd->SetPipelineState(pipeline.Get());
		// now we can draw
		cmd->IASetVertexBuffers(0, 1, &vertexView);
		cmd->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		cmd->IASetIndexBuffer(&indexView);

		// TODO: Part 1h
		// TODO: Part 3b
			// TODO: Part 3c
			// TODO: Part 4e
		/*int splitIndicies1 = 5988;
		int splitIndicies2 = 2544;*/
		for (int i = 0; i < FSLogo_meshcount; i++)
		{
			cmd->SetGraphicsRootConstantBufferView(0, ConstantBuffer->GetGPUVirtualAddress());
			if (i == 0)
			{
				cmd->SetGraphicsRootConstantBufferView(1, ConstantBuffer->GetGPUVirtualAddress() + sizeof(Scene_Data) + frame2);
			}
			else
			{
				cmd->SetGraphicsRootConstantBufferView(1, ConstantBuffer->GetGPUVirtualAddress() + sizeof(Scene_Data) + sizeof(Mesh_Data) + frame2);//+ sizeof(Mesh_Data));
			}
			cmd->DrawIndexedInstanced(FSLogo_meshes[i].indexCount, 1, FSLogo_meshes[i].indexOffset, 0, 0); // TODO: Part 1c
		}

		// release temp handles
		cmd->Release();
	}
	~Renderer()
	{
		// ComPtr will auto release so nothing to do here 
	}
};
