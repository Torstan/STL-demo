/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */


#include <stddef.h>
#include <iostream>
//#include <function.h>

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class T, class Distance> struct input_iterator {
  typedef input_iterator_tag iterator_category;
  typedef T                  value_type;
  typedef Distance           difference_type;
  typedef T*                 pointer;
  typedef T&                 reference;
};

struct output_iterator {
  typedef output_iterator_tag iterator_category;
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;
};

template <class T, class Distance> struct forward_iterator {
  typedef forward_iterator_tag iterator_category;
  typedef T                    value_type;
  typedef Distance             difference_type;
  typedef T*                   pointer;
  typedef T&                   reference;
};

template <class T, class Distance> struct bidirectional_iterator {
  typedef bidirectional_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef Distance                   difference_type;
  typedef T*                         pointer;
  typedef T&                         reference;
};

template <class T, class Distance> struct random_access_iterator {
  typedef random_access_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef Distance                   difference_type;
  typedef T*                         pointer;
  typedef T&                         reference;
};

template <class Category, class T, class Distance, class Pointer = T*, class Reference = T&>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};


template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type        value_type;
  typedef typename Iterator::difference_type   difference_type;
  typedef typename Iterator::pointer           pointer;
  typedef typename Iterator::reference         reference;
};

template <class T>
struct iterator_traits<T*> {
  typedef random_access_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef ptrdiff_t                  difference_type;
  typedef T*                         pointer;
  typedef T&                         reference;
};

template <class T>
struct iterator_traits<const T*> {
  typedef random_access_iterator_tag iterator_category;
  typedef T                          value_type;
  typedef ptrdiff_t                  difference_type;
  typedef const T*                   pointer;
  typedef const T&                   reference;
};

template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
  return iterator_traits<Iterator>::iterator_category();
}

template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

template <class Iterator>
inline typename iterator_traits<Iterator>::pointer
pointer_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::pointer>(0);
}

template <class Container>
class back_insert_iterator {
protected:
    Container* container;
public:
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    explicit back_insert_iterator(Container& x) : container(&x) {}
    back_insert_iterator<Container>&
    operator=(const typename Container::value_type& value) { 
        container->push_back(value);
        return *this;
    }
    back_insert_iterator<Container>& operator*() { return *this; }
    back_insert_iterator<Container>& operator++() { return *this; }
    back_insert_iterator<Container>& operator++(int) { return *this; }
};


template <class Container>
inline back_insert_iterator<Container> back_inserter(Container& x) {
  return back_insert_iterator<Container>(x);
}

template <class Container>
class front_insert_iterator {
protected:
    Container* container;
public:
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    explicit front_insert_iterator(Container& x) : container(&x) {}
    front_insert_iterator<Container>&
    operator=(const typename Container::value_type& value) { 
        container->push_front(value);
        return *this;
    }
    front_insert_iterator<Container>& operator*() { return *this; }
    front_insert_iterator<Container>& operator++() { return *this; }
    front_insert_iterator<Container>& operator++(int) { return *this; }
};


template <class Container>
inline front_insert_iterator<Container> front_inserter(Container& x) {
  return front_insert_iterator<Container>(x);
}

template <class Container>
class insert_iterator {
protected:
    Container* container;
    typename Container::iterator iter;
public:
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;

    insert_iterator(Container& x, typename Container::iterator i) 
        : container(&x), iter(i) {}
    insert_iterator<Container>&
    operator=(const typename Container::value_type& value) { 
        iter = container->insert(iter, value);
        ++iter;
        return *this;
    }
    insert_iterator<Container>& operator*() { return *this; }
    insert_iterator<Container>& operator++() { return *this; }
    insert_iterator<Container>& operator++(int) { return *this; }
};


template <class Container, class Iterator>
inline insert_iterator<Container> inserter(Container& x, Iterator i) {
  typedef typename Container::iterator iter;
  return insert_iterator<Container>(x, iter(i));
}

