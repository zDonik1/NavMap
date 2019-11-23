#pragma once

#include "singlelist.h"


// Wrapper for SingleList
template<typename T>
class Stack
{
private:

    // --- Member variables

    SingleList<T> list;


public:

    // --- Member functions

    void push(const T &l_value)
    {
        list.push_front(l_value);
    }

    bool pop()
    {
        return list.pop_front();
    }

    T &top()
    {
        return *list.begin();
    }

    bool empty()
    {
        return list.empty();
    }

};
