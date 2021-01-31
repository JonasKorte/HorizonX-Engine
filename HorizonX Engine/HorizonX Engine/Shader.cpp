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

		if (ifs.fail())
		{
			std::string error = "Shader not found at: ";

			error.append(this->m_path);
			error.append("!");

			LOGERR(error);

			return false;
		}

		const char* raw = "";

		char c = ifs.get();

		while (ifs.good()) {
			raw += c;
			c = ifs.get();
		}

		ifs.close();

		HX_ShaderData data = this->ParseShader(raw);

		int success = 0;

		this->m_shaderProgram = glCreateProgram();

		if (this->m_toggles.hasVertex)
		{
			this->m_vertexShader = glCreateShader(GL_VERTEX_SHADER);

			glShaderSource(this->m_vertexShader, 1, &this->m_data.vertexData, NULL);

			glCompileShader(this->m_vertexShader);

			glGetShaderiv(this->m_vertexShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				LOGERR("Vertex shader failed to compile!");

				return false;
			}

			glAttachShader(this->m_shaderProgram, this->m_vertexShader);
		}

		if (this->m_toggles.hasFragment)
		{
			this->m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(this->m_fragmentShader, 1, &this->m_data.fragmentData, NULL);

			glCompileShader(this->m_fragmentShader);

			glGetShaderiv(this->m_fragmentShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				LOGERR("Fragment shader failed to compile!");

				return false;
			}

			glAttachShader(this->m_shaderProgram, this->m_fragmentShader);
		}

		if (this->m_toggles.hasGeometry)
		{
			this->m_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

			glShaderSource(this->m_geometryShader, 1, &this->m_data.geometryData, NULL);

			glCompileShader(this->m_geometryShader);

			glGetShaderiv(this->m_geometryShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				LOGERR("Geometry shader failed to compile!");

				return false;
			}

			glAttachShader(this->m_shaderProgram, this->m_geometryShader);
		}

		if (this->m_toggles.hasTesselation)
		{
			this->m_tesselationControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);

			glShaderSource(this->m_tesselationControlShader, 1, &this->m_data.tesselationControlData, NULL);

			glCompileShader(this->m_tesselationControlShader);

			glGetShaderiv(this->m_tesselationControlShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				LOGERR("Tesselation Control shader failed to compile!");

				return false;
			}

			glAttachShader(this->m_shaderProgram, this->m_tesselationControlShader);

			this->m_tesselationEvalShader = glCreateShader(GL_TESS_EVALUATION_SHADER);

			glShaderSource(this->m_tesselationEvalShader, 1, &this->m_data.tesselationEvalData, NULL);

			glCompileShader(this->m_tesselationEvalShader);

			glGetShaderiv(this->m_tesselationEvalShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				LOGERR("Tesselation Evaluation shader failed to compile!");

				return false;
			}

			glAttachShader(this->m_shaderProgram, this->m_tesselationEvalShader);
		}

		if (this->m_toggles.hasCompute)
		{
			this->m_computeShader = glCreateShader(GL_COMPUTE_SHADER);

			glShaderSource(this->m_computeShader, 1, &this->m_data.computeData, NULL);

			glCompileShader(this->m_computeShader);

			glGetShaderiv(this->m_computeShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				LOGERR("Compute shader failed to compile!");

				return false;
			}

			glAttachShader(this->m_shaderProgram, this->m_computeShader);
		}

		glLinkProgram(this->m_shaderProgram);

		glGetProgramiv(this->m_shaderProgram, GL_LINK_STATUS, &success);

		if (!success)
		{
			LOGERR("Shader program failed to compile!");

			return false;
		}

		if (this->m_toggles.hasVertex)
		{
			glDeleteShader(this->m_vertexShader);
		}

		if (this->m_toggles.hasFragment)
		{
			glDeleteShader(this->m_fragmentShader);
		}

		if (this->m_toggles.hasGeometry)
		{
			glDeleteShader(this->m_geometryShader);
		}

		if (this->m_toggles.hasTesselation)
		{
			glDeleteShader(this->m_tesselationControlShader);


			glDeleteShader(this->m_tesselationEvalShader);
		}

		if (this->m_toggles.hasCompute)
		{
			glDeleteShader(this->m_computeShader);
		}

		return true;
	}

	bool HX_Shader::BindShader()
	{
		glUseProgram(this->m_shaderProgram);

		return true;
	}

	HX_Shader::~HX_Shader()
	{
		glDeleteProgram(this->m_shaderProgram);
	}
	void HX_Shader::SetBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(this->m_shaderProgram, name.c_str()), (int)value);
	}

	void HX_Shader::SetInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(this->m_shaderProgram, name.c_str()), value);
	}

	void HX_Shader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(this->m_shaderProgram, name.c_str()), value);
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

				else if (token == "<tess_control>")
				{
					current = "tesselation_control";
				}

				else if (token == "<tess_eval>")
				{
					current = "tesselation_eval";
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

			else if (current == "tesselation_control")
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

				if (token == "</tess_control>")
				{
					shader.erase(shader.end() - 15, shader.end());
					shaderSource.tesselationControlData = shader.c_str();

					token = "";
					current = "";
					shader = "";
				}
			}

			else if (current == "tesselation_evaluation")
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

				if (token == "</tess_eval>")
				{
					shader.erase(shader.end() - 12, shader.end());
					shaderSource.tesselationControlData = shader.c_str();

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
					shader.erase(shader.end() - 10, shader.end());
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