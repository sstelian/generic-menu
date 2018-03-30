#pragma once

#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <string>

class MenuItem
{
public:
  typedef std::unique_ptr<MenuItem> unique_it_ptr;
  MenuItem(const MenuItem&) = delete;
  MenuItem& operator=(const MenuItem&) = delete;
  ~MenuItem() = default;
  MenuItem() : m_name{} {_parent = nullptr; }; //root constructor
  MenuItem(std::string const &name) : m_name{name}{ _parent = nullptr; }; //intermediate node constructor
  //leaf constructor
  MenuItem(std::string const &name,
           std::function<void ()> _leafInitialAction,
           std::function<void ()> _leafUp,
           std::function<void ()> _leafDown,
           std::function<void ()> _leafFinal) :
              m_name{name},
              leafInitialAction{_leafInitialAction},
              leafUp{_leafUp},
              leafDown{_leafDown},
              leafFinal{_leafFinal}{};
  std::string name() {return m_name;}
  MenuItem* addNode(unique_it_ptr &subNode);
  std::vector<unique_it_ptr> *children();
  MenuItem* parent();
  void callInitial();
  void callUp();
  void callDown();
  void callFinal();
  bool hasChildren();
  bool hasParent();
  MenuItem* child(int index);

private:
  std::string m_name;
  std::function<void ()> leafInitialAction, leafUp, leafDown, leafFinal;
  std::vector<unique_it_ptr> m_children;
  MenuItem* _parent;
};
