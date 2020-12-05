/*!
 * This sample is inspired by another one found here :
 * https://www.bogotobogo.com/DesignPatterns/chain_of_responsibility.php
 */

#include <iostream>
#include <string>

// Scale of the photo
enum SCALE { S50, S100, S200, S300, S500 };

// Priority of a photo to be treated
enum PRIO { NO_PRIO, MEDIUM_PRIO, HIGH_PRIO };

/*!
 * @brief : Request class representation
 */
class Photo
{
public:
    Photo(std::string p_title, PRIO p_prio = NO_PRIO) :
    m_title(p_title), m_curScale(S100), m_prio(p_prio) {}

    void  setScale(const SCALE& p_scale) { m_curScale = p_scale; }
    SCALE getScale(void) const { return m_curScale; }

    PRIO  getPrio(void) const { return m_prio; }

private:
    std::string m_title;
    SCALE       m_curScale;
    PRIO        m_prio;
};

/*!
 * @brief : Handler interface.
 *          - Provides the handle method default behaviour
 *              * Handle the Photo
 *              * Forward it to the successor if any
 *          - Also provide implementation for adding a
 *            successor.
 */
class PhotoProcessor
{
public:
    PhotoProcessor() : m_next(nullptr) { }

public:
    virtual void handle( Photo &p ) {
        handleImpl(p);
        if ( m_next ) { m_next->handle(p); }
    }

    virtual ~PhotoProcessor() = default;

    void setNext(PhotoProcessor* p_next) { m_next = p_next; }

protected:
    virtual void handleImpl(Photo &p) = 0;
    PhotoProcessor* m_next;
};

/*!
 * @brief : ConcreteHandler.
 *          Implements Handler's interface.
 */
class Scale : public PhotoProcessor
{
public:
    Scale(SCALE p_scale) : m_scale(p_scale) { }

private:
    void handleImpl(Photo &a) override {
        std::cout << "Scaling photo\n";
        a.setScale(m_scale);
    }

    SCALE m_scale;
};

class PriorityChecker : public PhotoProcessor
{
public:
    PriorityChecker(PRIO p_prio) : m_prio(p_prio) { }

    /*!
     * This ConcreteChecker overrides the handle
     * method to define a new behaviour :
     *    - Handle and perform the next operation
     *      only if the request's priority is high
     *      enough.
     */
    void handle( Photo &p ) override {
        if ( m_prio <= p.getPrio() )
        {
            handleImpl(p);
            if ( m_next ) { m_next->handle(p); }
        }
        else
        {
            std::cout << "This Photo is not a priority and will not be treated now\n";
        }
    }


private:
    void handleImpl(Photo &a) override {
        (void)a;
        std::cout << "Checked photo priority\n";
    }

    PRIO m_prio;
};

class RedEye : public PhotoProcessor
{
private:
    void handleImpl(Photo &a) override { (void)a; std::cout << "Removing red eye\n"; }
};

class Filter : public PhotoProcessor
{
private:
    void handleImpl(Photo &a) override { (void)a; std::cout << "Applying filters\n"; }
};

class ColorMatch : public PhotoProcessor
{
private:
    void handleImpl(Photo &a) override { (void)a; std::cout << "Matching colors\n"; }
};

/*!
 * @brief : Client code.
 *          Declare the ConcreteHandlers and
 *          combine them to perform sequential
 *          operations on the Request.
 */
void processPhoto( Photo& photo )
{
    // Declare the ConcreteHandlers
    ColorMatch      match;
    RedEye          eye;
    Filter          filter;
    PriorityChecker prioCheck(HIGH_PRIO);

    // Build the chain of command
    // i.e. the order of the operations
    Scale scale(S200);
    scale    .setNext(&prioCheck);
    prioCheck.setNext(&eye);
    eye      .setNext(&match);
    match    .setNext(&filter);

    // Perform the operations
    scale    .handle(photo);
}

int main()
{
    Photo p("Y2013 Photo");
    processPhoto(p);

    return 0;
}
