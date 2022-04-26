class Device;
class Callable {
public:
  Device *objectRefernce = nullptr;
  void (Device::*functionPointer)();
  int value = 0;
  std::string actiavtationCondition;
  Callable(Device *obj, int val, void (Device::*func)(),
           std::string condition = "") {
    objectRefernce = obj;
    value = val;
    functionPointer = func;
    actiavtationCondition = condition;
  }
  void call() { // std::cout<<"called\n";
                // std::cout<<objectRefernce->deviceName;
    (objectRefernce->*functionPointer)();
  }
};

class Sensors {
public:
  std::string sensorsName,purpose;  
  int sensorState = 0;
  int sensorValue = 0;
  std::vector<Callable *> onEqual;
  std::vector<Callable *> onGreater;
  std::vector<Callable *> onLesser;

  Sensors(std::string sensorname,std::string use) { sensorsName = sensorname; purpose=use;}

  virtual void onConnect(void) {
    sensorState = 1;
    std::cout << "Connected" << sensorsName << std::endl;
  }
  virtual void onDisconnect(void) {
    sensorState = 0;
    std::cout << "Disconnected" << sensorsName << std::endl;
  }
  virtual std::string currentState() {
    return sensorState == 0 ? "Offline" : "Online";
  }
  void onBatteryLevelChange(int newLevl) {}
  void onChangeOfValue(int newValue) {
    sensorValue = newValue;
    // for equal
    for (int i = 0; i < onEqual.size(); i++) {
      if (onEqual[i]->value == sensorValue)
        onEqual[i]->call(); // std::cout<<sensorValue;
    }
    for (int i = 0; i < onGreater.size(); i++) {
      if (onGreater[i]->value > sensorValue)
        onGreater[i]->call();
      ;
    }
    for (int i = 0; i < onLesser.size(); i++) {
      if (onLesser[i]->value < sensorValue)
        ;
      onLesser[i]->call();
    }
  }
  friend void add_onequal(Sensors *obj, Callable *Callableobj);
  friend void add_ongreater(Sensors *obj, Callable *Callableobj);
  friend void add_onlesser(Sensors *obj, Callable *Callableobj);
  friend void automate_task(std::string Ifstate, std::string Todo);
};

class Device {
public:
  std::string deviceName;
  int deviceState = 0;
  int deviceValue = 0;
  std::string customOnMessage = "Started", customOffMessage = "Stopped";

  Device(std::string devicename) {
    deviceName = devicename;
    std::cout << deviceName << "created \n";
  }
  virtual void onConnect(void) {
    deviceState = 1;
    std::cout << "Connected" << deviceName << std::endl;
  }
  virtual void onDisconnect(void) {
    deviceState = 0;
    std::cout << "Disconnected" << deviceName << std::endl;
  }
  void getDevicename() { std::cout << deviceName; }
  virtual void stateOn() {
    deviceState = 1;
    std::cout << customOnMessage << deviceName;
  }
  virtual void stateOff() {
    deviceState = 0;
    std::cout << customOffMessage << deviceName;
  }
  void setCustomMessege(std::string onMessage, std::string offMessage) {
    customOnMessage = onMessage;
    customOffMessage = offMessage;
  }
  void fakefun(){}
};


