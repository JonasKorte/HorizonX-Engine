#pragma once
#include "API.h"
#include "Log.h"
#include "glad/glad.h"

namespace HX
{
	struct HX_API HX_ShaderToggles
	{
		bool hasVertex = true;
		bool hasFragment = true;
		bool hasGeometry = false;
		bool hasTesselation = false;
		bool hasCompute = false;
	};
	struct HX_API HX_ShaderData
	{
		const char* vertexData;
		const char* fragmentData;
		const char* fragmentData;
	};

	class HX_API HX_Shader
	{
	public:
		HX_Shader(const char* path);

		bool Bind();

	private:

	};
}