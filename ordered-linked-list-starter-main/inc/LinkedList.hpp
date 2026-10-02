#ifndef ORDEREDLINKEDLIST_HPP
#define ORDEREDLINKEDLIST_HPP
#include <iostream>
#include <stdexcept>

using std::ostream;

template <typename Type>
struct Node
{
  Type data{};
  Node<Type>* next{ nullptr };
};

template <typename Type>
class OrderedLinkedList;

template <typename Type>
ostream& operator<<(ostream&, const OrderedLinkedList<Type>& list);

template <typename Type>
class OrderedLinkedList
{
public:
  OrderedLinkedList() { } // Default constructor has no code boy has data members initialize themselves
  OrderedLinkedList(const OrderedLinkedList& other);
  OrderedLinkedList<Type>& operator=(const OrderedLinkedList<Type>& other);
  ~OrderedLinkedList();

  int size() const;
  bool empty() const;
  Type get(int) const;
  Type getFirst() const;
  Type getLast() const;
  void insert(const Type&);
  int find(const Type&) const;
  void remove(const Type&);
  void clear();
  OrderedLinkedList<Type> everyOtherOdd();
  OrderedLinkedList<Type> everyOtherEven();
  friend ostream& operator<< <>(ostream&, const OrderedLinkedList<Type>& list);
private:
  Node<Type>* front{ nullptr };
  Node<Type>* back{nullptr};
  int count{ 0 };
};

template <typename Type>
OrderedLinkedList<Type>::OrderedLinkedList(const OrderedLinkedList<Type>& other)
{
  for (Node<Type>* cur = other.front; cur != nullptr; cur = cur->next)
  {
    Node<Type>* n = new Node<Type>{ cur->data, nullptr };
    if (back == nullptr) front = n;
    else back->next = n;
    back = n;
    ++count;
  }
}

template <typename Type>
OrderedLinkedList<Type>& OrderedLinkedList<Type>::operator=(const OrderedLinkedList& other)
{
  if (this != &other)
  {
    clear();
    for (Node<Type>* cur = other.front; cur != nullptr; cur = cur->next)
    {
      Node<Type>* n = new Node<Type>{ cur->data, nullptr };
      if (back == nullptr) front = n;
      else back->next = n;
      back = n;
      ++count;
    }
  }
  return *this;
}

template <typename Type>
OrderedLinkedList<Type>::~OrderedLinkedList()
{
  clear();
}

template <typename Type>
int OrderedLinkedList<Type>::size() const
{
  return count;
}

template <typename Type>
bool OrderedLinkedList<Type>::empty() const
{
  return count == 0;
}

template <typename Type>
Type OrderedLinkedList<Type>::get(int pos) const
{
  if (pos < 0 || pos >= count)
    throw std::out_of_range("position out of range");
  Node<Type>* cur = front;
  for (int i = 0; i < pos; ++i) cur = cur->next;
  return cur->data;
}

template <typename Type>
Type OrderedLinkedList<Type>::getFirst() const
{
  if (empty()) throw std::out_of_range("list is empty");
  return front->data;
}

template <typename Type>
Type OrderedLinkedList<Type>::getLast() const
{
  if (empty()) throw std::out_of_range("list is empty");
  return back->data;
}

template <typename Type>
void OrderedLinkedList<Type>::insert(const Type& item)
{
  Node<Type>* n = new Node<Type>{ item, nullptr };
  if (front == nullptr)
  {
    front = back = n;
  }
  else if (item < front->data)
  {
    n->next = front;
    front = n;
  }
  else
  {
    // Insert after the last node that is not greater than item (stable for duplicates).
    Node<Type>* prev = front;
    while (prev->next != nullptr && !(item < prev->next->data))
      prev = prev->next;
    n->next = prev->next;
    prev->next = n;
    if (n->next == nullptr) back = n;
  }
  ++count;
}

template <typename Type>
int OrderedLinkedList<Type>::find(const Type& item) const
{
  int pos = 0;
  for (Node<Type>* cur = front; cur != nullptr; cur = cur->next, ++pos)
    if (cur->data == item) return pos;
  return -1;
}

template <typename Type>
void OrderedLinkedList<Type>::remove(const Type& item)
{
  Node<Type>* prev = nullptr;
  Node<Type>* cur = front;
  while (cur != nullptr && !(cur->data == item))
  {
    prev = cur;
    cur = cur->next;
  }
  if (cur == nullptr) return;
  if (prev == nullptr) front = cur->next;
  else prev->next = cur->next;
  if (cur == back) back = prev;
  delete cur;
  --count;
}

template <typename Type>
void OrderedLinkedList<Type>::clear()
{
  while (front != nullptr)
  {
    Node<Type>* tmp = front;
    front = front->next;
    delete tmp;
  }
  back = nullptr;
  count = 0;
}

template <typename Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherOdd()
{
  OrderedLinkedList<Type> retVal;
  int i = 0;
  for (Node<Type>* cur = front; cur != nullptr; cur = cur->next, ++i)
    if (i % 2 == 0) retVal.insert(cur->data);
  return retVal;
}

template <typename Type>
OrderedLinkedList<Type> OrderedLinkedList<Type>::everyOtherEven()
{
  OrderedLinkedList<Type> retVal;
  int i = 0;
  for (Node<Type>* cur = front; cur != nullptr; cur = cur->next, ++i)
    if (i % 2 == 1) retVal.insert(cur->data);
  return retVal;
}

template <typename Type>
ostream& operator<<(ostream& out, const OrderedLinkedList<Type>& list)
{
  for (Node<Type>* cur = list.front; cur != nullptr; cur = cur->next)
  {
    out << cur->data;
    if (cur->next != nullptr) out << "->";
  }
  return out;
}
#endif