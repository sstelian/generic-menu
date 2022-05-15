#include <iostream>
#include "menuNavigator.hxx"
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

json menu = R"(
  {
      "bluetooth_config" : false,
      "color" :
        {
          "_selection" : "",
          "_predefined_list" : ["blue", "orange", "red"]
        },
      "regular_list" : ["element 1", "element 2"],
      "light_sensors_enabled" :
        {
          "front_left" : true,
          "front_right" : true,
          "back_left" : true,
          "back_right" : true
        },
      "smoke_sensors_enabled" :
          {
            "0" : true,
            "1" : true,
            "2" : true,
            "3" : true,
            "4" : true,
            "5" : true,
            "6" : true
          }
  }
)"_json;

int main()
{
  MenuNavigator navigator(menu);
  char c = '\0';
  while((c != 'q') && !navigator.done())
  {
    cin >> c;
    switch(c)
    {
      case 'd': //go forward
      {
        navigator.forward();
        break;
      };
      case 'a': //go backward
      {
        navigator.backward();
        break;
      };
      case 'w': //go up
      {
        navigator.up();
        break;
      };
      case 's': //go down
      {
        navigator.down();
        break;
      }
    }
  }
  cout << endl << endl << "Menu setup complete." << endl;
  cout << "Menu dump :" << endl;
  cout << menu.dump(2);
  return 0;
}
