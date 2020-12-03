/*!
 * @brief : This example was originally declared in "Desgin Patterns :
 *          Elements of reusable Object-oriented software".
 */

#include <vector>
#include <iostream> 
#include <algorithm> 
#include <functional> 
 
// ------- COMPONENT ------- //
/*!
 * @brief Component - declares the common interface for every
 *        objects (Leaf or Composite) of the composition.
 */
class Graphic {
public:
  virtual ~Graphic() = default;

  virtual void draw       (void) const = 0; // An operation method
  virtual bool isComposite(void) const { return false; }

  virtual void     setParent(Graphic* p_parent) { m_parent = p_parent; }
  virtual Graphic* getParent(void) const { return m_parent; }

  /*! 
   * Note : These are child-management operations.
   * Defining them in the Component class ensure you that you
   * will not need to expose any Leaf/Composite to the client code.
   */
  virtual void remove     (Graphic *g) { /* EMPTY */ }
  virtual void add        (Graphic *g) { /* EMPTY */ }

protected:
  Graphic* m_parent;
};

// --------- LEAFS --------- //
/*!
 * @brief Leafs - Leaf objects of the composition.
 *        - They have no children.
 *        - They define the behaviour of the primitive objects.
 */ 
class Line : public Graphic {
public:
  void draw(void) const override { std::cout << "Line\n"; }
};

class Rectangle : public Graphic {
public:
  void draw(void) const override { std::cout << "Rectangle\n"; }
};

class Text : public Graphic {
public:
  void draw(void) const override { std::cout << "Text\n"; }
};


// --------- COMPOSITE --------- //
/*!
 * @brief Composite - Composite objects
 *        - Stores children (Leaf or Composite)
 *        - Implement the Component interface for
 *          the child-related operations
 */ 
class Picture : public Graphic {
public:
  Picture(std::string&& p_name = ""): m_name(p_name) {}
  virtual ~Picture() = default; 

  virtual bool isComposite(void) const override { return true; }

  void draw(void) const override {
    std::for_each( std::begin(m_sons), 
                   std::end  (m_sons), 
                   [](Graphic* it){ it->draw(); } );
  }
 
  void add   (Graphic* p_elem) { m_sons.push_back(p_elem); }
  void remove(Graphic* p_elem) { 
    m_sons.erase(std::remove(std::begin(m_sons), 
                             std::end  (m_sons), 
                             p_elem), std::end  (m_sons));
}

private:
  std::vector<Graphic*> m_sons;
  std::string           m_name;

};
 
// --------- CLIENT CODE --------- //
/*!
 * @brief : Client Code 
 * Can work with Picture just as if
 * it was a Leaf.
 */
int main()
{
  Line      line; line.draw();
  Rectangle rect; rect.draw();
  Text      text; text.draw();

  std::cout << std::endl;
  
  Picture pic;
  pic.add(&line);
  pic.add(&rect);
  pic.add(&text);
  pic.draw();

  return 0;
}