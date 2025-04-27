#ifndef NTC_NTC_H
#define NTC_NTC_H
#include <cinttypes>
namespace NTC
{
    class TemperatureSensor
    {
    public:
        TemperatureSensor(const uint8_t id);
        ~TemperatureSensor();
        void Initialize(
            const double pullDownResistorInkOhm,
            const double coeffA,
            const double coeffB,
            const double coeffC);

            void Initialize(
                const double pullDownResistorInkOhm
                // coeffA = 0.8270233505e-3,
                // coeffB = 2.088130425e-4,
                // coeffC = 0.8056639038e-7,
            );
        bool Read(double &temperatureInCelcius);

    private:
        const uint8_t m_ID;
        double m_PullDownResistorInOhm;
        double m_CoeffA;
        double m_CoeffB;
        double m_CoeffC;

    private:
        double m_TermistorConstant;
    };
} // namespace NTC

#endif // NTC_NTC_H