/**
 * @brief This methods must be implemented on the mcu or os side. Eeprom24C uses this methods
 * The id shall be equal to the given Id of the Eeprom24C classes constructor.
 */


#ifndef EEPROM24C_EEPROM24CDEPENDENCIES_H
#define EEPROM24C_EEPROM24CDEPENDENCIES_H
#include "EepromI2CBuffer.h"

namespace Eeprom24C
{
    bool WriteToI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToWrite, const EepromI2CBuffer &i2cBuffer);
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, EepromI2CBuffer &i2cBuffer, const uint16_t size);
    void DelayInMillisecond(const uint32_t durationInMillisecond);
} // namespace Eeprom24C

#endif // EEPROM24C_EEPROM24CDEPENDENCIES_H