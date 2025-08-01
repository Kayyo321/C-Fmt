//
// Created by Jessica Bruce on 8/1/25.
//

#ifndef CSTRAT_H
#define CSTRAT_H

#include "cstring.h"
#include "cresult.h"

/// Forward declaration of the strategy object type.
typedef struct _Strat Strat;

/// Type definition for a strategy function.
/// This function is intended to be overridden for polymorphic behavior.
/// @param strat A pointer to the strategy object (which may be cast to a derived type).
/// @return A `Result` indicating success or error.
typedef Result (*StratFunc)(Strat *strat);

/// Represents a general strategy object with a tag and a virtual execute method.
struct _Strat {
    StratFunc execute;
    GlobalString tag;
};

/// Creates a new strategy.
/// @param tag The identifying tag for the strategy.
/// @param execute The function to run when the strategy is executed.
/// @return A new `Strat` instance.
Strat make_strategy(GlobalString tag, StratFunc execute);

/// Runs the strategy's associated function.
/// @param strat Pointer to the strategy object.
/// @return The result of executing the strategy.
Result run_strategy(Strat *strat);

/// Checks if a strategy matches the provided tag.
/// @param strat Pointer to the strategy object.
/// @param other_tag The tag to compare with.
/// @return true if the tags match, false otherwise.
bool is_strategy(const Strat *strat, GlobalString other_tag);

/// Macro to embed base `Strat` struct into a derived struct (simulates inheritance).
#define inherit_strategy Strat base;


/// Macro to define an overriding execute function for a specific derived strategy type.
/// Use this inside a derived strategy's `.c` file to implement custom behavior.
/// Example:
/// ```c
/// override_strategy(MyStrategy, self) {
///     // Your logic using `self`
///     return ok_result(...);
/// } end_override_strategy
/// ```
#define override_strategy(StratType, self) \
    Result override_##StratType##_execute(Strat *strat) { \
        StratType *self = (StratType *)strat;

/// Marks the end of an `override_strategy` implementation.
#define end_override_strategy \
    }

/// Casts a derived strategy struct to its base `Strat*` pointer.
#define as_strat(xyz) ((Strat*)&xyz)

#endif // CSTRAT_H
