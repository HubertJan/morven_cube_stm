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
        if(statusCode = STATUS::MOTOR){
            motorController->ExecuteInstruction()
        }
        if (statusCode == STATUS::SENSOR)
        {
            float values[6] = 
            sensorController->getSensorValues(values*);
            connector->SendSensor(values[0],values[1], values[2], values[3], values[4], values[5]);
        }
        motorController->runMotors();
    }

    void SetSensorMode()
    {
        statusCode = STATUS::SENSOR;
    }

    void ChangeLights(String inst){
        if (statusCode != STATUS::MOTOR){
            statusCode = STATUS::MOTOR;
        }
        instruction = inst;
    }

    void ChangeMotor(String inst){
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
