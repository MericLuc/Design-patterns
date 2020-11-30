#include <iostream>
#include <string>

class Button {
public:
    virtual void paint(void) = 0;
};
 
class OSXButton: public Button {
public:
    void paint(void) { std::cout << "OSX button" << std::endl; }
};
 
class WindowsButton: public Button  {
public:
    void paint(void) {std::cout << "Windows button" << std::endl;  }
};
 
class IPhoneButton: public Button {
public:
    void paint(void) { std::cout << "IPhone button" << std::endl;  }
};

class ButtonFactory {
public:
    virtual Button* createButton(std::string&& p_type) {
        if      ( p_type.compare("Windows") == 0 ) { return new WindowsButton; }
        else if ( p_type.compare("OSX"    ) == 0 ) { return new OSXButton;     }
        return nullptr;
    }
};

class Factory: public ButtonFactory {
    virtual Button* createButton(std::string&& p_type) {
        if      ( p_type.compare("Windows") == 0 ) { return new WindowsButton; }
        else if ( p_type.compare("OSX"    ) == 0 ) { return new OSXButton;     }
        else if ( p_type.compare("Iphone" ) == 0 ) { return new IPhoneButton;  }
        return nullptr;
    }
};

int main()
{
    ButtonFactory* factory = new Factory;
    Button*        button  = nullptr;

    button = factory->createButton("OSX");
    button -> paint();
    delete button;

    button = factory->createButton("Windows");
    button -> paint();
    delete button;

    button = factory->createButton("Iphone");
    button -> paint();
    delete button;

    return 0;
}