#include <iostream>
#include <vector>
#include<conio.h>
#include <windows.h>
#include <string>
#include "smartdevices.h"

std::vector<ConnectionManager *> device_manager;
int val=0;
#include"automatetask.h"

int main() {
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
  //  Sleep(500);
  // print_sensor_status();
  // stimulate();
 std::string i;
 while (1)
 { std::cout<<"options:add_sensor,add_device,print,IFTTT,simulate: ";
   std::cin>>i;
  if(i=="add_sensor") 
  addsensor();
  if(i=="add_devive")
  adddevice();
  if(i=="print")
    print_sensor_status();
  if(i=="IFTTT")
     { std::string ifstring,thenstring;
      std::cout<<"IF: ";
       std::cin>>ifstring;
       std::cout<<"THEN: ";
       std::cin>>thenstring;
     automate_task(ifstring,thenstring);}
  if(i=="remove")
      remove();
  if(i=="simulate")// Sleep(500);
  while(1)
  {
      Sleep(1000);
      print_sensor_status();
      if (stimulate())
          break;
  }
  if(i=="exit") break;


 }
  return 0;

}
// implement string tokenisation!
// complete auto mate function!
// make a console to show status of the sensors and devices
// stimulate battery
// make function to add sensors and devices
