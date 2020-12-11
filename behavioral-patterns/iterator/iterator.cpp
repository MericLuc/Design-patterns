#include <memory>
#include <iostream>
#include <cstdint>
#include <cstring>

template <typename Item>
class staticArray {
public:
    // ------------- Iterators -------------- //
    typedef int size_type;

    class iterator
    {
    public:
        /* C++17 comittee voted to depreciate inheriting from std::iterator
             and recommandates to write the following typedefs instead */
        typedef iterator                   self_type;
        typedef Item                       value_type;
        typedef Item&                      reference;
        typedef Item*                      pointer;
        typedef int                        difference_type;
        typedef std::forward_iterator_tag  iterator_category;

        iterator(pointer p_ptr) : m_ptr(p_ptr) {}
        virtual ~iterator() = default;

        self_type operator++(int dummy) /* Postfix */ {
            (void)dummy; self_type l_ret = *this; m_ptr++; return l_ret;
        }
        self_type operator++(void)      /* Prefix */  { m_ptr++; return *this;             }
        reference operator* (void)                    { return *m_ptr;                     }
        pointer   operator->(void)                    { return m_ptr;                      }
        bool      operator==(const self_type& p_rhs ) { return m_ptr == p_rhs.m_ptr;       }
        bool      operator!=(const self_type& p_rhs ) { return m_ptr != p_rhs.m_ptr;       }

    private:
        pointer m_ptr;
    };

    class reverse_iterator
    {
    public:
        /* C++17 comittee voted to depreciate inheriting from std::iterator
             and recommandates to write the following typedefs instead */
        typedef reverse_iterator           self_type;
        typedef Item                       value_type;
        typedef Item&                      reference;
        typedef Item*                      pointer;
        typedef int                        difference_type;
        typedef std::forward_iterator_tag  iterator_category;

        reverse_iterator(pointer p_ptr) : m_ptr(p_ptr) {}
        virtual ~reverse_iterator() = default;

        self_type operator++(int dummy) /* Postfix */ {
           (void)dummy; self_type l_ret = *this; m_ptr--; return l_ret;
        }
        self_type operator++(void)      /* Prefix */  { m_ptr--; return *this;             }
        reference operator* (void)                    { return *m_ptr;                     }
        pointer   operator->(void)                    { return m_ptr;                      }
        bool      operator==(const self_type& p_rhs)  { return m_ptr == p_rhs.m_ptr;       }
        bool      operator!=(const self_type& p_rhs)  { return m_ptr != p_rhs.m_ptr;       }

    private:
        pointer m_ptr;
    };

    class const_iterator
    {
    public:
        /* C++17 comittee voted to depreciate inheriting from std::iterator
             and recommandates to write the following typedefs instead */
        typedef const_iterator             self_type;
        typedef Item                       value_type;
        typedef Item&                      reference;
        typedef Item*                      pointer;
        typedef int                        difference_type;
        typedef std::forward_iterator_tag  iterator_category;

        const_iterator(pointer p_ptr) : m_ptr(p_ptr) {}
        virtual ~const_iterator() = default;

        self_type       operator++(int dummy) /* Postfix */ {
            (void)dummy; self_type l_ret = *this; m_ptr++; return l_ret;
        }
        self_type       operator++(void)      /* Prefix */  { m_ptr++; return *this;       }
        const reference operator* (void)                    { return *m_ptr;               }
        pointer         operator->(void)                    { return m_ptr;                }
        bool            operator==(const self_type& p_rhs)  { return m_ptr == p_rhs.m_ptr; }
        bool            operator!=(const self_type& p_rhs)  { return m_ptr != p_rhs.m_ptr; }

    private:
        pointer m_ptr;
    };

    // ----- Constructors && destructor ----- //
    staticArray(size_type p_capacity) : m_capa(p_capacity) {
        ASSERT(m_capa >= 0, "staticArray cannot have a negative capacity!");
        m_data = new Item[m_capa];
    }
    virtual ~staticArray() { clear(); }

    // ----------- Public methods ----------- //
    size_type size     (void) const { return m_capa; }

    void clear(void) {
        if ( m_data ) {
            delete[] m_data;
            m_data = nullptr;
            m_capa = 0;
        }
    }

    Item& operator[](size_type p_index) {
        ASSERT(p_index >= 0 && p_index < m_capa, "Out of range!");
        return m_data[p_index];
    }

    const Item& operator[](size_type p_index) const {
       ASSERT(p_index >= 0 && p_index < m_capa, "Out of range!");
       return m_data[p_index];
    }

    iterator         begin  (void)       { return iterator(m_data);                }
    iterator         end    (void)       { return iterator(m_data + m_capa);       }

    reverse_iterator rbegin (void)       { return reverse_iterator(m_data + m_capa - 1);   }
    reverse_iterator rend   (void)       { return reverse_iterator(m_data - 1);            }

    const_iterator   cbegin (void) const { return const_iterator(m_data);          }
    const_iterator   cend   (void) const { return const_iterator(m_data + m_capa); }

protected:
    void ASSERT(bool cond, const std::string& msg) {
        if ( !(cond) ) {
            std::cerr << "Assertion `" << cond << "` failed in " << __FILE__
                      << " line " << __LINE__ << ": " << msg << std::endl;
            std::terminate();
        }
    }

private:
    size_type m_capa;
    Item*     m_data;
};

// ------------ Client code ------------ //
int main()
{
    staticArray<int> myArray(100);

    int i(0);
    for ( auto it  = myArray.begin();
               it != myArray.end  ();
          it++ ) {
        *it = i++;
    }

    for ( auto it  = myArray.rbegin();
               it != myArray.rend  ();
          it++ ) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << myArray[8]   << std::endl;
    // std::cout << myArray[102] << std::endl; /*!< Throws */

    return 0;
}
