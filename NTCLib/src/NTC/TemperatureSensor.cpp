#include "NTC/TemperatureSensor.h"
#include <cmath>

namespace NTC
{
    void StartAdc(const uint8_t id);
    uint32_t ReadAdc(const uint8_t id);

    TemperatureSensor::TemperatureSensor(const uint8_t id) : 
        m_ID ( id )
    {
    }

    TemperatureSensor::~TemperatureSensor()
    {
    }

    void TemperatureSensor::Initialize(
        const double pullDownResistorInkOhm,
        const double coeffA,
        const double coeffB,
        const double coeffC)
    {
        StartAdc(m_ID);
        m_PullDownResistorInOhm = pullDownResistorInkOhm * 1000.0;
        m_CoeffA = coeffA;
        m_CoeffB = coeffB;
        m_CoeffC = coeffC;
        m_TermistorConstant = 4095.0 * m_PullDownResistorInOhm;
    }


    void TemperatureSensor::Initialize(
        const double pullDownResistorInkOhm
        // coeffA = 0.8270233505e-3,
        // coeffB = 2.088130425e-4,
        // coeffC = 0.8056639038e-7,
    )
    {
        Initialize(pullDownResistorInkOhm, 0.8270233505e-3, 2.088130425e-4, 0.8056639038e-7);
    }


    bool TemperatureSensor::Read(double &temperatureInCelcius)
    {
        bool bResult = false;
        const uint32_t adcValue =  ReadAdc(m_ID);
        if (adcValue > static_cast<uint32_t>(0UL))
        {
            static constexpr double KELVIN_TO_CELCIUS_CONSTANT = 273.15;
            bResult = true;
            const double resistanceInOhm = (m_TermistorConstant / static_cast<double>(adcValue)) - m_PullDownResistorInOhm;
            const double temperatureCoeff = log(resistanceInOhm);
            temperatureInCelcius = (1.0 / (m_CoeffA + (m_CoeffB + (m_CoeffC * temperatureCoeff * temperatureCoeff)) * temperatureCoeff)) - KELVIN_TO_CELCIUS_CONSTANT;
        }
        return bResult;
    }

} // namespace NTC
