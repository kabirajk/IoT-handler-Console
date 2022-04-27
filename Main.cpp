#include <iostream>
#include <vector>
#include<conio.h>
#include <windows.h>
#include <string>
#include<future>
#include "smartdevices.h"

std::vector<ConnectionManager *> device_manager;
int val=0;
#include"automatetask.h"

int main() {
  // unsigned char key[256]={};
  // unsigned char m_key[256]={}; 
  // Sleep(1000);
  // GetKeyboardState(key);
  // GetKeyboardState(m_key);
  // for(unsigned int i=0;i<256;i++)
  //   std::cout<< (key[i] & 0x88)<<"\n";
  // for(unsigned int i=0;i<256;i++)
  //   std::cout<< (m_key[i] & 0x88)<<"\n";
  // return 0;

  device_manager.push_back(new Sensor("Temperature Sensor", "Temperature"));
  std::cout << "\n";
  device_manager.push_back(new Device("Smart Fan", "Fan"));
    device_manager.back()->setCustomMessege("Fan On","Fan off");
  std::cout << "\n";
  device_manager.push_back(new Sensor("Motion sensor", "Motion"));
  device_manager.push_back(new Sensor("Water level sensor", "Water level"));
  device_manager.push_back(new Sensor("Gas detection sensor", "Gas detection"));
  device_manager.push_back(new Device("Smart Light", "Light"));
    device_manager.back()->setCustomMessege("Lights on","Lights off");
  device_manager.push_back(new Device("Door Control", "Door"));
  device_manager.back()->setCustomMessege("open Door","Close door");
  automate_task("Temperature > 20", "Fan = OFF");
 while (1)
 {
   Sleep(500);
  print_sensor_status();
  stimulate();
 }
  return 0;

}
// implement string tokenisation!
// complete auto mate function!
// make a console to show status of the sensors and devices
// stimulate battery
// make function to add sensors and devices
