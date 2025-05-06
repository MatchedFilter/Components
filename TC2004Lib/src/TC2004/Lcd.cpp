#include "TC2004/Lcd.h"
#include "TC2004/TC2004Dependencies.h"

namespace TC2004
{
    static constexpr uint8_t CLEAR_SCREEN_COMMAND = 0x01U;


    static bool RegisterSpecialCharsForLcd(const uint8_t id);

    static bool RegisterSpecialCharsForLcd(const uint8_t id)
    {
        constexpr uint8_t SPECIAL_CHAR_BASE_ADDRESS = 0x40U;
        constexpr uint8_t LOWER_I_OFFSET = 0U;
        constexpr uint8_t LOWER_U_OFFSET = 8U;
        constexpr uint8_t LOWER_O_OFFSET = 16U;
        constexpr uint8_t LOWER_G_OFFSET = 24U;
        constexpr uint8_t LOWER_C_OFFSET = 32U;
        constexpr uint8_t UPPER_O_OFFSET = 40U;
        constexpr uint8_t SPECIAL_CHAR_BYTE_COUNT = 8U;
    
        constexpr uint8_t SPECIAL_CHAR_LOWER_I[SPECIAL_CHAR_BYTE_COUNT] = { 
            0x00U, 0x00U, 0x0CU, 0x04U, 0x04U, 0x04U, 0x0EU, 0x00U
        };
    
        constexpr uint8_t SPECIAL_CHAR_LOWER_U[SPECIAL_CHAR_BYTE_COUNT] = {
            0x00U, 0x11U, 0x00 ,0x11U, 0x11U, 0x11U, 0x0FU, 0x00U
        };
    
        constexpr uint8_t SPECIAL_CHAR_LOWER_O[SPECIAL_CHAR_BYTE_COUNT] = {
            0x00U, 0x0AU, 0x00 ,0x0EU, 0x11U, 0x11U, 0x0EU, 0x00U
        };
    
        constexpr uint8_t SPECIAL_CHAR_LOWER_G[SPECIAL_CHAR_BYTE_COUNT] = {
            0x00U, 0x0EU, 0x00 ,0x0EU, 0x0AU, 0x0EU, 0x02U, 0x0EU
        };

        constexpr uint8_t SPECIAL_CHAR_LOWER_C[SPECIAL_CHAR_BYTE_COUNT] = {
            0x00U, 0x00U, 0x0EU, 0x10U, 0x10U, 0x11U, 0x0EU, 0x04U
        };

        constexpr uint8_t SPECIAL_CHAR_UPPER_O[SPECIAL_CHAR_BYTE_COUNT] = {
            0x0AU, 0x0EU, 0x11U, 0x11U, 0x11U, 0x11U, 0x0EU, 0x00U
        };

        bool bResult = SendCommand(id, SPECIAL_CHAR_BASE_ADDRESS + LOWER_I_OFFSET);
        DelayInMillisecond(static_cast<uint32_t>(1UL));
            if (bResult)
        {
            for (uint8_t i = 0; i < SPECIAL_CHAR_BYTE_COUNT; i++)
            {
                if (bResult)
                {
                    bResult = SendData(id, SPECIAL_CHAR_LOWER_I[i]);
                    DelayInMillisecond(static_cast<uint32_t>(1UL));
                }
                else
                {
                    break;
                }
            }
        }

        if (bResult)
        {
            bResult = SendCommand(id, SPECIAL_CHAR_BASE_ADDRESS + LOWER_U_OFFSET);
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            for (uint8_t i = 0; i < SPECIAL_CHAR_BYTE_COUNT; i++)
            {
                if (bResult)
                {
                    bResult = SendData(id, SPECIAL_CHAR_LOWER_U[i]);
                    DelayInMillisecond(static_cast<uint32_t>(1UL));
                }
                else
                {
                    break;
                }
            }
        }

        if (bResult)
        {
            bResult = SendCommand(id, SPECIAL_CHAR_BASE_ADDRESS + LOWER_O_OFFSET);
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            for (uint8_t i = 0; i < SPECIAL_CHAR_BYTE_COUNT; i++)
            {
                if (bResult)
                {
                    bResult = SendData(id, SPECIAL_CHAR_LOWER_O[i]);
                    DelayInMillisecond(static_cast<uint32_t>(1UL));
                }
                else
                {
                    break;
                }
            }
        }

        if (bResult)
        {
            bResult = SendCommand(id, SPECIAL_CHAR_BASE_ADDRESS + LOWER_G_OFFSET);
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            for (uint8_t i = 0; i < SPECIAL_CHAR_BYTE_COUNT; i++)
            {
                if (bResult)
                {
                    bResult = SendData(id, SPECIAL_CHAR_LOWER_G[i]);
                    DelayInMillisecond(static_cast<uint32_t>(1UL));
                }
                else
                {
                    break;
                }
            }
        }

        if (bResult)
        {
            bResult = SendCommand(id, SPECIAL_CHAR_BASE_ADDRESS + LOWER_C_OFFSET);
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            for (uint8_t i = 0; i < SPECIAL_CHAR_BYTE_COUNT; i++)
            {
                if (bResult)
                {
                    bResult = SendData(id, SPECIAL_CHAR_LOWER_C[i]);
                    DelayInMillisecond(static_cast<uint32_t>(1UL));
                }
                else
                {
                    break;
                }
            }
        }

        if (bResult)
        {
            bResult = SendCommand(id, SPECIAL_CHAR_BASE_ADDRESS + UPPER_O_OFFSET);
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            for (uint8_t i = 0; i < SPECIAL_CHAR_BYTE_COUNT; i++)
            {
                if (bResult)
                {
                    bResult = SendData(id, SPECIAL_CHAR_UPPER_O[i]);
                    DelayInMillisecond(static_cast<uint32_t>(1UL));
                }
                else
                {
                    break;
                }
            }
        }

        return bResult;
    }

