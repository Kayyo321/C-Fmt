//
// Created by Jessica Bruce on 8/1/25.
//

/// I've chosen a more in-depth example for Strategy matching, as it will
/// show off the perks better, I hope that it's easy to follow

#include "../cstrat.h"

#include <time.h>

/// A game-state struct for demonstration
typedef struct {
    int health;
    int enemy_distance;
} GameState;

/// We need polymorphic ways that players can interact with this game!
/// Let's make some strategies.

/// These are some enums that we use to tag our strategies later
global_string_enum(AGGRESSIVE_STRATEGY)
global_string_enum(DEFENSIVE_STRATEGY)
global_string_enum(RANDOM_STRATEGY)

typedef struct {
    /// This macro inserts the base reference to the strategy struct
    /// Simply fake polymorphism!
    inherit_strategy

    GameState *state;
} AggressiveStrategy;

/// If we're aggressive, we always charge at the enemy
override_strategy(AggressiveStrategy, self)
    c_println("[AGGRESSIVE] Charging at the enemy!");
    return ok_result(ACStr("Attacked aggressively"));
end_override_strategy

typedef struct {
    inherit_strategy
    GameState *state;
} DefensiveStrategy;

/// If we're defensive, we check if we have less than health 50 remaining and heal,
/// otherwise, we hold our position!
override_strategy(DefensiveStrategy, self)
    if (self->state->health < 50) {
        c_println("[DEFENSIVE] Healing self...");

        return ok_result(ACStr("Healed"));
    }

    c_println("[DEFENSIVE] Holding position...");

    return ok_result(ACStr("Guarding"));
end_override_strategy

typedef struct {
    inherit_strategy

    GameState *state;
} RandomStrategy;

/// Our random strategy is to choose a move at random!
override_strategy(RandomStrategy, self)
    int choice = rand() % 2;
    if (choice == 0) {
        c_println("[RANDOM] Surprise attack!");
        return ok_result(ACStr("Random attack"));
    } else {
        c_println("[RANDOM] Taking cover.");
        return ok_result(ACStr("Random defense"));
    }
end_override_strategy

void use_strategies() {
    srand((unsigned int)time(NULL));

    GameState state = { .health = 45, .enemy_distance = 10 };

    AggressiveStrategy aggro = {
        .base = make_strategy(AGGRESSIVE_STRATEGY, override_AggressiveStrategy_execute),
        .state = &state
    };

    DefensiveStrategy def = {
        .base = make_strategy(DEFENSIVE_STRATEGY, override_DefensiveStrategy_execute),
        .state = &state
    };

    RandomStrategy rand_strat = {
        .base = make_strategy(RANDOM_STRATEGY, override_RandomStrategy_execute),
        .state = &state
    };

    // Polymorphic behavior in action
    Strat *strategies[] = {
        as_strat(aggro),
        as_strat(def),
        as_strat(rand_strat)
    };

    for (int i = 0; i < 3; i++) {
        Result result = run_strategy(strategies[i]);
        if (is_ok(result)) {
            c_println("Result: {}", result.value);
        } else {
            println_err_result(result);
        }
    }
}