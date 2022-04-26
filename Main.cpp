#include <iostream>
#include <vector>
#include <string>
#include "smartdevices.h"
// std::vector<Sensor *> sensor_list;
// std::vector<Device *> device_list;
std::vector<ConnectionManager *> device_manager;
// std::vector<ConnectionManager*>device_m;
// function to tokenise the string
#include"automatetask.h"

int main() {
  device_manager.push_back(new Sensor("Temperature Sensor", "Temperature"));
  std::cout << "\n";
  device_manager.push_back(new Device("Smart Fan", "Fan"));
  std::cout << "\n";
  device_manager.push_back(new Sensor("Motion sensor", "Motion"));
  device_manager.push_back(new Sensor("Water level sensor", "Water level"));
  device_manager.push_back(new Sensor("Gas detection sensor", "Gas detection"));
  device_manager.push_back(new Device("Smart Light", "Light"));
  device_manager.push_back(new Device("Door Control", "Door"));
  device_manager.back()->setCustomMessege("open Door","Close door");
  automate_task("Temperature > 20", "fan = ON");
  device_manager[0]->onChangeOfValue(30);
  print_sensor_status();
//  while (1)
//  {
//    /* code */
//  }
 
  // device_manager[0]->onChangeOfValue(30);
  // std::cout << "\n";
  // device_manager[0]->onChangeOfValue(15);
  // std::cout << "\n";

  return 0;
}
// implement string tokenisation!
// complete auto mate function!
// make a console to show status of the sensors and devices
// stimulate battery
// make function to add sensors and devices
