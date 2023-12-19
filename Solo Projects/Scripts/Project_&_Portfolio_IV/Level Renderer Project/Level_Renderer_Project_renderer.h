// minimalistic code to draw a single triangle, this is not part of the API.
// required for compiling shaders on the fly, consider pre-compiling instead
#include <d3dcompiler.h>
#include <chrono>
#pragma comment(lib, "d3dcompiler.lib")
#include "d3dx12.h" // official helper file provided by microsoft
//#include "h2bParser.h"
#include <filesystem>
#include "Level_Data.h"

// Simple Vertex Shader
const char* vertexShaderSource = R"(
// an ultra simple hlsl vertex shader
// TODO: Part 2b
	// TODO: Part 2f
	// TODO: Part 3b
// TODO: Part 1c
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
	ATTRIBUTES material;
	unsigned padding[28];
};


// Creation, Rendering & Cleanup
using namespace GW::MATH;
using namespace H2B;
class Renderer
{
	GW::SYSTEM::GWindow win;
	GW::GRAPHICS::GDirectX12Surface d3d;
	// TODO: Part 4a
	GW::INPUT::GInput input;
	GW::INPUT::GController control;
	std::chrono::steady_clock::time_point last_update;
	// TODO: Part 2a
	GMATRIXF world[6];
	GMatrix math;
	GVector vector;
	// TODO: Part 3c
	// TODO: Part 2e
	GMATRIXF view = GIdentityMatrixF;

	// TODO: Part 3a
	GMATRIXF PerspectiveProj = GIdentityMatrixF;
	GMATRIXF projView = GIdentityMatrixF;
	float aspRatio;
	// what we need at a minimum to draw a triangle
	D3D12_VERTEX_BUFFER_VIEW					vertexView;
	D3D12_INDEX_BUFFER_VIEW						indexView;
	Microsoft::WRL::ComPtr<ID3D12Resource>		vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource>		indexBuffer;

	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapper;
	DXGI_SWAP_CHAIN_DESC swapDesc;

	Microsoft::WRL::ComPtr<ID3D12RootSignature>	rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState>	pipeline;

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;

	D3D12_CONSTANT_BUFFER_VIEW_DESC constBufferDesc = { 0 };
	D3D12_CPU_DESCRIPTOR_HANDLE descHandle;

	Level_Data loading;
	Scene_Data scene;
	Mesh_Data mesh[2];

public:

