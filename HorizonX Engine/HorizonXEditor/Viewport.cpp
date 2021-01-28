#include "Viewport.h"

namespace HXEditor
{
	namespace Components
	{
		HXEC_Viewport::HXEC_Viewport(HX::HX_GLWindow* window, const char* title)
		{
			this->m_window = window;
			this->m_title = title;
			this->m_viewportActive = false;
		}

		HXEC_Viewport::HXEC_Viewport(HXEC_Viewport& viewport)
		{
			this->m_window = viewport.m_window;
			this->m_title = viewport.m_title;
			this->m_viewportActive = false;
		}

		HXEC_Viewport::~HXEC_Viewport()
		{
			this->m_viewportActive = false;
		}

		void HXEC_Viewport::Load()
		{
			this->m_viewportActive = true;
		}

		void HXEC_Viewport::Unload()
		{
			this->m_window->SetViewport(0, 0, 0, 0);
		}

		void HXEC_Viewport::Update()
		{

		}

		void HXEC_Viewport::Unregister()
		{
			delete this;
		}

		HX_Component HXEC_Viewport::MakeComponent()
		{
			HX_Component component;
			component.Load = [this]() { this->Load();  };
			component.Unload = [this]() { this->Unload();  };
			component.Update = [this]() { this->Update();  };
			component.Unregister = [this]() { this->Unregister();  };

			HX_ID id = HX_UIManager::RegisterComponent(component);

			component.id = id;

			return component;
		}
	}
}