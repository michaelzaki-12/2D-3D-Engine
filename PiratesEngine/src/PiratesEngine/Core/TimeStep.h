#pragma once

namespace Pirates
{
	class TimeStep
	{
	public:
		TimeStep(float Time = 0.0f) : m_Time(Time)
		{
		}
		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

}