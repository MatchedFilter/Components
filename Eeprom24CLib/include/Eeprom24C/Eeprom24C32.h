#ifndef EEPROM24C_EEPROM24C32_H
#define EEPROM24C_EEPROM24C32_H
#include "EepromBuffer.h"
namespace Eeprom24C
{
    class Eeprom24C32
    {
    public:
        Eeprom24C32(const uint8_t id);
        ~Eeprom24C32();
        void Initialize(void);
        void Initialize(const bool a0State, const bool a1State, const bool a2State);
        bool Write(const uint32_t memoryAddress, const EepromBuffer &buffer);
        bool Read(const uint32_t memoryAddress, EepromBuffer &buffer, const uint32_t size);

    private:
        const uint8_t m_ID;
        uint16_t m_I2CAddress;
        static constexpr uint32_t PAGE_SIZE = static_cast<uint32_t>(32UL);
        static constexpr uint32_t NUMBER_OF_PAGES = static_cast<uint32_t>(512UL);
        static constexpr uint32_t PAGE_SHIFT_SIZE = static_cast<uint32_t>(5UL);
        static constexpr uint32_t MAX_MEMORY_ADDRESS = PAGE_SIZE * NUMBER_OF_PAGES;

    private:
        static bool ReadPageWithOffset(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t page, const uint32_t offset, const uint32_t size, EepromBuffer &buffer);
        static bool ReadFirstChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const uint32_t size, EepromBuffer &buffer, uint32_t &readSize);
        static bool ReadUntilLastChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const uint32_t initialReadSize, const uint32_t size, EepromBuffer &buffer);
        static bool ReadLastChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t memoryAddress, const uint32_t size, EepromBuffer &buffer);
        
        static bool WritePageWithOffset(const uint8_t &id, const uint16_t deviceAddress, const uint32_t page, const uint32_t offset, const EepromBuffer &buffer, const uint32_t bufferStartIndex, const uint32_t size);
        static bool WriteFirstChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const EepromBuffer &buffer, uint32_t &writtenSize);
        static bool WriteUntilLastChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const EepromBuffer &buffer, uint32_t &writtenSize);
        static bool WriteLastChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const EepromBuffer &buffer, const uint32_t &writtenSize);

    };
} // namespace Eeprom24C

#endif // EEPROM24C_EEPROM24C32_H