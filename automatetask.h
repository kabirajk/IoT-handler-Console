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
  Callable *CALL = nullptr;
  int devicesindex = 0;
  for (devicesindex = 0;device_manager.size();devicesindex++)
       if(device_manager[devicesindex]->getType() &&(stringfind((device_manager[devicesindex])->getName(), todo_tokens[0])))
           {if (todo_tokens[2] == "ON")
                  CALL = new Callable(device_manager[devicesindex],
                                      std::stof(ifstate_tokens[2]), &Device::stateOn);
          else if (todo_tokens[2] == "OFF")
                CALL = new Callable(device_manager[devicesindex],
                                    std::stof(ifstate_tokens[2]), &Device::stateOff);
            break;}
              
   device_manager[devicesindex]->printDeviceName();
  // for sensor chosing
  int sensorindex = 0;
  for (sensorindex = 0;device_manager.size();sensorindex++)
    if(!(device_manager[sensorindex])->getType() &&(device_manager[sensorindex])->useCase() == ifstate_tokens[0])
      {  if (ifstate_tokens[1] == "=") // equal  //chnage callables
          add_onequal(device_manager[sensorindex], CALL);
        if (ifstate_tokens[1] == ">") // greter
          add_ongreater(device_manager[sensorindex], CALL);
        if (ifstate_tokens[1] == "<") // lesser
          add_onlesser(device_manager[sensorindex], CALL);
          break;}
  CALL = nullptr;
}
void print_sensor_status() {
  system("cls");
  std::cout <<" "<< "Sensor/device name"
            << "       "
            << "status  "
            << "   "
            << "value"
            << "       "
            <<"Power"
            << std::endl;
  for (int i = 0; i < device_manager.size(); i++) {
    std::cout <<i<<".";
    std::cout.width(25);
    std::cout.flags(std::ios::left);
    std::cout <<device_manager[i]->getName();
    std::cout.width(12);
    std::cout.flags(std::ios::left);
    std::cout << device_manager[i]-> connectionStatus();
    std::cout.width(20);
    std::cout.flags(std::ios::left);
    std::cout << device_manager[i]->currentValue();
    std::cout.width(20);
    std::cout.flags(std::ios::left);
    std::cout << device_manager[i]->currentState()<< std::endl;
  }
}

void create_custom_task() {
  std::string todo, ifwhen;
  std::cout << "If: ";
  std::cin >> ifwhen;
  std::cout << "Then: ";
  std::cin >> todo;
  automate_task(ifwhen, todo);
}
void remove()
{//remove certains dex cecnosr and device
  for(int i=0;i<device_manager.size();i++)
  {
    std::cout<<i<<". "<<device_manager[i]->getName()<<std::endl;
  }
  int index=0;
  std::cout<<"enter the index to delete: ";
  std::cin>>index;
  delete device_manager[index];
  device_manager.erase(device_manager.begin()+index);//iter need to be passed
  device_manager.shrink_to_fit();
}
void addsensor()
{
    // add new sensor
    std::string sensorName,sensorPurpose;
    std::cout<<"enter the name of sensor: ";
    std::cin>>sensorName;
    std::cout<<"enter the purpose of the sensor";
    std::cin>>sensorPurpose;
    device_manager.push_back(new Sensor(sensorName,sensorPurpose));
}

void adddevice()
{
    // add new sensor
    std::string deviceName,devicePurpose;
    std::cout<<"enter the name of sensor: ";
    std::cin>>deviceName;
    std::cout<<"enter the purpose of the sensor";
    std::cin>>devicePurpose;
    device_manager.push_back(new Device(deviceName,devicePurpose));
}

void deallocate()
{
  for(int i=0;i<device_manager.size();i++)
  {
    delete device_manager[i];
  }
}

void change_battery()
{
  for(int i=0;i<device_manager.size();i++)
  {
    device_manager[i]->onBatteryLevelChange(1);
  }
}

int stimulate()
{   while(1)
    {
      if((GetKeyState('t'-32) & 0x800)&&(GetKeyState('i'-32) & 0x800))
        {device_manager[0]->onChangeOfValue((device_manager[0]->currentValue())+1);GetKeyState('t'-32)||GetKeyState('i'-32);system("cls");break;}
      if((GetKeyState('t'-32) & 0x800) && (GetKeyState('d'-32) & 0x800))
        {device_manager[0]->onChangeOfValue((device_manager[0]->currentValue())-1);system("cls");break;}
      if(GetKeyState('l'-32)& 0x800)
        {device_manager[5]->onChangeOfValue(!device_manager[5]->currentValue());break;}
      if(GetKeyState('d'-32)& 0x800)
        {device_manager[6]->onChangeOfValue(!device_manager[6]->currentValue());break;}
      if(GetKeyState('f'-32)& 0x800)
        {device_manager[1]->onChangeOfValue(!device_manager[1]->currentValue());break;}
      if(GetKeyState('m'-32)& 0x800)
        {device_manager[2]->onChangeOfValue(!device_manager[2]->currentValue());break;}
      if((GetKeyState('w'-32) & 0x800)&&(GetKeyState('i'-32) & 0x800))
        {device_manager[3]->onChangeOfValue((device_manager[3]->currentValue())+1);GetKeyState('t'-32)||GetKeyState('i'-32);system("cls");break;}
      if((GetKeyState('w'-32) & 0x800) && (GetKeyState('d'-32) & 0x800))
        {device_manager[3]->onChangeOfValue((device_manager[3]->currentValue())-1);system("cls");break;}
      if((GetKeyState('g'-32) & 0x800)&&(GetKeyState('i'-32) & 0x800))
        {device_manager[4]->onChangeOfValue((device_manager[4]->currentValue())+1);GetKeyState('t'-32)||GetKeyState('i'-32);system("cls");break;}
      if((GetKeyState('g'-32) & 0x800) && (GetKeyState('d'-32) & 0x800))
        {device_manager[4]->onChangeOfValue((device_manager[4]->currentValue())-1);system("cls");break;}
      if(GetKeyState(0x1B)& 0x800){ return 1;}

    }
    return 0;
} 