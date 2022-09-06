#include "pc_connector.cpp"
#include "motor_controller.cpp"
#include "sensor_controller.cpp"

class Magic : ArduinoClient
{
public:
    Magic() = delete;
    Magic(int baudRate)
    {
        connector = new PCConnector(baudRate, this);
        motorController = new MotorController();
        sensorController = new SensorController();
    }
    void Update()
    {
        connector->Update();
        motorController->runMotors();
        if(statusCode == STATUS::MOTOR){
          Serial.println(instruction);
          motorController->ExecuteInstruction(instruction);
          statusCode = STATUS::IDLE;
          instruction = "";
        }
        if (statusCode == STATUS::IDLE || statusCode == STATUS::SENSOR)
        {
            float values[6];
            sensorController->getSensorValues(values);
            connector->SendSensor(String(values[0]),String(values[1]), String(values[2]), String(values[3]), String(values[4]), String(values[5]));
        }
        motorController->runMotors();
    }

    void SetSensorMode()
    {
        statusCode = STATUS::SENSOR;
    }

    void ChangeLights(String inst){
      Serial.println(inst);
        if (statusCode != STATUS::MOTOR){
            statusCode = STATUS::MOTOR;
        }
        instruction = inst;
    }

    void ChangeMotor(String inst){
      Serial.println("lalala");
        if (statusCode != STATUS::MOTOR){
            statusCode = STATUS::MOTOR;
        }
        instruction = inst;
    }

private:
    String instruction = "";
    bool hasMoveInit = false;

    enum class STATUS
    {
        IDLE,
        SENSOR,
        MOTOR,
    };

    String StatusCodeAsString()
    {
        switch (statusCode)
        {
        case (STATUS::IDLE):
            return "IDLE";
            break;
        case (STATUS::SENSOR):
            return "STATUS";
            break;
        case (STATUS::MOTOR):
            return "MOTOR";
            break;
        default:
            return "UNKNOWN";
            break;
        }
    }

    STATUS statusCode = STATUS::IDLE;
    bool stateChanged = true;
    String executedInstruction = "";

    PCConnector *connector;
    MotorController *motorController;
    SensorController *sensorController;
};
