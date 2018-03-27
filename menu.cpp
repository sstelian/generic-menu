#include "menu.hxx"

MenuItem* MenuItem::addNode(MenuItem::unique_it_ptr &subNode)
{
  subNode->_parent = this;
  m_children.push_back(move(subNode));
  return m_children[m_children.size() - 1].get();
}

std::vector<MenuItem::unique_it_ptr>* MenuItem::children()
{
  return &m_children;
}

MenuItem* MenuItem::parent()
{
  return _parent;
}

void MenuItem::call()
{
  if (m_action != nullptr)
    m_action();
}

bool MenuItem::hasChildren()
{
  return (m_children.size() > 0);
}

bool MenuItem::hasParent()
{
  return (_parent != nullptr);
}

MenuItem* MenuItem::child(int index)
{
  if (this->hasChildren())
  {
    return m_children[index].get();
  }
  else
  {
    return nullptr;
  }
}
