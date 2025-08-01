cmake_minimum_required(VERSION 3.31)
project(CFmt C)

set(CMAKE_C_STANDARD 11)

add_executable(CFmt main.c
        cfmt.c
        cfmt.h
        cresult.h
        cresult.c
        creadonly.h
        creadonly.c
        citer.h
        citer.c
        cdefer.h
        cexcept.h
        cexcept.c
        chash.h
        coptional.h
        coptional.c
        cstring.h
        cstring.c
        a_string.h
        a_cvector.h
        cstrat.h
        c_strat.c
)
