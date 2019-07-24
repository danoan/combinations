#ifndef EVENT_H
#define EVENT_H

namespace magLac
{
    namespace Core
    {
        struct Event
        {
            typedef unsigned long int Size;

            enum Action{DIVE,BRANCH,DONE,END};
            Event(Action action,Size cIndex,Size itMove):action(action),cIndex(cIndex),itMove(itMove){}

            Action action;
            Size cIndex;
            Size itMove;
        };
    }
}



#endif
