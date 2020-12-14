#ifndef  CHATROOM_H
#define CHATROOM_H

#include <memory>
#include <vector>

class ChatRoom
{
  public:
    ChatRoom() = default;
    ~ChatRoom() = default;

    void broadcast(const std::string &p_from,
                            const std::string &p_msg);

    void join  ( Person* p );

    void leave( Person* p );

    void message(const std::string &p_from,
                           const std::string &p_to,
                           const std::string &p_msg);

  private:
    std::vector<Person*> m_people;
};

#endif // CHATROOM_H

