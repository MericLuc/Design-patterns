// Rewritten example - Original here
// https://en.wikipedia.org/wiki/Decorator_pattern#UML_class_and_sequence_diagram

#include <memory>
#include <iostream>
#include <string>

/*!
 * @brief : Component - defines the interface of the
 *          objects you want to provide additional layers
 *          of behaviours to.
 */
class WebPage
{
public:
    virtual void display(void) const = 0;
    virtual ~WebPage() = default;
};

/*!
 * @brief : ConcreteComponent - The objects you want to
 *          be able to add responsabilities to.
 */
class BasicWebPage : public WebPage
{
public:
    void display(void) const override { std::cout << "Basic WEB page" << std::endl; }

     BasicWebPage(std::string&& p_html = "") : m_html(p_html) {}
    ~BasicWebPage()=default;

private:
    std::string m_html;
};

/*!
 * @brief : Decorator - Interface that conforms to WebPage interface
 *          Keep a reference (in that case a std::unique_ptr) on the
 *          WebPage object.
 */
class WebPageDecorator : public WebPage
{
public:
    WebPageDecorator(std::unique_ptr<WebPage> webPage): _webPage(std::move(webPage)) {}
    ~WebPageDecorator()=default;

    /*!
     * @brief : Note that the "basic behaviour" is still realized by the wrappee.
     */
    void display(void) const override { _webPage->display(); }

private:
    std::unique_ptr<WebPage> _webPage;
};

/*!
 * @brief : ConcreteDecorator1 - Implements the new behaviour
 *          added to the wrappee.
 */
class AuthenticatedWebPage : public WebPageDecorator
{
public:
    AuthenticatedWebPage(std::unique_ptr<WebPage> webPage):
    WebPageDecorator(std::move(webPage)) {}
    ~AuthenticatedWebPage()=default;

    /*!
     * @brief : New behaviour enhanced by the ConcreteDecorator
     */
    void display(void) const override
    {
        // Could be in any order
        authenticateUser();
        WebPageDecorator::display();
    }

private:
    void authenticateUser(void) const { std::cout << "authentification done" << std::endl; }
};

/*!
 * @brief : ConcreteDecorator2 - Implements the new behaviour
 *          added to the wrappee.
 */
class AuthorizedWebPage : public WebPageDecorator
{
public:
    AuthorizedWebPage(std::unique_ptr<WebPage> webPage):
    WebPageDecorator(std::move(webPage)) {}
    ~AuthorizedWebPage()=default;

    void display(void) const override
    {
        // Once again, could be in any order
        WebPageDecorator::display();
        authorizedUser();
    }

private:
    void authorizedUser(void) const { std::cout << "authorized done" << std::endl; }
};

int main()
{
    std::unique_ptr<WebPage> myPage = std::make_unique<BasicWebPage>();
    std::cout << "     ---    ConcreteComponent     --- " << std::endl;
    myPage->display();

    myPage = std::make_unique<AuthorizedWebPage   >(std::move(myPage));
    std::cout << "     --- Added ConcreteDecorator1 --- " << std::endl;
    myPage->display();

    myPage = std::make_unique<AuthenticatedWebPage>(std::move(myPage));
    std::cout << "     --- Added ConcreteDecorator2 --- " << std::endl;
    myPage->display();

    std::cout << std::endl;

    return 0;
}
