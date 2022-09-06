#include <Arduino.h>

struct MotorSetting
{
    int acc50;
    int acc100;
    int cc50;
    int cc100;
    int maxSp;
};

class ArduinoClient
{
public:
    virtual void SetSensorMode() = 0;
    virtual void ChangeLights(String instruction) = 0;
    virtual void ChangeMotor(String instruction) = 0;
};

class PCConnector
{
public:
    PCConnector(int b, ArduinoClient *ard)
    {
        arduino = ard;
        baud = b;
        Serial.begin(115200);
        bool stop = false;
        while(!stop){
          Serial.println("TRY");
          delay(100);
          char inChar = (char)Serial.read();
          if (inChar == '\n')
            {
                stop = true;
            }
        }
        Serial.println("Started");
    }
    void Update()
    {
        String commandLine = ReceiveCommandLine();
        if (commandLine != "")
        {
            String command[2];
            SeparateCommandLine(commandLine, command);
            HandleCommand(command);
        }
    }

    void SendSensor(String temp1, String temp2, String temp3, String volt1, String volt2, String volt3)
    {
        Serial.println("data;" + DataToString("t1", temp1) + DataToString("t2", temp2) + DataToString("t3", temp3) + DataToString("v1", volt1) + DataToString("v2", volt2) + DataToString("v3", volt3));
    }

    void DebugPrint(String msg)
    {
        //Serial.println("debug;" + msg);
        //delay(100);
    }

private:
    int baud = 0;
    ArduinoClient *arduino;

    String DataToString(String name, String value)
    {
        return name + "=" + value + ";";
    }

    void SetSensor(String _)
    {
        arduino->SetSensorMode();
        Serial.println("response;");
        
        delay(100);
    }

    void ChangeLights(String inst)
    {
      Serial.println("pc");
        arduino->ChangeLights(inst);
        Serial.println("response;");
        delay(100);
    }

    void ChangeMotor(String inst)
    {
        Serial.println("response;");
        arduino->ChangeMotor(inst);
        Serial.println("response;");
        delay(100);
    }



    int CountArguments(String inp)
    {
        int symbols = CountCharacter(inp, '"');
        int counter = symbols / 2;

        return counter;
    }

    int CountCharacter(String inp, char character)
    {
        int counter = 0;
        int charIndex = 0;
        bool finished = false;
        DebugPrint(": " + String(inp) + " ;");
        while (finished == false)
        {
            charIndex = inp.indexOf(character, charIndex);
            DebugPrint(": " + String(charIndex) + " ;");
            if (charIndex != -1)
            {
                counter += 1;
                charIndex += 1;
            }
            else
            {
                finished = true;
            }
        }

        return counter;
    }

    void ArgsToArray(String args, int numberOfArgs, String *resultArray)
    {
        int arrayIndex = 0;
        int stringIndex = 0;
        int firstQuoteMark = -1;
        int secondQuoteMark = -1;
        while (arrayIndex < numberOfArgs)
        {
            if (firstQuoteMark == -1)
            {
                firstQuoteMark = args.indexOf("\"", stringIndex);
                stringIndex = firstQuoteMark + 1;
            }
            else
            {
                secondQuoteMark = args.indexOf("\"", stringIndex);
                stringIndex = secondQuoteMark + 1;
                resultArray[arrayIndex] = args.substring(firstQuoteMark + 1, secondQuoteMark);
                firstQuoteMark = -1;
                secondQuoteMark = -1;
                arrayIndex += 1;
            }
        }
    }

    typedef void (PCConnector::*CommandHandler)(const String);
    const String cdKeywords[3] = {
        "sensor",
        "motor",
    };
    const CommandHandler cdFunctions[3] = {
        &PCConnector::SetSensor,
        &PCConnector::ChangeLights,
    };

    String receivedString = "";
    bool stringComplete = false;

    void SeparateCommandLine(String cdLine, String *resultCd)
    {
        int argumentPosition = cdLine.indexOf(" ");
        String commandWord;
        String argumentLine;
        if (argumentPosition == -1)
        {
            commandWord = cdLine;
        }
        else
        {
            commandWord = cdLine.substring(0, argumentPosition);
            argumentLine = cdLine.substring(argumentPosition + 1);
        }
        resultCd[0] = commandWord;
        resultCd[1] = argumentLine;
    }

    String ReceiveCommandLine()
    {

        while (Serial.available())
        {
            char inChar = (char)Serial.read();
            if (inChar == '\n')
            {
                DebugPrint(receivedString);
                String commandLine = receivedString;
                receivedString = "";
                return commandLine; //commandLine;
            }
            else
            {
                receivedString += inChar;
            }
        }
        return "";
    }

    void HandleCommand(const String command[2])
    {
        for (int i = 0; i < 2; i++)
        {
            if (cdKeywords[i] == command[0])
            {
                (*this.*cdFunctions[i])(command[1]);
            }
        }
    }
};