    Lcd::Lcd(const uint8_t id) : 
        m_ID ( id ),
        m_bMultiLinesUsed ( false )
    {
    }

    Lcd::~Lcd()
    {
    }

    bool Lcd::Initialize(const bool bMultiLinesUsed)
    {
        bool bResult = true;
        // 4 bits init
        DelayInMillisecond(static_cast<uint32_t>(70UL));
        bResult = SendCommand(m_ID, 0x30U);
        if (bResult)
        {
            DelayInMillisecond(static_cast<uint32_t>(5UL));
            bResult = SendCommand(m_ID, 0x30U);
        }
        if (bResult)
        {
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            bResult = SendCommand(m_ID, 0x30U);
        }
        if (bResult)
        {
            DelayInMillisecond(static_cast<uint32_t>(10UL));
            bResult = SendCommand(m_ID, 0x20U);
        }
        if (bResult)
        {
            DelayInMillisecond(static_cast<uint32_t>(10UL));
            if (bMultiLinesUsed)
            {
                bResult = SendCommand(m_ID, 0x28U);
            }
            else
            {
                bResult = SendCommand(m_ID, 0x20U);
            }
            if (bResult)
            {
                m_bMultiLinesUsed = bMultiLinesUsed;
            }
        }
        if (bResult)
        {
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            constexpr uint8_t DISPLAY_OFF_COMMAND = 0x08U;
            bResult = SendCommand(m_ID, DISPLAY_OFF_COMMAND);
        }
        if (bResult)
        {
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            bResult = SendCommand(m_ID, CLEAR_SCREEN_COMMAND);
        }

        if (bResult)
        {
            constexpr uint8_t INCREMENT_CURSOR_NO_SHIFT_COMMAND = 0x06U;
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            bResult = SendCommand(m_ID, INCREMENT_CURSOR_NO_SHIFT_COMMAND);
        }
        if (bResult)
        {
            constexpr uint8_t DISPLAY_ON_CURSOR_NO_BLINK_COMMAND = 0x0CU;
            DelayInMillisecond(static_cast<uint32_t>(3UL));
            bResult = SendCommand(m_ID, DISPLAY_ON_CURSOR_NO_BLINK_COMMAND);
        }

        if (bResult)
        {
            bResult = RegisterSpecialCharsForLcd(m_ID);
            DelayInMillisecond(static_cast<uint32_t>(3UL));
        }

        if (bResult)
        {
            MoveCursor(0U, 0U);
        }

        return bResult;
    }

