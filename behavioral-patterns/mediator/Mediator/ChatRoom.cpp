#include "person.hpp"
#include "ChatRoom.hpp"
#include <algorithm>

void ChatRoom::broadcast(const std::string& p_from, const std::string& p_msg )
{
  for (auto& p : m_people)
    if ( p->getName() != p_from ) p->receive(p_from, p_msg);
}

void ChatRoom::join( Person* p )
{
  std::string join_msg = p->getName() + " joins the chat";
  broadcast( "room", join_msg );
  m_people.push_back( p );
}

void ChatRoom::leave( Person* p )
{
  std::string leave_msg = p->getName() + " left the chat";
  broadcast( "room", leave_msg );
  m_people.erase ( 
    std::remove( std::begin(m_people), std::end   (m_people), p ), std::end(m_people) );
}

void ChatRoom::message(const std::string &p_from,
             const std::string &p_to,
             const std::string &p_msg)
{
  auto target = std::find_if(
      std::begin(m_people),
      std::end(m_people),
      [&](const Person* p) {
        return p->getName() == p_to;
      });
  if (target != std::end(m_people))
  {
    (*target)->receive(p_from, p_msg);
  }
}