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
			ImGui::End();
			this->m_viewportActive = false;
		}

		void HXEC_Viewport::Load()
		{

			this->m_viewportActive = true;

			ImGui::SetNextWindowPos(ImVec2(HX::HX_EditorDefaults::defaultViewportX, HX::HX_EditorDefaults::defaultViewportY));

			ImGui::SetNextWindowSize(ImVec2(HX::HX_EditorDefaults::defaultViewportWidth, HX::HX_EditorDefaults::defaultViewportHeight));

			ImGui::Begin(this->m_title, &this->m_viewportActive, ImGuiWindowFlags_MenuBar);

			this->m_window->SetViewport(ImGui::GetWindowContentRegionMin().x, ImGui::GetWindowContentRegionMin().y, ImGui::GetWindowContentRegionMax().x, ImGui::GetWindowContentRegionMax().y);
		}

		void HXEC_Viewport::Unload()
		{
			this->m_window->SetViewport(0, 0, 0, 0);
		}

		void HXEC_Viewport::Update()
		{
			this->m_window->SetViewport(ImGui::GetWindowContentRegionMin().x, ImGui::GetWindowContentRegionMin().y, ImGui::GetWindowContentRegionMax().x, ImGui::GetWindowContentRegionMax().y);
		}

		void HXEC_Viewport::Unregister()
		{
			delete this;
		}

		HX_Component HXEC_Viewport::MakeComponent()
		{
			HX_Component component;
			component.isLoaded = true;
			component.Load = std::bind(&HXEC_Viewport::Load, this);
			component.Unload = std::bind(&HXEC_Viewport::Unload, this);
			component.Update = std::bind(&HXEC_Viewport::Update, this);
			component.Unregister = std::bind(&HXEC_Viewport::Unregister, this);

			return component;
		}
	}
}