#include <Windows.h>
#include <iostream>
#include "dev_app.h"
#include "debug_renderer.h"
#include <DirectXMath.h>
#include "view.h"



//TODO include debug_renderer.h and anything else you might need here


namespace end
{
	using namespace DirectX;
	double delta_time = 0.0;

	bool rTurn = true, gTurn, bTurn;
	float4x4 Obj; //movement matrix
	float4x4 objLocal;

	float4x4 looker; // look-at matrix
	float4x4 turner; // turn-to matrix

	float3 rgb{ 0,0,1 };
	CamPos dev_app_t::mouseMove;

	float3 minPos;
	float3 maxPos;

	#define on1
//#define on2

	void Identity(float4x4& matrix)
	{
		for (int i = 0; i < 4; i++)
		{

			matrix.data()[i][i] = 1;
			matrix.data()[i].w = 1;
		}
	}
	void Identity(DirectX::XMMATRIX& matrix)
	{
		matrix = DirectX::XMMatrixIdentity();
	}

	double dev_app_t::get_delta_time()const
	{
		return delta_time;
	}
	float3 RandomVector(float min, float max, float3 vector)
	{
		vector.x = RAND_FLOAT(min, max);
		vector.y = RAND_FLOAT(min, max);
		vector.z = RAND_FLOAT(min, max);
		return vector;
	}

	dev_app_t::dev_app_t()
	{
		std::cout << "Log whatever you need here.\n"; // Don’t forget to include <iostream>

		Identity(Obj);
		Identity(looker);
		Identity(turner);


		minPos = RandomVector(1, 5, minPos);
		maxPos = RandomVector(1, 5, maxPos);
	}

	double calc_delta_time()
	{
		static std::chrono::time_point<std::chrono::high_resolution_clock> last_time = std::chrono::high_resolution_clock::now();

		std::chrono::time_point<std::chrono::high_resolution_clock> new_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_seconds = new_time - last_time;
		last_time = new_time;

		return min(1.0 / 15.0, elapsed_seconds.count());
	}

	float RandomFloat(int min, int max)
	{
		return RAND_FLOAT(min, max);
	}
	float Radians(float degree)
	{
		float pi = 3.14159;
		return degree * (pi / 180);
	}


	void GridDraw(float value1, float value2, float4 gradient, float gradientOffset, int drawCount = 5);
	void FreeDraw(pool_t< Particle, 4096>& free_pool, Emitter& emitter, float xyz[5]);
	void SortedDraw(sorted_pool_t<Particle, 512>& sorted_pool);
	float4x4 OrthoNorm(float4x4 matrix, float3 proxy);
	void MouseLook();
	void LargestToSmallest(float3& minSort, float3& maxSort);
	void AllDraw(sorted_pool_t<Particle, 512>& Spool, DrawPos& ParticlePos, pool_t<Particle, 4096>& Fpool, Emitter drawEmitter[4]);

