/**
 * @brief This methods must be implemented on the mcu or os side. TC2004 uses this methods
 * The id shall be equal to the given Id of the Lcd class constructor.
 */

#ifndef TC2004_TC2004DEPENDENCIES_H
#define TC2004_TC2004DEPENDENCIES_H
#include <cinttypes>
namespace TC2004
{
    void DelayInMillisecond(const uint32_t durationInMillisecond);
    bool SendCommand(const uint8_t id, const uint8_t command);
    bool SendData(const uint8_t id, const uint8_t data);
} // namespace TC2004

#endif // TC2004_TC2004DEPENDENCIES_H