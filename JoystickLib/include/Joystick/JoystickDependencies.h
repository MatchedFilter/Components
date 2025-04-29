/**
 * @brief This methods must be implemented on the mcu or os side. Joystick uses this methods
 * The id shall be equal to the given Id of the JoystickSensor class constructor.
 */


#ifndef JOYSTICK_JOYSTICKDEPENDENCIES_H
#define JOYSTICK_JOYSTICKDEPENDENCIES_H
#include <cinttypes>
namespace Joystick
{
    void StartHorizontalAdc(const uint8_t id);
    void StartVertialAdc(const uint8_t id);
    void DelayInMillisecond(const uint32_t durationInMillisecond);
    uint32_t ReadAdc(const uint8_t id);
    uint8_t ReadSwitchState(const uint8_t id);
} // namespace Joystick

#endif // JOYSTICK_JOYSTICKDEPENDENCIES_H