	Renderer(GW::SYSTEM::GWindow _win, GW::GRAPHICS::GDirectX12Surface _d3d)
	{

		loading.LoadLevel(loading.Objparser);






		win = _win;
		d3d = _d3d;
		ID3D12Device* creator;
		d3d.GetDevice((void**)&creator);
		// TODO: Part 4a
		input.Create(win);
		control.Create();
		// TODO: Part 2a

		mesh[0].world = GIdentityMatrixF;
		mesh[1].world = GIdentityMatrixF;
		mesh[0].material = loading.Materials.data()->attrib;
		mesh[1].material = loading.Materials.data()->attrib;


		GVECTORF translation[6] = {
			{0,0,0,1},//{0,-.52f,0,1}, //1
			{0,.52f,0,1}, //2
			{0.52f,0,0,1}, //3
			{-0.52f,0,0,1}, //4
			{0,0,0.52f,1}, //5
			{0,0,-.52f,1} //6
		};
		float rotation = G2D_DEGREE_TO_RADIAN_F(90);

		float fov = G2D_DEGREE_TO_RADIAN_F(65);
		float nPlane = .1f;
		float fPlane = 100;
		for (int i = 0; i < 6; i++)
		{
			world[i] = GIdentityMatrixF;
		}

		math.Create();
		math.MultiplyMatrixF(mesh[0].world, loading.WorldMatricies.data()[0], mesh[0].world);
		math.MultiplyMatrixF(mesh[1].world, loading.WorldMatricies.data()[1], mesh[1].world);



		GVECTORF eye = { 0.75, 1.25, -1.5, 1 };
		GVECTORF at = { .15, .75, 0, 1 };
		GVECTORF up = { 0, 1, 0, 0 };
		math.LookAtLHF(eye, at, up, scene.view);

		d3d.GetAspectRatio(aspRatio);
		math.ProjectionDirectXLHF(fov, aspRatio, nPlane, fPlane, scene.projection);


		scene.lightDirection = { -1,-1,2,1 };
		scene.lightColor = { .9,.9,1,1 };

		vector.NormalizeF(scene.lightDirection, scene.lightDirection);


		// TODO: part 2b
		// TODO: Part 4f
		scene.camVec = eye;
		scene.ambience = { .25,.25,.35 };


		// TODO: Part 1b
		// TODO: Part 1c
		// Create Vertex Buffer




#pragma region Grid_Verts
		//float verts[] =
		//{
		//	   -0.52f, -0.04f,0,1, //1
		//		0.52f, -0.04f,0,1,
		//	   -0.52f, -0.08f,0,1, //2
		//		0.52f, -0.08f,0,1,
		//	   -0.52f, -0.12f,0,1, //3
		//		0.52f, -0.12f,0,1,
		//	   -0.52f, -0.16f,0,1, //4
		//		0.52f, -0.16f,0,1,
		//	   -0.52f, -0.2f, 0,1,//5
		//		0.52f, -0.2f, 0,1,
		//	   -0.52f, -0.24f,0,1, //6
		//		0.52f, -0.24f,0,1,
		//	   -0.52f, -0.28f,0,1, //7
		//		0.52f, -0.28f,0,1,
		//	   -0.52f, -0.32f,0,1, //8
		//		0.52f, -0.32f,0,1,
		//	   -0.52f, -0.36f,0,1, //9
		//		0.52f, -0.36f,0,1,
		//	   -0.52f, -0.40f,0,1, //10
		//		0.52f, -0.40f,0,1,
		//	   -0.52f, -0.44f,0,1, //11
		//		0.52f, -0.44f,0,1,
		//	   -0.52f, -0.48f,0,1, //12
		//		0.52f, -0.48f,0,1,
		//		-.52f,  -.52f,0,1, //13
		//		 .52f, -.52f,0,1,

		//	   -0.52f, 0,0,1, //14
		//		0.52f, 0,0,1,

		//		//top
		//	   -0.52f, 0.04f,0,1, //15
		//		0.52f, 0.04f,0,1,
		//	   -0.52f, 0.08f,0,1, //16
		//		0.52f, 0.08f,0,1,
		//	   -0.52f, 0.12f,0,1, //17
		//		0.52f, 0.12f,0,1,
		//	   -0.52f, 0.16f,0,1, //18
		//		0.52f, 0.16f,0,1,
		//	   -0.52f, 0.2f, 0,1,//19
		//		0.52f, 0.2f, 0,1,
		//	   -0.52f, 0.24f,0,1, //20
		//		0.52f, 0.24f,0,1,
		//	   -0.52f, 0.28f,0,1, //21
		//		0.52f, 0.28f,0,1,
		//	   -0.52f, 0.32f,0,1, //22
		//		0.52f, 0.32f,0,1,
		//	   -0.52f, 0.36f,0,1, //23
		//		0.52f, 0.36f,0,1,
		//	   -0.52f, 0.40f,0,1, //24
		//		0.52f, 0.40f,0,1,
		//	   -0.52f, 0.44f,0,1, //25
		//		0.52f, 0.44f,0,1,
		//	   -0.52f, 0.48f,0,1, //26
		//		0.52f, 0.48f,0,1,
		//	   -0.52f, 0.52f,0,1, //27
		//		0.52f, 0.52f,0,1,

		//		//vertical
		//		//right
		//			.52f,  .52f,0,1, //1
		//			.52f, -.52f,0,1,
		//			.48f,  .52f,0,1, //2
		//			.48f, -.52f,0,1,
		//			.44f,  .52f,0,1, //3
		//			.44f, -.52f,0,1,
		//			 .4f,  .52f,0,1, //4
		//			 .4f, -.52f,0,1,
		//			.36f,  .52f,0,1, //5
		//			.36f, -.52f,0,1,
		//			.32f,  .52f,0,1, //6
		//			.32f, -.52f,0,1,
		//			.28f,  .52f,0,1, //7
		//			.28f, -.52f,0,1,
		//			.24f,  .52f,0,1, //8
		//			.24f, -.52f,0,1,
		//			 .2f,  .52f,0,1, //9
		//			 .2f, -.52f,0,1,
		//			.16f,  .52f,0,1, //10
		//			.16f, -.52f,0,1,
		//			.12f,  .52f,0,1, //11
		//			.12f, -.52f,0,1,
		//			.08f,  .52f,0,1, //12
		//			.08f, -.52f,0,1,
		//			.04f,  .52f,0,1, //13
		//			.04f, -.52f,0,1,

		//			 .0f,  .52f,0,1, //14
		//			 .0f, -.52f,0,1,

		//			 //left
		//			-.52f,  .52f,0,1, //15
		//			-.52f, -.52f,0,1,
		//			-.48f,  .52f,0,1, //16
		//			-.48f, -.52f,0,1,
		//			-.44f,  .52f,0,1, //17
		//			-.44f, -.52f,0,1,
		//			-.4f,	.52f,0,1, //18
		//			-.4f,  -.52f,0,1,
		//			-.36f,  .52f,0,1, //19
		//			-.36f, -.52f,0,1,
		//			-.32f,  .52f,0,1, //20
		//			-.32f, -.52f,0,1,
		//			-.28f,  .52f,0,1, //21
		//			-.28f, -.52f,0,1,
		//			-.24f,  .52f,0,1, //22
		//			-.24f, -.52f,0,1,
		//			-.2f,	.52f,0,1, //23
		//			-.2f,  -.52f,0,1,
		//			-.16f,  .52f,0,1, //24
		//			-.16f, -.52f,0,1,
		//			-.12f,  .52f,0,1, //25
		//			-.12f, -.52f,0,1,
		//			-.08f,  .52f,0,1, //26
		//			-.08f, -.52f,0,1,
		//			-.04f,  .52f,0,1, //27
		//			-.04f, -.52f,0,1,
		//};
#pragma endregion

		// TODO: Part 1d
		//Create Vertex Buffer
		creator->CreateCommittedResource( // using UPLOAD heap for simplicity
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // DEFAULT recommend  
			D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(VERTEX) * loading.vertices.size()),  // sizeof(VERTEX) * loading.vertices.size()
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(loading.LevelVertexData.GetAddressOf()));
		// Transfer triangle data to the vertex buffer.
		UINT8* transferMemoryLocation;
		loading.LevelVertexData->Map(0, &CD3DX12_RANGE(0, 0),
			reinterpret_cast<void**>(&transferMemoryLocation));
		memcpy(transferMemoryLocation, loading.vertices.data(), sizeof(VERTEX) * loading.vertices.size());
		loading.LevelVertexData->Unmap(0, nullptr);
		// TODO: Part 1c
		// Create a vertex View to send to a Draw() call.
		vertexView.BufferLocation = loading.LevelVertexData->GetGPUVirtualAddress();
		vertexView.StrideInBytes = sizeof(VERTEX);
		vertexView.SizeInBytes = sizeof(VERTEX) * loading.vertices.size();

