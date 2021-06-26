#pragma once

#include "Flongo/Core.h"
#include "Flongo/Events/Event.h"

namespace Flongo
{
	class FLONGO_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return debugName; }

	protected:
		std::string debugName;
	};
}