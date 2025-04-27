#ifndef TC2004_STRING80_H
#define TC2004_STRING80_H
#include <cinttypes>
namespace TC2004
{
    static constexpr uint32_t MAX_STRING80_SIZE = static_cast<uint32_t>(80UL);

    class String80
    {
    public:
        String80();
        template <uint32_t SIZE>
        explicit String80(const char (&str)[SIZE]);

        ~String80();
        void Clear();
        void Copy(const String80 &other);
        char Get(const uint32_t index) const { return index < MAX_STRING80_SIZE ? static_cast<char>(m_Buffer[index]) : static_cast<char>(0); }
        uint32_t GetSize() const  { return m_Size; }

        template <uint32_t SIZE>
        String80 operator+=(const char (&str)[SIZE]);
        String80 operator+=(const String80 &other);
        String80 operator+=(const int32_t i32);
        
        String80 operator+(const String80 &other);
        String80 operator+(const int32_t i32);

        template<uint32_t SIZE>
        void operator=(const char (&str)[SIZE]);


    private:
        uint8_t m_Buffer[MAX_STRING80_SIZE + static_cast<uint32_t>(sizeof('\0'))];
        uint32_t m_Size;
    };

    template <uint32_t SIZE>
    String80::String80(const char (&str)[SIZE])
    {
        *this = str;
    }


    template <uint32_t SIZE>
    String80 String80::operator+=(const char (&str)[SIZE])
    {
        if (SIZE > static_cast<uint32_t>(0UL))
        {
            uint32_t sizeToAdd = SIZE;
            uint32_t LAST_INDEX = SIZE - static_cast<uint32_t>(1UL);
            if (str[LAST_INDEX] == static_cast<char>(0x00))
            {
                sizeToAdd = LAST_INDEX;
            }
            for (uint32_t i = static_cast<uint32_t>(0UL); i < sizeToAdd; i++)
            {
                if (m_Size < MAX_STRING80_SIZE)
                {
                    m_Buffer[m_Size] = str[i];
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

    template<uint32_t SIZE>
    void String80::operator=(const char (&str)[SIZE])
    {
        Clear();
        if (SIZE > static_cast<uint32_t>(0UL))
        {
            m_Size = SIZE;
            if (m_Size > MAX_STRING80_SIZE)
            {
                m_Size = MAX_STRING80_SIZE;
            }
            else
            {
                const uint32_t lastIndex = m_Size - static_cast<uint32_t>(1UL);
                if (str[lastIndex] == static_cast<uint8_t>('\0'))
                {
                    m_Size--;
                }
            }
            for (uint32_t i = static_cast<uint32_t>(0UL); i < m_Size; i++)
            {
                m_Buffer[i] = str[i];
            }
        }
    }


} // namespace TC2004

#endif // TC2004_STRING80_H