#include <iostream>
#include "menu.hxx"
#include "menuNavigator.hxx"
#include <vector>

using namespace std;

int main()
{
  //menu tree creation
  auto root = make_unique<MenuItem>("root");
  auto node = make_unique<MenuItem>("strategies");
  auto strats = root->addNode(node);

  node = make_unique<MenuItem>("strategy1",[](){
    cout << "strategy 1 action" << endl;
  });
  strats->addNode(node);

  node = make_unique<MenuItem>("strategy2");
  strats->addNode(node);

  node = make_unique<MenuItem>("sensors");
  auto sensors = root->addNode(node);

  node = make_unique<MenuItem>("enemy sensors");
  auto enemySensors = sensors->addNode(node);

  node = make_unique<MenuItem>("line sensors");
  auto lineSensors = sensors->addNode(node);

  node = make_unique<MenuItem>("line sensor 1",[](){
    cout << "line sensor 1 action" << endl;
  });
  lineSensors->addNode(node);

  node = make_unique<MenuItem>("line sensor 2");
  lineSensors->addNode(node);

  node = make_unique<MenuItem>("enemy sensor 1");
  enemySensors->addNode(node);


  //menu navigation
  cout << "\033c";
  MenuNavigator navigator(root.get(),[](MenuItem * const &selection, int const &selectionIndex){
    //cout << "\033c";
    auto ch = selection->children();
    int index = 0;
    for(auto it = ch->begin(); it != ch->end(); it++)
    {
      if (index == selectionIndex)
      {
        cout << ">" << (**it).name() << endl;
      } else
      {
        cout << " " << (**it).name() << endl;
      }
      index++;
    }
  });

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
