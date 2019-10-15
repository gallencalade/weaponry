#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUILD_YEAR_NUM0 (__DATE__[7] - '0')
#define BUILD_YEAR_NUM1 (__DATE__[8] - '0')
#define BUILD_YEAR_NUM2 (__DATE__[9] - '0')
#define BUILD_YEAR_NUM3 (__DATE__[10] - '0')

#define BUILD_MON_IS_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define BUILD_MON_IS_FEB (__DATE__[0] == 'F')
#define BUILD_MON_IS_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define BUILD_MON_IS_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define BUILD_MON_IS_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define BUILD_MON_IS_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define BUILD_MON_IS_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define BUILD_MON_IS_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define BUILD_MON_IS_SEP (__DATE__[0] == 'S')
#define BUILD_MON_IS_OCT (__DATE__[0] == 'O')
#define BUILD_MON_IS_NOV (__DATE__[0] == 'N')
#define BUILD_MON_IS_DEC (__DATE__[0] == 'D')

#define BUILD_MON_NUM0 \
  ((BUILD_MON_IS_OCT || BUILD_MON_IS_NOV || BUILD_MON_IS_DEC) ? 1 : 0)

#define BUILD_MON_NUM1 \
  ( \
    (BUILD_MON_IS_JAN) ? 1 : \
    (BUILD_MON_IS_FEB) ? 2 : \
    (BUILD_MON_IS_MAR) ? 3 : \
    (BUILD_MON_IS_APR) ? 4 : \
    (BUILD_MON_IS_MAY) ? 5 : \
    (BUILD_MON_IS_JUN) ? 6 : \
    (BUILD_MON_IS_JUL) ? 7 : \
    (BUILD_MON_IS_AUG) ? 8 : \
    (BUILD_MON_IS_SEP) ? 9 : \
    (BUILD_MON_IS_OCT) ? 0 : \
    (BUILD_MON_IS_NOV) ? 1 : \
    (BUILD_MON_IS_DEC) ? 2 : \
    '?' \
    )

#define BUILD_DAY_NUM0 ((__DATE__[4] >= 0) ? (__DATE__[4] - '0') : 0)
#define BUILD_DAY_NUM1 (__DATE__[5] - '0')

#define COMPILED_TIME_DAY   (BUILD_DAY_NUM0 * 10 + BUILD_DAY_NUM1)
#define COMPILED_TIME_MON   (BUILD_MON_NUM0 * 10 + BUILD_MON_NUM1)
#define COMPILED_TIME_YEAR  (BUILD_YEAR_NUM0 * 1000 + BUILD_YEAR_NUM1 * 100 + BUILD_YEAR_NUM2 * 10 + BUILD_YEAR_NUM3)

