/*========================================================================================
EWENIT.c
Version 0.8.2

⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣐⡙⠶⣿⣷⣌⡳⣿⡿⠿⢷⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣠⡴⠮⠁⠀⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠙⠟⢿⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢠⡾⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⣀⡘⠿⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣿⠃⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠻⣅⠀⠀⠀⠀⠀⢈⣹⣄⣼⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣿⠓⠒⠂⠀⣿⣰⣠⡀⠀⠀⢰⣦⣾⠷⠶⢤⣾⡦⠾⠉⠉⠉⠙⠿⢶⣦⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣿⣤⣤⣀⢀⣠⠄⠉⣻⡷⠾⠛⠁⠀⠀⠀⠀⠀⠝⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⣻⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⢀⣀⣠⡴⢿⣤⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠻⣧⣀⣌⠁⢀⡶⠞⠁⠀⠀⠀⣀⣤⣤⣄⠀⠀⢀⡾⠀⠀⠀⠀⠀⣠⡾⠿⠛⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡼⠛⠋⠉⠀⠀⠀⠀⠀⠉⠉⠙⠳⣄⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣠⣿⡿⠉⠉⠉⠀⠀⠀⠀⣰⣾⣿⣿⠾⠋⠀⠀⠈⢹⡷⠶⠶⠶⠿⠟⣷⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣴⠟⠒⠛⠉⠛⠒⠦⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠙⢦⡀⠀⠀⠀
⠀⠀⢀⣼⡿⠋⠀⠀⠀⠀⠀⠀⠀⠘⠉⠀⠀⠀⠀⠀⠀⠀⠀⣸⠇⠀⠀⠀⠀⠀⠹⣷⣶⠶⠶⠤⠶⣶⣟⡋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⢦⠀⠀⠀⠀⠀⠀⠀⠀⢻⡄⠀⠀
⠀⣠⣾⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠏⠀⠀⠀⠀⠀⠀⠀⠙⣷⡄⠀⠀⠀⠀⠀⠙⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⡄⠀
⣸⡿⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠰⣏⢿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣄
⢿⣇⠀⢀⣶⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠋⠘⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⢺
⢸⣿⢿⡏⠀⠀⠀⣀⡤⠀⢀⣀⣀⣠⣤⡶⠶⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠟⠀⠾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸
⠀⠙⢿⡟⠓⠛⠋⣁⣀⣴⣿⣿⣿⡉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶⠋⠀⠀⣤⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀
⠀⠀⠀⠙⠻⠟⠛⠛⠉⠉⠀⠀⢹⣿⠦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣆⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡟⠛⠓⠦⢤⠆⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠖⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡗⠢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠟⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣶⢤⣤⣀⣀⡀⠀⢀⣴⠴⠚⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⡀⠀⠀⠀⠀⢸⡏
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⡀⣈⠉⠉⠉⡟⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢐⡏⢰⡇⠀⠀⠀⠀⣾⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⣿⠓⠶⣞⣁⡀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣹⠀⠀⠀⠀⠀⠀⣰⠟⢐⡿⠃⠀⠀⠀⠀⣸⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣧⠀⠀⠀⠀⠙⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡴⠋⠀⠀⠀⢠⣤⠞⠁⢀⡿⠃⠀⠀⣠⠟⣴⡟⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡛⠲⢦⣄⣀⣠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⣀⣀⢀⡴⠋⠀⠀⠀⠀⠀⠀⠀⣠⣴⣿⣁⣀⣠⣞⣡⣼⡿⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣷⣄⣀⣈⡉⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠀⠀⠉⠉⢹⡇⠀⠀⠀⠀⠀⣀⣰⣾⠛⣻⡟⠈⠉⠉⠉⢿⣿⠁⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣌⣉⠉⠉⣡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠞⠁⠀⠀⢀⣴⡿⣤⣀⣴⠶⡴⠏⠉⢹⣿⠀⣿⡇⠀⠀⠀⠀⠈⣿⡄⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣧⡉⠓⠆⠀⠙⣦⡀⠀⠀⣀⡀⠀⣀⣤⠴⠛⠁⠀⠀⠀⠀⢼⡏⠀⠀⠀⣿⡇⠀⠀⠀⢸⣿⠀⢿⣇⠀⠀⠀⠀⣰⣿⠃⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣷⠤⢤⣄⣀⣈⣙⣻⡿⠋⠉⠻⣿⣀⠀⠀⠀⢀⣀⣤⣶⠏⠀⠀⠀⠀⣿⡇⠀⠀⠀⢸⣿⠀⠘⣿⡄⠀⠀⠀⣿⡏⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣇⠀⠀⠈⠉⠉⢿⣿⠃⠀⠀⠀⢻⣿⡟⠃⠀⠈⠉⢹⣿⠀⠀⠀⠀⢀⣿⠁⠀⠀⠀⠘⣿⠀⠀⢹⡇⠀⠀⠀⣿⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡀⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⠈⣿⡇⠀⠀⠀⠀⢸⡟⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⢀⣿⡇⠀⢸⡇⠀⠀⠀⣿⡆⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣇⠀⠀⠀⠀⣿⡏⠀⠀⠀⠀⠀⢻⣇⠀⠀⠀⠀⢸⣧⠀⠀⠀⠀⢸⣿⠀⢀⡀⠀⣾⣿⠁⠀⣼⡇⠀⠀⠀⠘⣿⡀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠀⠀⠀⢀⣿⡇⠀⠀⠀⠀⠀⠀⣿⡀⠀⠀⠀⢀⣿⡄⠀⠀⠀⣿⣏⣀⣾⣀⣰⡿⠃⠀⣰⣿⠀⠀⠀⠀⠀⣼⡇⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠃⠀⠀⢸⣿⡀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⣼⣿⠇⠀⠀⠀⠉⠉⠉⠉⠉⠉⠀⠀⠀⣿⠇⠀⢀⡀⠀⢰⣿⠁⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡏⠀⠀⠀⠀⢿⣇⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠀⠀⣼⡇⢀⣿⡿⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡟⠀⠀⠀⠀⢀⣾⣿⠂⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⠷⠿⠿⠟⠛⠋⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀⠀⠀⠀⣼⣿⠁⠀⠀⠀⠀⠀⣠⣿⠀⠀⠀⠀⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠇⢀⡆⠀⠀⣠⣿⡏⠀⠀⠀⠀⠀⣠⣿⠇⠀⠀⠀⠀⢹⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⠶⠛⠻⠿⠟⠛⠋⠀⠀⠀⠀⠀⢀⣿⠏⠀⠀⠀⠀⢀⣾⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⠋⢀⡄⠀⠀⣰⣿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣧⣤⣾⣷⡤⠾⢟⢁⠀⠀⠀⠀

========================================================================================*/
#ifndef INCLUDE_GUARD_EWENIT_MASTER
#define INCLUDE_GUARD_EWENIT_MASTER


