#include "DHT11/DHT11Sensor.h"
#include "DHT11/DHT11Dependencies.h"
namespace DHT11
{
    static constexpr uint8_t HIGH_VALUE = 0x01U;
    static constexpr uint8_t LOW_VALUE = 0x00U;

    constexpr uint32_t MIN_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS = static_cast<uint32_t>(0UL);
    constexpr uint32_t MAX_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS = static_cast<uint32_t>(500UL);

    DHT11Sensor::DHT11Sensor(const uint8_t id) : 
        m_ID ( id )
    {
    }

    DHT11Sensor::~DHT11Sensor()
    {
    }

    static bool WaitForGivenOutputToChange(const uint8_t id, const uint8_t outputValue, const uint32_t minimumTimeDurationInMicroseconds, const uint32_t maximumTimeDurationInMicroseconds, uint32_t *durationInMicroseconds);
    static bool InitializeForReading(const uint8_t id);
    static bool ReadTemperatureAndHumidity(const uint8_t id, double &temperatureInCelcius, double &humidityInPercentage);

    static bool WaitForGivenOutputToChange(const uint8_t id, const uint8_t outputValue, const uint32_t minimumTimeDurationInMicroseconds, const uint32_t maximumTimeDurationInMicroseconds, uint32_t *durationInMicroseconds)
    {
        constexpr uint32_t MAX_LOOP_COUNT = static_cast<uint32_t>(1000000000UL);
        constexpr uint32_t MAX_LOOP_DURATION_IN_MICROSECOND = 512;
        bool bResult = false;
        ResetTimer(id);
        for (uint32_t i = static_cast<uint32_t>(0UL); i < MAX_LOOP_COUNT; i++)
        {
            const uint32_t totalDurationInMicrosecond = GetTimestampInMicrosecondFromTimer(id);

            bool bBreakCondition = true;
            if (totalDurationInMicrosecond < MAX_LOOP_DURATION_IN_MICROSECOND)
            {
                if (ReadDataPin(id) != outputValue)
                {
                    if ((totalDurationInMicrosecond >= minimumTimeDurationInMicroseconds) && (totalDurationInMicrosecond <= maximumTimeDurationInMicroseconds))
                    {
                        bResult = true;
                    }
                    if (durationInMicroseconds != nullptr)
                    {
                        *durationInMicroseconds = totalDurationInMicrosecond;
                    }
                }
                else
                {
                    bBreakCondition = false;
                }
            }
            if (bBreakCondition)
            {
                break;
            }
        }
        return bResult;
    }

    static bool InitializeForReading(const uint8_t id)
    {
        constexpr uint32_t INITIALIZATION_HIGH_TIMEOUT_IN_MILLISECOND = static_cast<uint32_t>(5UL);
        constexpr uint32_t INITIALIZATION_LOW_TIMEOUT_IN_MILLISECOND = static_cast<uint32_t>(20UL);
        constexpr uint32_t INITIALIZATION_MIN_OUTPUT_TIME_IN_MICROSECONDS = static_cast<uint32_t>(72UL);
        constexpr uint32_t INITIALIZATION_MAX_OUTPUT_TIME_IN_MICROSECONDS = static_cast<uint32_t>(88UL);
        
        bool bResult = false;
        SetDataPinAsOutput(id);
        // SetDataPinAsHigh(id);
        DelayInMillisecond(INITIALIZATION_HIGH_TIMEOUT_IN_MILLISECOND);
        SetDataPinAsLow(id);
        DelayInMillisecond(INITIALIZATION_LOW_TIMEOUT_IN_MILLISECOND);
        SetDataPinAsInput(id);

        if (WaitForGivenOutputToChange(id, HIGH_VALUE, MIN_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, MAX_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, nullptr))
        {
            if (WaitForGivenOutputToChange(id, LOW_VALUE, INITIALIZATION_MIN_OUTPUT_TIME_IN_MICROSECONDS, INITIALIZATION_MAX_OUTPUT_TIME_IN_MICROSECONDS, nullptr))
            {
                if (WaitForGivenOutputToChange(id, HIGH_VALUE, INITIALIZATION_MIN_OUTPUT_TIME_IN_MICROSECONDS, INITIALIZATION_MAX_OUTPUT_TIME_IN_MICROSECONDS, nullptr))
                {
                    bResult = true;
                }
            }
        }

        return bResult;
    }

