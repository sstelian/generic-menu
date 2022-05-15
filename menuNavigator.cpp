#include "menuNavigator.hxx"

//#define MENU_DEBUG

//TODO: remove std::cout
//TODO: display dependecy injection
using namespace std;

//selected options are appended to the json_pointer
//the json_pointer is then used for navigation and for altering primitive values
void MenuNavigator::forward()
{
  if (selection().is_object())
  {
    // handle regular object
    pushHistory(selection_it.key());
    selection_it = selection().begin();

    // handle predefined list
    if (contains_element(selection(), "_predefined_list") && (contains_element(selection(), "_selection")))
    {
      pushHistory("_predefined_list");
      selection_it = selection().begin();
    }
  } else
  // handle arrays but do not allow changing elements in a predefined list
  if (selection().is_array() && (history_pointer.to_string().find("_predefined_list") == std::string::npos))
  {
    pushHistory(selectionIndex);
    selection_it = selection().begin();
  }

  // skip redundant step
  if ((selection().is_object()) && (selection().size() == 1))
  {
    pushHistory(selection_it.key());
    selection_it = selection().begin();
  }

  displayCurrentView();
  selectionIndex = 0;
}

//removes last option from json_pointer and displays new view
void MenuNavigator::backward()
{
  if (history_pointer.to_string() != "")
  {
    popHistory();
    
    // save old selection iterator for predefined lists handling
    auto old_selection_it = selection_it;
    selection_it = selection().begin();

    // handle predefined list
    if (selection().is_object() && contains_element(selection(), "_predefined_list") && (contains_element(selection(), "_selection")))
    {
      // save predefined list selection
      string predefinedListSelection = (*old_selection_it).dump();
      // remove all double-quote characters
      predefinedListSelection.erase(
        remove(predefinedListSelection.begin(), predefinedListSelection.end(), '\"'),
        predefinedListSelection.end()
      );
      selection()["_selection"] = predefinedListSelection;

      // hide predefined list implementation from menu
      popHistory();
      selection_it = selection().begin();
    }

    if ((selection().is_object()) && (selection().size() == 1)) //skip redundant step
    {
      popHistory();
      selection_it = selection().begin();
    }
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
    else
    if (selection().is_number_float())
      selection() = selection().get<float>()+0.5;
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
    if (selection().is_number_integer())
      selection() = selection().get<int>()-1;
    else
    if (selection().is_boolean())
      selection() = !(selection().get<bool>());
    else
    if (selection().is_number_float())
      selection() = selection().get<float>()-0.5;
  }
  displayCurrentView();
}

bool MenuNavigator::done()
{
  return _done;
}

void MenuNavigator::displayCurrentView()
{
  #ifdef MENU_DEBUG
    cout << endl << endl;
  #else
    cout << "\033c";
  #endif

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
      #ifdef MENU_DEBUG
        cout << it.key() << " : " << it.value() << endl;
      #else
      cout << it.key() << endl;
      #endif
    }
  } else
  //display each key:value pair of each element of the array
  if (selection().is_array())
  {
    for (json::iterator element = selection().begin(); element != selection().end(); ++element)
    {
      if (selection_it == element)
        cout << ">";
        else
        cout << " ";
        cout << (*element).dump() << endl;
    }
  } else // selection is primitive
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
