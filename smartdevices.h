class Device;

class ConnectionManager {

  //   std::string deviceName = "hello", purpose;
  //   int deviceState = 0;
  //   int devicetype = 0;
  //   int deviceValue = 0;
  //   int deviceBattery = 100;
  //   std::string customOnMessage = "Started";
  //   std::string customOffMessage = "Stopped";
public:
  virtual void printDeviceName() = 0;
  virtual std::string getname() = 0;
  virtual void onConnect(void) = 0;
  virtual int gettype() = 0;
  virtual void onDisconnect(void) = 0;
  virtual void onChangeOfValue(int newValue) = 0; //{ std::cout << "warning"; }

  virtual std::string currentState() = 0; // {
  //     return deviceState == 0 ? "Offline" : "Online";
  //   }

  virtual void onBatteryLevelChange(int newLevl) = 0; //{ /*battery */
  //}
  virtual std::string useCase() = 0; // { return purpose; }
  virtual void setCustomMessege(std::string onMessage,
                                std::string offMessage) = 0;
  virtual void stateOn() = 0;
  virtual void stateOff() = 0;
};

class Callable {
public:
  Device *objectRefernce = nullptr;
  void (Device::*functionPointer)();
  int value = 0;
  std::string actiavtationCondition;
  Callable(void *obj, int val, void (Device::*func)(),
           std::string condition = "") {
    objectRefernce = (Device *)obj;
    value = val;
    functionPointer = func;
    actiavtationCondition = condition;
  }
  void call() { (objectRefernce->*functionPointer)(); }
};

class Sensor : public ConnectionManager {
  std::string deviceName, purpose;
  int devicetype = 0; // 0=sensor
  int deviceState = 0;
  int deviceValue = 0;
  int deviceBattery = 100;
  std::vector<Callable *> onEqual;
  std::vector<Callable *> onGreater;
  std::vector<Callable *> onLesser;
  std::string customOnMessage = "Started", customOffMessage = "Stopped";

public:
  void stateOff() {
    deviceState = 0;
    std::cout << customOffMessage << deviceName;
  }
  void stateOn() {
    deviceState = 1;
    std::cout << customOnMessage << deviceName;
  }

  void printDeviceName() { std::cout << deviceName; }
  std::string getname() { return deviceName; }
  void onConnect(void) {
    deviceState = 1;
    std::cout << "Connected" << deviceName << std::endl;
  }
  int gettype() { return devicetype; }

  void onDisconnect(void) {
    deviceState = 0;
    std::cout << "Disconnected" << deviceName << std::endl;
  }

  std::string currentState() { return deviceState == 0 ? "Offline" : "Online"; }

  void onBatteryLevelChange(int newLevl) { /*battery */
  }

  Sensor(std::string name, std::string use) {
    deviceName = name;
    purpose = use;
    std::cout << deviceName << purpose;
  }
  std::string useCase() { return purpose; }
  void onChangeOfValue(int newValue) {
    deviceValue = newValue;
    // for equal
    //std::cout << newValue;
    for (int i = 0; i < onEqual.size(); i++) {
      if (onEqual[i]->value == deviceValue)
        onEqual[i]->call(); // std::cout<<sensorValue;
    }
    for (int i = 0; i < onGreater.size(); i++) {
      if (deviceValue > onGreater[i]->value)
        onGreater[i]->call(); //
    }
    for (int i = 0; i < onLesser.size(); i++) {
      if (deviceValue < onLesser[i]->value)
        onLesser[i]->call();
    }
  }
  void setCustomMessege(std::string onMessage, std::string offMessage) {
    customOnMessage = onMessage;
    customOffMessage = offMessage;
  }
  friend void add_onequal(void *obj, Callable *Callableobj);
  friend void add_ongreater(void *obj, Callable *Callableobj);
  friend void add_onlesser(void *obj, Callable *Callableobj);
  friend void automate_task(std::string Ifstate, std::string Todo);
};
class Device : public ConnectionManager {
  std::string deviceName, category;
  int deviceState = 0;
  int devicetype = 1;
  int deviceValue = 0;
  int deviceBattery = 100;
  std::string customOnMessage = "Started", customOffMessage = "Stopped";

public:
  void printDeviceName() { std::cout << deviceName; }
  std::string getname() { return deviceName; }
  void onConnect(void) {
    deviceState = 1;
    std::cout << "Connected" << deviceName << std::endl;
  }
  int gettype() { return devicetype; }
  void onDisconnect(void) {
    deviceState = 0;
    std::cout << "Disconnected" << deviceName << std::endl;
  }

  void onChangeOfValue(int newValue) { std::cout << "warning"; }

  std::string currentState() { return deviceState == 0 ? "Offline" : "Online"; }

  void onBatteryLevelChange(int newLevl) { /*battery */
  }
  std::string useCase() { return category; }

  Device(std::string Name, std::string Category) {
    deviceName = Name;
    category = Category;
    onConnect();
  }
  void stateOff() {
    deviceState = 0;
    std::cout << customOffMessage << deviceName;
  }
  void stateOn() {
    deviceState = 1;
    std::cout << customOnMessage << deviceName;
  }

  void setCustomMessege(std::string onMessage, std::string offMessage) {
    customOnMessage = onMessage;
    customOffMessage = offMessage;
  }
};