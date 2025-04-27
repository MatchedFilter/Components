#ifndef DHT11_DHT11SENSOR_H
#define DHT11_DHT11SENSOR_H
#include <cinttypes>
namespace DHT11
{
    class DHT11Sensor
    {
    public:
        DHT11Sensor(const uint8_t id);
        ~DHT11Sensor();
        uint8_t Read(double &temperatureInCelcius, double &humidityInPercentage);

    private:
        const uint8_t m_ID;
    };
} // namespace DHT11

#endif // DHT11_DHT11SENSOR_H