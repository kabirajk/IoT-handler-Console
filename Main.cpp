#include <iostream>
#include <vector>
#include <string>
#include "smartdevices.h"

std::vector<ConnectionManager *> device_manager;

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

  return 0;
  
}
// implement string tokenisation!
// complete auto mate function!
// make a console to show status of the sensors and devices
// stimulate battery
// make function to add sensors and devices
