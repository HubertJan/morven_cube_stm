#include <Arduino.h>
#include <AccelStepper.h>
#include <Servo.h>
#include <WS2812B.h>

#define NUM_LEDS 30


/*AccelStepper stD(1, 0, 6); // STEP, DIR
AccelStepper stR(1, 1, 7); // STEP, DIR
AccelStepper stF(1, 2, 8); // STEP, DIR
AccelStepper stL(1, 3, 9); // STEP, DIR
AccelStepper stB(1, 4, 10); // STEP, DIR
AccelStepper stU(1, 5, 11); // STEP, DIR
*/

#define stepperAcceleration 10000 //Limit 60000
#define stepperMaxSpeed 2500
#define stepperspeed 2500

#define endStopPin PB13


class MotorController
{
public:
    WS2812B strip = WS2812B(NUM_LEDS);
    AccelStepper Stepper1 = AccelStepper(1,PB5,PB4); // STEP, DIR
    Servo Servo1;
    Servo Servo2;
    Servo Servo3;
    Servo Servo4;
    Servo Servo5;
    Servo Servo6;
    Servo webcamServo;
    void runMotors()
    {
    }
    //void MotorsOn
    MotorController()
    {
        strip.begin();// Sets up the SPI
        strip.show();// Clears the strip, as by default the strip data is set to all LED's off.
        strip.setBrightness(128);
        Stepper1.setAcceleration(stepperAcceleration); //set acceleration (steps/second^2) VERMUTLICH IDEAL Ac: 8000 MaxSpeed: 3000 Speed: 1100
        Stepper1.setMaxSpeed(stepperMaxSpeed); //set max speed the motor will turn (steps/second)  
         Stepper1.setSpeed(stepperspeed);
        
        Servo1.attach(PA10);
        Servo2.attach(PA3);
        Servo3.attach(PA2);
        Servo4.attach(PA1);
        Servo5.attach(PA8);
        Servo6.attach(PB9);
        webcamServo.attach(PB8);
        webcamServo.write(49);
        
        pinMode(endStopPin, INPUT);
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

    bool ExecuteInstruction(String instruction)
    {      
      Serial.println("JETZT FUNC");
      Serial.println(instruction);
        if (instruction == "\"OP\"")
        {
            webcamServo.write(180);
            MoveStepperTop();
        }
        else if (instruction == "\"CL\"")
        {
            HomeStepper();
            webcamServo.write(49);
        }
        else if (instruction == "\"KA\"")
        {
          webcamServo.write(100);
        }
        else if (instruction == "\"BL\"")
        {
          Serial.println("JETZT BL");
          strip.setBrightness(255);
          FrontToArmsColor(strip.Color(0,0,255));
        }
        else if (instruction == "\"WH\"")
        {
          strip.setBrightness(128);
          FrontToArmsColor(strip.Color(255,255,255));
        }
        else if (instruction == "\"OF\"")
        {
          FrontToArmsColor(strip.Color(0,0,0));
          FrontToArmsColor(strip.Color(0,0,0));
        }
        else if (instruction == "\"TO\"")
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
        else if (instruction == "\"AB\"")
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
            delay(400);
            Servo1.detach();
            Servo2.detach();
            Servo3.detach();
            Servo4.detach();
            Servo5.detach();
            Servo6.detach();
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
    void FrontToArmsColor(uint32_t c){
      for(uint16_t i=0; i<strip.numPixels(); i++) 
      {
          strip.setPixelColor(i, strip.Color(0,0, 0));
      }
      for(uint16_t i=4; i<12; i++) 
      {
          strip.setPixelColor(i, c);
      }
      for(uint16_t i=14; i<16; i++) 
      {
          strip.setPixelColor(i, c);
      }
      strip.show();
    }
    
    
    void HomeStepper(){      
      digitalWrite(PB3, LOW);
    
      Stepper1.move(-50000);
      while(digitalRead(endStopPin) == LOW){
        Stepper1.run();
      }
      Stepper1.stop();  
      Serial.println("Endschalter erreicht");
      digitalWrite(PB3, HIGH);
    }
    void MoveStepperTop(){
      digitalWrite(PB3, LOW);
      Stepper1.move(18300);//Top Position 20000, mittlere: 17000
      Serial.println("Erster");
      Stepper1.runToPosition();
      Serial.println("Andere Seite erreicht");
      digitalWrite(PB3, HIGH);
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
