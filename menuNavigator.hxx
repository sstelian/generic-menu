#pragma once
#include <iostream>
#include "json.hpp"

//TODO: remove iostream

using json = nlohmann::json;

class MenuNavigator
{
  public:
    MenuNavigator(json &_menu):
      menu{_menu},
      history_pointer{},
      selectionIndex{},
      _done{false}
    {
        selection_it = _menu.begin();
        displayCurrentView();
    };
    void forward();
    void backward();
    void up();
    void down();
    bool done();
  private:
    json &menu;
    json::iterator selection_it;
    json::json_pointer history_pointer;
    void pushHistory(std::string key);
    void pushHistory(int index);
    void popHistory();
    void displayCurrentView();
    json &selection();
    int selectionIndex;
    bool _done;

    static bool contains_element(json& _json, std::string element)
    {
      return (_json.find(element) != _json.end());
    }
};
