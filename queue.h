#pragma once

#include "circsinglelist.h"


// Wrapper for CircSingleList
template<typename T>
class Queue
{
private:

    // --- Member variables

    CircSingleList<T> list;


public:

    // --- Member functions

    void push(const T &l_value)
    {
        list.push_back(l_value);
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
