#ifndef SHT3X_CRCUTILS_H
#define SHT3X_CRCUTILS_H
#include "SHT3X/ShtBuffer.h"
namespace SHT3X
{
    class CrcUtils
    {
    public:
        static uint8_t CalculateNrsc5Crc(const ShtBuffer &buffer, const uint32_t crcStartIndex, const uint32_t crcSize);
    };
} // namespace SHT3X

#endif // SHT3X_CRCUTILS_H