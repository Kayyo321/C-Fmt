//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef CSTRAT_H
#define CSTRAT_H

#include "cstring.h"
#include "cresult.h"

typedef struct _Strat Strat;

typedef Result (*StratFunc)(Strat *strat);

struct _Strat {
    StratFunc execute;
    GlobalString tag;
};

Strat make_strategy(GlobalString tag, StratFunc execute);
Result run_strategy(Strat *strat);
bool is_strategy(const Strat *start, GlobalString other_tag);

#define inherit_strategy Strat base;

#define override_strategy(StratType, self) \
    Result override_##StratType_execute(Strat *strat) { \
        StratType *self = (StratType *)strat;

#define end_override_strategy \
    }

#define as_strat(xyz) ((Strat*)&xyz)

#endif //CSTRAT_H
