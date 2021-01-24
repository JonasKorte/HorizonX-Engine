#pragma once
#include <map>

namespace HXEditor
{
	typedef const char* HX_ID;

	struct HX_Component
	{
		HX_ID id;
		
		void* Load();
		void* Unload();
		void* Update();

		HX_ID parent;
	};

	typedef std::map<HX_ID, HX_Component> HX_ComponentCollection;


	class HX_UIManager
	{
	public:
		static void RegisterComponent(HX_Component component)
		{
			HX_ID id = "0x" + cast<HX_ID>(m_numComponents);

			m_numComponents++;
		}

	private:
		static std::map<HX_ComponentCollection, bool> m_components;

		static int m_numComponents;

		static HX_UIManager* m_instance;
	};
}