#ifndef SHT3X_SHT31SENSOR_H
#define SHT3X_SHT31SENSOR_H
#include <cinttypes>
namespace SHT3X
{
    class SHT31Sensor
    {
    public:
        SHT31Sensor(const uint8_t id);
        ~SHT31Sensor();
        void Initialize(bool addrPinState);
        void Initialize(void);
        bool Read(double &temperatureInCelcius, double &humidityInPercentage);

    private:
        const uint8_t m_ID;
        uint16_t m_I2CDeviceAddress;
    };
} // namespace SHT3X

#endif // SHT3X_SHT31SENSOR_H