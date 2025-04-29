#include "Joystick/JoystickSensor.h"
#include "Joystick/JoystickDependencies.h"

namespace Joystick
{


    JoystickSensor::JoystickSensor(const uint8_t id) : 
        m_ID ( id )
    {
    }
    
    JoystickSensor::~JoystickSensor()
    {
    }
    
    uint32_t JoystickSensor::ReadHorizontalValue()
    {
        StartHorizontalAdc(m_ID);
        DelayInMillisecond(static_cast<uint32_t>(1UL));
        return ReadAdc(m_ID);
    }

    uint32_t JoystickSensor::ReadVerticalValue()
    {
        StartVertialAdc(m_ID);
        DelayInMillisecond(static_cast<uint32_t>(1UL));
        return ReadAdc(m_ID);
    }

    bool JoystickSensor::IsSwitchPressed()
    {
        return 0x01U == ReadSwitchState(m_ID);
    }

    

} // namespace Joystick