template <class BidirectionalIterator, class T, class Reference, 
          class Distance> 
class reverse_bidirectional_iterator {
    typedef reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                           Distance> self;
    friend bool operator==(const self& x, const self& y);
    friend bool operator!=(const self& x, const self& y);
protected:
    BidirectionalIterator current;
public:
    typedef bidirectional_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef Distance                   difference_type;
    typedef T*                         pointer;
    typedef Reference                  reference;

    reverse_bidirectional_iterator() {}
    explicit reverse_bidirectional_iterator(BidirectionalIterator x)
      : current(x) {}
    BidirectionalIterator base() { return current; }
    Reference operator*() const {
        BidirectionalIterator tmp = current;
        return *--tmp;
    }
    self& operator++() {
        --current;
        return *this;
    }
    self operator++(int) {
        self tmp = *this;
        --current;
        return tmp;
    }
    self& operator--() {
        ++current;
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        ++current;
        return tmp;
    }
};


template <class BidirectionalIterator, class T, class Reference,
          class Distance>
inline bool operator==(
    const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                         Distance>& x, 
    const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                         Distance>& y) {
    return x.current == y.current;
}

template <class BidirectionalIterator, class T, class Reference,
          class Distance>
inline bool operator!=(
    const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                         Distance>& x, 
    const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                         Distance>& y) {
    return x.current != y.current;
}

// This is the new version of reverse_iterator, as defined in the
//  draft C++ standard.  It relies on the iterator_traits template,
//  which in turn relies on partial specialization.  The class
//  reverse_bidirectional_iterator is no longer part of the draft
//  standard, but it is retained for backward compatibility.

template <class Iterator>
class reverse_iterator : public iterator_traits<Iterator>
{
protected:
  Iterator current;
public:
  typedef Iterator iterator_type;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::difference_type difference_type;
  typedef reverse_iterator<Iterator> self;

public:
  reverse_iterator() {}
  explicit reverse_iterator(iterator_type x) : current(x) {}

  reverse_iterator(const self& x) : current(x.current) {}

  template <class Iter>
  reverse_iterator(const reverse_iterator<Iter>& x) : current(x.current) {}
    
  iterator_type base() const { return current; }
  reference operator*() const {
    Iterator tmp = current;
    return *--tmp;
  }
  self& operator++() {
    --current;
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    --current;
    return tmp;
  }
  self& operator--() {
    ++current;
    return *this;
  }
  self operator--(int) {
    self tmp = *this;
    ++current;
    return tmp;
  }

  self operator+(difference_type n) const {
    return self(current - n);
  }
  self& operator+=(difference_type n) {
    current -= n;
    return *this;
  }
  self operator-(difference_type n) const {
    return self(current + n);
  }
  self& operator-=(difference_type n) {
    current += n;
    return *this;
  }
  reference operator[](difference_type n) { return *(*this + n); }  
}; 
 
template <class Iterator>
inline bool operator==(const reverse_iterator<Iterator>& x, 
                       const reverse_iterator<Iterator>& y) {
  return x.base() == y.base();
}

template <class Iterator>
inline bool operator!=(const reverse_iterator<Iterator>& x, 
                       const reverse_iterator<Iterator>& y) {
  return x.base() != y.base();
}

template <class Iterator>
inline bool operator<(const reverse_iterator<Iterator>& x, 
                      const reverse_iterator<Iterator>& y) {
  return y.base() < x.base();
}

template <class Iterator>
inline typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& x, 
          const reverse_iterator<Iterator>& y) {
  return y.base() - x.base();
}

template <class Iterator>
inline reverse_iterator<Iterator> 
operator+(typename reverse_iterator<Iterator>::difference_type n,
          const reverse_iterator<Iterator>& x) {
  return reverse_iterator<Iterator>(x.base() - n);
}


template <typename... T>
class DT;

