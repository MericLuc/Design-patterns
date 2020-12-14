#include "Person.hpp"
#include "ChatRoom.hpp"
#include <iostream>
#include <string>

Person::Person(const std::string &p_name, ChatRoom &p_room) : 
m_name(p_name), m_room(p_room)
{
  m_room.join( this );
}

Person::~Person() 
{
  m_room.leave(this);
}

void Person::say(const std::string &p_msg) const
{
  m_room.broadcast(m_name, p_msg);
}

void Person::pm(const std::string &p_to, const std::string &p_msg) const
{
  m_room.message(m_name, p_to, p_msg);
}

void Person::receive(const std::string &p_from, const std::string &p_msg)
{
  std::string s{p_from + ": \"" + p_msg + "\""};
  std::cout << "[" << p_from << "'s chat session]" << s << "\n";
  m_logs.emplace_back(s);
}

bool Person::operator==(const Person &rhs) const {
  return m_name == rhs.getName();
}

bool Person::operator!=(const Person &rhs) const {
  return !(rhs == *this);
}
