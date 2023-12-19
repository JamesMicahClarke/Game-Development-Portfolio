#include "debug_renderer.h"
#include"frustum_culling.h"

// Anonymous namespace
namespace
{
	// Declarations in an anonymous namespace are global BUT only have internal linkage.
	// In other words, these variables are global but are only visible in this source file.

	// Maximum number of debug lines at one time (i.e: Capacity)
	constexpr size_t MAX_LINE_VERTS = 10196;

	// CPU-side buffer of debug-line verts
	// Copied to the GPU and reset every frame.
	size_t line_vert_count = 0;
	std::array< end::colored_vertex, MAX_LINE_VERTS> line_verts;
	std::array< end::aabb_t, MAX_LINE_VERTS> aabb;
}

namespace end
{
	namespace debug_renderer
	{
		//TODO Once you finish thisfile correctly, you should see a green checkmark when you run the game.
		void add_line(float3 point_a, float3 point_b, float4 color_a, float4 color_b)
		{
			//TODO Add points to debug_verts, increments debug_vert_count
			if (get_line_vert_count() == MAX_LINE_VERTS)
			{
				line_vert_count--;
			}
			else
			{
				line_verts[line_vert_count].pos = point_a;
				line_verts[line_vert_count].color = color_a;
				line_vert_count++;

			}
			if (get_line_vert_count() == MAX_LINE_VERTS)
			{
				line_vert_count--;
			}
			line_verts[line_vert_count].pos = point_b;
			line_verts[line_vert_count].color = color_b;
			line_vert_count++;

			
		}

		void clear_lines()
		{
			//TODO Resets debug_vert_count to 0
			line_vert_count = 0;
		}

		const colored_vertex* get_line_verts()
		{
			//TODO Returns the line vert array pointer
			colored_vertex* line_vert_ptr = line_verts.data();

			return line_vert_ptr;
		}

		size_t get_line_vert_count()
		{
			//TODO Returns how many vertices there are now
			return line_vert_count;
		}

		size_t get_line_vert_capacity()
		{
			//TODO returns the maximum size the line vert array
			return MAX_LINE_VERTS;
		}

		void AABBDraw(float3 minPos, float3 maxPos)
		{
			float3 centerPos;
			
			centerPos.x = (minPos.x + maxPos.x) / 2;
			centerPos.y = (minPos.y + maxPos.y) / 2;
			centerPos.z = (minPos.z + maxPos.z) / 2;

			aabb.data()->center = centerPos;
			aabb.data()->extents = maxPos - centerPos;
			float3 negExtent = minPos + centerPos;
			//float3 flat = { maxPos.x, 0, maxPos.z };
			//front horizontal
			end::debug_renderer::add_line(aabb.data()->center, negExtent, float4(0, 0, 1, 1));
			end::debug_renderer::add_line(aabb.data()->center, aabb.data()->extents, float4(0, 0, 1, 1));
			////front vertical
			//end::debug_renderer::add_line(float3(-5, 5, 0), float3(-5, -5, 0), float4(0, 0, 1, 1));
			//end::debug_renderer::add_line(float3(5, 5, 0), float3(5, -5, 0), float4(0, 0, 1, 1));
			////back horizontal
			//end::debug_renderer::add_line(float3(5, 5, 15), float3(-5, 5, 15), float4(0, 0, 1, 1));
			//end::debug_renderer::add_line(float3(5, -5, 15), float3(-5, -5, 15), float4(0, 0, 1, 1));
			////back vertical
			//end::debug_renderer::add_line(float3(-5, 5, 15), float3(-5, -5, 15), float4(0, 0, 1, 1));
			//end::debug_renderer::add_line(float3(5, 5, 15), float3(5, -5, 15), float4(0, 0, 1, 1));
			////right top horizontal
			//end::debug_renderer::add_line(float3(5, 5, 0), float3(5, 5, 15), float4(0, 0, 1, 1));
			////right bottom horizontal
			//end::debug_renderer::add_line(float3(5, -5, 0), float3(5, -5, 15), float4(0, 0, 1, 1));
			////left top horizontal
			//end::debug_renderer::add_line(float3(-5, 5, 0), float3(-5, 5, 15), float4(0, 0, 1, 1));
			////left bottom horizontal
			//end::debug_renderer::add_line(float3(-5, -5, 0), float3(-5, -5, 15), float4(0, 0, 1, 1));
		}
	}
}