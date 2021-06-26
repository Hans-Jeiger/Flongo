#pragma once

#include "Flongo/Layers/Layer.h"
#include "Flongo/Events/ApplicationEvent.h"
#include "Flongo/Events/MouseEvent.h"
#include "Flongo/Events/KeyEvent.h"

namespace Flongo
{
	class FLONGO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();

	private:
		float time = 0.0f;
	};
}