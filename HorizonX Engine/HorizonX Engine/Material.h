#pragma once
#include "API.h"
#include "Shader.h"
#include "Color.h"
#include <variant>
#include <map>

namespace HX
{
	enum HX_API TextureType
	{
		TEX_COLOR = 0,
		TEX_GREYSCALE = 1,
		TEX_NORMAL = 2
	};

	struct HX_API Texture
	{
		const char* path;

		TextureType type;
	};

	template<typename T>
	struct HX_API Parameter
	{
		const char* name;

		T value;
	};

	class HX_API Material
	{
	public:
		Material(Shader* shader);

		Material(const Material& material);

		std::variant<Parameter<Texture>, Parameter<Color>, Parameter<float>, Parameter<int>, Parameter<bool>> GetParameter(const char* name);

		void SetParameter(const char* name, std::variant<Parameter<Texture>, Parameter<Color>, Parameter<float>, Parameter<int>, Parameter<bool>> value);

		void Bind();

		~Material();
	private:
		Shader* m_shader;

		std::map<const char*, std::variant<Parameter<Texture>, Parameter<Color>, Parameter<float>, Parameter<int>, Parameter<bool>>> m_parameters;
	};
}