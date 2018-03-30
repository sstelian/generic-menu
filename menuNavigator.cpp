#include "menuNavigator.hxx"

void MenuNavigator::forward()
{
  if (selection->hasChildren())
  {
    selection = selection->child(childIndex);
    childIndex = 0;
    displayNode(selection, childIndex);
    if (!selection->hasChildren()) //leaf selected
    {
      selection->callInitial();
    }
  }
}

void MenuNavigator::backward()
{
  if (selection->hasParent())
  {
    if (!selection->hasChildren()) //leaf selected
    {
      selection->callFinal();
    }
    childIndex = 0;
    selection = selection->parent();
    displayNode(selection, childIndex);
  }
}

void MenuNavigator::up()
{
  if(selection->hasChildren())
  {
    if (childIndex > 0)
    {
      childIndex--;
      displayNode(selection, childIndex);
    }
  }else
  {
    selection->callUp();
  }
}

void MenuNavigator::down()
{
  if(selection->hasChildren())
  {
    if (childIndex < selection->children()->size()-1)
    {
      childIndex++;
      displayNode(selection, childIndex);
    }
  } else
  {
    selection->callDown();
  }
}
