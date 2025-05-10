#ifndef TC2004_LCD_H
#define TC2004_LCD_H
#include "String80.h"
namespace TC2004
{
    constexpr uint8_t TC2004_CHAR_LOWER_I = 0x00U;
    constexpr uint8_t TC2004_CHAR_LOWER_U = 0x01U;
    constexpr uint8_t TC2004_CHAR_LOWER_O = 0x02U;
    constexpr uint8_t TC2004_CHAR_LOWER_G = 0x03U;
    constexpr uint8_t TC2004_CHAR_LOWER_C = 0x04U;
    constexpr uint8_t TC2004_CHAR_UPPER_O = 0x05U;
    constexpr uint8_t TC2004_CHAR_DEGREE_SYMBOL = 0xDFU;
    constexpr uint8_t TC2004_CHAR_ARROW_SYMBOL = 0x7EU;

    /**
     * @brief TC2004 LCD module Library. In order to use it following methods must be implemented
     * void TC2004::DelayInMillisecond(const uint32_t durationInMillisecond);
     * bool TC2004::SendCommand(const uint8_t id, const uint8_t command); // sends data to TC2004 for more information look at the TC2004 datasheet
     * bool TC2004::SendData(const uint8_t id, const uint8_t data); // sends command to TC2004 for more information look at the TC2004 datasheet
     */
    class Lcd
    {
    public:
        Lcd(const uint8_t id);
        ~Lcd();
        bool Initialize(const bool bMultiLinesUsed);
        void Print(const String80 &str) const ;
        void Print(const String80 &&str) const ;
        void Print(const uint8_t specialChar) const;
        void MoveCursor(const uint8_t lineNumber, const uint8_t column) const;
        void Clear(void) const;

    private:
        const uint8_t m_ID;
        bool m_bMultiLinesUsed;
        
    };
} // namespace TC2004

#endif // TC2004_LCD_H