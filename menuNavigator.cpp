#include "menuNavigator.hxx"

void MenuNavigator::forward()
{
  cout << "\033c";
  if(selection->hasChildren())
  {
    if(!(selection->child(childIndex)->hasChildren()))
    {
      cout << "\t" << selection->child(childIndex)->name() << endl;
    }
  }
  if (selection->hasChildren())
  {
    selection = selection->child(childIndex);
    display(selection, childIndex);
  } else
  {
    selection->call();
  }
  childIndex = 0;
}

void MenuNavigator::backward()
{
  if (selection->hasParent())
  {
    //cout << "\033c";
    selection = selection->parent();
    auto ch = selection->children();
    display(selection, childIndex);
  }
}

void MenuNavigator::up()
{
  if(selection->hasChildren())
  {
    if (childIndex > 0)
    {
      childIndex--;
      display(selection, childIndex);
    }
  }else
  {
    ;//TODO:add up functionality for leaf
  }
}

void MenuNavigator::down()
{
  if(selection->hasChildren())
  {
    if (childIndex < selection->children()->size()-1)
    {
      childIndex++;
      display(selection, childIndex);
    }
  } else
  {
    ;//TODO:add down functionality for leaf
  }
}
