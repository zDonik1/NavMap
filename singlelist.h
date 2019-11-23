#pragma once

template<typename T>
class SingleList
{
private:

    // --- Private classes

    struct Node
    {

        T value;
        Node *next = nullptr;


        Node(T l_value) : value(l_value)
        {
        }

    };


    // --- Member variables

    Node *m_head = nullptr;


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
            if (m_ptr) {
                m_ptr = m_ptr->next;
            }
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

    SingleList() = default;

    SingleList(const SingleList &list)
    {
        for (const auto &node_val : list) {
            push_back(node_val);
        }
    }

    SingleList(SingleList &&list)
    {
        Node *temp = m_head;
        m_head = list.m_head;
        list.m_head = temp;
    }

    ~SingleList()
    {
        Node *ptr = m_head;
        Node *preptr = nullptr;

        while (ptr) {
            preptr = ptr;
            ptr = ptr->next;
            delete preptr;
        }
    }


    // --- Iterator methods

    forward_iterator begin()
    {
        return forward_iterator(m_head);
    }

    forward_iterator end()
    {
        return forward_iterator(nullptr);
    }

    forward_iterator begin() const
    {
        return forward_iterator(m_head);
    }

    forward_iterator end() const
    {
        return forward_iterator(nullptr);
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
        return !m_head;
    }

    void push_front(const T &l_value)
    {
        Node *new_node = new Node(l_value);
        new_node->next = m_head;
        m_head = new_node;
    }

    void push_back(const T &l_value)
    {
        if (empty()) {
            m_head = new Node(l_value);
            return;
        }

        Node *ptr = m_head;
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = new Node(l_value);
    }

    bool pop_front()
    {
        if (m_head) {
            Node *ptr = m_head;
            m_head = m_head->next;
            delete ptr;
            return true;
        }

        return false;
    }

};
