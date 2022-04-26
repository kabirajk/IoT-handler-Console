#include <iostream>
#include <vector>
#include "smartdevices.h"


std::vector<Sensors *> sensor_list;
std::vector<Device *> device_list;
std::vector<std::string> ifstate_tokens;
std::vector<std::string> todo_tokens;
// function to tokenise the string
void string_tokeniser(std::string s, std::vector<std::string> &string_tokens) {
  string_tokens.clear();
  int index = 0;
  std::string token;
  while (index < s.length()) {
    if (s[index] != ' ')
      token += s[index];
    if (s[index] == ' ' && token != " ") {
      if (token != "")
        string_tokens.push_back(token);
      token = "";
    }
    index++;
  }
  if (token != " ")
    string_tokens.push_back(token);
}

int stringfind(std::string source, std::string target) {
  int srcindex = 0, tarindex = 0;
  while (srcindex < source.length()) {
    if (tarindex == target.length())
      return 1;
    if (target[tarindex] == source[srcindex])
      tarindex++;
    // cout<<target[tarindex]<<s[srcindex]<<tarindex<<endl;
    srcindex++;
  }
  if (tarindex == target.length())
    return 1;
  return 0;
}

void add_onequal(Sensors *obj, Callable *Callableobj) {
  obj->onEqual.push_back(Callableobj);
}
void add_ongreater(Sensors *obj, Callable *Callableobj) {
  obj->onGreater.push_back(Callableobj);
  //std::cout<<"greater"<<obj->onGreater.size()<<obj->onGreater.front()->value;//(obj->onGreater[0])->value;
}
void add_onlesser(Sensors *obj, Callable *Callableobj) {
  obj->onLesser.push_back(Callableobj);
}

void automate_task(std::string Ifstate, std::string Todo) {
  // tokenise string 1. chosse object ffrom list 2.based on comparision // add 3.add callabe object // for device choosing
  string_tokeniser(Todo, todo_tokens);
  string_tokeniser(Ifstate, ifstate_tokens);
  int devicesindex = 0;
  for (devicesindex = 0;
       !stringfind(device_list[devicesindex]->deviceName, todo_tokens[0]);
       devicesindex++)
    ;
  // std::cout<<(todo_tokens[2]=="ON");
  Callable* CALL=nullptr;
  //auto funptr = &Device::fakefun;
  if (todo_tokens[2] == "ON")
      CALL =new Callable(device_list[devicesindex],20,&Device::stateOn);
  else if (todo_tokens[2] == "OFF")
      CALL =new Callable(device_list[devicesindex],20,&Device::stateOff);

  // for sensor chosing
  int sensorindex = 0;
  for (sensorindex = 0; sensor_list[sensorindex]->purpose != ifstate_tokens[0];
       sensorindex++)
    ;
  if (ifstate_tokens[1] == "=") // equal  //chnage callables
        add_onequal(sensor_list[sensorindex],CALL);
    if (ifstate_tokens[1] == ">") // greter
      add_ongreater(sensor_list[sensorindex],CALL);
  if (ifstate_tokens[1] == "<") // lesser
    add_onlesser(sensor_list[sensorindex],CALL);
  CALL=nullptr;
}
class mysens {
public:
  void (*funcptr)();
  void movements(void (*func)()) {
    std::cout << "hello";
    funcptr = func;
    funcptr();
  }
};

int main() {
   sensor_list.push_back(new Sensors("Temperature Sensor", "Temperature"));
   device_list.push_back(new Device("Smart fan"));
   automate_task("Temperature > 20","fan = ON");
   automate_task("Temperature < 20","fan = OFF");
  //  std::cout<<
  sensor_list[0]->onChangeOfValue(30);
  sensor_list[0]->onChangeOfValue(15);
  // // Callable c(device_list[0],20,&Device::getDevicename);
  // add_onequal(sensor_list[0],
  //             new Callable(device_list[0], 20, &Device::stateOn));
  // add_onequal(sensor_list[0],
  //             new Callable(device_list[0], 30, &Device::stateOff));
  // sensor_list[0]->onChangeOfValue(20);
  // sensor_list[0]->onChangeOfValue(21);
  // sensor_list[0]->onChangeOfValue(22);
  // sensor_list[0]->onChangeOfValue(30);

  // mysens m;
  // auto fun=[](){std::cout<<"value is grater than 0";};
  // auto fun2=mysens::movements;
  // // (m.*fun2)(fun);
  // mysens*k=&m;
  // (k->*fun2)(fun);

  return 0;
}
// implement string tokenisation!
// complete auto mate function!
// make a console to show status of the sensors and devices
// stimulate battery
// make function to add sensors and devices
