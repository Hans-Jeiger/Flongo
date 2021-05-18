#pragma once

#include "Flongo/Layers/Layer.h"

namespace Flongo
{
	class FLONGO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);

	private:
		float time = 0.0f;
	};
}