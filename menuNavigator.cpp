#include "menuNavigator.hxx"

void MenuNavigator::forward()
{
  if (selection->hasChildren())
  {
    selection = selection->child(childIndex);
    childIndex = 0;
    display(selection, childIndex, MenuItem::leafAction::none);
    if (!selection->hasChildren()) //leaf selected
    {
      selection->call();
    }
  }
}

void MenuNavigator::backward()
{
  if (selection->hasParent())
  {
    childIndex = 0;
    selection = selection->parent();
    display(selection, childIndex, MenuItem::leafAction::none);
  }
}

void MenuNavigator::up()
{
  if(selection->hasChildren())
  {
    if (childIndex > 0)
    {
      childIndex--;
      display(selection, childIndex, MenuItem::leafAction::none);
    }
  }else
  {
    //TODO:add up functionality for leaf
    cout << "up called on leaf" << endl;
  }
}

void MenuNavigator::down()
{
  if(selection->hasChildren())
  {
    if (childIndex < selection->children()->size()-1)
    {
      childIndex++;
      display(selection, childIndex, MenuItem::leafAction::none);
    }
  } else
  {
    //TODO:add down functionality for leaf
    cout << "down called on leaf" << endl;
  }
}
