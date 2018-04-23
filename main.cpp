#include <iostream>
#include "menuNavigator.hxx"
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

json menu = R"(
  {
      "options" : [
        {"option1" : false},
        {"option2" : false},
        {"option3" : true}
      ],
      "sensors" : [
        {"analog sensors" : [
          {"analog sensor 1" : false, "low threshold" : 100, "high threshold" : 423},
          {"analog sensor 2" : true, "low threshold" : 104, "high threshold" : 893},
          {"analog sensor 3" : true, "low threshold" : 78, "high threshold" : 782},
          {"analog sensor 4" : false, "low threshold" : 167, "high threshold" : 1082}
        ]},
        {"digital sensors" :  [
          {"digital sensor 1" : true},
          {"digital sensor 2" : false},
          {"digital sensor 3" : true},
          {"digital sensor 4" : false},
          {"digital sensor 5" : true},
          {"digital sensor 6" : false},
          {"digital sensor 7" : true}
        ]}
      ],
      "status" : "ok"
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
