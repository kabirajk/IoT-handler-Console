#include <iostream>
#include <vector>
#include "smartdevices.h"

// std::vector<Sensor *> sensor_list;
// std::vector<Device *> device_list;
std::vector<ConnectionManager *> device_manager;
// std::vector<ConnectionManager*>device_m;
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

void add_onequal(void *obj, Callable *Callableobj) {
  ((Sensor *)obj)->onEqual.push_back(Callableobj);
}
void add_ongreater(void *obj, Callable *Callableobj) {
  ((Sensor *)obj)->onGreater.push_back(Callableobj);
  // std::cout<<"greater"<<obj->onGreater.size()<<obj->onGreater.front()->value;//(obj->onGreater[0])->value;
}
void add_onlesser(void *obj, Callable *Callableobj) {
  ((Sensor *)obj)->onLesser.push_back(Callableobj);
}

void automate_task(std::string Ifstate, std::string Todo) {
  // tokenise string 1. chosse object ffrom list 2.based on comparision //
  // add 3.add callabe object // for device choosing
  std::vector<std::string> ifstate_tokens;
  std::vector<std::string> todo_tokens;
  string_tokeniser(Todo, todo_tokens);
  string_tokeniser(Ifstate, ifstate_tokens);
  int devicesindex = 0;
  for (devicesindex = 0;
       (device_manager[devicesindex])->gettype() &&
       !(stringfind((device_manager[devicesindex])->getname(), todo_tokens[0]));
       devicesindex++)
    ;
  device_manager[devicesindex]->printDeviceName();
  // std::cout<<(todo_tokens[2]=="ON");
  Callable *CALL = nullptr;
  // auto funptr = &Device::fakefun;
  if (todo_tokens[2] == "ON")
    CALL = new Callable(device_manager[devicesindex], 20, &Device::stateOn);
  else if (todo_tokens[2] == "OFF")
    CALL = new Callable(device_manager[devicesindex], 20, &Device::stateOff);

  // for sensor chosing
  int sensorindex = 0;
  for (sensorindex = 0;
       !(device_manager[sensorindex])->gettype() &&
       (device_manager[sensorindex])->useCase() != ifstate_tokens[0];
       sensorindex++)
    ;
  if (ifstate_tokens[1] == "=") // equal  //chnage callables
    add_onequal(device_manager[sensorindex], CALL);
  if (ifstate_tokens[1] == ">") // greter
    add_ongreater(device_manager[sensorindex], CALL);
  if (ifstate_tokens[1] == "<") // lesser
    add_onlesser(device_manager[sensorindex], CALL);
  CALL = nullptr;
}

int main() {
  device_manager.push_back(new Sensor("Temperature Sensor", "Temperature"));
  std::cout << "\n";
  device_manager.push_back(new Sensor("Smart fan", "fan"));
  std::cout << "\n";

  automate_task("Temperature > 20", "fan = ON");
  automate_task("Temperature < 20", "fan = OFF");
  device_manager[0]->onChangeOfValue(30);
  device_manager[0]->onChangeOfValue(15);

  return 0;
}
// implement string tokenisation!
// complete auto mate function!
// make a console to show status of the sensors and devices
// stimulate battery
// make function to add sensors and devices
