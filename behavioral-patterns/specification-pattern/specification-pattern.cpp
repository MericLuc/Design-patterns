#include <stdint.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

// --------- Typedefs --------- //
typedef uint32_t Price;
typedef enum { Small, Medium, Large, Huge } Size;  /*!< Possible sizes of the Products  */
typedef enum { Blue, Red, Green, Yellow   } Color; /*!< Possible colors of the Products */

/*!
 * \brief The Product class is the class
 *        on which you want to apply and combine
 *        different business logics.
 */
class Product {
public:
    Product( std::string&& p_name  = "",
             Color&&       p_color = Blue,
             Size &&       p_size  = Small,
             Price&&       p_price = 0) :
    m_name(p_name), m_color(p_color), m_size(p_size), m_price(p_price) {}
    virtual ~Product() = default;

    std::string getDescription(void) const { return "\t- " + m_name; }

    // Getters
    Color getColor (void) const { return m_color;  }
    Size  getSize  (void) const { return m_size;   }
    Price getPrice (void) const { return m_price;  }

private:
    std::string m_name;
    Color       m_color;
    Size        m_size;
    Price       m_price;
};

// --------- SPECIFICATIONS INTERFACE --------- //
/*!
 * \brief ISpecification - interface of specification
 *        to be implemented by ConcreteSpecifications.
 */

// Forward declarations
template <typename T> class ANDSpecification;
template <typename T> class ORSpecification;
template <typename T> class NOTSpecification;

template <typename T>
class ISpecification
{
public:
    virtual bool isSatisfiedBy(const T&) const = 0;

    std::unique_ptr<ISpecification<T> > operator&&  (ISpecification<T>&& other) {
        return std::make_unique<ANDSpecification<T> >(*this, other);
    }

    std::unique_ptr<ISpecification<T> > operator||  (ISpecification<T>&& other) {
        return std::make_unique<ORSpecification <T> >(*this, other);
    }

    std::unique_ptr<ISpecification<T> > operator!   (void) {
        return std::make_unique<NOTSpecification<T> >(*this);
    }
};

// --------- FILTER INTERFACE --------- //

template <typename T>
class IFilter
{
public:
    virtual std::vector<T> filter(std::vector<T>& items,
                                  std::unique_ptr<ISpecification<T>>& spec ) = 0;
};

class ProductFilter : public IFilter<Product>
{
public:
    std::vector<Product> filter(std::vector<Product>& items,
                                std::unique_ptr<ISpecification<Product>>& spec ) override
    {
        std::vector<Product> ret;

        for ( auto& it : items )
            if ( spec->isSatisfiedBy(it) ) { ret.push_back(it); }
        return ret;
    }
};

// --------- SPECIFICATIONS BUSINESS LOGICS --------- //
template <typename T>
class ANDSpecification : public ISpecification<T>
{
public:
    ANDSpecification(ISpecification<T>& p_left,
                     ISpecification<T>& p_right) : m_leftSpec(p_left), m_rightSpec(p_right) {}
    virtual ~ANDSpecification() = default;

    virtual bool isSatisfiedBy(const T& item) const override {
        return m_leftSpec.isSatisfiedBy(item) && m_rightSpec.isSatisfiedBy(item);
    }

private:
    ISpecification<T>& m_leftSpec;
    ISpecification<T>& m_rightSpec;
};

template <typename T>
class ORSpecification : public ISpecification<T>
{
public:
    ORSpecification(ISpecification<T>& p_left,
                    ISpecification<T>& p_right) : m_leftSpec(p_left), m_rightSpec(p_right) {}
    virtual ~ORSpecification() = default;

    virtual bool isSatisfiedBy(const T& item) const override {
        return m_leftSpec.isSatisfiedBy(item) || m_rightSpec.isSatisfiedBy(item);
    }

private:
    ISpecification<T>& m_leftSpec;
    ISpecification<T>& m_rightSpec;
};

template <typename T>
class NOTSpecification : public ISpecification<T>
{
public:
    NOTSpecification(ISpecification<T>& p_cnd) : m_Spec(p_cnd) {}
    virtual ~NOTSpecification() = default;

    virtual bool isSatisfiedBy(const T& item) const override {
        return !m_Spec.isSatisfiedBy(item);
    }

private:
    ISpecification<T>& m_Spec;
};

// --------- CONCRETE SPECIFICATIONS --------- //

/*!
 * \brief ConcreteSpecification - implements the Specification
 *        interface for a particular business logic.
 */
class ColorSpecification : public ISpecification<Product>
{
public:
    ColorSpecification(Color&& p_color) : m_color(p_color) {}
    virtual ~ColorSpecification() = default;

    virtual bool isSatisfiedBy(const Product& item) const override { return item.getColor() == m_color; }

private:
    Color m_color;
};

class SizeSpecification : public ISpecification<Product>
{
public:
    SizeSpecification(Size&& p_size) : m_size(p_size) {}
    virtual ~SizeSpecification() = default;

    virtual bool isSatisfiedBy(const Product& item) const override { return item.getSize() == m_size; }

private:
    Size m_size;

};

class PriceSpecification : public ISpecification<Product>
{
public:
    PriceSpecification(Size&& p_price) : m_price(p_price) {}
    virtual ~PriceSpecification() = default;

    virtual bool isSatisfiedBy(const Product& item) const override { return item.getPrice() == m_price; }

private:
    Price m_price;
};

// --------- MAIN --------- //

int main()
{
    std::vector<Product> prods = {  Product("House", Blue  , Huge  , 500000),
                                    Product("Cake" , Yellow, Small ,      3),
                                    Product("Tree" , Green , Large ,    100),
                                    Product("Plant", Green , Medium,     12) };

    auto mySpecs1 = ColorSpecification(Green) && SizeSpecification (Large );
    auto mySpecs2 = ColorSpecification(Blue ) || ColorSpecification(Yellow);
    auto mySpecs3 = !PriceSpecification(static_cast<Size>(500000));

    ProductFilter myFilter;

    std::cout << "Items corresponding to specs 1 :\n";
    for ( auto& it : myFilter.filter(prods, mySpecs1) )
        std::cout << it.getDescription() << std::endl;
    std::cout << std::endl;

    std::cout << "Items corresponding to specs 2 :\n";
    for ( auto& it : myFilter.filter(prods, mySpecs2) )
        std::cout << it.getDescription() << std::endl;
    std::cout << std::endl;

    std::cout << "Items corresponding to specs 3 :\n";
    for ( auto& it : myFilter.filter(prods, mySpecs3) )
        std::cout << it.getDescription() << std::endl;
    std::cout << std::endl;

}