#include "EWENIT.h"
#include "extensions/extensions_master.h"

#include "int_assertions.h"
#include "str_assertions.h"
#include "float_assertions.h"
#include "double_assertions.h"

TestSuite* ts;

#define ASSERT_EQUAL_INT(val1, val2)            ERROR_CHECK(assert_equal_int(ts, val1, val2, __LINE__))
#define ASSERT_NOT_EQUAL_INT(val1, val2)        ERROR_CHECK(assert_not_equal_int(ts, val1, val2, __LINE__))
#define ASSERT_GREATER_THAN_INT(val1, val2)     ERROR_CHECK(assert_greater_than_int(ts, val1, val2, __LINE__))

#define ASSERT_TRUE(val1)                       ERROR_CHECK(assert_true(ts, val1, __LINE__))
#define ASSERT_FALSE(val1)                      ERROR_CHECK(assert_false(ts, val1, __LINE__))

#define ASSERT_EQUAL_STR(val1, val2)            ERROR_CHECK(assert_equal_str(ts, val1, val2, __LINE__))
#define ASSERT_NOT_EQUAL_STR(val1, val2)        ERROR_CHECK(assert_not_equal_str(ts, val1, val2, __LINE__))


#define ASSERT_EQUAL_FLOAT(val1, val2)          ERROR_CHECK(assert_equal_float(ts, val1, val2, __LINE__))
#define ASSERT_NOT_EQUAL_FLOAT(val1, val2)      ERROR_CHECK(assert_not_equal_float(ts, val1, val2, __LINE__))
#define ASSERT_GREATER_THAN_FLOAT(val1, val2)   ERROR_CHECK(assert_greater_than_float(ts, val1, val2, __LINE__))
#define ASSERT_ALMOST_EQUAL_FLOAT(val1, val2)   ERROR_CHECK(assert_almost_equal_float(ts, val1, val2, __LINE__))
#define ASSERT_NOT_ALMOST_EQUAL_FLOAT(val1, val2) \
                                                ERROR_CHECK(assert_not_almost_equal_float(ts, val1, val2, __LINE__))


#define ASSERT_EQUAL_DOUBLE(val1, val2)         ERROR_CHECK(assert_equal_double(ts, val1, val2, __LINE__))
#define ASSERT_NOT_EQUAL_DOUBLE(val1, val2)     ERROR_CHECK(assert_not_equal_double(ts, val1, val2, __LINE__))
#define ASSERT_GREATER_THAN_DOUBLE(val1, val2)  ERROR_CHECK(assert_greater_than_double(ts, val1, val2, __LINE__))
#define ASSERT_ALMOST_EQUAL_DOUBLE(val1, val2)  ERROR_CHECK(assert_almost_equal_double(ts, val1, val2, __LINE__))
#define ASSERT_NOT_ALMOST_EQUAL_DOUBLE(val1, val2) \
                                                ERROR_CHECK(assert_not_almost_equal_double(ts, val1, val2, __LINE__))


#endif