#include "menuNavigator.hxx"

//TODO: remove std::cout
using namespace std;

//selected options are appended to the json_pointer
//the json_pointer is then used for navigation and for altering primitive values
void MenuNavigator::forward()
{
  if (selection().is_object())
  {
    pushHistory(selection_it.key());
  } else
  if (selection().is_array())
  {
    pushHistory(selectionIndex);
  }
  selection_it = selection().begin();
  displayCurrentView();
  selectionIndex = 0;
}

//removes last option from json_pointer and displays new view
void MenuNavigator::backward()
{
  if (history_pointer.to_string() != "")
  {
    popHistory();
    selection_it = selection().begin();
    displayCurrentView();
  } else
  {
    _done = 1;
  }
}

//if selection is array or object, it iterates through its elements
//if selection is primitive, it alters it
void MenuNavigator::up()
{
  if (selection_it != selection().begin())
  {
    selection_it = prev(selection_it, 1);
    --selectionIndex;
  }
  else
  {
    if (selection().is_number())
      selection() = selection().get<int>()+1;
    else
    if (selection().is_boolean())
      selection() = !(selection().get<bool>());
  }
  displayCurrentView();
}

void MenuNavigator::down()
{
  if (next(selection_it, 1) != selection().end())
  {
    ++selection_it;
    ++selectionIndex;
  }
  else
  {
    if (selection().is_number())
      selection() = selection().get<int>()-1;
    else
    if (selection().is_boolean())
      selection() = !(selection().get<bool>());
  }
  displayCurrentView();
}

bool MenuNavigator::done()
{
  return _done;
}

void MenuNavigator::displayCurrentView()
{
  //cout << "\033c";
  cout << endl << endl;
  //display each key:value pair of object
  if (selection().is_object())
  {
    for (json::iterator it = selection().begin(); it != selection().end(); ++it)
    {
      //graphical pointer to current selection
      if (selection_it == it)
        cout << ">";
        else
        cout << " ";
      cout << it.key() << " : " << it.value() << endl;
    }
  } else
  //display each key:value pair of each element of the array
  if (selection().is_array())
  {
    for (json::iterator array_el = selection().begin(); array_el != selection().end(); ++array_el)
    {
      for (json::iterator el = array_el->begin(); el != array_el->end(); ++el)
      {
        if (selection_it == array_el)
          cout << ">";
          else
          cout << " ";
        cout << el.key() << " : " << el.value() << endl;
      }
    }
  } else
  {
    cout << selection();
  }
}

//helper functions for history pointer manipulation
void MenuNavigator::pushHistory(string key)
{
  string buffer = history_pointer.to_string();
  buffer += "/" + key;
  history_pointer = json::json_pointer(buffer);
}

void MenuNavigator::pushHistory(int index)
{
  string buffer = history_pointer.to_string();
  buffer += "/" + to_string(index);
  history_pointer = json::json_pointer(buffer);
}

void MenuNavigator::popHistory()
{
  string buffer = history_pointer.to_string();
  if (buffer != "")
  {
    int i = buffer.find_last_of("/");
    buffer.erase(i, buffer.length()-i);
    history_pointer = json::json_pointer(buffer);
  }
}

json& MenuNavigator::selection()
{
  return menu[history_pointer];
}
