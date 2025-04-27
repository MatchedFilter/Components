#include "SHT3X/SHT31Sensor.h"
#include "CrcUtils.h"

namespace SHT3X
{
    bool ReadFromI2C(const uint8_t id, const uint16_t deviceAddress, const uint16_t addressToRead, ShtBuffer &buffer, const uint16_t size);
    SHT31Sensor::SHT31Sensor(const uint8_t id) : 
        m_ID ( id ),
        m_I2CDeviceAddress ( static_cast<uint16_t>(0x44U << 1U) )
    {
    }

    SHT31Sensor::~SHT31Sensor()
    {
    }

    void SHT31Sensor::Initialize(bool addrPinState)
    {
        if (true == addrPinState)
        {
            m_I2CDeviceAddress = static_cast<uint16_t>(0x45U << 1U);
        }
    }

    void SHT31Sensor::Initialize(void)
    {
        Initialize(false);
    }


    bool SHT31Sensor::Read(double &temperatureInCelcius, double &humidityInPercentage)
    {
        bool bResult = false;
        ShtBuffer buffer;
        buffer.Reset();
        static constexpr uint16_t HIGH_REPEATIBILITY_NO_CLOCK_STRETCHING = static_cast<uint16_t>(0x2400U);
        constexpr uint16_t TEMPERATURE_DATA_SIZE = static_cast<uint16_t>(6U);
        
        if (ReadFromI2C(m_ID, m_I2CDeviceAddress, HIGH_REPEATIBILITY_NO_CLOCK_STRETCHING, buffer, TEMPERATURE_DATA_SIZE))
        {
            constexpr uint32_t TEMPERATURE_CRC_START_INDEX = static_cast<uint32_t>(0UL);
            constexpr uint32_t TEMPERATURE_CRC_INDEX = static_cast<uint32_t>(2UL);
            constexpr uint32_t CRC_SIZE = static_cast<uint32_t>(2UL);
            const uint8_t temperatureCrc = CrcUtils::CalculateNrsc5Crc(buffer, TEMPERATURE_CRC_START_INDEX, CRC_SIZE);
            if (temperatureCrc == buffer.m_Buffer[TEMPERATURE_CRC_INDEX])
            {
                constexpr uint32_t HUMIDITY_CRC_START_INDEX = static_cast<uint32_t>(3UL);
                constexpr uint32_t HUMIDITY_CRC_INDEX = static_cast<uint32_t>(5UL);
                const uint8_t humidityCrc = CrcUtils::CalculateNrsc5Crc(buffer, HUMIDITY_CRC_START_INDEX, CRC_SIZE);
                if (humidityCrc == buffer.m_Buffer[HUMIDITY_CRC_INDEX]) 
                {
                    bResult = true;
                    constexpr  double DIVISION_CONSTANT = static_cast<double>(0xFFFFU) - static_cast<double>(1U);
                    const uint16_t rawTemperature = static_cast<uint16_t>(static_cast<uint16_t>(buffer.m_Buffer[0] << static_cast<uint16_t>(8U)) | static_cast<uint16_t>(buffer.m_Buffer[1]));
                    const double rawTemperatureInDouble = static_cast<double>(rawTemperature);
                    temperatureInCelcius = -45.0 + (175 * (rawTemperatureInDouble / DIVISION_CONSTANT));
        
                    const uint16_t rawHumidity = static_cast<uint16_t>(static_cast<uint16_t>(buffer.m_Buffer[3] << static_cast<uint16_t>(8U)) | static_cast<uint16_t>(buffer.m_Buffer[4]));
                    const double rawHumidityInDouble = static_cast<double>(rawHumidity);
                    humidityInPercentage = 100.0 * (rawHumidityInDouble / DIVISION_CONSTANT);
                }
            }
        }
        return bResult;
    }
} // namespace SHT3X
