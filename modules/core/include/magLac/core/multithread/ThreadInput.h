#ifndef LAZY_COMBINATOR_THREADINPUT_H
#define LAZY_COMBINATOR_THREADINPUT_H

namespace magLac
{
    namespace Core
    {
        namespace MultiThread
        {
            template<class TCombinator, class TUserVars, class TParams>
            struct ThreadInput
            {
                typedef TCombinator MyCombinator;
                typedef typename TCombinator::MyResolver MyResolver;
                typedef TUserVars UserVars;
                typedef TParams Params;

                typedef ThreadInput<MyCombinator,UserVars,Params> Self;

                ThreadInput(){}

                ThreadInput(MyCombinator *combinatorPt,
                            const Params& params) : combinatorPt(combinatorPt),
                                                    params(params) {}


                void restart()
                {
                    vars.restart();
                }


                MyCombinator* combinatorPt;
                const Params& params;
                UserVars vars;

            };
        }
    }

}

#endif //LAZY_COMBINATOR_THREADINPUT_H
