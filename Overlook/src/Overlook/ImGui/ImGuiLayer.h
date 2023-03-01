#pragma once

#include "Overlook/Core/Layer.h"

#include "Overlook/Events/ApplicationEvent.h"
#include "Overlook/Events/KeyEvent.h"
#include "Overlook/Events/MouseEvent.h"

namespace Overlook {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

		virtual void OnEvent(Event& e) override;
		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}