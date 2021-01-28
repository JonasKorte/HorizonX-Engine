#pragma once
#include <Log.h>
#include <GLWindow.h>
#include <EditorDefaults.h>
#include "imgui.h"

#include "UIManager.h"

namespace HXEditor
{
	namespace Components
	{
		class HXEC_Viewport
		{
		public:
			HXEC_Viewport(const char* title);
			HXEC_Viewport(HXEC_Viewport& viewport);

			~HXEC_Viewport();

			HX_Component MakeComponent();

			void Load();
			void Unload();

			void Unregister();

			void Update();

		private:
			const char* m_title;

			bool m_viewportActive;
		};
	}
}
