#include <iostream>

class Singleton 
{
    // Public methods
    public :
        static Singleton& getInstance(void) {
            // This is thread-safe since C++11
            static Singleton instance;
            return instance;
        }

        void setID(int p_id)   { m_id = p_id; }
        int  getID(void) const { return m_id; }

    // Private methods
    private :
         Singleton() : m_id(0) {} /*!< Cstr */
        ~Singleton() {} /*!< Dstr */

         Singleton(const Singleton&)            = delete; /*!< Cpy cstrc  */
         Singleton(Singleton&&)                 = delete; /*!< Mve cstrc  */
         Singleton& operator=(const Singleton&) = delete; /*!< Cpy assign */
         Singleton& operator=(Singleton&&)      = delete; /*!< Mve assign */

    // Private attributes (used as example only)
    private :
        int m_id;
};


int main() {

    Singleton::getInstance().setID(5);
    std::cout << "Singleton ID is now " << Singleton::getInstance().getID() << std::endl;
    Singleton::getInstance().setID(0);
    std::cout << "Singleton ID is now " << Singleton::getInstance().getID() << std::endl;

    return 0;
}