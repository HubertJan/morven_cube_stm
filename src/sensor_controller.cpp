#include <Arduino.h>
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/*AccelStepper stD(1, 0, 6); // STEP, DIR
AccelStepper stR(1, 1, 7); // STEP, DIR
AccelStepper stF(1, 2, 8); // STEP, DIR
AccelStepper stL(1, 3, 9); // STEP, DIR
AccelStepper stB(1, 4, 10); // STEP, DIR
AccelStepper stU(1, 5, 11); // STEP, DIR
*/

#define STATUS_PIN 3
#define STV_PIN PB1
#define STVAmps_PIN PA5
#define twelveV_PIN PA0
#define ServoVoltagePIN PB0
#define ServoAmpsPIN PA4
#define homeButtonPIN PB13

#define ONE_WIRE_BUS PA15

class SensorController
{
public:
    void runMotors()
    {
    }
    //void MotorsOn
    SensorController()
    {
        pinMode(STV_PIN, INPUT);
        pinMode(STVAmps_PIN, INPUT);
        pinMode(twelveV_PIN, INPUT);
        pinMode(ServoVoltagePIN, INPUT);
        pinMode(ServoAmpsPIN, INPUT);
        pinMode(homeButtonPIN, INPUT);
    }

    float getAverage(int pin)
    {
        int i = 0;
        float valueV = 0;
        while (i < 50)
        {
            i++;
            valueV += analogRead(pin);
        }
        valueV = valueV / 50;
        return valueV;
    }

    void getSensorValues(float *values)
    {
        values[0] = (getAverage(STV_PIN)-0) * (45 / 3520.0))
        values[1] = (getAverage(ServoVoltagePIN) * (5.0 / 3970.0);
        values[2] = getAverage(twelveV_PIN) * (12 / 3885.0);
        sensors.requestTemperatures();
        values[3] = sensors.getTempCByIndex(0);
        values[4] = sensors.getTempCByIndex(1);
        values[5] = sensors.getTempCByIndex(2);
        return values;
    }

private:
    OneWire oneWire(ONE_WIRE_BUS);
    DallasTemperature sensors(&oneWire);
};
