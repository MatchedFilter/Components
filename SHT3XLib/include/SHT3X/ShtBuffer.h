#ifndef SHT3X_SHTBUFFER_H
#define SHT3X_SHTBUFFER_H
#include <cinttypes>
namespace SHT3X
{
    struct ShtBuffer
    {
    public:
        static const uint32_t MAX_SHT_BUFFER_SIZE = static_cast<uint32_t>(16UL);
        uint8_t m_Buffer[MAX_SHT_BUFFER_SIZE];
        uint32_t m_Size;
    
    public:
        void Reset();
    };
} // namespace SHT3X

#endif // SHT3X_SHTBUFFER_H