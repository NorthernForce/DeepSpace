#pragma once

#include "../RobotMap.h"
#include "../Main.h"

class AdjustPotentiometer
{
	public:
		AdjustPotentiometer()
		{
			m_adjust = Main::getOI().GetManipulatorStick().GetZ();

			m_defaultValue = DefaultPosition::kValue + m_adjust;
			m_downValue = DownPosition::kValue + m_adjust;
			m_upValue = UpPosition::kValue + m_adjust;
			m_portcullisValue = PortcullisPosition::kValue + m_adjust;

			CheckBounds(m_defaultValue);
			CheckBounds(m_downValue);
			CheckBounds(m_upValue);
			CheckBounds(m_portcullisValue);

			DefaultValue::m_value = m_defaultValue;
			DownValue::m_value = m_downValue;
			UpValue::m_value = m_upValue;
			PortcullisValue::m_value = m_portcullisValue;
		}

		void CheckBounds(float value)
		{
			if (value > 1)
			{
				--value;
			}

			if (value < 0)
			{
				++value;
			}
		}

		struct DefaultValue{ static float m_value; };
		struct DownValue{ static float m_value; };
		struct UpValue{ static float m_value; };
		struct PortcullisValue{ static float m_value; };

		static float m_defaultValue;
		static float m_downValue;
		static float m_upValue;
		static float m_portcullisValue;

	private:
		static float m_adjust;
};
