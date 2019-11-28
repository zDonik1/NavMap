#pragma once

#include "circsinglelist.h"


// Wrapper for CircSingleList
template<typename T>
class Stack
{
private:

    // --- Member variables

    CircSingleList<T> m_list;


public:

    // --- Member functions

    void push(const T &l_value)
    {
        m_list.push_front(l_value);
    }

    bool pop()
    {
        return m_list.pop_front();
    }

    T &top()
    {
        return *m_list.begin();
    }

    bool empty()
    {
        return m_list.empty();
    }

};
