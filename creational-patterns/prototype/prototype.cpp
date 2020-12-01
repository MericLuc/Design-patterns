#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

typedef enum {
    XML    = 1,
    PLAIN  = 2,
    SPREAD = 3
} DocType;

/*
 * @brief Prototype declares an interface to clone itself.
 */
class DocPrototype
{
public:
  virtual std::unique_ptr<DocPrototype> clone(void) const = 0;
  virtual void                          print(void) const = 0;
  virtual ~DocPrototype() { }
};

/*
 * @brief : ConcretePrototypes : xmlDoc, plainDoc, spreadsheetDoc
 *          Implement the interface of the Prototype to be able
 *          to clone themselves.
 */
class xmlDoc : public DocPrototype
{
public:
  xmlDoc(void) {}
  ~xmlDoc()    {}

  std::unique_ptr<DocPrototype> clone(void) const override {
      return std::make_unique<xmlDoc>(*this);
  }
  void  print(void) const override { std::cout << "xmlDoc\n"; }
};

class plainDoc : public DocPrototype
{
public:
  plainDoc(void) {}
  ~plainDoc()    {}

  std::unique_ptr<DocPrototype> clone(void) const override {
    return std::make_unique<plainDoc>(*this);
  }
  void print(void) const override { std::cout << "plainDoc\n"; }
};

class spreadsheetDoc : public DocPrototype
{
public:
  spreadsheetDoc(void) {}
  ~spreadsheetDoc()    {}

  std::unique_ptr<DocPrototype> clone(void) const override {
    return std::make_unique<spreadsheetDoc>(*this);
  }
  void print(void) const override { std::cout << "spreadsheetDoc\n"; }
};

/*!
 * @brief : FactoryManager contains one instance of each
 *          ConcretePrototype so that it can use their
 *          clone() method to provide the client with the
 *          required ConcretePrototype.
 */
class DocFactoryManager {
public:
    DocFactoryManager(void) {
        m_docs[XML   ] = std::make_unique<xmlDoc        >();
        m_docs[PLAIN ] = std::make_unique<plainDoc      >();
        m_docs[SPREAD] = std::make_unique<spreadsheetDoc>();
    }
   ~DocFactoryManager(){}

    std::unique_ptr<DocPrototype> makeDocument( DocType type ) {
        return m_docs[type]->clone();
    }

private:
    std::unordered_map<DocType,
                       std::unique_ptr<DocPrototype> >  m_docs;
};

/*!
 * @brief : Client code
 *          Only uses the FactoryManager to create the document
 *          type he needs.
 */
void clientCode(DocFactoryManager& mngr) {
  std::vector<std::unique_ptr<DocPrototype> > clientDocs;
  int                                         clientChoice;

  std::cout << "quit(0), xml(1), plain(2), spreadsheet(3): \n";
  while (true) 
  {
      std::cout << "Type in your choice (0-3)\n";
      std::cin  >> clientChoice;
      if ( clientChoice <= 0 || clientChoice > SPREAD ) break;
      clientDocs.push_back( mngr.makeDocument( static_cast<DocType>(clientChoice) ) );
   }

   for ( auto& it : clientDocs ) it->print();
}

int main() {
   DocFactoryManager mngr;
   clientCode(mngr);
   
   return 0;
}
