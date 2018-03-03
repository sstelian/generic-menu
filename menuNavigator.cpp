#include "menuNavigator.hxx"

void MenuNavigator::forward()
{
  if ((selection->children()->size() > 0) && ((*selection->children())[childIndex].get() != nullptr))
  {
    selection = (*selection->children())[childIndex].get();
    display(selection, childIndex);
  } else
  {
    cout << "can't go forward. no children." << endl;
    selection->call();
  }
  childIndex = 0;
}

void MenuNavigator::backward()
{
  if (selection->parent() != nullptr)
  {
    selection = selection->parent();
    auto ch = selection->children();
    display(selection, childIndex);
  } else
  {
    cout << "can't go backward. root." << endl;
  }
}

void MenuNavigator::up()
{
  if (childIndex > 0)
    childIndex--;
}

void MenuNavigator::down()
{
  if (childIndex < selection->children()->size()-1)
    childIndex++;
}
