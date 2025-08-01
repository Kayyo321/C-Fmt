//
// Created by Jessica Bruce on 7/31/25.
//

#ifndef CREADONLY_H
#define CREADONLY_H

#include "cresult.h"

#ifndef READONLY_POOL_DEFAULT_SIZE
#define READONLY_POOL_DEFAULT_SIZE 64
#endif

typedef size_t Readonly;

void init_readonly_pool();
void free_readonly_pool();

bool readonly_equal(Readonly a, Readonly b);

Readonly make_readonly(c_fmt_FormatArg a_value);
Readonly make_empty_readonly();
Result set_readonly(Readonly a_readonly, c_fmt_FormatArg a_value);
Result get_readonly(Readonly a_readonly);

#endif //CREADONLY_H
