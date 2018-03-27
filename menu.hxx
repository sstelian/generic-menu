#pragma once

#include <functional>
#include <string>
#include <memory>
#include <vector>

class MenuItem
{
public:
  typedef std::unique_ptr<MenuItem> unique_it_ptr;
  MenuItem(const MenuItem&) = delete;
  MenuItem& operator=(const MenuItem&) = delete;
  ~MenuItem() = default;
  MenuItem(std::string const &name) : m_name{name}{ _parent = nullptr; };
  MenuItem(std::string const &name, std::function<void ()> action) : m_name{name}, m_action{action} {};
  std::string name() {return m_name;}
  MenuItem* addNode(unique_it_ptr &subNode);
  std::vector<unique_it_ptr> *children();
  MenuItem* parent();
  void call();
  bool hasChildren();
  bool hasParent();
  MenuItem* child(int index);

private:
  std::string m_name;
  std::function<void ()> m_action;
  std::vector<unique_it_ptr> m_children;
  MenuItem* _parent;
};
