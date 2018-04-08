#include "menuNavigator.hxx"

using namespace std;

void MenuNavigator::forward()
{
  if(selection.is_object() || selection.is_array())
  {
    history.push_back(selection);
    selection = *selection_it;
    selection_it = selection.begin();
  }
  displayCurrentView();
}

void MenuNavigator::backward()
{
  if(history.size() > 0)
  {
    selection = history.back();
    selection_it = selection.begin();
    history.pop_back();
  }
  displayCurrentView();
}

void MenuNavigator::up()
{
  if (selection_it != selection.begin())
    selection_it = prev(selection_it, 1);
  else
  {
    if (selection.is_number())
      selection = selection.get<int>()+1;
    else
    if (selection.is_boolean())
      selection = !(selection.get<bool>());
  }
  displayCurrentView();
}

void MenuNavigator::down()
{
  if (next(selection_it, 1) != selection.end())
    ++selection_it;
  else
  {
    if (selection.is_number())
      selection = selection.get<int>()-1;
    else
    if (selection.is_boolean())
      selection = !(selection.get<bool>());
  }
  displayCurrentView();
}

void MenuNavigator::displayCurrentView()
{
  cout << "\033c";
  //cout << endl << endl;
  if (selection.is_object())
  {
    for (json::iterator it = selection.begin(); it != selection.end(); ++it)
    {
      if (selection_it == it)
        cout << ">";
        else
        cout << " ";
      cout << it.key() << endl;
    }
  } else
  if (selection.is_array())
  {
    for (json::iterator array_el = selection.begin(); array_el != selection.end(); ++array_el)
    {
      for (json::iterator el = array_el->begin(); el != array_el->end(); ++el)
      {
        if (selection_it == array_el)
          cout << ">";
          else
          cout << " ";
        cout << el.key() << endl;
      }
    }
  } else
  {
    cout << selection;
  }
}
