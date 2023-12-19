#pragma once
#include <cstdint>
#include <chrono>
#include "../../pools.h"
#include "math_types.h"
#include "renderer.h"


namespace end
{
#define RAND_FLOAT(min, max) ((float(rand()) / RAND_MAX) * (max - min) + min)

	struct Particle
	{
		float3 pos;
		float3 prev_pos;
		float4 color;
		float3 velocity;
	};
	struct Emitter
	{
		float3 pos;
		float4 color;
		sorted_pool_t<int, 1024> indicies;
	};

	//used for FreeDraw func
	struct DrawPos
	{

		
		float x, y, z;
		
		union
		{

			float draw_xyz[3];
		};

	};
	struct CamPos
	{
		//x position saves
		float xPos;
		float xPrev;

		//y position saves
		float yPos;
		float yPrev;
	};

	// Simple app class for development and testing purposes
	struct dev_app_t
	{
		sorted_pool_t<Particle, 512> Spool;
		pool_t<Particle, 4096> Fpool;
		Emitter drawEmitter[4];
		DrawPos ParticlePos;
		static CamPos mouseMove;
		renderer_t* renderer;

		void update(renderer_t* renderer);

		dev_app_t();

		double get_delta_time()const;
	};
}