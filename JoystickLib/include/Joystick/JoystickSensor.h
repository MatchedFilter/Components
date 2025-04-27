#ifndef JOYSTICK_JOYSTICKSENSOR_H
#define JOYSTICK_JOYSTICKSENSOR_H
#include <cinttypes>
namespace Joystick
{
    class JoystickSensor
    {
    public:
        JoystickSensor(const uint8_t id);
        ~JoystickSensor();
        uint32_t ReadHorizontalValue();
        uint32_t ReadVerticalValue();
        bool IsSwitchPressed();
    
    private:
        const uint8_t m_ID;
    };
} // namespace Joystick

#endif // JOYSTICK_JOYSTICKSENSOR_H