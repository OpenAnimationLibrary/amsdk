////////////////////////////////////////////////////////////////////////////
// Single linked list implementation.
// By Jonathan Shapiro from the book "A C++ Toolkit"
// For the clopy and minor changes: Eleftherios Gkioulekas
//
// Usage:
// ------
// 1. On the header file of your module, include this file.
//    #include "list.h"
//    or something like that
// 2. Say you have a class called "Object" and you know you will be needing
//    linked lists of that class. Declare the class
//    class Object;
// 3. Call the macros "MakeLink" and "MakeList"
//    MakeLink(Object);
//    MakeList(Object);
//    This macro will implement two classes: ObjectLink and ObjectList
// 4. Define the class Object and inherit from the class ObjectLink
//    The methods next and prev are reserved, as are the _next and _prev
//    variables.
//
// The *List class contains the following methods:
// ObjectList list;
// * list interface
// list.append(Object *obj)        // add entry to the end of the list
// list.prepend(Object *obj)       // add entry to beginning of the list
// list.remove(Object *obj)        // add entry to the end of the list
// list.erase()                    // wipe out the list entirely
// * stack interface
// list.push(Object *obj)          // Push an object to the stack
// obj = list.pop()                // Pop an object from the stack
// obj = list.top()                // Look at the top element on stack
// * accessors
// obj = list.first()              // first element on list
// obj = list.last()               // last element on list
// obj = obj->next();              // next object
// forEach(obj,list) {...stuff...}  loop over all Object *obj of
// list ObjectList list;
///////////////////////////////////////////////////////////////////////////

#ifndef __INCLUDED_LIST
#define __INCLUDED_LIST

// Declaration
class Link;
class List;

// Single link class - base class for any object that needs to be part
// of a singly linked list
class Link
{
 friend class List;
 protected:
 Link *_next;
 Link *_prev;

 public:
 Link()            { _next = _prev = 0; }
 virtual ~Link();
 Link *next(void)  { return _next; }
 Link *prev(void)  { return _prev; }
};

class List
{
 protected:
 Link *_first;
 Link *_last;

 public: 
 // Constructor and destructor
 List()            { _first = _last = 0; }
 virtual ~List()   { erase(); }
 inline void erase(void);

 Link *last(void)  { return _last; }
 Link *first(void) { return _first; }
 
 inline List& append(Link *);
 inline List& prepend(Link *);
 inline List& remove(Link *);

 List& push(Link *l) { return append(l); }
 Link *pop(void)     { Link *l = _last; remove(_last); return l; }
 Link *top(void)     { return _last; }
};

// Generic single link class - base class for any object that needs to be 
// part of a singly linked list. This version is strongly typed

// I don't like using generic.h so here is a safer "name2" macro
#ifndef _name2
#define _name2(a,b) a ## b
#endif

// Macros to implement strongly typed classes.
#define MakeLink(TYPE)                                         \
class _name2(TYPE,Link) : public Link                          \
{                                                              \
 public:                                                       \
 _name2(TYPE,Link)():Link()   { }                              \
 virtual ~_name2(TYPE,Link)() { }                              \
 TYPE *next() { return (TYPE *) _next; }                       \
 TYPE *prev() { return (TYPE *) _prev; }                       \
}
#define MakeList(TYPE)                                         \
class _name2(TYPE,List) : public List                          \
{                                                              \
 public:                                                       \
 _name2(TYPE,List)():List()   { }                              \
 virtual ~_name2(TYPE,List)() { }                              \
 TYPE *last()  { return (TYPE *) _last; }                      \
 TYPE *first() { return (TYPE *) _first; }                     \
 TYPE *pop()   { return (TYPE *) List::pop(); }                \
 TYPE *top()   { return (TYPE *) _last; }                      \
}
#define MakeListBase(TYPE)                                     \
class _name2(TYPE,List) : public List                          \
{                                                              \
 public:                                                       \
 _name2(TYPE,ListBase)():List()   { }                          \
 virtual ~_name2(TYPE,ListBase)() { }                          \
 TYPE *last()  { return (TYPE *) _last; }                      \
 TYPE *first() { return (TYPE *) _first; }                     \
 TYPE *pop()   { return (TYPE *) List::pop(); }                \
 TYPE *top()   { return (TYPE *) _last; }                      \
}


// Define a macro for looping over all the elements in a list
#define forEach(OBJECT_PTR,LIST)                               \
for ((OBJECT_PTR) = (LIST).first();                            \
     (OBJECT_PTR) != 0;                                        \
     (OBJECT_PTR) = (OBJECT_PTR)->next())                      \

// Linked list implementation
inline List& List::append(Link *l)
{
 if (_last) { _last->_next = l; l->_prev = _last; }
 else       { _first = l; }
 _last = l;
 return *this;
}

inline List& List::prepend(Link *l)
{
 if (_first) { _first->_prev = l; l->_next = _first; }
 else        { _last = l; }
 _first = l;
 return *this; 
}

inline List& List::remove(Link *l)
{
 if (l == _first) { _first = _first->_next; }
 if (l == _last)  { _last  = _last->_prev; }
 if (l->_next)    { l->_next->_prev = l->_prev; l->_next = 0; }
 if (l->_prev)    { l->_prev->_next = l->_next; l->_prev = 0; }
 return *this;
}

inline Link::~Link()
{
 if (_next) _next->_prev = _prev;
 if (_prev) _prev->_next = _next;
 _next = 0;
 _prev = 0; 
}

inline void List::erase(void)
{ 
 Link *l,*n; 
 for (l = _first; l != 0; l = n) { n = l->_next; delete l; }
 _first = 0; _last = 0;
}

#endif