		//Create Index Buffer
		creator->CreateCommittedResource( // using UPLOAD heap for simplicity
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // DEFAULT recommend  
			D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(unsigned) * loading.indices.size()),
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(loading.LevelIndexData.GetAddressOf()));
		// Transfer triangle data to the vertex buffer.
		UINT8* transferMemoryLocation2;
		loading.LevelIndexData->Map(0, &CD3DX12_RANGE(0, 0),
			reinterpret_cast<void**>(&transferMemoryLocation2));
		memcpy(transferMemoryLocation2, loading.indices.data(), sizeof(unsigned) * loading.indices.size());
		loading.LevelIndexData->Unmap(0, nullptr);
		// Create a vertex View to send to a Draw() call.
		indexView.BufferLocation = loading.LevelIndexData->GetGPUVirtualAddress();
		indexView.Format = DXGI_FORMAT_R32_UINT; // TODO: Part 1e
		indexView.SizeInBytes = sizeof(unsigned) * loading.indices.size();

#if 1 //Problem Causer
		d3d.GetSwapchain4((void**)swapper.GetAddressOf());
		swapper->GetDesc(&swapDesc); //root of the problem
		unsigned int sceneSize = sizeof(Scene_Data);
		unsigned int meshSize = sizeof(Mesh_Data);
		unsigned int constantData = (sceneSize + meshSize + meshSize) * swapDesc.BufferCount;

		creator->CreateCommittedResource( // using UPLOAD heap for simplicity
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // DEFAULT recommend  
			D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(constantData),
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(loading.MatriciesCBuffer.GetAddressOf()));

		UINT8* transferMemoryLocation3;
		loading.MatriciesCBuffer->Map(0, &CD3DX12_RANGE(0, 0),
			reinterpret_cast<void**>(&transferMemoryLocation3));
		memcpy(transferMemoryLocation3, &scene, sizeof(Scene_Data));
		memcpy(transferMemoryLocation3 + sizeof(Scene_Data), &mesh[0], sizeof(Mesh_Data));
		memcpy(transferMemoryLocation3 + sizeof(Scene_Data) + sizeof(Mesh_Data), &mesh[1], sizeof(Mesh_Data));

		//memcpy(transferMemoryLocation3 + sizeof(Scene_Data) + (swapDesc.BufferCount * sizeof(Mesh_Data)), &scene, sizeof(Scene_Data));*/
		loading.MatriciesCBuffer->Unmap(0, nullptr);

		// TODO: Part 2e
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		heapDesc.NodeMask = 0;
		heapDesc.NumDescriptors = 1;
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		HRESULT hResult = creator->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descHeap));

		// TODO: Part 2f
		constBufferDesc.BufferLocation = loading.MatriciesCBuffer->GetGPUVirtualAddress();
		constBufferDesc.SizeInBytes = constantData;
		descHandle = descHeap->GetCPUDescriptorHandleForHeapStart(); //affected
		creator->CreateConstantBufferView(&constBufferDesc, descHandle);
