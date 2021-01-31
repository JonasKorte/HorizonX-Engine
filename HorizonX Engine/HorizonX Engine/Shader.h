#pragma once
#include "API.h"
#include "Log.h"
#include "glad/glad.h"
#include "Color.h"
#include <fstream>
#include <map>
#include <string>

namespace HX
{
	struct HX_API ShaderToggles
	{
		bool hasVertex = true;
		bool hasFragment = true;
		bool hasGeometry = false;
		bool hasTesselation = false;
		bool hasCompute = false;
	};
	struct HX_API ShaderData
	{
		const char* vertexData;
		const char* fragmentData;
		const char* geometryData;
		const char* tesselationControlData;
		const char* tesselationEvalData;
		const char* computeData;
	};

	class HX_API Shader
	{
	public:
		Shader(const char* path, ShaderToggles toggles);

		Shader(const Shader& shader);

		~Shader();

		bool BindShader();

		bool LoadShader();

		void SetBool(const std::string& name, bool value);

		void SetInt(const std::string& name, int value);

		void SetFloat(const std::string& name, float value);

		void SetColor(const std::string& name, Color value);

	private:
		const char* m_path;

		ShaderToggles m_toggles;

		ShaderData m_data;

		ShaderData ParseShader(const char* data);

		GLuint m_shaderProgram;

		GLuint m_vertexShader;

		GLuint m_fragmentShader;

		GLuint m_geometryShader;

		GLuint m_tesselationControlShader;

		GLuint m_tesselationEvalShader;

		GLuint m_computeShader;
	};
}