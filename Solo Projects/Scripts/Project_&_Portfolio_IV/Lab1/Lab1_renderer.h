// minimalistic code to draw a single triangle, this is not part of the API.
// required for compiling shaders on the fly, consider pre-compiling instead
#include <d3dcompiler.h>
#include <chrono>
#pragma comment(lib, "d3dcompiler.lib")
#include "d3dx12.h" // official helper file provided by microsoft
// Simple Vertex Shader
const char* vertexShaderSource = R"(
// an ultra simple hlsl vertex shader
// TODO: Part 2b
cbuffer Shader_Vars
{
		float4x4 World;
		float4x4 ProjView;
};
	// TODO: Part 2f
	// TODO: Part 3b
// TODO: Part 1c
float4 main(float3 inputVertex : POSITION) : SV_POSITION
{
	// TODO: Part 2d, Part 2f, Part 3b
	float4 pos = float4(inputVertex,1);
	pos = mul(World, pos);
	pos = mul(ProjView, pos);
	return pos;
}
)";
// Simple Pixel Shader
const char* pixelShaderSource = R"(
// an ultra simple hlsl pixel shader
float4 main() : SV_TARGET 
{	
	return float4(0.3f,0.25f,0.15f,0); // TODO: Part 1a
}
)";
// Creation, Rendering & Cleanup
using namespace GW::MATH;
class Renderer
{
	// proxy handles
	GW::SYSTEM::GWindow win;
	GW::GRAPHICS::GDirectX12Surface d3d;
	// TODO: Part 4a
	GW::INPUT::GInput input;
	GW::INPUT::GController control;
	std::chrono::steady_clock::time_point last_update;
	// TODO: Part 2a
	GMATRIXF world[6];
	GMatrix math;
	// TODO: Part 3c
	// TODO: Part 2e
	GMATRIXF view = GIdentityMatrixF;

	// TODO: Part 3a
	GMATRIXF PerspectiveProj = GIdentityMatrixF;
	GMATRIXF projView = GIdentityMatrixF;
	float aspRatio;
	// what we need at a minimum to draw a triangle
	D3D12_VERTEX_BUFFER_VIEW					vertexView;
	Microsoft::WRL::ComPtr<ID3D12Resource>		vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D12RootSignature>	rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState>	pipeline;
public:
	// TODO: Part 1c
	// TODO: Part 2b
	struct Shader_Vars
	{
		GMATRIXF World;
		GMATRIXF ProjView;
	};
	// TODO: Part 2f
	// TODO: Part 3b

