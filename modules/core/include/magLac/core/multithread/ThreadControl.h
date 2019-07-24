#ifndef COMBINATIONS_THREADCONTROL_H
#define COMBINATIONS_THREADCONTROL_H

namespace magLac
{
    namespace Core
    {
        namespace MultiThread
        {
            struct ThreadControl
            {
                enum ThreadState{RUNNING,STOP};

                ThreadControl(int vectorPos,
                              int maxQueryElems):   state(RUNNING),
                                                    vectorPos(vectorPos),
                                                    maxQueries(maxQueryElems){}

                void stop(){ state= STOP; }

                ThreadState state;
                int vectorPos;
                int maxQueries;
            };
        }
    }
}

#endif //COMBINATIONS_THREADCONTROL_H
