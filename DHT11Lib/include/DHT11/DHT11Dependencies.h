/**
 * @brief This methods must be implemented on the mcu or os side. DHT11 uses this methods
 * The id shall be equal to the given Id of the DHT11Sensor class constructor.
 */

#ifndef DHT11_DHT11DEPENDENCIES_H
#define DHT11_DHT11DEPENDENCIES_H
#include <cinttypes>
namespace DHT11
{
    void StartTimer(const uint8_t id);
    void ResetTimer(const uint8_t id);
    void StopTimer(const uint8_t id);
    uint32_t GetTimestampInMicrosecondFromTimer(const uint8_t id);
    void SetDataPinAsOutput(const uint8_t id);
    void SetDataPinAsLow(const uint8_t id);
    void SetDataPinAsHigh(const uint8_t id);
    void DelayInMillisecond(const uint32_t durationInMillisecond);
    void SetDataPinAsInput(const uint8_t id);
    uint8_t ReadDataPin(const uint8_t id);

} // namespace DHT11

#endif // DHT11_DHT11DEPENDENCIES_H