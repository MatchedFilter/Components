/**
 * @brief This methods must be implemented on the mcu or os side. SHT3X uses this methods
 * The id shall be equal to the given Id of the SHT3XSensor classes constructor.
 */

#ifndef SHT3X_SHT3XDEPENDENCIES_H
#define SHT3X_SHT3XDEPENDENCIES_H
#include "ShtBuffer.h"
namespace SHT3X
{
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, ShtBuffer &buffer, const uint16_t size);
} // namespace SHT3X

#endif // SHT3X_SHT3XDEPENDENCIES_H