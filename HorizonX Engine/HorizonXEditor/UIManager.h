#pragma once
#include <map>
#include <string>
#include <functional>
#include <Log.h>

namespace HXEditor
{
	typedef std::string HX_ID;

	struct HX_Component
	{
		HX_ID id;
		std::function<void()> Load;
		std::function<void()> Unload;
		std::function<void()> Update;
		std::function<void()> Unregister;

		bool isLoaded = true;
	};

	typedef std::map<HX_ID, HX_Component> HX_ComponentCollection;

	class HX_UIManager
	{
	public:
		static HX_ID RegisterComponent(HX_Component component);
		
		static void UnregisterComponent(HX_ID id);

		static void LoadComponent(HX_ID id);

		static void UnloadComponent(HX_ID id);

		static void UpdateComponents();

		static HX_ComponentCollection m_components;

		static int m_numComponents;

	private:
		static HX_UIManager* m_instance;
	};
}