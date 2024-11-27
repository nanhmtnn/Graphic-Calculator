#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>

#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

template <typename T>
class Stack
{
public:
  class Iterator
  {
  public:
    //Give access to list to access _ptr
    friend class Stack;

    //Default CTOR
    Iterator()
    { 
      _ptr = NULL;
    }
    //Point Iterator to where p is pointing to
    Iterator(node<T>* p)
    { 
      _ptr = p;
    }

    //Casting operator: true if _ptr not NULL
    //This turned out to be a pain!
    operator bool() 
    { 
      if (_ptr != NULL) return true;
      return false;
    }
    
    //dereference operator
    T& operator *()
    { 
      assert(_ptr); // _ptr != NULL
      return _ptr->_item;
    }               
    //member access operator
    T* operator ->()
    { 
      return _ptr;
    }
    //true if _ptr is NULL
    bool is_null()
    { 
      if (_ptr == true) return true;
      return false;
    }   

    //true if left != right
    friend bool operator !=(const Iterator &left, const Iterator &right)
    { 
      return left._ptr != right._ptr;
    }
    //true if left == right
    friend bool operator ==(const Iterator &left, const Iterator &right)
    { 
      return left._ptr == right._ptr;
    }

    //member operator:  ++it; or ++it = new_value
    Iterator& operator ++()
    { 
      _ptr = _ptr->_next;
      return *this;
    }
    //friend operator: it++
    friend Iterator operator ++(Iterator &it, int unused)
    { 
      Iterator temp;
      temp = it;
      it._ptr = it._ptr->_next;
      return temp;
    }
    
  private:
    node<T>* _ptr; //pointer being encapsulated
  };

  //constructor: CTOR
  Stack()
  {
    _top = NULL;
    _size = 0;
  }

  //BIG 3:
  Stack(const Stack<T>& copyMe)
  {
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
  }

  ~Stack()
  {
    _clear_list(_top);
    _size = 0;
  }

  Stack<T>& operator =(const Stack<T>& RHS)
  {
    if (this->_top == RHS._top) return *this;

    _size = RHS._size;
    _clear_list(this->_top);
    _top = _copy_list(RHS._top);
    return *this;
  }

  //Operations:
  void push(T item)
  {
    _insert_head(_top, item);
    _size++;
  }
  void pop()
  {
    // node<T>* temp = _top->_next;
    // _delete_node(_top, _top);
    // _top = temp;
    // _size--;

    node<T>* temp = new node<T>;
    if (_top != NULL)
    {
      temp = _top;
      _top = _top->_next;
      free(temp);
      _size--;
    }

  }

  //Accessors:
  Iterator begin() const            //Iterator to the head node
  {
    return Iterator(_top);
  }
  Iterator end() const              //Iterator to NULL
  {
    return Iterator(_last_node(_top)->_next);
  }

  //Checkers:
  int size() const
  {
    return _size;
  }
  bool empty()
  {
    return _top == NULL;
  }
  T top()
  {
    return _top->_item;
  }

  template<typename U>
  friend ostream& operator <<(ostream& outs, const Stack<U>& printMe);

private:
  node<T>* _top;
  int _size;
};

//Definition


template<typename U>
ostream& operator <<(ostream& outs, const Stack<U>& printMe)
{
  _print_list(printMe._top);
  return outs;
}






//TODO

#endif // MYSTACK_H