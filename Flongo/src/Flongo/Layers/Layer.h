#pragma once

#include "Flongo/Core.h"
#include "Flongo/Events/Event.h"
#include "Flongo/Core/Timestep.h"

namespace Flongo
{
	class FLONGO_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(Timestep timestep) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return debugName; }

	protected:
		std::string debugName;
	};
}