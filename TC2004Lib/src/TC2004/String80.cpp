#include "TC2004/String80.h"

namespace TC2004
{

    String80::String80()
    {
        Clear();
    }
    
    String80::~String80()
    {
    }

    void String80::Clear()
    {
        for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_STRING80_SIZE; i++)
        {
            m_Buffer[i] = static_cast<uint8_t>('\0');
        }
        m_Size = static_cast<uint32_t>(0UL);
    }

    void String80::Copy(const String80 &other)
    {
        Clear();
        m_Size = other.m_Size;
        if (other.m_Size > MAX_STRING80_SIZE)
        {
            m_Size = MAX_STRING80_SIZE;
        }
        for (uint32_t i = static_cast<uint32_t>(0UL); i < m_Size; i++)
        {
            m_Buffer[i] = other.m_Buffer[i];
        }
    }

    String80 String80::operator+=(const String80 &other)
    {
        if (other.m_Size > static_cast<uint32_t>(0UL))
        {
            const uint32_t otherStringSize = (other.m_Size < MAX_STRING80_SIZE) ? other.m_Size : MAX_STRING80_SIZE;
            for (uint32_t i = static_cast<uint32_t>(0UL); i < otherStringSize; i++)
            {
                if (m_Size < MAX_STRING80_SIZE)
                {
                    m_Buffer[m_Size] = other.m_Buffer[i];
                    m_Size++;
                }
                else
                {
                    break;
                }
            }
        }
        return *this;
    }

    String80 String80::operator+=(const int32_t i32)
    {
        static constexpr uint32_t MAX_I32_SIZE = static_cast<uint8_t>(11U);
        char reverseString[MAX_I32_SIZE] = { 0 };
        const bool bIsNegative = i32 < static_cast<int32_t>(0L);
        int32_t positiveNumber = bIsNegative ? -i32 : i32;
        uint32_t digitSize = static_cast<uint32_t>(0UL);
        
        for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_I32_SIZE; i ++)
        {
            digitSize++;
            const int32_t digit = positiveNumber % static_cast<int32_t>(10);
            const uint8_t digitChar = static_cast<uint8_t>(digit) + static_cast<uint8_t>('0');
            reverseString[i] = digitChar;
            positiveNumber /= static_cast<int32_t>(10L);
            if (positiveNumber == static_cast<int32_t>(0L))
            {
                break;
            }
        }
        
        if (m_Size < MAX_STRING80_SIZE)
        {
            if (bIsNegative)
            {
                m_Buffer[m_Size] = static_cast<uint8_t>('-');
                m_Size++;
            }
        }

        for (uint32_t i = static_cast<uint32_t>(0UL); i < digitSize; i++)
        {
            if (m_Size < MAX_STRING80_SIZE)
            {
                m_Buffer[m_Size] = static_cast<uint8_t>(reverseString[(digitSize - i) - static_cast<uint32_t>(1UL)]);
                m_Size++;
            }
        }
        return *this;
    }


    String80 String80::operator+(const String80 &other)
    {
        String80 result = *this;
        result += other;
        return result;
    }

    String80 String80::operator+(const int32_t i32)
    {
        String80 result = *this;
        result += i32;
        return result;
    }



} // namespace TC2004
