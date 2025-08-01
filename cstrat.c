//
// Created by Jessica Bruce on 8/1/25.
//

#include "cstrat.h"

Strat make_strategy(GlobalString tag, const StratFunc execute) {
    return (Strat){.execute = execute, .tag = tag};
}

Result run_strategy(Strat *strat) {
    return strat->execute(strat);
}

bool is_strategy(const Strat *start, GlobalString other_tag) {
    return cstrings_equal(start->tag, other_tag);
}