	void dev_app_t::update(renderer_t* renderer)
	{
		delta_time = calc_delta_time();

		//This drawn the green checkmark

#pragma region MemoryManagement
#ifdef on1 



		int drawCount = 5;
		float vertMove1 = 0;
		float vertMove2 = 0;
		float4 gradient = { 0,0,0,1 };
		float gradientOffset = 1;



		GridDraw(vertMove1, vertMove2, gradient, gradientOffset, drawCount);

		//TODO do your Updates here

		AllDraw(Spool, ParticlePos, Fpool, drawEmitter);


#endif
#pragma endregion

#pragma region MatrixBehaviors
#ifdef on2


		float value1 = 0;
		float value2 = 0;
		float4 gradient = { 0,0,0,1 };
		float gradientOffset = .7f;
		GridDraw(value1, value2, gradient, gradientOffset);



		float moveSpeed = 5;
		float speedMult = 2;
		float rotSpeed = 0.008f;
		float4x4 temp;
		if (GetAsyncKeyState('W'))
		{
			DirectX::XMMATRIX tra = DirectX::XMMatrixTranslation(0.0f, 0.0f, moveSpeed * delta_time);
			Obj = (end::float4x4&)DirectX::XMMatrixMultiply(tra, (DirectX::XMMATRIX&)Obj);
		}
		if (GetAsyncKeyState('A'))
		{
			DirectX::XMMATRIX yrot = DirectX::XMMatrixRotationY(-rotSpeed);
			Obj = (end::float4x4&)DirectX::XMMatrixMultiply(yrot, (DirectX::XMMATRIX&)Obj);
		}
		if (GetAsyncKeyState('S'))
		{
			DirectX::XMMATRIX tra = DirectX::XMMatrixTranslation(0.0f, 0.0f, -moveSpeed * delta_time);
			Obj = (end::float4x4&)DirectX::XMMatrixMultiply(tra, (DirectX::XMMATRIX&)Obj);
		}
		if (GetAsyncKeyState('D'))
		{
			DirectX::XMMATRIX yrot = DirectX::XMMatrixRotationY(rotSpeed);
			Obj = (end::float4x4&)DirectX::XMMatrixMultiply(yrot, (DirectX::XMMATRIX&)Obj);
		}

		//Camera Movement
		float3 prox;
		float4x4 cam = (float4x4&)renderer->default_view.view_mat;
		if (GetAsyncKeyState(VK_UP))
		{
			DirectX::XMMATRIX fwd = DirectX::XMMatrixTranslation(0.0f, 0.0f, moveSpeed * delta_time * speedMult);
			cam = (end::float4x4&)DirectX::XMMatrixMultiply(fwd, (DirectX::XMMATRIX&)cam);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			DirectX::XMMATRIX lft = DirectX::XMMatrixTranslation(-moveSpeed * delta_time * speedMult, 0.0f, 0);
			cam = (end::float4x4&)DirectX::XMMatrixMultiply(lft, (DirectX::XMMATRIX&)cam);
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			DirectX::XMMATRIX bck = DirectX::XMMatrixTranslation(0.0f, 0.0f, -moveSpeed * delta_time * speedMult);
			cam = (end::float4x4&)DirectX::XMMatrixMultiply(bck, (DirectX::XMMATRIX&)cam);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			DirectX::XMMATRIX rht = DirectX::XMMatrixTranslation(moveSpeed * delta_time * speedMult, 0.0f, 0);
			cam = (end::float4x4&)DirectX::XMMatrixMultiply(rht, (DirectX::XMMATRIX&)cam);
		}
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			float mSpeed = .005f;
			float xDelta = mouseMove.xPos - mouseMove.xPrev;
			float yDelta = mouseMove.yPos - mouseMove.yPrev;

			XMMATRIX Yrot = XMMatrixRotationY(mSpeed * yDelta);
			XMMATRIX Xrot = XMMatrixRotationX(mSpeed * xDelta);

			cam = (float4x4&)XMMatrixMultiply(Xrot, (XMMATRIX&)cam);

			float4 prevCam;
			prevCam.xyz = cam[3].xyz;
			prevCam.w = cam[3].w;

			cam[3] = float4(0, 0, 0, 1);

			cam = (float4x4&)XMMatrixMultiply((XMMATRIX&)cam, Yrot);
			cam[3] = prevCam;
			(float4x4&)renderer->default_view.view_mat = cam;
			cam = OrthoNorm(cam, prox);
		}

		mouseMove.xPrev = mouseMove.xPos;
		mouseMove.yPrev = mouseMove.yPos;



		float3 proxy;
		float3 start = Obj[3].xyz;
		float3 xEnd = start + proxy.normalize(Obj[0].xyz);
		float3 yEnd = start + proxy.normalize(Obj[1].xyz);
		float3 zEnd = start + proxy.normalize(Obj[2].xyz);
		end::debug_renderer::add_line(start, xEnd, float4(1, 0, 0, 1)); //x-axis
		end::debug_renderer::add_line(start, yEnd, float4(0, 1, 0, 1)); //y-axis
		end::debug_renderer::add_line(start, zEnd, float4(0, 0, 1, 1)); //z-axis

