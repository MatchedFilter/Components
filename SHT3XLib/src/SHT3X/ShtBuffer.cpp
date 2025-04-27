#include "SHT3X/ShtBuffer.h"

namespace SHT3X
{
    void ShtBuffer::Reset()
    {
        for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_SHT_BUFFER_SIZE; i++)
        {
            m_Buffer[i] = 0x00U;
        }
        m_Size = static_cast<uint32_t>(0UL);
    }
    
} // namespace SHT3X