	Renderer(GW::SYSTEM::GWindow _win, GW::GRAPHICS::GDirectX12Surface _d3d)
	{
		win = _win;
		d3d = _d3d;
		ID3D12Device* creator;
		d3d.GetDevice((void**)&creator);
		// TODO: Part 4a
		input.Create(win);
		control.Create();
		// TODO: Part 2a
		
		GVECTORF translation[6] = {
			{0,-.52f,0,1}, //1
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
		math.RotateXLocalF(world[0], rotation, world[0]);
		math.TranslateGlobalF(world[0], translation[0], world[0]);

		math.RotateXLocalF(world[1], rotation, world[1]);
		math.TranslateGlobalF(world[1], translation[1], world[1]);
		
		math.RotateYLocalF(world[2], rotation, world[2]);
		math.TranslateGlobalF(world[2], translation[2], world[2]);
		
		math.RotateYLocalF(world[3], rotation, world[3]);
		math.TranslateGlobalF(world[3], translation[3], world[3]);
		
		math.RotateZLocalF(world[4], rotation, world[4]);
		math.TranslateGlobalF(world[4], translation[4], world[4]);

		math.RotateZLocalF(world[5], rotation, world[5]);
		math.TranslateGlobalF(world[5], translation[5], world[5]);



		// TODO: Part 3c
		// TODO: Part 2e
		//math.InverseF(world[0], view);
		GVECTORF eye = { 0.25f,-0.125f,-.25f,0 };
		GVECTORF at = { 0,-.5f,0,0 };
		GVECTORF up = { 0,1,0, 0 };
		math.LookAtLHF(eye, at, up, view);

		d3d.GetAspectRatio(aspRatio);
		math.ProjectionDirectXLHF(fov, aspRatio, nPlane, fPlane, PerspectiveProj);
		math.MultiplyMatrixF(view, PerspectiveProj, projView);

		// TODO: Part 1b
		// TODO: Part 1c
		// Create Vertex Buffer
		float verts[] = {
			   -0.52f, -0.04f,0,1, //1
				0.52f, -0.04f,0,1,
			   -0.52f, -0.08f,0,1, //2
				0.52f, -0.08f,0,1,
			   -0.52f, -0.12f,0,1, //3
				0.52f, -0.12f,0,1,
			   -0.52f, -0.16f,0,1, //4
				0.52f, -0.16f,0,1,
			   -0.52f, -0.2f, 0,1,//5
				0.52f, -0.2f, 0,1,
			   -0.52f, -0.24f,0,1, //6
				0.52f, -0.24f,0,1,
			   -0.52f, -0.28f,0,1, //7
				0.52f, -0.28f,0,1,
			   -0.52f, -0.32f,0,1, //8
				0.52f, -0.32f,0,1,
			   -0.52f, -0.36f,0,1, //9
				0.52f, -0.36f,0,1,
			   -0.52f, -0.40f,0,1, //10
				0.52f, -0.40f,0,1,
			   -0.52f, -0.44f,0,1, //11
				0.52f, -0.44f,0,1,
			   -0.52f, -0.48f,0,1, //12
				0.52f, -0.48f,0,1,
				-.52f,  -.52f,0,1, //13
				 .52f, -.52f,0,1,

			   -0.52f, 0,0,1, //14
				0.52f, 0,0,1,

				//top
			   -0.52f, 0.04f,0,1, //15
				0.52f, 0.04f,0,1,
			   -0.52f, 0.08f,0,1, //16
				0.52f, 0.08f,0,1,
			   -0.52f, 0.12f,0,1, //17
				0.52f, 0.12f,0,1,
			   -0.52f, 0.16f,0,1, //18
				0.52f, 0.16f,0,1,
			   -0.52f, 0.2f, 0,1,//19
				0.52f, 0.2f, 0,1,
			   -0.52f, 0.24f,0,1, //20
				0.52f, 0.24f,0,1,
			   -0.52f, 0.28f,0,1, //21
				0.52f, 0.28f,0,1,
			   -0.52f, 0.32f,0,1, //22
				0.52f, 0.32f,0,1,
			   -0.52f, 0.36f,0,1, //23
				0.52f, 0.36f,0,1,
			   -0.52f, 0.40f,0,1, //24
				0.52f, 0.40f,0,1,
			   -0.52f, 0.44f,0,1, //25
				0.52f, 0.44f,0,1,
			   -0.52f, 0.48f,0,1, //26
				0.52f, 0.48f,0,1,
			   -0.52f, 0.52f,0,1, //27
				0.52f, 0.52f,0,1,

				//vertical
				//right
					.52f,  .52f,0,1, //1
					.52f, -.52f,0,1,
					.48f,  .52f,0,1, //2
					.48f, -.52f,0,1,
					.44f,  .52f,0,1, //3
					.44f, -.52f,0,1,
					 .4f,  .52f,0,1, //4
					 .4f, -.52f,0,1,
					.36f,  .52f,0,1, //5
					.36f, -.52f,0,1,
					.32f,  .52f,0,1, //6
					.32f, -.52f,0,1,
					.28f,  .52f,0,1, //7
					.28f, -.52f,0,1,
					.24f,  .52f,0,1, //8
					.24f, -.52f,0,1,
					 .2f,  .52f,0,1, //9
					 .2f, -.52f,0,1,
					.16f,  .52f,0,1, //10
					.16f, -.52f,0,1,
					.12f,  .52f,0,1, //11
					.12f, -.52f,0,1,
					.08f,  .52f,0,1, //12
					.08f, -.52f,0,1,
					.04f,  .52f,0,1, //13
					.04f, -.52f,0,1,

					 .0f,  .52f,0,1, //14
					 .0f, -.52f,0,1,

					 //left
					-.52f,  .52f,0,1, //15
					-.52f, -.52f,0,1,
					-.48f,  .52f,0,1, //16
					-.48f, -.52f,0,1,
					-.44f,  .52f,0,1, //17
					-.44f, -.52f,0,1,
					-.4f,	.52f,0,1, //18
					-.4f,  -.52f,0,1,
					-.36f,  .52f,0,1, //19
					-.36f, -.52f,0,1,
					-.32f,  .52f,0,1, //20
					-.32f, -.52f,0,1,
					-.28f,  .52f,0,1, //21
					-.28f, -.52f,0,1,
					-.24f,  .52f,0,1, //22
					-.24f, -.52f,0,1,
					-.2f,	.52f,0,1, //23
					-.2f,  -.52f,0,1,
					-.16f,  .52f,0,1, //24
					-.16f, -.52f,0,1,
					-.12f,  .52f,0,1, //25
					-.12f, -.52f,0,1,
					-.08f,  .52f,0,1, //26
					-.08f, -.52f,0,1,
					-.04f,  .52f,0,1, //27
					-.04f, -.52f,0,1,
		};
		// TODO: Part 1d
		creator->CreateCommittedResource( // using UPLOAD heap for simplicity
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // DEFAULT recommend  
			D3D12_HEAP_FLAG_NONE, &CD3DX12_RESOURCE_DESC::Buffer(sizeof(verts)),
			D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexBuffer));
		// Transfer triangle data to the vertex buffer.
		UINT8* transferMemoryLocation;
		vertexBuffer->Map(0, &CD3DX12_RANGE(0, 0),
			reinterpret_cast<void**>(&transferMemoryLocation));
		memcpy(transferMemoryLocation, verts, sizeof(verts));
		vertexBuffer->Unmap(0, nullptr);
		// TODO: Part 1c
		// Create a vertex View to send to a Draw() call.
		vertexView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
		vertexView.StrideInBytes = sizeof(float) * 4;
		vertexView.SizeInBytes = sizeof(verts);
		// Create Vertex Shader
		UINT compilerFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if _DEBUG
		compilerFlags |= D3DCOMPILE_DEBUG;
#endif
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob, errors;
		if (FAILED(D3DCompile(vertexShaderSource, strlen(vertexShaderSource),
			nullptr, nullptr, nullptr, "main", "vs_5_0", compilerFlags, 0,
			vsBlob.GetAddressOf(), errors.GetAddressOf())))
		{
			std::cout << (char*)errors->GetBufferPointer() << std::endl;
			abort();
		}
		// Create Pixel Shader
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob; errors.Reset();
		if (FAILED(D3DCompile(pixelShaderSource, strlen(pixelShaderSource),
			nullptr, nullptr, nullptr, "main", "ps_5_0", compilerFlags, 0,
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
			}
		};
		// TODO: Part 2c
		// create root parameter
		CD3DX12_ROOT_PARAMETER rootParameter[1];
		rootParameter[0].InitAsConstants(32, 0, 0, D3D12_SHADER_VISIBILITY_ALL);
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
		psDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE; // TODO: Part 1b
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
		cmd->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		// TODO: Part 1b
		math.MultiplyMatrixF(view, PerspectiveProj, projView);
		Shader_Vars sVar;
		for (int i = 0; i < 6; i++)
		{
			sVar.World = world[i];
			sVar.ProjView = projView;
			cmd->SetGraphicsRoot32BitConstants(0, 32, &sVar, 0);
			cmd->DrawInstanced(108, 1, 0, 0); // TODO: Part 1d
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
		math.InverseF(view, camera);

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
		input.GetState(G_KEY_W,forward);
		input.GetState(G_KEY_S,backward);
		input.GetState(G_KEY_D,right);
		input.GetState(G_KEY_A,left);
		float Total_Z_Change = forward - backward;
		float Total_X_Change = right -  left;
		GMATRIXF translationM = GIdentityMatrixF;
		GVECTORF t = {Total_X_Change * PerFrameSpeed, 0, Total_Z_Change * PerFrameSpeed};
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

		result = input.GetMouseDelta(mousex,mousey);
		if (G_PASS(result) && result != GW::GReturn::REDUNDANT)
		{
			float Total_Pitch = fov * (mousey / screenHeight) * -Thumb_Speed;
			GMATRIXF pitchMatrix = GIdentityMatrixF;
			math.RotateXLocalF(pitchMatrix, Total_Pitch, pitchMatrix);
			math.MultiplyMatrixF(pitchMatrix, camera, camera);
		}
		// TODO: Part 4g
		if (G_PASS(result) && result != GW::GReturn::REDUNDANT)
		{ 
			
			float Total_Yaw = fov * aspRatio * (mousex / screenWidth) * Thumb_Speed;
			GMATRIXF YawMatrix = GIdentityMatrixF;
			math.RotateYLocalF(YawMatrix, Total_Yaw, YawMatrix);
			math.MultiplyMatrixF(camera, YawMatrix, camera);
		}
		// TODO: Part 4c
		math.InverseF(camera, view);
	}
	~Renderer()
	{
		// ComPtr will auto release so nothing to do here 
	}
};
