#ifndef EEPROM24C_EEPROMBUFFER_H
#define EEPROM24C_EEPROMBUFFER_H
#include <cinttypes>
namespace Eeprom24C
{
    struct EepromBuffer
    {
    public:
        static constexpr uint32_t MAX_EEPROMBUFFER_SIZE = static_cast<uint32_t>(512UL); 
        uint8_t m_Buffer[MAX_EEPROMBUFFER_SIZE];
        uint32_t m_Size;
    };
} // namespace Eeprom24C

#endif // EEPROM24C_EEPROMBUFFER_H