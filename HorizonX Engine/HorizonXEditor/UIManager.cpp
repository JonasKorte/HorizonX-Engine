#include "UIManager.h"

namespace HXEditor
{
	int HX_UIManager::m_numComponents = 0;
	HX_ComponentCollection HX_UIManager::m_components;

	void HX_UIManager::RegisterComponent(HX_Component component)
	{
		HX_ID id = "0x";
		id.append(std::to_string(m_numComponents));

		component.id = id;

		m_components[id] = component;

		m_numComponents++;
	}

	void HX_UIManager::UnregisterComponent(HX_ID id)
	{
		m_components[id].Unregister();
		m_components.erase(id);
	}

	void HX_UIManager::LoadComponent(HX_ID id)
	{
		m_components[id].isLoaded = true;

		m_components[id].Load();
	}

	void HX_UIManager::UnloadComponent(HX_ID id)
	{
		m_components[id].isLoaded = false;
		m_components[id].Unload();
	}

	void HX_UIManager::UpdateComponents()
	{
		for (auto const& component : m_components)
		{
			m_components[component.first].Update();
		}
	}
}