		//look-at
		looker[3].xyz = { -10,3,0 };
		start = looker[3].xyz;
		float4x4 yrot;
		float3 up = float3(0, 1, 0);
		float3 z = proxy.normalize(Obj[3].xyz - start);
		float3 x = proxy.normalize(proxy.cross(up, z));
		float3 y = proxy.normalize(proxy.cross(z, x));
		looker[0].xyz = x;
		looker[1].xyz = y;
		looker[2].xyz = z;


		xEnd = start + proxy.normalize(looker[0].xyz);
		yEnd = start + proxy.normalize(looker[1].xyz);
		zEnd = start + proxy.normalize(looker[2].xyz);
		end::debug_renderer::add_line(start, xEnd, float4(1, 0, 0, 1)); //x-axis
		end::debug_renderer::add_line(start, yEnd, float4(0, 1, 0, 1)); //y-axis
		end::debug_renderer::add_line(start, zEnd, float4(0, 0, 1, 1)); //z-axis

		//turn-to
		float turnSpeed = .005;
		XMMATRIX turnRot;
		turner[3].xyz = { 10,3,0 };
		start = turner[3].xyz;
		float xSpeed = 20;
		float ySpeed = 20;

		float3 zTurn = proxy.normalize(Obj[3].xyz - start);

		float yDot = proxy.dot(zTurn, turner[0].xyz);
		XMMATRIX yRot = XMMatrixRotationY(yDot * delta_time);
		turner = (float4x4&)XMMatrixMultiply(yRot, (DirectX::XMMATRIX&)turner);

		float xDot = proxy.dot(zTurn, turner[1].xyz);
		XMMATRIX xRot = XMMatrixRotationX(xDot * -delta_time);
		turner = (float4x4&)XMMatrixMultiply(xRot, (DirectX::XMMATRIX&)turner);
		
		turner = OrthoNorm(turner, proxy);

		xEnd = start + proxy.normalize(turner[0].xyz);
		yEnd = start + proxy.normalize(turner[1].xyz);
		zEnd = start + proxy.normalize(turner[2].xyz);
		end::debug_renderer::add_line(start, xEnd, float4(1, 0, 0, 1)); //x-axis
		end::debug_renderer::add_line(start, yEnd, float4(0, 1, 0, 1)); //y-axis
		end::debug_renderer::add_line(start, zEnd, float4(0, 0, 1, 1)); //z-axis


#endif // on2
#pragma endregion

#pragma region Frustrum Culling
#if 0


		LargestToSmallest(minPos, maxPos);

		end::debug_renderer::AABBDraw(minPos, maxPos);

#endif 
#pragma endregion

	}
#pragma region Matrix Behavior Functions


	float4x4 OrthoNorm(float4x4 matrix, float3 proxy)
	{
		float3 up = float3(0, 1, 0);
		float3 z = proxy.normalize(matrix[2].xyz);
		float3 x = proxy.normalize(proxy.cross(up, z));
		float3 y = proxy.normalize(proxy.cross(z, x));

		matrix[0].xyz = x;
		matrix[1].xyz = y;
		matrix[2].xyz = z;
		

		return matrix;

	}

#pragma endregion

