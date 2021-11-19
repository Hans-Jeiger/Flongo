#pragma once

namespace Flongo
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: time(time)
		{
		}

		operator float() const { return time; }

		float getSeconds() const { return time; }
		float getMilliseconds() const { return time * 1000; }

	private:
		float time = 0.0f;
	};
}