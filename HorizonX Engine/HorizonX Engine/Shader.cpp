#include "Shader.h"

namespace HX
{
	HX_Shader::HX_Shader(const char* path, HX_ShaderToggles toggles)
	{
		this->m_path = path;
		this->m_toggles = toggles;
		this->m_data = {};
	}

	HX_Shader::HX_Shader(const HX_Shader& shader)
	{
		this->m_data = shader.m_data;

		this->m_path = shader.m_path;

		this->m_toggles = shader.m_toggles;
	}

	bool HX_Shader::LoadShader()
	{
		std::ifstream ifs(this->m_path);

		const char* raw = "";

		char c = ifs.get();

		while (ifs.good()) {
			raw += c;
			c = ifs.get();
		}

		ifs.close();

		HX_ShaderData data = this->ParseShader(raw);

		this->m_shaderProgram = glCreateProgram();

		if (this->m_toggles.hasVertex)
		{
			this->m_vertexShader = glCreateShader(GL_VERTEX_SHADER);

			glShaderSource(this->m_vertexShader, 1, &this->m_data.vertexData, NULL);

			glCompileShader(this->m_vertexShader);

			glAttachShader(this->m_shaderProgram, this->m_vertexShader);
		}

		if (this->m_toggles.hasFragment)
		{
			this->m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(this->m_fragmentShader, 1, &this->m_data.fragmentData, NULL);

			glCompileShader(this->m_fragmentShader);

			glAttachShader(this->m_shaderProgram, this->m_fragmentShader);
		}

		if (this->m_toggles.hasGeometry)
		{
			this->m_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

			glShaderSource(this->m_geometryShader, 1, &this->m_data.geometryData, NULL);

			glCompileShader(this->m_geometryShader);

			glAttachShader(this->m_shaderProgram, this->m_geometryShader);
		}

		if (this->m_toggles.hasTesselation)
		{
			this->m_tesselationShader = glCreateShader(GL_TESS_CONTROL_SHADER);

			glShaderSource(this->m_tesselationShader, 1, &this->m_data.tesselationData, NULL);

			glCompileShader(this->m_tesselationShader);

			glAttachShader(this->m_shaderProgram, this->m_tesselationShader);
		}

		if (this->m_toggles.hasCompute)
		{
			this->m_computeShader = glCreateShader(GL_COMPUTE_SHADER);

			glShaderSource(this->m_computeShader, 1, &this->m_data.computeData, NULL);

			glCompileShader(this->m_computeShader);

			glAttachShader(this->m_shaderProgram, this->m_computeShader);
		}

		glLinkProgram(this->m_shaderProgram);

		return true;
	}

	bool HX_Shader::BindShader()
	{
		glUseProgram(this->m_shaderProgram);

		return true;
	}

	HX_Shader::~HX_Shader()
	{
		if (this->m_toggles.hasVertex)
		{
			glDetachShader(this->m_shaderProgram, this->m_vertexShader);

			glDeleteShader(this->m_vertexShader);
		}

		if (this->m_toggles.hasFragment)
		{
			glDetachShader(this->m_shaderProgram, this->m_fragmentShader);

			glDeleteShader(this->m_fragmentShader);
		}

		if (this->m_toggles.hasGeometry)
		{
			glDetachShader(this->m_shaderProgram, this->m_geometryShader);

			glDeleteShader(this->m_geometryShader);
		}

		if (this->m_toggles.hasTesselation)
		{
			glDetachShader(this->m_shaderProgram, this->m_tesselationShader);

			glDeleteShader(this->m_tesselationShader);
		}

		if (this->m_toggles.hasCompute)
		{
			glDetachShader(this->m_shaderProgram, this->m_computeShader);

			glDeleteShader(this->m_computeShader);
		}

		glDeleteProgram(this->m_shaderProgram);
	}

	HX_ShaderData HX_Shader::ParseShader(const char* data)
	{
		HX_ShaderData shaderSource = {};

		const char* token = "";

		int line = 0;
		const char* current = "";

		std::string shader;


		for (int i = 0; i < sizeof(data); i++)
		{
			if (current == "")
			{
				char c = data[i];
				token += c;

				if (c == '\n')
				{
					token = "";
					line++;
				}

				if (c == ' ')
				{
					token = "";
				}

				if (token == "<vertex>")
				{
					current = "vertex";
				}

				else if (token == "<fragment>")
				{
					current = "fragment";
				}

				else if (token == "<geometry>")
				{
					current = "geometry";
				}

				else if (token == "<tesselation>")
				{
					current = "tesselation";
				}

				else if (token == "<compute>")
				{
					current = "compute";
				}
			}

			else if (current == "vertex")
			{
				char c = data[i];
				token += c;

				shader += c;

				if (c == '\n')
				{
					token = "";
					line++;
				}

				if (c == ' ')
				{
					token = "";
				}

				if (token == "</vertex>")
				{
					shader.erase(shader.end() - 9, shader.end());
					shaderSource.vertexData = shader.c_str();

					token = "";
					current = "";
					shader = "";
				}
			}

			else if (current == "fragment")
			{
				char c = data[i];
				token += c;

				shader += c;

				if (c == '\n')
				{
					token = "";
					line++;
				}

				if (c == ' ')
				{
					token = "";
				}

				if (token == "</fragment>")
				{
					shader.erase(shader.end() - 11, shader.end());
					shaderSource.fragmentData = shader.c_str();

					token = "";
					current = "";
					shader = "";
				}
			}

			else if (current == "geometry")
			{
				char c = data[i];
				token += c;

				shader += c;

				if (c == '\n')
				{
					token = "";
					line++;
				}

				if (c == ' ')
				{
					token = "";
				}

				if (token == "</geometry>")
				{
					shader.erase(shader.end() - 11, shader.end());
					shaderSource.geometryData = shader.c_str();

					token = "";
					current = "";
					shader = "";
				}
			}

			else if (current == "tesselation")
			{
				char c = data[i];
				token += c;

				shader += c;

				if (c == '\n')
				{
					token = "";
					line++;
				}

				if (c == ' ')
				{
					token = "";
				}

				if (token == "</tesselation>")
				{
					shader.erase(shader.end() - 11, shader.end());
					shaderSource.tesselationData = shader.c_str();

					token = "";
					current = "";
					shader = "";
				}
			}

			else if (current == "compute")
			{
				char c = data[i];
				token += c;

				shader += c;

				if (c == '\n')
				{
					token = "";
					line++;
				}

				if (c == ' ')
				{
					token = "";
				}

				if (token == "</compute>")
				{
					shader.erase(shader.end() - 11, shader.end());
					shaderSource.computeData = shader.c_str();

					token = "";
					current = "";
					shader = "";
				}
			}
		}

		return shaderSource;
	}
}