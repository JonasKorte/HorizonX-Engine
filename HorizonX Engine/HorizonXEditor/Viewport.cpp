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

		bool HXEC_Viewport::Load()
		{

			this->m_viewportActive = true;

			ImGui::SetNextWindowPos(ImVec2(HX::HX_EditorDefaults::defaultViewportX, HX::HX_EditorDefaults::defaultViewportY));

			ImGui::SetNextWindowSize(ImVec2(HX::HX_EditorDefaults::defaultViewportWidth, HX::HX_EditorDefaults::defaultViewportHeight));

			ImGui::Begin(this->m_title, &this->m_viewportActive, ImGuiWindowFlags_MenuBar);

			this->m_window->SetViewport(ImGui::GetWindowContentRegionMin().x, ImGui::GetWindowContentRegionMin().y, ImGui::GetWindowContentRegionMax().x, ImGui::GetWindowContentRegionMax().y);
		}

		bool HXEC_Viewport::Unload()
		{
			delete this;
		}

		void HXEC_Viewport::Update()
		{
			this->m_window->SetViewport(ImGui::GetWindowContentRegionMin().x, ImGui::GetWindowContentRegionMin().y, ImGui::GetWindowContentRegionMax().x, ImGui::GetWindowContentRegionMax().y);
		}
	}
}