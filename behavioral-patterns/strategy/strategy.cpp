/*!
 * Adapted from "Design Patterns in Modern C++"
 * Dmitri Nesteruk (Apress, 2018).
 */

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

enum class OutputFormat
{
    Md,
    Html,
    Latex,
    RawText
};

/*!
 * @brief Strategy
 *        Declares a common interface for all supported algorithms.
 *        Implemented by ConcreteStrategy.
 */
class ListStrategy
{
public:
    virtual ~ListStrategy() = default;

    virtual void addItem(std::ostringstream& p_oss, const std::string& p_item) = 0;

    /*!
     * Some formats actually do not have any start/end markers
     * for lists, so the ListStrategy offers default empty
     * implementations for those.
     */
    virtual void start  (std::ostringstream& p_oss) {}
    virtual void end    (std::ostringstream& p_oss) {}
};

/*!
 * @brief ConcreteStrategy
 *        Implements the algorithms using the Strategy interface.
 * 
 * A Markdown list item is written the following way :
 * // No start marker
 * * item1
 * * item2
 * // No end marker
 */
class MdListStrategy : public ListStrategy
{
public:
    void addItem(std::ostringstream& p_oss, const std::string& p_item) override
    {
        p_oss << " * " << p_item << "\n";
    }
};

/*!
 * @brief ConcreteStrategy
 *        Implements the algorithms using the Strategy interface.
 * 
 * A html list is written the following way :
 * <ul>  // Start the list
 *    <li>item1</li>
 *    <li>item2</li>
 * </ul> // End the list
 */
class HtmlListStrategy : public ListStrategy
{
public:
    void start  (std::ostringstream& p_oss) override { p_oss << "<ul>\n";  }

    void end    (std::ostringstream& p_oss) override { p_oss << "</ul>\n"; }

    void addItem(std::ostringstream& p_oss, const std::string& p_item) override
    {
        p_oss << "<li>" << p_item << "</li>\n";
    }
};

/*!
 * @brief ConcreteStrategy
 *        Implements the algorithms using the Strategy interface.
 * 
 * A Latex list is written the following way :
 * \begin{itemize}  // Start the list
 *    \item item1
 *    \item item2
 * \end{itemize}    // End the list
 */
class LatexListStrategy : public ListStrategy
{
public:
    void start  (std::ostringstream& p_oss) override { p_oss << "\\begin{itemize}\n"; }

    void end    (std::ostringstream& p_oss) override { p_oss << "\\end{itemize}\n";   }

    void addItem(std::ostringstream& p_oss, const std::string& p_item) override
    {
        p_oss << "\\item " << p_item << "\n";
    }
};

/*!
 * @brief ConcreteStrategy
 *        Implements the algorithms using the Strategy interface.
 * 
 * A raw text list is written the following way :
 * // No start marker
 *      - item1
 *      - item2
 * // No end marker
 */
class RawTextListStrategy : public ListStrategy
{
public:
    void addItem(std::ostringstream& p_oss, const std::string& p_item) override
    {
        p_oss << "\t- " << p_item << "\n";
    }
};

/*!
 * @brief Context
 *        Configured with a ConcreteStrategy object.
 *        Maintains a reference to that ConcreteStrategy object.
 *        Calls its interface to use the algorithm defined
 *        by the Strategy.
 */
class TextProcessor
{
public:
    TextProcessor( const OutputFormat p_format = OutputFormat::RawText ) :
        m_list(std::make_unique<RawTextListStrategy>())
    {}

    void setFormat( const OutputFormat p_format ) 
    { 
        switch( p_format )
        {
            case OutputFormat::Html   : m_list = std::make_unique<HtmlListStrategy   >(); break;
            case OutputFormat::Latex  : m_list = std::make_unique<LatexListStrategy  >(); break;
            case OutputFormat::Md     : m_list = std::make_unique<MdListStrategy     >(); break;
            case OutputFormat::RawText: m_list = std::make_unique<RawTextListStrategy>(); break;
        }
    }

    void clear(void)
    {
        m_oss.str("");
        m_oss.clear();
    }

    void append_list(const std::vector<std::string>& p_items)
    {
        m_list->start(m_oss);
        for ( auto& l_item : p_items )
            m_list->addItem(m_oss, l_item);
        m_list->end(m_oss);
    }
    std::string str(void) const { return m_oss.str(); }

private:
    std::ostringstream            m_oss;
    std::unique_ptr<ListStrategy> m_list;
};

int main()
{
    TextProcessor            myList;
    std::vector<std::string> myItems = {"item1", "item2", "item3"};

    // Raw text List (default behaviour)
    myList.append_list(myItems);
    std::cout << "\n----- RAW -----\n" << myList.str() << "\n";
    myList.clear();

    // Markdown List 
    myList.setFormat(OutputFormat::Md);
    myList.append_list(myItems);
    std::cout << "\n----- MARKDOWN -----\n" << myList.str() << "\n";
    myList.clear();

    // HTML List
    myList.setFormat(OutputFormat::Html);
    myList.append_list(myItems);
    std::cout << "\n----- HTML -----\n" << myList.str() << "\n";
    myList.clear();

    // Latex List
    myList.setFormat(OutputFormat::Latex);
    myList.append_list(myItems);
    std::cout << "\n----- LATEX -----\n" << myList.str() << "\n";
    myList.clear();

    return 0;
}

/*
----- RAW -----
        - item1
        - item2
        - item3


----- MARKDOWN -----
 * item1
 * item2
 * item3


----- HTML -----
<ul>
<li>item1</li>
<li>item2</li>
<li>item3</li>
</ul>


----- LATEX -----
\begin{itemize}
\item item1
\item item2
\item item3
\end{itemize}


*/
