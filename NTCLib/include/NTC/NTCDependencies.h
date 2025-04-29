/**
 * @brief This methods must be implemented on the mcu or os side. NTC uses this methods
 * The id shall be equal to the given Id of the TemperatureSensor class constructor.
 */


#ifndef NTC_NTCDEPENDENCIES_H
#define NTC_NTCDEPENDENCIES_H
#include <cinttypes>

namespace NTC
{
    void StartAdc(const uint8_t id);
    uint32_t ReadAdc(const uint8_t id);
} // namespace NTC

#endif // NTC_NTCDEPENDENCIES_H