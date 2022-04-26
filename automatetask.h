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
  int devicesindex = 0;
  for (devicesindex = 0;
       (device_manager[devicesindex])->gettype() &&
       !(stringfind((device_manager[devicesindex])->getname(), todo_tokens[0]));
       devicesindex++)
    ; // device_manager[devicesindex]->printDeviceName();

  Callable *CALL = nullptr;

  if (todo_tokens[2] == "ON")
    CALL = new Callable(device_manager[devicesindex],
                        std::stof(ifstate_tokens[2]), &Device::stateOn);
  else if (todo_tokens[2] == "OFF")
    CALL = new Callable(device_manager[devicesindex],
                        std::stof(ifstate_tokens[2]), &Device::stateOff);

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
void print_sensor_status() {
  system("cls");
  std::cout << "Sensor/device name"
            << "       "
            << "connection status"
            << "       "
            << "value\n"
            << std::endl;
  for (int i = 0; i < device_manager.size(); i++) {
    std::cout.width(25);
    std::cout.flags(std::ios::left);
    std::cout << device_manager[i]->getname();
    std::cout.width(25);
    std::cout.flags(std::ios::left);
    std::cout << device_manager[i]->currentState();
    std::cout.width(20);
    std::cout.flags(std::ios::left);
    std::cout << device_manager[i]->currentValue() << std::endl;
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