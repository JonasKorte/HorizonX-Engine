#include "Viewport.h"

namespace HXEditor
{
	namespace Components
	{
		HXEC_Viewport::HXEC_Viewport(const char* title)
		{
			this->m_title = title;
			this->m_viewportActive = false;
		}

		HXEC_Viewport::HXEC_Viewport(HXEC_Viewport& viewport)
		{
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

			ImGui::SetNextWindowSize(ImVec2(HX::HX_EditorDefaults::defaultViewportWidth, HX::HX_EditorDefaults::defaultViewportHeight));
			ImGui::SetNextWindowPos(ImVec2(HX::HX_EditorDefaults::defaultViewportX, HX::HX_EditorDefaults::defaultViewportY));

			ImGui::Begin("Viewport", NULL, ImGuiCond_FirstUseEver);

			ImGui::End();
		}

		void HXEC_Viewport::Unload()
		{
			this->m_viewportActive = false;
		}

		void HXEC_Viewport::Update()
		{
			ImGui::Begin("Viewport");


			glViewport(ImGui::GetWindowContentRegionMin().x, ImGui::GetWindowContentRegionMin().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

			ImGui::End();
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