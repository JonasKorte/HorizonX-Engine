#include "UIManager.h"

namespace HXEditor
{
	int HX_UIManager::m_numComponents = 0;
	HX_ComponentCollection HX_UIManager::m_components;

	HX_ID HX_UIManager::RegisterComponent(HX_Component component)
	{
		HX_ID id = "0x";
		id.append(std::to_string(m_numComponents));

		component.id = id;


		m_components[id] = component;

		m_numComponents++;

		return id;
	}

	void HX_UIManager::UnregisterComponent(HX_ID id)
	{
		m_components[id].Unregister();
		if (m_components[id].Load == nullptr)
		{
			std::string error = "Empty Load function empty for component: ";
			error.append(id);
			LOGERR(error);
			return;
		}
		m_components.erase(id);
	}

	void HX_UIManager::LoadComponent(HX_ID id)
	{
		m_components[id].isLoaded = true;
		if (m_components[id].Load == nullptr)
		{
			std::string error = "Empty Load function empty for component: ";
			error.append(id);
			LOGERR(error);
			return;
		}
		m_components[id].Load();
	}

	void HX_UIManager::UnloadComponent(HX_ID id)
	{
		m_components[id].isLoaded = false;
		if (m_components[id].Unload == nullptr)
		{
			std::string error = "Empty Unload function empty for component: ";
			error.append(id);
			LOGERR(error);
			return;
		}
		m_components[id].Unload();
	}

	void HX_UIManager::UpdateComponents()
	{
		for (auto const& component : m_components)
		{
			if (m_components[component.first].Load == nullptr)
			{
				std::string error = "Empty Load function empty for component: ";
				error.append(component.first);
				LOGERR(error);
				return;
			}
			if (m_components[component.first].isLoaded)
			{
				m_components[component.first].Update();
			}
		}
	}
}