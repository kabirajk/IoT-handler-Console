class Device;

class ConnectionManager {

public:
  virtual void printDeviceName() = 0;
  virtual std::string getName() = 0;
  virtual void onConnect(void) = 0;
  virtual int getType() = 0;
  virtual float currentValue() = 0;
  virtual void onDisconnect(void) = 0;
  virtual void onChangeOfValue(float newValue) = 0;
  virtual std::string currentState() = 0;
  virtual std::string connectionStatus() = 0;
  virtual void onBatteryLevelChange(int newLevl) = 0;
  virtual std::string useCase() = 0;
  virtual void setCustomMessege(std::string onMessage,
                                std::string offMessage) = 0;
  virtual void stateOn() = 0;
  virtual void backupData(Devices::Device *backupobj) = 0;
  virtual void stateOff() = 0;
};

class Callable {
public:
  Device *objectRefernce = nullptr;
  void (Device::*functionPointer)();
  float value = 0;
  std::string activationConditionIf;
  std::string activationConditionDo;
  Callable(void *obj, float val, void (Device::*func)(),
           std::string condition1 = "", std::string condition2 = "") {
    objectRefernce = (Device *)obj;
    value = val;
    functionPointer = func;
    activationConditionIf = condition1;
    activationConditionDo = condition2;
  }
  void call() { (objectRefernce->*functionPointer)(); }
};

class Sensor : public ConnectionManager {
  std::string deviceName, category;
  int devicetype = 0; // 0=sensor
  int deviceState = 0;
  int deviceConnection = 0;
  float deviceValue = 0;
  int deviceBattery = 100;
  std::vector<Callable *> onEqual;
  std::vector<Callable *> onGreater;
  std::vector<Callable *> onLesser;
  std::string customOnMessage = "Started", customOffMessage = "Stopped";

public:
  Sensor(std::string name, std::string use) {
    deviceName = name;
    category = use;
    onConnect();
    stateOn();
    // std::cout << deviceName << category;
  }

  Sensor(Devices::Device *Devicedetail) {
    deviceName = Devicedetail->devicename();
    category = Devicedetail->devicecategory();
    deviceState = Devicedetail->devicestate();
    deviceConnection = Devicedetail->deviceconnectionstate();
    deviceValue = Devicedetail->devicevalue();
    deviceBattery = Devicedetail->devicebattery();
  }

  void backupData(Devices::Device *backupobj) {
    backupobj->set_devicename(deviceName);
    backupobj->set_devicestate(deviceState);
    backupobj->set_devicecategory(category);
    backupobj->set_devicetype(devicetype);
    backupobj->set_devicebattery(deviceBattery);
    backupobj->set_deviceconnectionstate(deviceConnection);
    backupobj->set_devicevalue(deviceValue);
    Devices::IfDo *onequalobj = nullptr;
    Devices::IfDo *ongreaterobj = nullptr;
    Devices::IfDo *onelesserobj = nullptr;
    int index = 0;
    if (onEqual.size() != 0 || onGreater.size() != 0 || onLesser.size() != 0)
    while (1) {
      if (index < onEqual.size()) {
          onequalobj = backupobj->add_onequal();
          onequalobj->set_if_(onEqual[index]->activationConditionIf);
          onequalobj->set_do_(onEqual[index]->activationConditionDo);
      }
      if (index < onGreater.size()) {
          ongreaterobj = backupobj->add_ongreater();
          ongreaterobj->set_if_(onGreater[index]->activationConditionIf);
          ongreaterobj->set_do_(onGreater[index]->activationConditionDo);

      }
      if (index < onLesser.size()) {
          onelesserobj = backupobj->add_onlesser();
          onelesserobj->set_if_(onLesser[index]->activationConditionIf);
          onelesserobj->set_do_(onLesser[index]->activationConditionDo);
      }
      index++;
      if (onEqual.size() >= index && onGreater.size() >= index && onLesser.size() >= index) break;
    }
  }

  void stateOff() {
    deviceState = 0;
    // std::cout << customOffMessage << deviceName;
  }
  void stateOn() {
    deviceState = 1;
    // std::cout << customOnMessage << deviceName;
  }

  void printDeviceName() { std::cout << deviceName; }

  std::string getName() { return deviceName; }

  void onConnect(void) {
    deviceConnection = 1;
    //    std::cout << "Connected" << deviceName << std::endl;
  }

  int getType() { return devicetype; }

  float currentValue() { return deviceValue; }

  void onDisconnect(void) {
    deviceConnection = 0;
    std::cout << "Disconnected" << deviceName << std::endl;
  }

  std::string currentState() {
    return deviceState == 0 ? "OFF" : "ON";
  } // power

  std::string connectionStatus() {
    return (int)deviceConnection == 0 ? "Offline" : "online";
  } // connecion

  void onBatteryLevelChange(int newLevl) {
    deviceBattery -= newLevl;
    if (deviceBattery <= 0) {
      deviceBattery = 0;
      onDisconnect();
      stateOff();
    }
  }

  std::string useCase() { return category; }

  void onChangeOfValue(float newValue) {
    deviceValue = newValue; // for equal   // std::cout << newValue;
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
  int deviceConnection = 0;
  float deviceValue = 0;
  int deviceBattery = 100;
  std::string customOnMessage = "Started", customOffMessage = "Stopped";

public:
  Device(std::string Name, std::string Category) {
    deviceName = Name;
    category = Category;
    onConnect();
    stateOff();
  }
  Device(Devices::Device *Devicedetail) {
    deviceName = Devicedetail->devicename();
    category = Devicedetail->devicecategory();
    deviceState = Devicedetail->devicestate();
    deviceConnection = Devicedetail->deviceconnectionstate();
    deviceValue = Devicedetail->devicevalue();
    deviceBattery = Devicedetail->devicebattery();
  }
  void backupData(Devices::Device* backupobj) {
      backupobj->set_devicename(deviceName);
      backupobj->set_devicestate(deviceState);
      backupobj->set_devicecategory(category);
      backupobj->set_devicetype(devicetype);
      backupobj->set_devicebattery(deviceBattery);
      backupobj->set_deviceconnectionstate(deviceConnection);
      backupobj->set_devicevalue(deviceValue);
  }

  void printDeviceName() { std::cout << deviceName; }

  std::string getName() { return deviceName; }

  void onConnect(void) {
    deviceConnection = 1;
    //  std::cout << "Connected" << deviceName << std::endl;
  }

  int getType() { return devicetype; }

  void onDisconnect(void) {
    deviceConnection = 0;
    // std::cout << "Disconnected" << deviceName << std::endl;
  }

  float currentValue() { return deviceValue; }

  void onChangeOfValue(float newValue) {
    deviceValue = newValue;
    if (deviceState == 0)
      stateOn();
    else
      stateOff();
  }

  std::string currentState() { return (deviceState == 0) ? "OFF" : "ON"; }
  void onBatteryLevelChange(int newLevl) {
    deviceBattery -= newLevl;
    if (deviceBattery <= 0) {
      deviceBattery = 0;
      onDisconnect();
      stateOff();
    }
  }

  std::string connectionStatus() {
    return (int)deviceConnection == 0 ? "Offline" : "online";
  }

  std::string useCase() { return category; }

  void stateOff() {
    deviceState = 0;
    // std::cout << customOffMessage << deviceName;
  }

  void stateOn() {
    deviceState = 1;
    // std::cout << customOnMessage << deviceName;
  }

  void setCustomMessege(std::string onMessage, std::string offMessage) {
    customOnMessage = onMessage;
    customOffMessage = offMessage;
  }
};