    void Lcd::Print(const String80 &str)
    {
        for (uint32_t i = static_cast<uint32_t>(0UL); i < str.GetSize(); i++)
        {
            (void) SendData(m_ID, str.Get(i));
            DelayInMillisecond(static_cast<uint32_t>(1UL));
        }
    }

    void Lcd::Print(const String80 &&str)
    {
        for (uint32_t i = static_cast<uint32_t>(0UL); i < str.GetSize(); i++)
        {
            (void) SendData(m_ID, str.Get(i));
            DelayInMillisecond(static_cast<uint32_t>(1UL));
        }
    }

    void Lcd::Print(const uint8_t specialChar)
    {
        (void) SendData(m_ID, specialChar);
        DelayInMillisecond(static_cast<uint32_t>(1UL));
    }

    void Lcd::MoveCursor(const uint8_t lineNumber, const uint8_t column)
    {
        const uint8_t columnPart = static_cast<uint8_t>(column & static_cast<uint8_t>(0x0FU));
        switch (lineNumber)
        {
        case 0U:
        {
            const uint8_t command = 0x80U + columnPart;
            (void) SendCommand(m_ID, command);
            DelayInMillisecond(static_cast<uint32_t>(1UL));
            break;
        }

        case 1U:
        {
            if (m_bMultiLinesUsed)
            {
                const uint8_t command = 0xC0U + columnPart;
                (void) SendCommand(m_ID, command);
                DelayInMillisecond(static_cast<uint32_t>(1UL));
            }
            else
            {
                (void) SendCommand(m_ID, 0x8FU);
                DelayInMillisecond(static_cast<uint32_t>(1UL));
                const uint8_t restShiftSize = 5U + column;
                for (uint8_t i = 0U; i < restShiftSize; i++)
                {
                    constexpr uint8_t SET_CURSOR_TO_NEXT_CHAR_COMMAND = 0x14U;
                    (void) SendCommand(m_ID, SET_CURSOR_TO_NEXT_CHAR_COMMAND);
                    DelayInMillisecond(static_cast<uint32_t>(1UL));
                }
            }
            break;
        }

        case 2U:
        {
            if (m_bMultiLinesUsed)
            {
                (void) SendCommand(m_ID, 0x8FU);
                DelayInMillisecond(static_cast<uint32_t>(1UL));
                const uint8_t restShiftSize = 5U + column;
                for (uint8_t i = 0U; i < restShiftSize; i++)
                {
                    constexpr uint8_t SET_CURSOR_TO_NEXT_CHAR_COMMAND = 0x14U;
                    (void) SendCommand(m_ID, SET_CURSOR_TO_NEXT_CHAR_COMMAND);
                    DelayInMillisecond(static_cast<uint32_t>(1UL));
                }
            }
            break;
        }

        case 3U:
        {
            if (m_bMultiLinesUsed)
            {
                (void) SendCommand(m_ID, 0xCFU);
                DelayInMillisecond(static_cast<uint32_t>(1UL));
                const uint8_t restShiftSize = 5U + column;
                for (uint8_t i = 0U; i < restShiftSize; i++)
                {
                    constexpr uint8_t SET_CURSOR_TO_NEXT_CHAR_COMMAND = 0x14U;
                    (void) SendCommand(m_ID, SET_CURSOR_TO_NEXT_CHAR_COMMAND);
                    DelayInMillisecond(static_cast<uint32_t>(1UL));
                }
                break;
            }
        }
        
        default:
            break;
        }
    }

    void Lcd::Clear(void)
    {
        (void) SendCommand(m_ID, CLEAR_SCREEN_COMMAND);
        DelayInMillisecond(static_cast<uint32_t>(2U));
    }
    
} // namespace TC2004
