#include <stdio.h> 
#include "unit_test.h" 
 
int main(int argc, char* argv[]) 
{ 
   Status (*tests[])(char*, int) = 
       {  
            test_init_default_returns_nonNULL, 
            test_get_size_on_init_default_returns_0,
	    test_mrezkall_get_capacity_on_init_default_returns_20,
	    test_mrezkall_get_data_on_init_c_string_hello_returns_hello,
	    test_mrezkall_string_compare_on_init_c_string_hello_returns_0,
	    test_mrezkall_push_back_on_init_c_string_hello_returns_helloo,
	    test_mrezkall_pop_back_on_init_c_string_helloo_returns_hello,
	    test_mrezkall_my_string_at_on_init_c_string_hello_returns_h,
	    test_mrezkall_my_string_c_str_init_c_string_hello_returns_hello,
	    test_mrezkall_hellohello,
	    test_mrezkall_empty,
	    test_mrezkall_empty2,
	    test_mrezkall_test1,
test_mrezkall_test2,
test_mrezkall_test3,
test_mrezkall_test4,
test_mrezkall_test5,
test_mrezkall_test6,
test_mrezkall_test7,
test_mrezkall_test8,
test_mrezkall_test9,
test_mrezkall_test10,
test_mrezkall_test11,
test_mrezkall_test12,
test_mrezkall_test13,
test_mrezkall_test14

       }; 
   int number_of_functions = sizeof(tests) / sizeof(tests[0]); 
   int i; 
   char buffer[500]; 
   int success_count = 0; 
   int failure_count = 0; 
 
   for(i=0; i<number_of_functions; i++) 
   { 
      if(tests[i](buffer, 500) == FAILURE) 
      { 
         printf("FAILED: Test %d failed miserably\n", i); 
         printf("\t%s\n", buffer); 
         failure_count++; 
      } 
      else 
      { 
// printf("PASS: Test %d passed\n", i); 
  // printf("\t%s\n", buffer); 
         success_count++; 
      } 
   } 
   printf("Total number of tests: %d\n", number_of_functions); 
   printf("%d/%d Pass, %d/%d Failure\n", success_count, 
      number_of_functions, failure_count, number_of_functions); 
   return 0; 
}
