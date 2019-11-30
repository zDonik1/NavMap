#pragma once

#include <memory>
#include <iterator>


template<typename T, typename Alloc = std::allocator<T>>
class DynArray
{
public:

    class random_iterator;


private:

    // --- Member variables

    Alloc alloc;
    T *m_array = nullptr;
    size_t m_arr_size = 0;
    size_t m_buff_size = 1;


    // --- Helper methods

    void allocate()
    {
        m_array = alloc.allocate(1);
        m_buff_size = 1;
    }

    void reallocate(size_t l_size)
    {
        if (l_size > m_buff_size) {
            T *ptr = alloc.allocate(l_size);
            for (size_t i = 0; i < m_arr_size; ++i) {
                alloc.construct(ptr + i, m_array[i]);
                alloc.destroy(m_array + i);
            }
            alloc.deallocate(m_array, m_buff_size);
            m_array = ptr;
            m_buff_size = l_size;
        }
    }

    void checkSize()
    {
        if (!m_array) {
            allocate();
        }
        if (m_arr_size == m_buff_size) {
            reallocate(m_buff_size * 2);
        }
    }

    void shift_right(random_iterator l_itr)
    {
        if (m_arr_size > 0) {
            for (auto itr = end(); itr != l_itr - 1; --itr) {
                *itr = *(itr - 1);
            }
        }
    }


public:

    // --- Public classes

    class random_iterator
    {
    private:

        T *m_ptr = nullptr;


    public:

        using difference_type = int32_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::random_access_iterator_tag;


        random_iterator(pointer l_ptr) : m_ptr(l_ptr)
        {
        }

        const pointer get() const
        {
            return m_ptr;
        }

        void operator++ ()
        {
            ++m_ptr;
        }

        void operator-- ()
        {
            --m_ptr;
        }

        random_iterator operator+ (size_t l_n) const
        {
            return random_iterator(m_ptr + l_n);
        }

        random_iterator operator- (size_t l_n) const
        {
            return random_iterator(m_ptr - l_n);
        }

        int32_t operator+ (random_iterator l_itr) const
        {
            return m_ptr + l_itr.m_ptr;
        }

        int32_t operator- (random_iterator l_itr) const
        {
            return m_ptr - l_itr.m_ptr;
        }

        bool operator!= (const random_iterator &itr) const
        {
            if (this->m_ptr != itr.m_ptr) {
                return true;
            }

            return false;
        }

        bool operator== (const random_iterator &itr) const
        {
            return !(*this != itr);
        }

        reference operator* ()
        {
            return *m_ptr;
        }

        const T &operator* () const
        {
            return *m_ptr;
        }
    };


    // --- C/D-tors

    DynArray()
    {
        allocate();
    }

    DynArray(size_t l_size)
    {
        resize(l_size);
    }

    DynArray(size_t l_size, const T &l_obj)
    {
        resize(l_size, l_obj);
    }

    DynArray(const DynArray &l_dyn_array)
    {
        for (auto value : l_dyn_array) {
            push_back(value);
        }
    }


    // --- Iterator methods

    random_iterator begin()
    {
        return random_iterator(m_array);
    }

    random_iterator end()
    {
        return random_iterator(m_array + m_arr_size);
    }

    random_iterator begin() const
    {
        return random_iterator(m_array);
    }

    random_iterator end() const
    {
        return random_iterator(m_array + m_arr_size);
    }

    const random_iterator cbegin() const
    {
        return begin();
    }

    const random_iterator cend() const
    {
        return end();
    }


    // --- Member functions

    void resize(size_t l_size, const T &l_obj = T())
    {
        reallocate(l_size);

        for (int i = m_arr_size; i < l_size; ++i) {
            alloc.construct(m_array + i, l_obj);
        }

        m_arr_size = l_size;
    }

    size_t size() const
    {
        return m_arr_size;
    }

    void push_front(const T &l_obj)
    {
        checkSize();

        shift_right(begin());

        m_array[0] = l_obj;

        ++m_arr_size;
    }

    void push_back(const T &l_obj)
    {
        checkSize();

        m_array[m_arr_size] = l_obj;

        ++m_arr_size;
    }

    void insert(random_iterator l_itr, const T &l_obj)
    {
        checkSize();

        shift_right(l_itr);
        *l_itr = l_obj;

        ++m_arr_size;
    }


    // --- Accessors

    T &at(size_t l_index)
    {
        return m_array[l_index];
    }

    const T &at(size_t l_index) const
    {
        return m_array[l_index];
    }

    T &operator[] (size_t l_index)
    {
        return at(l_index);
    }

    const T &operator[] (size_t l_index) const
    {
        return at(l_index);
    }

    T &back()
    {
        return m_array[m_arr_size - 1];
    }

    const T &back() const
    {
        return m_array[m_arr_size - 1];
    }

};