#pragma region Particle Functions
	float4 Cycle(float3& rgb)
	{
		if (rTurn)
		{
			if (rgb.x <= 1)
			{
				rgb.x += .1f * delta_time;
				rgb.z -= .1f * delta_time;
			}
			else
			{
				rTurn = false;
				gTurn = true;

			}
		}
		else if (gTurn)
		{
			if (rgb.y <= 1)
			{
				rgb.y += .1f * delta_time;
				rgb.x -= .1f * delta_time;
			}
			else
			{
				gTurn = false;
				bTurn = true;
			}
		}
		else if (bTurn)
		{
			if (rgb.z <= 1)
			{
				rgb.z += .1f * delta_time;
				rgb.y -= .1f * delta_time;
			}
			else
			{
				bTurn = false;
				rTurn = true;
			}
		}

		return float4(rgb.x, rgb.y, rgb.z, 1);
	}

	//Sorted pool particle set up helper
	void SortedPoolParticles(sorted_pool_t<Particle, 512>& sorted_pool)
	{
		int16_t index = sorted_pool.alloc();
		if (index != -1 && index < sorted_pool.capacity())
		{
			Particle sortedP;

			sortedP.pos = { 0,1,0 };
			sortedP.velocity = { RandomFloat(-1, 1), RandomFloat(3, 10), RandomFloat(-1, 1) };
			sortedP.color = { RandomFloat(0,1), RandomFloat(0,1), RandomFloat(0,1),1 };
			sorted_pool[index] = sortedP;
		}
	};

	void SortedDraw(sorted_pool_t<Particle, 512>& sorted_pool)
	{
		SortedPoolParticles(sorted_pool);

		for (int i = 0; i < sorted_pool.size(); i++)
		{
			if (sorted_pool[i].pos.y < 0)
			{
				sorted_pool.free(i);
				--i;
			}
			else
			{
				float3 gravity = { 0,-9.8f,0 };

				Particle& Particle = sorted_pool[i];
				Particle.prev_pos = Particle.pos;
				Particle.pos += (Particle.velocity * delta_time);
				Particle.velocity += (gravity * delta_time);
			}
		}
		for (int i = 0; i < sorted_pool.size(); i++)
		{
			end::debug_renderer::add_line(sorted_pool[i].pos, sorted_pool[i].prev_pos, sorted_pool[i].color);
		}
	}


	//Free pool particle set up helper
	void FreePoolParticles(pool_t< Particle, 4096>& free_pool, Emitter& emit, float xyz[3])
	{
		int Findex = free_pool.alloc();
		if (Findex != -1)
		{
			int Sindex = emit.indicies.alloc();
			if (Sindex != -1)
			{
				Particle FreeParticle;
				FreeParticle.pos = { xyz[0],xyz[1],xyz[2] };
				FreeParticle.prev_pos = FreeParticle.pos;
				FreeParticle.velocity = { RandomFloat(-1, 1), RandomFloat(3, 10), RandomFloat(-1, 1) };
				FreeParticle.color = { RandomFloat(0,1), RandomFloat(0,1), RandomFloat(0,1),1 };
				float3 col = float3(FreeParticle.color.x, FreeParticle.color.y, FreeParticle.color.z);
				Cycle(col);

				FreeParticle.color = { col.x,col.y, col.z,1 };

				free_pool[Findex] = FreeParticle;
				emit.indicies[Sindex] = Findex;
			}
			else
			{
				free_pool.free(Findex);
			}
		}
	}

	//draws Particles for Free Pool
	void FreeDraw(pool_t< Particle, 4096>& free_pool, Emitter& emitter, float xyz[3])
	{
		FreePoolParticles(free_pool, emitter, xyz);
		for (int i = 0; i < emitter.indicies.size(); i++)
		{
			Particle& RefParticle = free_pool[emitter.indicies[i]];
			if (RefParticle.pos.y < 0)
			{
				free_pool.free(emitter.indicies[i]);
				emitter.indicies.free(i);
				--i;
			}
			else
			{
				float3 gravity = { 0,-9.8f,0 };

				RefParticle.prev_pos = RefParticle.pos;
				RefParticle.pos += (RefParticle.velocity * delta_time);
				RefParticle.velocity += (gravity * delta_time);
			}
		}
		for (int i = 0; i < emitter.indicies.size(); i++)
		{
			Particle& RefParticle2 = free_pool[emitter.indicies[i]];
			end::debug_renderer::add_line(RefParticle2.pos, RefParticle2.prev_pos, RefParticle2.color);
		}
	}

	void AllDraw(sorted_pool_t<Particle, 512>& Spool, DrawPos& ParticlePos, pool_t<Particle, 4096>& Fpool, Emitter drawEmitter[4])
	{
		SortedDraw(Spool);

		ParticlePos.draw_xyz[0] = 9;
		ParticlePos.draw_xyz[1] = 1;
		ParticlePos.draw_xyz[2] = 9;

		FreeDraw(Fpool, drawEmitter[0], ParticlePos.draw_xyz);//1


		ParticlePos.draw_xyz[0] = 9;
		ParticlePos.draw_xyz[1] = 1;
		ParticlePos.draw_xyz[2] = -9;


		FreeDraw(Fpool, drawEmitter[1], ParticlePos.draw_xyz);//2


		ParticlePos.draw_xyz[0] = -9;
		ParticlePos.draw_xyz[1] = 1;
		ParticlePos.draw_xyz[2] = 9;

		FreeDraw(Fpool, drawEmitter[2], ParticlePos.draw_xyz);//3

		ParticlePos.draw_xyz[0] = -9;
		ParticlePos.draw_xyz[1] = 1;
		ParticlePos.draw_xyz[2] = -9;

		FreeDraw(Fpool, drawEmitter[3], ParticlePos.draw_xyz);//4
	}
