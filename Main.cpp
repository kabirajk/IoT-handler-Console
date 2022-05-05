
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

#include "devices.pb.h"
#include "smartdevices.h"
std::vector<ConnectionManager *> device_manager;
int val = 0;
#include "automatetask.h"

int main() {
//device_manager.push_back(new Sensor("Temperature Sensor", "Temperature"));
  //std::cout << "\n";
  //device_manager.push_back(new Device("Smart Fan", "Fan"));
  /*  device_manager.back()->setCustomMessege("Fan On", "Fan off");
  std::cout << "\n";
  device_manager.push_back(new Sensor("Motion sensor", "Motion"));
  device_manager.push_back(new Sensor("Water level sensor", "Water level"));
  device_manager.push_back(new Sensor("Gas detection sensor", "Gas detection"));
  device_manager.push_back(new Device("Smart Light", "Light"));
  device_manager.back()->setCustomMessege("Lights on", "Lights off");
  device_manager.push_back(new Device("Door Control", "Door"));
  device_manager.back()->setCustomMessege("open Door", "Close door");
  automate_task("Temperature > 20", "Fan = OFF");*/
  //  Sleep(500);
  // print_sensor_status();
  // stimulate();
  Builder build;
  std::string i;
  while (1) {
    std::cout << "options:1 =>add_sensor,2 =>add_device,3=> print,4=> IFTTT,5=> simulate:,exit ";
    std::cin >> i;
    if (i == "1")
      addsensor();
    if (i == "2")
      adddevice();
    if (i == "3")
      print_sensor_status();
    if (i == "IFTTT" || i == "4") {
      std::string ifstring, thenstring;
      std::cout << "IF: ";
      std::cin >> ifstring;
      std::cout << "THEN: ";
      std::cin >> thenstring;
      automate_task(ifstring, thenstring);
    }
    if (i == "5")
      remove();
    if (i == "simulate" || i=="6") // Sleep(500);
      while (1) {
        Sleep(1000);
        print_sensor_status();
        if (stimulate()) {
          break;
          change_battery();
        }
      }
    if (i == "exit")
      break;
  }
  return 0;
}
// implement string tokenisation!
// complete auto mate function!
// make a console to show status of the sensors and devices
// stimulate battery
// make function to add sensors and devices
