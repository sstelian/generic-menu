#include "menuNavigator.hxx"

using namespace std;

void MenuNavigator::forward()
{
  if (menu[history_pointer].is_object())
  {
    pushHistory(selection_it.key());
  } else
  if (menu[history_pointer].is_array())
  {
    pushHistory(selectionIndex);
  }
  selection_it = menu[history_pointer].begin();
  displayCurrentView();
  selectionIndex = 0;
}

void MenuNavigator::backward()
{
  popHistory();
  selection_it = menu[history_pointer].begin();
  displayCurrentView();
}

void MenuNavigator::up()
{
  if (selection_it != menu[history_pointer].begin())
  {
    selection_it = prev(selection_it, 1);
    --selectionIndex;
  }
  else
  {
    if (menu[history_pointer].is_number())
      menu[history_pointer] = menu[history_pointer].get<int>()+1;
    else
    if (menu[history_pointer].is_boolean())
      menu[history_pointer] = !(menu[history_pointer].get<bool>());
  }
  displayCurrentView();
}

void MenuNavigator::down()
{
  if (next(selection_it, 1) != menu[history_pointer].end())
  {
    ++selection_it;
    ++selectionIndex;
  }
  else
  {
    if (menu[history_pointer].is_number())
      menu[history_pointer] = menu[history_pointer].get<int>()-1;
    else
    if (menu[history_pointer].is_boolean())
      menu[history_pointer] = !(menu[history_pointer].get<bool>());
  }
  displayCurrentView();
}

void MenuNavigator::displayCurrentView()
{
  //cout << "\033c";
  cout << endl << endl;
  if (menu[history_pointer].is_object())
  {
    for (json::iterator it = menu[history_pointer].begin(); it != menu[history_pointer].end(); ++it)
    {
      if (selection_it == it)
        cout << ">";
        else
        cout << " ";
      cout << it.key() << " : " << it.value() << endl;
    }
  } else
  if (menu[history_pointer].is_array())
  {
    for (json::iterator array_el = menu[history_pointer].begin(); array_el != menu[history_pointer].end(); ++array_el)
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
    cout << menu[history_pointer];
  }
}

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
