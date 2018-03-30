#pragma once
#include "menu.hxx"
#include <iostream>

class MenuNavigator
{
  public:
    typedef std::function<void(MenuItem* const&, int const&)> menu_display_node;
    MenuNavigator(MenuItem *root, menu_display_node _displayNode) : selection{root},
                  childIndex{},
                  displayNode{_displayNode}
     {
       displayNode(selection, childIndex);
     };
    void forward();
    void backward();
    void up();
    void down();
  private:
    MenuItem *selection;
    uint8_t childIndex;
    menu_display_node displayNode;
};
