#pragma once
#include "menu.hxx"
#include <iostream>

using namespace std;

class MenuNavigator
{
  public:
    typedef std::function<void(MenuItem* const&, int const&)> menu_display_callback;
    MenuNavigator(MenuItem *root, menu_display_callback _display) : selection{root},
                  childIndex{0},
                  display(_display)
     {
       display(selection, childIndex);
     };
    void forward();
    void backward();
    void up();
    void down();
  private:
    MenuItem *selection;
    uint8_t childIndex;
    menu_display_callback display;
};
