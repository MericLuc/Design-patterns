#ifndef  PERSON_H
#define PERSON_H

#include <string>
#include <vector>

class ChatRoom;

class Person {

public:
  Person( const std::string &p_name, ChatRoom& p_room );
  Person() = delete;
  virtual ~Person();

  void say      (const std::string& p_msg) const;
  void pm      (const std::string& p_to    , const std::string& p_msg) const;
  void receive(const std::string &p_from, const std::string &p_msg);

  bool operator==(const Person &p_rhs) const;
  bool operator!= (const Person &p_rhs) const;

  std::string getName(void) const { return m_name; }

private:
  const std::string             m_name;
  ChatRoom&                  m_room;
  std::vector<std::string> m_logs{};

};

#endif // PERSON_H
