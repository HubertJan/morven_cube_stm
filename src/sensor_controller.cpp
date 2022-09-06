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




  
class SensorController
{
public:
    OneWire oneWire = OneWire(15);
    DallasTemperature TempSensors = DallasTemperature(&oneWire);
    
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
        
        TempSensors.begin();
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
        values[3] = (getAverage(STV_PIN)-0) * (45 / 3520.0);
        values[4] = getAverage(ServoVoltagePIN) * (5.0 / 3970.0);
        values[5] = getAverage(twelveV_PIN) * (12 / 3885.0);
        TempSensors.requestTemperatures();
        values[0] = TempSensors.getTempCByIndex(0);
        values[1] = TempSensors.getTempCByIndex(1);
        values[2] = TempSensors.getTempCByIndex(2);
        
    }


};