    static bool ReadTemperatureAndHumidity(const uint8_t id, double &temperatureInCelcius, double &humidityInPercentage)
    {
        constexpr uint32_t DATA_SIZE = static_cast<uint32_t>(40UL);

        bool bResult = false;
        uint8_t data[DATA_SIZE] = { 0 };
        bool bIsDataRead = true;
        for (uint32_t i = static_cast<uint32_t>(0UL); i < DATA_SIZE; i++)
        {
            constexpr uint32_t INPUT_LOW_DATA_MAX_DURATION_IN_MICROSECOND = static_cast<uint32_t>(32UL);
            constexpr uint32_t INPUT_HIGH_DATA_MAX_DURATION_IN_MICROSECOND = static_cast<uint32_t>(80UL);
            if (false == WaitForGivenOutputToChange(id, LOW_VALUE, MIN_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, MAX_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, nullptr))
            {
                bIsDataRead = false;
                break;
            }
            uint32_t durationInMicroSeconds;
            if (false == WaitForGivenOutputToChange(id, HIGH_VALUE, MIN_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, MAX_WAIT_TIME_FOR_OUTPUT_IN_MICROSECONDS, &durationInMicroSeconds))
            {
                bIsDataRead = false;
                break;
            }
            if (durationInMicroSeconds < INPUT_LOW_DATA_MAX_DURATION_IN_MICROSECOND)
            {
                data[i] = LOW_VALUE;
            }
            else if (durationInMicroSeconds < INPUT_HIGH_DATA_MAX_DURATION_IN_MICROSECOND)
            {
                data[i] = HIGH_VALUE;
            }
            else
            {
                bIsDataRead = false;
                break;
            }
        }

        if (bIsDataRead)
        {
            constexpr uint32_t ONE_BYTE_INDEX_OFFSET = static_cast<uint32_t>(7UL);

            constexpr uint32_t HUMIDITY_HIGH_START_BIT = static_cast<uint32_t>(0UL);
            constexpr uint32_t HUMIDITY_HIGH_END_BIT = static_cast<uint32_t>(8UL);
            constexpr uint32_t HUMIDITY_LOW_START_BIT = HUMIDITY_HIGH_END_BIT;
            constexpr uint32_t HUMIDITY_LOW_END_BIT = static_cast<uint32_t>(16UL);

            constexpr uint32_t TEMPERATURE_HIGH_START_BIT = static_cast<uint32_t>(16UL);
            constexpr uint32_t TEMPERATURE_HIGH_END_BIT = static_cast<uint32_t>(24UL);
            constexpr uint32_t TEMPERATURE_LOW_START_BIT = TEMPERATURE_HIGH_END_BIT;
            constexpr uint32_t TEMPERATURE_LOW_END_BIT = static_cast<uint32_t>(32UL);

            constexpr uint32_t PARITY_START_BIT = static_cast<uint32_t>(32UL);
            constexpr uint32_t PARITY_END_BIT = static_cast<uint32_t>(40UL);

            uint8_t crcData[4] = { 0U };
            int8_t humidityHighData = static_cast<int8_t>(0);
            for (uint32_t i = HUMIDITY_HIGH_START_BIT; i < HUMIDITY_HIGH_END_BIT; i++)
            {
                humidityHighData |= static_cast<int8_t>(data[i] << (ONE_BYTE_INDEX_OFFSET - (i - HUMIDITY_HIGH_START_BIT)));
                crcData[0] |= static_cast<uint8_t>(data[i] << (ONE_BYTE_INDEX_OFFSET - (i - HUMIDITY_HIGH_START_BIT)));
            }
    
            uint8_t humidityLowData = static_cast<int8_t>(0);
            for (uint32_t i = HUMIDITY_LOW_START_BIT; i < HUMIDITY_LOW_END_BIT; i++)
            {
                humidityLowData |= static_cast<int8_t>(data[i] << (ONE_BYTE_INDEX_OFFSET - (i - HUMIDITY_LOW_START_BIT)));
                crcData[1] |= static_cast<uint8_t>(data[i] << (ONE_BYTE_INDEX_OFFSET - (i - HUMIDITY_LOW_START_BIT)));
            }
    
            int8_t temperatureHighData = static_cast<int8_t>(0);
            for (uint32_t i = TEMPERATURE_HIGH_START_BIT; i < TEMPERATURE_HIGH_END_BIT; i++)
            {
                temperatureHighData |= static_cast<int8_t>(data[i] << (ONE_BYTE_INDEX_OFFSET - (i - TEMPERATURE_HIGH_START_BIT)));
                crcData[2] |= static_cast<uint8_t>(data[i] << (ONE_BYTE_INDEX_OFFSET - (i - TEMPERATURE_HIGH_START_BIT)));
            }
    
            uint8_t temperatureLowData = static_cast<int8_t>(0);
            for (uint32_t i = TEMPERATURE_LOW_START_BIT; i < TEMPERATURE_LOW_END_BIT; i++)
            {
                temperatureLowData |= (data[i] << (ONE_BYTE_INDEX_OFFSET - (i - TEMPERATURE_LOW_START_BIT)));
                crcData[3] |= static_cast<uint8_t>(data[i] << (ONE_BYTE_INDEX_OFFSET - (i - TEMPERATURE_LOW_START_BIT)));
            }
    
            int16_t crcValue = 0;
            for (uint32_t i = PARITY_START_BIT; i < PARITY_END_BIT; i++)
            {
                crcValue |= (data[i] <<  (ONE_BYTE_INDEX_OFFSET - (i - PARITY_START_BIT)));
            }
    
            const uint8_t calculatedCrc = static_cast<uint8_t>(crcData[0] + crcData[1] + crcData[2] + crcData[3]);
            if (calculatedCrc == crcValue)
            {
                bResult = true;
                humidityInPercentage =  static_cast<double>(humidityHighData) + (static_cast<double>(humidityLowData) / 100.0F); 
                temperatureInCelcius =  static_cast<double>(temperatureHighData) + (static_cast<double>(temperatureLowData) / 100.0F); 
            }
        }
        return bResult;
    }

    bool DHT11Sensor::Read(double &temperatureInCelcius, double &humidityInPercentage)
    {
        bool bResult = false;
        StartTimer(m_ID);
        if ( InitializeForReading(m_ID))
        {
            bResult = ReadTemperatureAndHumidity(m_ID, temperatureInCelcius, humidityInPercentage);
        }
        StopTimer(m_ID);
        return bResult;
    }
} // namespace DHT11
