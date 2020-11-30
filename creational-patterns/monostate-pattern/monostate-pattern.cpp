#include <iostream>
#include <string>

class Monostate 
{
    // Public methods
    public :
         Monostate() {} /*!< Cstr */
        ~Monostate() {} /*!< Dstr */

        void setID(int p_id)   { m_id = p_id; }
        int  getID(void) const { return m_id; }

        void        setName(std::string&& p_name) { m_name = p_name; }
        std::string getName(void) const { return m_name; }

    // Private attributes
    /*!< Shared between every instances */
    private :
        static int         m_id; 
        static std::string m_name;
};

int Monostate::m_id           = 0;
std::string Monostate::m_name = "";

int main() {

    Monostate m1, m2;
    m1.setID(3);
    std::cout << "Every monostates now have ID " << m2.getID() << std::endl;
    m2.setName("Global");
    std::cout << "Every monostates now have name " << m1.getName() << std::endl;

    return 0;
}