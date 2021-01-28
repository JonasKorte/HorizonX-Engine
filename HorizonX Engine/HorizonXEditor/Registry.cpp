#include "Registry.h"

namespace HX
{
	const char* GetExecutablePath()
	{
		const char* path = "";
		char value[255];

		DWORD BufferSize = HX_REGISTRY_READ_BUFFER;

		RegGetValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Jonas Korte\\HorizonX Engine\\v1.0", L"ExecutablePath", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);

		path = value;

		return path;
	}

	const char* GetShaderPath()
	{
		const char* path = "";
		char value[255];

		DWORD BufferSize = HX_REGISTRY_READ_BUFFER;

		RegGetValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Jonas Korte\\HorizonX Engine\\v1.0", L"ShaderPath", RRF_RT_ANY, NULL, (PVOID)&value, &BufferSize);

		path = value;

		return path;
	}
}