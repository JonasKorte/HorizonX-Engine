#pragma once
#include "API.h"
#include "Log.h"
#include "glad/glad.h"
#include "Vector.h"
#include <vector>

namespace HX
{
	struct HX_API Vertex
	{
		Vector3 position;
		Vector3 color;
		Vector2 uv;
	};

	typedef HX_API std::vector<Vertex> Mesh;

	class HX_API MeshRenderer
	{
	public:
		MeshRenderer(Mesh mesh);

		void Draw();

	private:
		Mesh m_mesh;
	};
}