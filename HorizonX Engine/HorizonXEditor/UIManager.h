#pragma once

namespace HXEditor
{
	struct HX_Component
	{
		const char* id;
		
		void* Load();
		void* Unload();
		void* Update();
	};

	class HX_UIManager
	{
	public:
		static HX_UIManager* GetInstance();
	};
}