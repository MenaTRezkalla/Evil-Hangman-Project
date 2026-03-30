#ifndef UNIT_TEST_H 
#define UNIT_TEST_H 
#include "my_string.h" 
 
Status test_init_default_returns_nonNULL(char* buffer, int length); 
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_mrezkall_get_capacity_on_init_default_returns_20(char* buffer, int length);
Status test_mrezkall_get_data_on_init_c_string_hello_returns_hello(char* buffer, int length);
Status test_mrezkall_string_compare_on_init_c_string_hello_returns_0(char* buffer, int length);
Status test_mrezkall_push_back_on_init_c_string_hello_returns_helloo(char* buffer, int length);
Status test_mrezkall_pop_back_on_init_c_string_helloo_returns_hello(char* buffer, int length);
Status test_mrezkall_my_string_at_on_init_c_string_hello_returns_h(char* buffer, int length);
Status test_mrezkall_my_string_c_str_init_c_string_hello_returns_hello(char* buffer, int length);
Status test_mrezkall_hellohello(char* buffer, int length);
Status test_mrezkall_empty(char* buffer, int length);
Status test_mrezkall_empty2(char* buffer, int length);

Status test_mrezkall_test1(char* buffer, int length);
Status test_mrezkall_test2(char* buffer, int length);
Status test_mrezkall_test3(char* buffer, int length);
Status test_mrezkall_test4(char* buffer, int length);
Status test_mrezkall_test5(char* buffer, int length);
Status test_mrezkall_test6(char* buffer, int length);
Status test_mrezkall_test7(char* buffer, int length);
Status test_mrezkall_test8(char* buffer, int length);
Status test_mrezkall_test9(char* buffer, int length);
Status test_mrezkall_test10(char* buffer, int length);
Status test_mrezkall_test11(char* buffer, int length);
Status test_mrezkall_test12(char* buffer, int length);
Status test_mrezkall_test13(char* buffer, int length);
Status test_mrezkall_test14(char* buffer, int length);

#endif
