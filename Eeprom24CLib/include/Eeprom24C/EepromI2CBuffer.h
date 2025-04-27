#ifndef EEPROM24C_EEPROMI2CBUFFER_H
#define EEPROM24C_EEPROMI2CBUFFER_H
#include <cinttypes>
namespace Eeprom24C
{
    struct EepromI2CBuffer
    {
    public:
        static constexpr uint32_t MAX_EEPROMI2CBUFFER_SIZE = static_cast<uint32_t>(32UL);
        uint8_t m_Buffer[MAX_EEPROMI2CBUFFER_SIZE];
        uint32_t m_Size;
    };
} // namespace Eeprom24C

#endif // EEPROM24C_EEPROMI2CBUFFER_H