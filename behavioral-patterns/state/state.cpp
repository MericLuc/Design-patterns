/*!
 * From https://github.com/pezy/DesignPatterns/blob/master/State/main.cpp
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

// ------------------ State ------------------ //
/*!
 * @brief State class
 *        Defines an interface to encapsulate the behaviour
 *        associated to a particular state of the Context.
 */
class IWritingState {
public:
    virtual void Write(std::string p_words) = 0;
};

// ------------- ConcreteStates ------------- //
/*!
 * @brief ConcreteState subclasses
 *        Implements the behaviour of a particular state of the Context.
 */
class UpperCase : public IWritingState {
public:
    void Write(std::string p_words) override {
        std::transform(p_words.begin(), p_words.end(), p_words.begin(), ::toupper);
        std::cout << p_words << std::endl;
    }
};

class LowerCase : public IWritingState {
public:
    void Write(std::string p_words) override {
        std::transform(p_words.begin(), p_words.end(), p_words.begin(), ::tolower);
        std::cout << p_words << std::endl;
    }
};

class Default : public IWritingState {
public:
    void Write(std::string p_words) override { std::cout << p_words << std::endl; }
};

/*!
 * @brief Context
 *        Interface of interest for the client.
 *        Maintains a reference to its current state (ConcreteState)
 */
class TextEditor {
public:
    TextEditor(const std::shared_ptr<IWritingState>& p_state): m_state(p_state) {}
    void SetState(const std::shared_ptr<IWritingState>& p_state) { m_state = p_state; }
    void Type(const std::string& p_words) { m_state->Write(p_words); }
private:
    std::shared_ptr<IWritingState> m_state; /*!< Current state */
};

// --------------- Client code --------------- //
int main()
{
  TextEditor editor(std::make_shared<Default>());
  editor.Type("First line");

  editor.SetState(std::make_shared<UpperCase>());
  editor.Type("Second line");
  editor.Type("Third line");

  editor.SetState(std::make_shared<LowerCase>());
  editor.Type("Fourth line");
  editor.Type("Fifth line");
}
