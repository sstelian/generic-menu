#pragma once
#include <iostream>
#include "json.hpp"
#include <vector>

using nlohmann::json;

class MenuNavigator
{
  public:
    MenuNavigator(json &_menu):
      menu{_menu},
      history{}
    {
        selection = menu;
        selection_it = selection.begin();
        displayCurrentView();
    };
    void forward();
    void backward();
    void up();
    void down();
  private:
    json &menu;
    json::iterator selection_it;
    json selection;
    std::vector<json> history;
    void displayCurrentView();
};
