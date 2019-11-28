#pragma once

template<typename T>
class CircSingleList
{
private:

    // --- Private classes

    struct Node
    {

        T value;
        Node *next = nullptr;


        Node() = default;
        Node(T l_value) : value(l_value)
        {
        }

    };


    // --- Member variables

    Node *m_tail = nullptr;


    // --- Helper methods

    void initTail()
    {
        m_tail = new Node();
        m_tail->next = m_tail;
    }


public:

    // --- Public classes

    class forward_iterator
    {
    private:

        Node *m_ptr = nullptr;


    public:

        forward_iterator(Node *l_ptr) : m_ptr(l_ptr)
        {
        }

        void operator++ ()
        {
            m_ptr = m_ptr->next;
        }

        bool operator!= (const forward_iterator &itr) const
        {
            if (this->m_ptr != itr.m_ptr) {
                return true;
            }

            return false;
        }

        bool operator== (const forward_iterator &itr) const
        {
            return !(*this != itr);
        }

        T &operator* ()
        {
            return m_ptr->value;
        }

    };


    // --- C/D-tors

    CircSingleList()
    {
        initTail();
    }

    CircSingleList(const CircSingleList &list)
    {
        initTail();
        for (const auto &node_val : list) {
            push_back(node_val);
        }
    }

    CircSingleList(CircSingleList &&list)
    {
        initTail();
        Node *temp = m_tail;
        m_tail = list.m_tail;
        list.m_tail = temp;
    }

    ~CircSingleList()
    {
        Node *ptr = m_tail;
        Node *preptr = nullptr;

        do {
            preptr = ptr;
            ptr = ptr->next;
            delete preptr;
        }
        while (ptr != m_tail);
    }


    // --- Iterator methods

    forward_iterator begin()
    {
        return forward_iterator(m_tail->next->next);
    }

    forward_iterator end()
    {
        return forward_iterator(m_tail->next);
    }

    forward_iterator begin() const
    {
        return forward_iterator(m_tail->next->next);
    }

    forward_iterator end() const
    {
        return forward_iterator(m_tail->next);
    }

    forward_iterator find(const T &l_value)
    {
        for (auto itr = begin(); itr != end(); ++itr) {
            if (*itr == l_value) {
                return itr;
            }
        }

        return end();
    }


    // --- Member functions

    bool empty()
    {
        return m_tail->next == m_tail;
    }

    void push_front(const T &l_value)
    {
        bool is_empty = empty();

        Node *new_node = new Node(l_value);
        new_node->next = m_tail->next->next;
        m_tail->next->next = new_node;

        if (is_empty) {
            m_tail = new_node;
        }
    }

    void push_back(const T &l_value)
    {
        Node *new_node = new Node(l_value);
        new_node->next = m_tail->next;
        m_tail->next = new_node;
        m_tail = new_node;
    }

    bool pop_front()
    {
        if (!empty()) {
            Node *ptr = m_tail->next->next;
            m_tail->next->next = ptr->next;
            if (m_tail == ptr) {
                m_tail = m_tail->next;
            }
            delete ptr;
            return true;
        }

        return false;
    }

};
