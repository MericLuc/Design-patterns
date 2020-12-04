#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <utility>

// ------------------- PROPERTY PROXY ------------------- //
/*!
 * @brief : PROPERTY PROXY
 *          Allow you to perform additional actions
 *          (For example, log or intercept) on properties
 *          access by a client without him seeing any difference.
 */

template<typename T>
class PropertyProxy {
public:
    PropertyProxy(const T& p_val) : m_val(p_val) { }
    ~PropertyProxy() = default;

    // Allow conversion to T
    operator T() const { return m_val; }

    // Allow conversion from T
    T operator= (const T& p_val) { return m_val = p_val; }

private:
    T   m_val;
};

class ClassWithProperties {
public:
    ClassWithProperties (
        uint32_t p_prop1 = 0,
        uint32_t p_prop2 = 0 ) :
                m_prop1 (p_prop1),
                m_prop2 (p_prop2) {}
    ~ClassWithProperties() = default;

public:
    PropertyProxy<uint32_t>  m_prop1;
    PropertyProxy<uint32_t>  m_prop2 ;
};

// ------------------- VIRTUAL PROXY ------------------- //
/*!
 * @brief : VIRTUAL PROXY
 *          Allow you to perform lazy initializations
 *          to not waste memory without the client to
 *          even know about it.
 */

class IPicture {
public:
    IPicture(std::string p_fileName = ""): m_fileName(p_fileName) {}

    virtual void draw(void) = 0;
    std::string  getSrcFile(void) const { return m_fileName; }

protected:
    // Assuming images will always be loaded from a file
    std::string m_fileName;
};

class JpgPicture : public IPicture {
public:
    JpgPicture(std::string p_fileName = "") : IPicture(std::move(p_fileName))
    {
        /*
         *  Actually perform the loading of the image eventho
         *  we might never use it !
         */
        std::cout << "\tLoading the JPEG picture from file " << m_fileName << std::endl;
        // Do the job
        // ...
    }

    void draw(void) override
    {
        // All we have to do it to draw
        std::cout << "\tDrawing image loaded from " << m_fileName << std::endl;
        // Draw the image
    }
};

class JpgLazyPicture : public IPicture {
public:
    JpgLazyPicture(std::string p_fileName = "") : IPicture(std::move(p_fileName))
    {
        // We do not load the image yet since nobody asked for it yet...
    }

    void draw(void) override
    {
        // We load the image now if this is the first request
        if ( !m_jpg ) { m_jpg = std::make_unique<JpgPicture>(m_fileName); }

        // And then rely on JpgPicture to draw it
        m_jpg->draw();
    }

private:
    std::unique_ptr<JpgPicture> m_jpg;
};


// ------------------- COMMUNICATION PROXY ------------------- //
/*!
 * @brief : COMMUNICATION PROXY
 * FROM http://www.vishalchovatiya.com/proxy-design-pattern-in-modern-cpp/#Property_Proxy
 */

template <typename T>
struct arr2D {
    struct proxy {
        proxy(T *arr) : m_arr_1D(arr) {}
        T &operator[](int32_t idx) {
            return m_arr_1D[idx];
        }

        T   *m_arr_1D;
    };

    arr2D::proxy operator[](int32_t idx) {
        return arr2D::proxy(m_arr_2D[idx]);
    }

    T   m_arr_2D[10][10];
};

/*!
 * @brief CLIENT CODE
 */
int main() {

    // -------- Property proxy -------- //
    {
        /* The client will use the ClassWithProperties just
         * as if those properties actually were of their
         * base type (i.e. uint32_t)
         */

        ClassWithProperties anObject(10, 5);
        anObject.m_prop1 = 20;
        anObject.m_prop2 = 8;

        std::cout << anObject.m_prop1 << std::endl;
        std::cout << anObject.m_prop2 << std::endl;
    }

    // -------- Virtual proxy -------- //
    {
        JpgLazyPicture jpgLazy("myJpg.jpg");
        JpgPicture     jpgBase("myJpg.jpg");

        std::cout << "At this point, only jpgBase object has been loaded..." << std::endl;

        std::cout << "Now let's ask for jpgLazy..." << std::endl;
        jpgLazy.draw();
    }

    // ---- Communication proxy ---- //
    {
        arr2D<int32_t> arr;
        arr[0][0] = 1;  // Uses the proxy object
    }

    return 0;
}
