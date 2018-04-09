#include <iostream>
#include "menu.hxx"
#include "menuNavigator.hxx"
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

json menu = R"(
  {
      "strategies" : [
        {"strategy1" : false},
        {"strategy2" : false},
        {"strategy3" : true}
      ],
      "sensors" : [
        {"line sensors" : [
          {"line sensor 1" : false, "low threshold" : 100, "high threshold" : 423},
          {"line sensor 2" : true, "low threshold" : 104, "high threshold" : 893},
          {"line sensor 3" : true, "low threshold" : 78, "high threshold" : 782},
          {"line sensor 4" : false, "low threshold" : 167, "high threshold" : 1082}
        ]},
        {"enemy sensors" :  [
          {"enemy sensor 1" : true},
          {"enemy sensor 2" : false},
          {"enemy sensor 3" : true},
          {"enemy sensor 4" : false},
          {"enemy sensor 5" : true},
          {"enemy sensor 6" : false},
          {"enemy sensor 7" : true}
        ]}
      ],
      "status" : "ok"
  }
)"_json;

int main()
{
  // auto it = menu.begin();
  // auto sel = *it;
  // sel = sel[0];
  // cout << sel.dump(2);
  MenuNavigator navigator(menu);
  char c = '\0';
  while(c != 'q')
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
  return 0;
}
