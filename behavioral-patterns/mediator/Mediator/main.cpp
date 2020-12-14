#include "Person.hpp"
#include "ChatRoom.hpp"

int main()
{
  ChatRoom room;

  Person john{"John", room};
  Person jane{"Jane", room};

  john.say("hi room");
  jane.say("oh, hey john");

  {
    Person simon{"Simon", room};
    simon.say("hi everyone! I'm in a hurry, I gotta go !");
  }

  Person sam{"Sam", room};
  jane.pm("Sam", "glad you found us, Sam!");

  return 0;
}