#endif // 0


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
		// TODO: Part 1c
		// Create Input Layout
		D3D12_INPUT_ELEMENT_DESC format[] = {
			{
				"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
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
		// TODO: Part 2c
		// create root parameter
		CD3DX12_ROOT_PARAMETER rootParameter[2];
		//rootParameter[0].InitAsConstants(32, 0, 0, D3D12_SHADER_VISIBILITY_ALL);
		rootParameter[0].InitAsConstantBufferView(0, 0);
		rootParameter[1].InitAsConstantBufferView(1, 0);
		// create root signature
		CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init(ARRAYSIZE(rootParameter), rootParameter, 0, nullptr,
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
		psDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // TODO: Part 1b
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


		// grab the context & render target
		ID3D12GraphicsCommandList* cmd;
		D3D12_CPU_DESCRIPTOR_HANDLE rtv;
		D3D12_CPU_DESCRIPTOR_HANDLE dsv;
		d3d.GetCommandList((void**)&cmd);
		d3d.GetCurrentRenderTargetView((void**)&rtv);
		d3d.GetDepthStencilView((void**)&dsv);
		// setup the pipeline
		cmd->SetGraphicsRootSignature(rootSignature.Get());
		cmd->OMSetRenderTargets(1, &rtv, FALSE, &dsv);
		cmd->SetPipelineState(pipeline.Get());
		// TODO: Part 3a

		// TODO: Part 2b
		// TODO: Part 2d
		// now we can draw
		cmd->IASetVertexBuffers(0, 1, &vertexView);
		cmd->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		cmd->IASetIndexBuffer(&indexView);



		UINT8* transferMovementLocation;
		loading.MatriciesCBuffer->Map(0, &CD3DX12_RANGE(0, 0),
			reinterpret_cast<void**>(&transferMovementLocation));

		memcpy(transferMovementLocation, &scene, sizeof(Scene_Data));

		loading.MatriciesCBuffer->Unmap(0, nullptr);

		// TODO: Part 1b
		for (int i = 0; i < 2; i++)
		{


			cmd->SetGraphicsRootConstantBufferView(0, loading.MatriciesCBuffer->GetGPUVirtualAddress());
			
				cmd->SetGraphicsRootConstantBufferView(1, loading.MatriciesCBuffer->GetGPUVirtualAddress() + sizeof(Scene_Data));

			
			
				cmd->SetGraphicsRootConstantBufferView(1, loading.MatriciesCBuffer->GetGPUVirtualAddress() + sizeof(Scene_Data) + sizeof(Mesh_Data));

			
			cmd->DrawIndexedInstanced(loading.batches[i].indexCount, 1, loading.batches[i].indexOffset, 0, 0);
		}
		// TODO: Part 3d
		// release temp handles
		cmd->Release();
	}
	// TODO: Part 4b
	void UpdateCamera()
	{
		auto now = std::chrono::steady_clock::now();
		float delta_time = std::chrono::duration_cast<std::chrono::microseconds>(now - last_update).count() / 100000.0f;
		last_update = now;
		// TODO: Part 4c
		GMATRIXF camera = GIdentityMatrixF;
		math.InverseF(scene.view, camera);

		GW::GReturn result;
		float up = 0, down = 0, cntrlUp = 0, cntrlDown = 0;
		input.GetState(G_KEY_SPACE, up);
		input.GetState(G_KEY_LEFTSHIFT, down);
		input.GetState(G_RIGHT_TRIGGER_AXIS, cntrlUp);
		input.GetState(G_LEFT_TRIGGER_AXIS, cntrlDown);
		// TODO: Part 4d
		const float Camera_Speed = .3f;
		float PerFrameSpeed = Camera_Speed * delta_time;
		float Total_Y_Change = up - down + cntrlUp - cntrlDown;
		camera.row4.y += Total_Y_Change * PerFrameSpeed;

		// TODO: Part 4e
		float forward = 0, backward = 0, right = 0, left = 0;
		input.GetState(G_KEY_W, forward);
		input.GetState(G_KEY_S, backward);
		input.GetState(G_KEY_D, right);
		input.GetState(G_KEY_A, left);
		if (forward != 0)
		{
			int debug = 0;
		}
		float Total_Z_Change = forward - backward;
		float Total_X_Change = right - left;
		GMATRIXF translationM = GIdentityMatrixF;
		GVECTORF t = { Total_X_Change * PerFrameSpeed, 0, Total_Z_Change * PerFrameSpeed };
		math.TranslateLocalF(translationM, t, translationM);
		math.MultiplyMatrixF(translationM, camera, camera);

		/*if (G_PASS(result) && yValue != 0)
		{
			int d = 0;
		}*/

		// TODO: Part 4f
		float screenHeight = 800;
		float screenWidth = 600;
		float Thumb_Speed = G_PI * delta_time * 10;
		float mousey = 0;
		float mousex = 0;
		float fov = G2D_DEGREE_TO_RADIAN_F(65);

		result = input.GetMouseDelta(mousex, mousey);
		if (G_PASS(result) && result != GW::GReturn::REDUNDANT)
		{
			float Total_Pitch = fov * (mousey / screenHeight);
			GMATRIXF pitchMatrix = GIdentityMatrixF;
			math.RotateXLocalF(pitchMatrix, Total_Pitch, pitchMatrix);
			math.MultiplyMatrixF(pitchMatrix, camera, camera);
		}
		// TODO: Part 4g
		if (G_PASS(result) && result != GW::GReturn::REDUNDANT)
		{

			float Total_Yaw = fov * aspRatio * (mousex / screenWidth);
			GMATRIXF YawMatrix = GIdentityMatrixF;
			math.RotateYLocalF(YawMatrix, Total_Yaw, YawMatrix);
			GVECTORF temp = camera.row4;
			math.MultiplyMatrixF(camera, YawMatrix, camera);
			camera.row4 = temp;
		}
		// TODO: Part 4c
		math.InverseF(camera, scene.view);
	}
	~Renderer()
	{
		// ComPtr will auto release so nothing to do here 
	}
};
