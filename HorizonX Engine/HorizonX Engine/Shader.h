#pragma once
#include "API.h"
#include "Log.h"
#include "glad/glad.h"
#include <fstream>
#include <map>
#include <string>

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
		const char* geometryData;
		const char* tesselationData;
		const char* computeData;
	};

	class HX_API HX_Shader
	{
	public:
		HX_Shader(const char* path, HX_ShaderToggles toggles);

		HX_Shader(const HX_Shader& shader);

		~HX_Shader();

		bool BindShader();

		bool LoadShader();

	private:
		const char* m_path;

		HX_ShaderToggles m_toggles;

		HX_ShaderData m_data;

		HX_ShaderData ParseShader(const char* data);

		GLuint m_shaderProgram;

		GLuint m_vertexShader;

		GLuint m_fragmentShader;

		GLuint m_geometryShader;

		GLuint m_tesselationShader;

		GLuint m_computeShader;
	};
}