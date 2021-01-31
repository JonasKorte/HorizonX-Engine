#include "Material.h"

namespace HX
{
	Material::Material(Shader* shader)
	{
		this->m_shader = shader;
	}

	Material::Material(const Material& material)
	{
		this->m_shader = material.m_shader;

		this->m_parameters = material.m_parameters;
	}

	Material::~Material()
	{
		delete this->m_shader;
	}

	void Material::Bind()
	{
		this->m_shader->BindShader();

		for (auto const& [key, val] : this->m_parameters)
		{
			if (val.index() == 0)
			{
				Parameter<Texture> param = std::get<Texture>(val);

				GLuint tex;

				glGenTextures(1, &tex);

				glBindTexture(GL_TEXTURE_2D, tex);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			}

			else if (val.index() == 1)
			{
				this->m_shader->SetColor(key, std::get<Color>(val));
			}

			else if (val.index() == 2)
			{
				this->m_shader->SetFloat(key, std::get<float>(val));
			}

			else if (val.index() == 3)
			{
				this->m_shader->SetInt(key, std::get<int>(val));
			}

			else if (val.index() == 4)
			{
				this->m_shader->SetBool(key, std::get<bool>(val));
			}
		}
	}

	std::variant<Parameter<Texture>, Parameter<Color>, Parameter<float>, Parameter<int>, Parameter<bool>> Material::GetParameter(const char* name)
	{
		return this->m_parameters[name];
	}

	void Material::SetParameter(const char* name, std::variant<Parameter<Texture>, Parameter<Color>, Parameter<float>, Parameter<int>, Parameter<bool>> value)
	{
		this->m_parameters[name] = value;
	}
}