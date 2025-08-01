#ifndef CDEFER_H
#define CDEFER_H

#if defined(__GNUC__) || defined(__clang__)

// Helper for concatenating names
#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)

// The actual defer macro
#define defer(func) \
__attribute__((cleanup(func))) __attribute__((unused))

#endif

#endif // CDEFER_H