#pragma endregion

	void LargestToSmallest(float3& minSort, float3& maxSort)
	{
		float temp = 0;
		if (minSort.x > maxSort.x)
		{
			temp = maxSort.x;
			maxSort.x = minSort.x;
			minSort.x = temp;
		}
		if (minSort.y > maxSort.y)
		{
			temp = maxSort.y;
			maxSort.y = minSort.y;
			minSort.y = temp;
		}
		if (minSort.x > maxSort.x)
		{
			temp = maxSort.z;
			maxSort.z = minSort.z;
			minSort.z = temp;
		}

	}


	void GridDraw(float zySet, float zxSet, float4 gradient, float gradientOffset, int drawCount)
	{
		float time = 0;
		time += delta_time;

		if (time > 0.3f)
		{
			time = 0;
		}

		Cycle(rgb);

		float4 gradient2 = { rgb.y,rgb.x,rgb.z,1 };

		gradient = { rgb.x,rgb.y,rgb.z,1 };

		for (int i = 0; i < drawCount; i++)
		{


			end::debug_renderer::add_line(float3(10, 0, zySet += .5), float3(-10, 0, zySet += .5), gradient, gradient2);
			end::debug_renderer::add_line(float3(zySet, 0, 10), float3(zySet, 0, -10), gradient, gradient2);


			end::debug_renderer::add_line(float3(10, 0, zySet += .5), float3(-10, 0, zySet += .5), gradient, gradient2);
			end::debug_renderer::add_line(float3(zySet, 0, 10), float3(zySet, 0, -10), gradient, gradient2);



		}
		for (int j = 0; j < drawCount; j++)
		{

			end::debug_renderer::add_line(float3(10, 0, zxSet -= .5), float3(-10, 0, zxSet -= .5), gradient, gradient2);
			end::debug_renderer::add_line(float3(zxSet, 0, 10), float3(zxSet, 0, -10), gradient, gradient2);

			end::debug_renderer::add_line(float3(10, 0, zxSet -= .5), float3(-10, 0, zxSet -= .5), gradient, gradient2);
			end::debug_renderer::add_line(float3(zxSet, 0, 10), float3(zxSet, 0, -10), gradient, gradient2);


		}

		end::debug_renderer::add_line(float3(10, 0, 0), float3(-10, 0, 0), gradient);
		end::debug_renderer::add_line(float3(0, 0, 10), float3(0, 0, -10), gradient);

		end::debug_renderer::add_line(float3(10, 0, 0), float3(-10, 0, 0), gradient);
		end::debug_renderer::add_line(float3(0, 0, 10), float3(0, 0, -10), gradient);

	}
}
