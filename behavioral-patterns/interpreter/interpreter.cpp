#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<memory>
#include<stack>

/*!
 * @brief The interpreter is actually implemented as a
 *        Facade such that the Client only uses high level
 *        features without having to dive into the "mess".
 */
class INTERPRETER {
public:
    INTERPRETER() = default;
    ~INTERPRETER() = default;

    int eval(const std::string& p_input) {
        if ( !conformityCheck(p_input) ) { throw "Input string is not conform!"; }

        auto        l_lexOutput   = lex  (p_input    );
        auto        l_parseOutput = parse(l_lexOutput);

        return l_parseOutput->eval();
    }

protected:
    struct TOKEN {
        enum TTYPE { minus, plus, lparen, rparen, integer } m_type;
        std::string m_text;

        TOKEN( TTYPE p_type, const std::string& p_text ) : m_type(p_type), m_text(p_text) {}

        friend std::ostream& operator<<(std::ostream &p_os, const TOKEN& p_token) {
            p_os << " " << p_token.m_text << " ";
            return p_os;
        }
    };
    struct ParseElem {
        virtual int eval(void) const = 0;
    };

    struct IntegerElem : ParseElem {
        int m_val;

        IntegerElem(int p_val) : m_val(p_val) {}

        int eval(void) const override { return m_val; }
    };

    struct BinaryElem : ParseElem {
        enum Type { add, sub } m_type;

        std::shared_ptr<ParseElem> lhs, rhs;

        int eval(void) const override {
            if ( !rhs )          { return lhs->eval();               }
            if ( m_type == add ) { return lhs->eval() + rhs->eval(); }
            return lhs->eval() - rhs->eval();
        }
    };

    template <typename T>
    T lexical_cast(const std::string& p_str)
    {
        T l_res;
        std::istringstream iss;
        iss.str(p_str);
        iss >> l_res;

        return l_res;
    }

/*!
 * @brief : Methods to compute the interpreted result
 *          that are hidden from the client.
 */
private:

    /*!
     * @brief : Parses the tokens to get the required ParseElem.
     */
    std::shared_ptr<ParseElem> parse(const std::vector<TOKEN>& p_toks ) {
        auto l_res = std::make_shared<BinaryElem>();
        bool l_have_lhs{false};

        for ( int i = 0; i < p_toks.size(); i++ ) {
            switch( p_toks[i].m_type )
            {
                case TOKEN::integer:
                {
                    int l_val      = lexical_cast<int>(p_toks[i].m_text);
                    auto l_intElem = std::make_shared<IntegerElem>(l_val);

                    if ( !l_have_lhs ) { l_res->lhs = l_intElem; l_have_lhs = true; }
                    else               { l_res->rhs = l_intElem; }
                    break;
                }
                case TOKEN::plus:
                    l_res->m_type = BinaryElem::Type::add;
                    break;
                case TOKEN::minus:
                    l_res->m_type = BinaryElem::Type::sub;
                    break;
                case TOKEN::lparen:
                {
                    int j{i};
                    for ( ; j < p_toks.size(); j++ )
                        if ( p_toks[j].m_type == TOKEN::rparen )
                            break;
                    std::vector<TOKEN> l_sub(&p_toks[i+1], &p_toks[j]);
                    auto l_elem = parse(l_sub);
                    if ( !l_have_lhs ) { l_res->lhs = l_elem; l_have_lhs = true; }
                    else               { l_res->rhs = l_elem; }
                    i = j;
                }
                    break;
            }
        }

        return l_res;
    }

    /*!
     * @brief Tokenize the input into corresponding tokens.
     */
    std::vector<TOKEN> lex(const std::string& p_input) {
        std::vector<TOKEN> l_res;
        std::ostringstream l_buf;

        for ( int i = 0; i < p_input.size(); i++ ) {
            switch( p_input[i] )
            {
                case ' ': /*! Let's ignore spaces */                      break;
                case '+': l_res.push_back( TOKEN{ TOKEN::plus  , "+" } ); break;
                case '-': l_res.push_back( TOKEN{ TOKEN::minus , "-" } ); break;
                case '(': l_res.push_back( TOKEN{ TOKEN::lparen, "(" } ); break;
                case ')': l_res.push_back( TOKEN{ TOKEN::rparen, ")" } ); break;
                default:
                    l_buf.str("");
                    l_buf.clear();
                    l_buf << p_input[i];
                    for ( int j = i+1; j < p_input.size(); j++ ) {
                        if ( isdigit(p_input[j]) ) {
                            i++;
                            l_buf << p_input[j];
                        }
                        else {
                            l_res.push_back( TOKEN{ TOKEN::integer, l_buf.str() } );
                            l_buf.str("");
                            l_buf.clear();
                            break;
                        }
                    }
                break;
            }
        }
        if ( !l_buf.str().empty() )
            l_res.push_back( TOKEN{ TOKEN::integer, l_buf.str() } );

        return l_res;
    }

    /*!
     * @brief Checks that the input string can actually be evaluated
     *
     * NB : This is a pretty basic check to illustrate a hidden step.
     */
    bool conformityCheck( const std::string& p_input ) {
        std::stack<char> l_stack;

        /* Check for undesired chars
           and parenthesis balance */

        for ( auto& c : p_input ) {
            switch ( c )
            {
            case '(': l_stack.push('('); break;
            case ')':
                if ( l_stack.empty() ) {
                    std::cerr << "Parenthesis check failed!" << std::endl;
                    return false;
                }
                l_stack.pop();
                break;
            case '+': break;
            case '-': break;
            case '*': break;
            case ' ': break;
            default :
                if ( !isdigit(c) ) {
                    std::cerr << "Unknown char " << c << std::endl;
                    return false;
                }
                break;
            }
        }

        return l_stack.empty();
    }
};

// ---------- CLIENT CODE ------------ //
int main()
{
    std::string l_input{"(1 - 3) - (5 - 12)"};
    INTERPRETER l_interpreter;

    std::cout << l_input << " = " << l_interpreter.eval(l_input) << std::endl;
}
