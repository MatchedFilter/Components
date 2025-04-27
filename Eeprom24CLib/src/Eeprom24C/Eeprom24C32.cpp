#include "Eeprom24C/Eeprom24C32.h"
#include "Eeprom24C/EepromI2CBuffer.h"

namespace Eeprom24C
{
    bool WriteToI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToWrite, const EepromI2CBuffer &i2cBuffer);
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, EepromI2CBuffer &i2cBuffer, const uint16_t size);
    void DelayInMillisecond(const uint32_t durationInMillisecond);


    bool Eeprom24C32::ReadPageWithOffset(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t page, const uint32_t offset, const uint32_t size, EepromBuffer &buffer)
    {
        bool bResult = false;
        EepromI2CBuffer i2cBuffer;
        i2cBuffer.m_Size = static_cast<uint32_t>(0UL);
        const uint16_t addressToRead = static_cast<uint16_t>(((page * PAGE_SIZE) << PAGE_SHIFT_SIZE) | offset);
        if (ReadFromI2C(id, deviceAddress, addressToRead, i2cBuffer, static_cast<uint16_t>(size)))
        {
            if ((buffer.m_Size + i2cBuffer.m_Size) <= EepromBuffer::MAX_EEPROMBUFFER_SIZE)
            {
                bResult = true;
                for (uint32_t i = static_cast<uint32_t>(0UL); i < i2cBuffer.m_Size; i++)
                {
                    buffer.m_Buffer[buffer.m_Size] = i2cBuffer.m_Buffer[i];
                    buffer.m_Size++;
                }
            }
        }

        DelayInMillisecond(static_cast<uint32_t>(1UL));
        return bResult;
    }

    bool Eeprom24C32::ReadFirstChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const uint32_t size, EepromBuffer &buffer, uint32_t &readSize)
    {
        bool bResult = false;
        buffer.m_Size = static_cast<uint32_t>(0UL);
        const uint32_t firstPage = memoryAddress / PAGE_SIZE;
        const uint32_t firstPageOffset = memoryAddress % PAGE_SIZE;
        if ((firstPageOffset + size) < PAGE_SIZE)
        {
            bResult = ReadPageWithOffset(id, deviceAddress, firstPage, firstPageOffset, size, buffer);
            if (bResult)
            {
                readSize = size;
            }
        }
        else
        {
            const uint32_t toFullPageRemainingSize = PAGE_SIZE - (firstPageOffset + size);
            bResult = ReadPageWithOffset(id, deviceAddress, firstPage, firstPageOffset, toFullPageRemainingSize, buffer);
            if (bResult)
            {
                readSize = toFullPageRemainingSize;
            }
        }
        return bResult;
    }

    bool Eeprom24C32::ReadUntilLastChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const uint32_t initialReadSize, const uint32_t size, EepromBuffer &buffer)
    {
        bool bResult = true;
        const uint32_t initialPage = (memoryAddress / PAGE_SIZE) + static_cast<uint32_t>(1UL);
        const uint32_t pageCount = (size - initialReadSize) / PAGE_SIZE;
        for (uint32_t i = static_cast<uint32_t>(0UL); i < pageCount; i++)
        {
            const uint32_t currentPage = initialPage + i;
            if (false == ReadPageWithOffset(id, deviceAddress, currentPage, static_cast<uint32_t>(0UL), PAGE_SIZE, buffer))
            {
                bResult = false;
                break;
            }
        }
        return bResult;
    }

    bool Eeprom24C32::ReadLastChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t memoryAddress, const uint32_t size, EepromBuffer &buffer)
    {
        bool bResult = false;
        const uint32_t lastChunkSize = (memoryAddress + size) % PAGE_SIZE;
        if (lastChunkSize > static_cast<uint32_t>(0UL))
        {
            const uint32_t lastPage = (memoryAddress + size) / PAGE_SIZE;
            bResult = ReadPageWithOffset(id, deviceAddress, lastPage, static_cast<uint32_t>(0UL), lastChunkSize, buffer);
        }
        else
        {
            bResult = true;
        }
        return bResult;
    }

    bool Eeprom24C32::WritePageWithOffset(const uint8_t &id, const uint16_t deviceAddress, const uint32_t page, const uint32_t offset, const EepromBuffer &buffer, const uint32_t bufferStartIndex, const uint32_t size)
    {
        bool bResult = false;
        EepromI2CBuffer i2cBuffer;
        if ((offset + size) <= PAGE_SIZE)
        {
            i2cBuffer.m_Size = size;
            if ((bufferStartIndex + size) < EepromBuffer::MAX_EEPROMBUFFER_SIZE)
            {
                for (uint32_t i = static_cast<uint32_t>(0UL); i < size; i++)
                {
                    i2cBuffer.m_Buffer[i] =  buffer.m_Buffer[bufferStartIndex + i];
                }
                const uint16_t addressToWrite = static_cast<uint16_t>(((page * PAGE_SIZE) << PAGE_SHIFT_SIZE) | offset);
                if (WriteToI2C(id, deviceAddress, addressToWrite, i2cBuffer))
                { 
                    bResult = true;
                }
                DelayInMillisecond(static_cast<uint32_t>(1UL));
            }
        }
        return bResult;
    }

    bool Eeprom24C32::WriteFirstChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const EepromBuffer &buffer, uint32_t &writtenSize)
    {
        bool bResult = false;
        const uint32_t firstPage = memoryAddress / PAGE_SIZE;
        const uint32_t firstPageOffset = memoryAddress % PAGE_SIZE;
        if((firstPageOffset + buffer.m_Size) > PAGE_SIZE)
        {
            const uint32_t firstPageLeftOverSize = PAGE_SIZE - firstPageOffset;
            bResult = WritePageWithOffset(id, deviceAddress, firstPage, firstPageOffset, buffer, static_cast<uint32_t>(0UL), firstPageLeftOverSize);
            if (bResult)
            {
                writtenSize = firstPageLeftOverSize;
            }
        }
        else
        {
            bResult = WritePageWithOffset(id, deviceAddress, firstPage, firstPageOffset, buffer, static_cast<uint32_t>(0UL), buffer.m_Size);
            if (bResult)
            {
                writtenSize = buffer.m_Size;
            }
        }
        return bResult;
    }

    bool Eeprom24C32::WriteUntilLastChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const EepromBuffer &buffer, uint32_t &writtenSize)
    {
        bool bResult = true;
        const uint32_t pageCount = (buffer.m_Size - writtenSize) / PAGE_SIZE;
        const uint32_t initialPage = (memoryAddress / PAGE_SIZE) + static_cast<uint32_t>(1UL);
        for (uint32_t i = static_cast<uint32_t>(0UL); i < pageCount; i++)
        {
            const uint32_t currentPage = initialPage + i;
            if (false == WritePageWithOffset(id, deviceAddress, currentPage, static_cast<uint32_t>(0UL), buffer, writtenSize, PAGE_SIZE))
            {
                bResult = false;
                break;
            }
            writtenSize += PAGE_SIZE;
        }
        return bResult;
    }

    bool Eeprom24C32::WriteLastChunk(const uint8_t &id, const uint16_t &deviceAddress, const uint32_t &memoryAddress, const EepromBuffer &buffer, const uint32_t &writtenSize)
    {
        bool bResult = false;
        if (buffer.m_Size > writtenSize)
        {
            const uint32_t lastChunkSize = buffer.m_Size - writtenSize;
            const uint32_t lastPage = (memoryAddress + buffer.m_Size) / PAGE_SIZE;
            if (lastChunkSize < PAGE_SIZE)
            {
                if (lastChunkSize > static_cast<uint32_t>(0UL))
                {
                    bResult = WritePageWithOffset(id, deviceAddress, lastPage, static_cast<uint32_t>(0UL), buffer, writtenSize, lastChunkSize);
                }
                else
                {
                    bResult = true;
                }
            }
        }
        return bResult;
    }

    Eeprom24C32::Eeprom24C32(const uint8_t id) : 
        m_ID ( id ),
        m_I2CAddress ( static_cast<uint16_t>(0xA0U) )
    {
    }

    Eeprom24C32::~Eeprom24C32()
    {
    }

    void Eeprom24C32::Initialize(void)
    {
        Initialize(false, false, false);
    }

    void Eeprom24C32::Initialize(const bool a0State, const bool a1State, const bool a2State)
    {
        const uint16_t a0Value = a0State == true;
        const uint16_t a1Value = a1State == true;
        const uint16_t a2Value = a2State == true;

        m_I2CAddress |= static_cast<uint16_t>(a0Value << static_cast<uint16_t>(1UL));
        m_I2CAddress |= static_cast<uint16_t>(a1Value << static_cast<uint16_t>(2UL));
        m_I2CAddress |= static_cast<uint16_t>(a2Value << static_cast<uint16_t>(3UL));
    }

    bool Eeprom24C32::Write(const uint32_t memoryAddress, const EepromBuffer &buffer)
    {
        bool bResult = false;
        if (buffer.m_Size > static_cast<uint32_t>(0UL))
        {
            if ((memoryAddress + buffer.m_Size) < MAX_MEMORY_ADDRESS)
            {
                uint32_t writtenSize = static_cast<uint32_t>(0UL);
                if (WriteFirstChunk(m_ID, m_I2CAddress, memoryAddress, buffer, writtenSize))
                {
                    if (writtenSize < buffer.m_Size)
                    {
                        if (WriteUntilLastChunk(m_ID, m_I2CAddress, memoryAddress, buffer, writtenSize))
                        {
                            bResult = WriteLastChunk(m_ID, m_I2CAddress, memoryAddress, buffer, writtenSize);
                        }
                    }
                    else
                    {
                        bResult = true;
                    }
                }
            }
        }
        return bResult;
    }

    bool Eeprom24C32::Read(const uint32_t memoryAddress, EepromBuffer &buffer, const uint32_t size)
    {
        bool bResult = false;
        if ((memoryAddress + size) < MAX_MEMORY_ADDRESS)
        {
            uint32_t readSize = static_cast<uint32_t>(0UL);
            if (ReadFirstChunk(m_ID, m_I2CAddress, memoryAddress, size, buffer, readSize))
            {
                if (readSize < size)
                {
                    if (ReadUntilLastChunk(m_ID, m_I2CAddress, memoryAddress, readSize, size, buffer))
                    {
                        bResult = ReadLastChunk(m_ID, m_I2CAddress, memoryAddress, size, buffer);
                        if (bResult)
                        {
                        }
                    }
                }
                else
                {
                    bResult = true;
                }
            }
        }
        return bResult;
    }


} // namespace Eeprom24C
