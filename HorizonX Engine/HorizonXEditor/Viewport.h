#pragma once
#include <Log.h>
#include <GLWindow.h>
#include <EditorDefaults.h>

#include "imgui.h"

namespace HXEditor
{
	namespace Components
	{
		class HXEC_Viewport
		{
		public:
			HXEC_Viewport(HX::HX_GLWindow* window, const char* title);
			HXEC_Viewport(HXEC_Viewport& viewport);

			~HXEC_Viewport();

			bool Load();
			bool Unload();

			void Update();

		private:
			const char* m_title;

			HX::HX_GLWindow* m_window;

			bool m_viewportActive;
		};
	}
}
