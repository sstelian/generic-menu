#include <iostream>
#include "menu.hxx"
#include "menuNavigator.hxx"
#include <vector>

using namespace std;

int main()
{
  //menu tree initialization
  auto root = make_unique<MenuItem>();
  auto node = make_unique<MenuItem>("strategies");
  auto strats = root->addNode(node);

  node = make_unique<MenuItem>("strategy1",[](){
    cout << "strategy 1 action" << endl;
  });
  strats->addNode(node);

  node = make_unique<MenuItem>("strategy2");
  strats->addNode(node);

  node = make_unique<MenuItem>("sensors config");
  auto sensorsConfig = root->addNode(node);

  node = make_unique<MenuItem>("enemy sensors config");
  auto enemySensors = sensorsConfig->addNode(node);

  node = make_unique<MenuItem>("line sensors config");
  auto lineSensors = sensorsConfig->addNode(node);

  node = make_unique<MenuItem>("line sensor 1",[](){
    cout << "line sensor 1 action" << endl;
  });
  lineSensors->addNode(node);

  node = make_unique<MenuItem>("line sensor 2");
  lineSensors->addNode(node);

  node = make_unique<MenuItem>("enemy sensor 1");
  enemySensors->addNode(node);

  auto statusItem = make_unique<MenuItem>("status",[](){
    cout << "System status : OK" << endl;
  });
  root->addNode(statusItem);

  //menu navigation
  cout << "\033c";
  auto displaySelection = [](MenuItem * const &selection,
                            int const &selectionIndex,
                            MenuItem::leafAction const &action){
          cout << "\033c";
          if(action==MenuItem::leafAction::none)
          {
            auto ch = selection->children();
            int index = 0;
            for(auto it = ch->begin(); it != ch->end(); it++)
            {
              if (index == selectionIndex)
              {
                cout << ">" << (*it)->name() << endl;
              } else
              {
                cout << " " << (*it)->name() << endl;
              }
              index++;
            }
        }
      };
  MenuNavigator navigator(root.get(), displaySelection);

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
