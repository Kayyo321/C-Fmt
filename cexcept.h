//
// Created by Jessica Bruce on 7/31/25.
//

#ifndef CEXCEPT_H
#define CEXCEPT_H

#include <setjmp.h>

#include "cfmt.h"

typedef struct _ExceptionContext {
    jmp_buf env;
    c_fmt_FormatArg value;
    struct _ExceptionContext *prev;
} ExceptionContext;

extern ExceptionContext *__exception_stack;

#define Try do { \
ExceptionContext __ctx; \
__ctx.prev = __exception_stack; \
__exception_stack = &__ctx; \
int __exception_code = setjmp(__ctx.env); \
if (__exception_code == 0) {

#define Catch(e) \
__exception_stack = __ctx.prev; \
} else { \
c_fmt_FormatArg e = __ctx.value;

#define Finally \
__exception_stack = __ctx.prev; \
} \
{

#define Finish \
} \
} while (0)

#define Throw(val) do { \
if (__exception_stack == NULL) { \
fprintf(stderr, "Uncaught exception: %s\n", val.value); \
exit(EXIT_FAILURE); \
} \
__exception_stack->value = val; \
longjmp(__exception_stack->env, 1); \
} while (0)

#endif //CEXCEPT_H
