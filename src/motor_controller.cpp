#include <Arduino.h>
#include <AccelStepper.h>
#include <Servo.h>


/*AccelStepper stD(1, 0, 6); // STEP, DIR
AccelStepper stR(1, 1, 7); // STEP, DIR
AccelStepper stF(1, 2, 8); // STEP, DIR
AccelStepper stL(1, 3, 9); // STEP, DIR
AccelStepper stB(1, 4, 10); // STEP, DIR
AccelStepper stU(1, 5, 11); // STEP, DIR
*/

#define stepperAcceleration 42000
#define stepper100Acceleration 43000 //Limit 60000
#define stepperMaxSpeed 4000
#define stepperspeed 4000

#define stepperDelay 0
#define cornerCuttingValue 19
#define cornerCutting100Value 20

class MotorController
{
public:
    Servo Servo1;
    Servo Servo2;
    Servo Servo3;
    Servo Servo4;
    Servo Servo5;
    Servo Servo6;
    Servo Servo7;
    void runMotors()
    {
    }
    //void MotorsOn
    MotorController()
    {
        Servo1.attach(PA10);
        Servo2.attach(PA3);
        Servo3.attach(PA2);
        Servo4.attach(PA1);
        Servo5.attach(PA8);
        Servo6.attach(PB9);
        //Servo7.attach(PB8);
        pinMode(PB3, OUTPUT);
        digitalWrite(PB3, HIGH);
        /*
   * Für altes Board: Servo1.attach(33);
  Servo2.attach(34);
  Servo3.attach(35);
  Servo4.attach(36);
  Servo5.attach(37);
  Servo6.attach(38); */
    }

    bool ExecuteInstruction(char instruction[3])
    {
        if (instruction == "OP")
        {
            Servo6.write(40);
            Servo4.write(0);
            Servo5.write(180);
            delay(150);
            Servo4.detach();
            Servo1.write(120); //öffnen
            //delay(200);
            Servo2.write(90);
            //delay(200);
            Servo3.write(74);
            //delay(200);
            Servo1.detach();
            Servo2.detach();
            Servo3.detach();
            Servo4.detach();
            Servo5.detach();
            Servo6.detach();
        }
        else if (instruction == "CL")
        {
            Servo1.attach(PA10);
            Servo2.attach(PA3);
            Servo3.attach(PA2);
            Servo4.attach(PA1);
            Servo5.attach(PA8);
            Servo6.attach(PB9);

            Servo6.write(108);
            delay(150);
            Servo4.write(45);
            Servo5.write(130);
            delay(300);
            Servo6.write(118);
            delay(200);
            Servo4.write(30); //großen arm mit würfel anheben, damit die anderen besser reinkommen
            Servo5.write(145);
            delay(300);

            Servo1.write(178); //schließen
            //delay(300);
            Servo2.write(149);
            //delay(300);
            Servo3.write(128);
            delay(100);
            Servo4.write(45); //großen Arm wieder senken
            Servo5.write(130);
            delay(200);
            Servo1.write(174); //bisschen zurückfahren, um stillstandstrom zu vermeiden
            Servo2.write(144);
            Servo3.write(123);
        }
        else if (instruction == "BL")
        {
        }
        else if (instruction == "WH")
        {
        }
        else if (instruction == "OF")
        {
        }
        else if (instruction == "TO")
        {
        }
        else if (instruction == "AW")
        {
        }
        // Return: Bool - If instruction is finished, return true. Otherwise false
        //tone(22, 1000); //Testton
        /*         stD.run();
        stR.run();
        stF.run();
        stL.run();
        stB.run();
        stU.run();

       moveMotor(instruction[0], instruction[1]); */
    }
    void ExecuteCubeDoubleInstruction(char instructionA[3], char instructionB[3])
    {
        /*      bool isFinished = false;
        while (isFinished == false)
        {
            bool instr1 = ExecuteCubeInstruction(instructionA);
            bool instr2 = ExecuteCubeInstruction(instructionB);
            if (instr1 && instr2)
            {
                isFinished = true;
            }
        } */
    }
};
