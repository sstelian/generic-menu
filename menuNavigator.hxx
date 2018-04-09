#pragma once
#include <iostream>
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

class MenuNavigator
{
  public:
    MenuNavigator(json &_menu):
      menu{_menu},
      history_pointer{},
      selectionIndex{}
    {
        selection_it = _menu.begin();
        displayCurrentView();
    };
    void forward();
    void backward();
    void up();
    void down();
  private:
    json &menu;
    json::iterator selection_it;
    json::json_pointer history_pointer;
    void pushHistory(std::string key);
    void pushHistory(int index);
    void popHistory();
    void displayCurrentView();
    int selectionIndex;
};