template<typename T>
struct IntArrayIter : public iterator<random_access_iterator_tag, T, int> {
    IntArrayIter(T* p) : p_ (p) {}
    IntArrayIter(const IntArrayIter& iter) : p_(iter.p_) {}
    IntArrayIter& operator= (const IntArrayIter& other) {
        p_ = other.p_;
        return *this;
    }
    T& operator*() {
        return *p_;
    }
    T* operator++ () {
        return ++p_;
    }
    T* operator++ (int) {
        return p_++;
    }
    T* operator-- () {
        return --p_;
    }
    T* operator-- (int) {
        return p_--;
    }
    bool operator== (const IntArrayIter& other) {
        return p_ == other.p_;
    }
    bool operator!= (const IntArrayIter& other) {
        return p_ != other.p_;
    }
    T* p_;
};

template <typename T>
struct ListNode {
  ListNode(T val, ListNode* next = nullptr, ListNode* prev = nullptr): value_(val), next_(next), prev_(prev) {}
  T value_;
  ListNode* next_;
  ListNode* prev_;
};

template <typename T>
struct ListIter : public iterator<bidirectional_iterator_tag, T, int>{
  ListIter(ListNode<T>* p) : p_(p) {}
  ListIter(const ListIter& iter) : p_(iter.p_) {}
  ListIter& operator= (const ListIter& iter) {
    p_ = iter.p_;
    return *this;
  }
    T& operator*() {
        return p_->value_;
    }
    ListIter operator++ () {
        p_ = p_->next_;
        return *this;
    }
    ListIter operator++ (int) {
      T* q = p_;
      p_ = p_->next_;
      return ListIter(q);
    }
    ListIter operator-- () {
      p_ = p_->prev_;
      return *this;
    }
    ListIter operator-- (int) {
      T* q = p_;
      p_ = p_->prev;
      return ListIter(q);
    }
    bool operator== (const ListIter& other) {
        return p_ == other.p_;
    }
    bool operator!= (const ListIter& other) {
        return p_ != other.p_;
    }
  ListNode<T>* p_;
};


template<typename I>
void __min_elem(I begin, I end, bidirectional_iterator_tag c) {
  std::cout << "bidirectional_iterator_tag\n";
}

template<typename I>
void __min_elem(I begin, I end, random_access_iterator_tag c) {
  std::cout << "random_access_iterator_tag\n";
}

template<typename I>
void min_elem(I begin, I end) {
  __min_elem(begin, end, typename I::iterator_category());
}

int main() {
    if (true) {
      double a[] = {1.1,2.2,3.2};
      /*
      const int* p = &a[0];
      DT<decltype(distance_type(p)), decltype(value_type(p)), decltype(pointer_type(p))> {};
      auto q = distance_type(p);
      //DT<decltype(q)> {};
      */
      IntArrayIter rbegin = &a[3];
      IntArrayIter rend = &a[0];
      //DT<decltype(rbegin)::iterator_category> {};
      reverse_iterator iter_rbegin(rbegin);
      reverse_iterator iter_rend(rend);
      for (; iter_rbegin != iter_rend; ++ iter_rbegin) 
          std::cout << *iter_rbegin << std::endl;
      
      IntArrayIter begin = &a[0];
      IntArrayIter end = &a[3];    
      for (; begin != end; ++ begin) {
          std::cout << *begin << std::endl;
      }
      min_elem(begin, end);
    }

    if (true)  {
      ListNode<int>* p1 = new ListNode<int>(5);
      ListNode<int>* p2 = new ListNode<int>(6, nullptr, p1);
      ListNode<int>* p3 = new ListNode<int>(1, nullptr, p2);
      p1->prev_ = nullptr;
      p1->next_ = p2;
      p2->next_ = p3;
      p3->next_ = nullptr;
      ListIter<int> begin = ListIter<int>(p1);
      ListIter<int> end = ListIter<int>(p3->next_);
      for (; begin != end; ++ begin) {
          std::cout << *begin << std::endl;
      }
      min_elem(begin, end);

    }
    return 0;
}

