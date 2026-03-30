#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"


Status test_init_default_returns_nonNULL(char* buffer, int length) 
{ 
   MY_STRING hString = NULL; 
 
   hString = my_string_init_default(); 
 
   if(hString == NULL) 
   { 
      strncpy(buffer, "test_init_default_returns_nonNULL\n" 
                   "my_string_init_default returns NULL", length); 
      return FAILURE; 
   } 
   else 
   { 
      my_string_destroy(&hString); 
      strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length); 
      return SUCCESS; 
   } 
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   if(my_string_get_size(hString) != 0)
   {
      status = FAILURE;
      printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
                   "Did not receive 0 from get_size after init_default\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
                   , length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_get_capacity_on_init_default_returns_20(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   if(my_string_get_capacity(hString) != 20)
   {
      status = FAILURE;
      printf("Expected a size of 20 but got %d\n", my_string_get_capacity(hString));
      strncpy(buffer, "test_mrezkall_get_capacity_on_init_default_returns_20\n"
                   "Did not receive 20 from get_capacity after init_default\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_mrezkall_get_capacity_on_init_default_returns_20\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_get_data_on_init_c_string_hello_returns_hello(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("hello");

   if(strcmp(my_string_get_data(hString), "hello") != 0)
   {
      status = FAILURE;
      printf("Expected data of hello but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test_mrezkall_get_data_on_init_c_string_hello_returns_hello\n" "Did not receive hello from get_data after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_mrezkall_get_data_on_init_c_string_hello_returns_hello\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_string_compare_on_init_c_string_hello_returns_0(char* buffer, int length)
{
   MY_STRING hString = NULL;
   MY_STRING hString2 = NULL;
   Status status;

   hString = my_string_init_c_string("hello");
   hString2 = my_string_init_c_string("hello");

   if(my_string_compare(hString, hString2) != 0)
   {
      status = FAILURE;
      printf("Expected 0 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test_mrezkall_string_compare_on_init_c_string_hello_returns_0\n" "Did not receive 0 from string_compare after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_mrezkall_string_compare_on_init_c_string_hello_returns_0\n", length);
   }

   my_string_destroy(&hString);
   my_string_destroy(&hString2);
   return status;
}

Status test_mrezkall_push_back_on_init_c_string_hello_returns_helloo(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("hello");

   my_string_push_back(hString, 'o');

   if(strcmp(my_string_get_data(hString), "helloo") != 0)
   {
      status = FAILURE;
      printf("Expected heloo but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test_mrezkall_push_back_on_init_c_string_hello_returns_helloo\n" "Did not receive helloo from get_data after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_mrezkall_push_back_on_init_c_string_hello_returns_helloo\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_pop_back_on_init_c_string_helloo_returns_hello(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("helloo");

   my_string_pop_back(hString);

   if(strcmp(my_string_get_data(hString), "hello") != 0)
   {
      status = FAILURE;
      printf("Expected data of hello but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test_mrezkall_pop_back_on_init_c_string_helloo_returns_hello\n" "Did not receive hello from get_data after init_c_string\n", length);
   }
   else
   {
	status = SUCCESS;                                                                                                                                           strncpy(buffer, "test_mrezkall_pop_back_on_init_c_string_helloo_returns_hello\n", length);
   }
   
   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_my_string_at_on_init_c_string_hello_returns_h(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("hello");

   if(*my_string_at(hString, 0) != 'h')
   {
      status = FAILURE;
      printf("Expected h but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test_mrezkall_pop_back_on_init_c_string_helloo_returns_hello\n" "Did not receive h from get_data after init_c_string\n", length);   }
   else
   {
        status = SUCCESS;                                                                                                                                           strncpy(buffer, "test_mrezkall_pop_back_on_init_c_string_helloo_returns_hello\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_my_string_c_str_init_c_string_hello_returns_hello(char* buffer, int length)
{

   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("hello");

   if(strcmp(my_string_c_str(hString), "hello") != 0)
   {
      status = FAILURE;
      printf("Expected data of hello but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test_mrezkall_get_data_on_init_c_string_hello_returns_hello\n" "Did not receive hello from get_data after init_c_string\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_mrezkall_get_data_on_init_c_string_hello_returns_hello\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_hellohello(char* buffer, int length)
{
   MY_STRING hString = NULL;
   MY_STRING hString2 = NULL;
   Status status;

   hString = my_string_init_c_string("hello");
   hString2 = my_string_init_c_string("hello");

   my_string_concat(hString, hString2);

   if(strcmp(my_string_c_str(hString), "hellohello") != 0)
   {
      status = FAILURE;
      printf("Expected data of hello but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "hellohello\n" "hellohellono\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_mrezkall_hellohello\n", length);
   }

   my_string_destroy(&hString);
   my_string_destroy(&hString2);
   return status;
}

Status test_mrezkall_empty(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   if(my_string_empty(hString) != TRUE)
   {
      status = FAILURE;
      printf("Expected empty but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "empty\n" "notempty\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_mrezkall_empty\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_empty2(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("hello");

   if(my_string_empty(hString) == TRUE)
   {
      status = FAILURE;
      printf("Expected not empty but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "empty\n" "notempty\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test_mrezkall_empty2\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test1(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("1");

   if(strcmp(my_string_get_data(hString), "1") != 0)
   {
      status = FAILURE;
      printf("Expected 1 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test1\n" "test1 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test1\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test2(char* buffer, int length)
{
   MY_STRING hString = NULL;
   MY_STRING hString2 = NULL;
   Status status;

   hString = my_string_init_c_string("");
   hString2 = my_string_init_c_string("");

   my_string_concat(hString, hString2);

   if(strcmp(my_string_get_data(hString), "") != 0)
   {
      status = FAILURE;
      printf("Expected  but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test2\n" "test2 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test2\n", length);
   }

   my_string_destroy(&hString);
   my_string_destroy(&hString2);
   return status;
}

Status test_mrezkall_test3(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("za");

   if(*my_string_at(hString, 1) != 'a')
   {
      status = FAILURE;
      printf("Expected a but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test3\n" "test3 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test3\n", length);
   }

   my_string_destroy(&hString);
   return status;
}
	
Status test_mrezkall_test4(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_default();

   my_string_push_back(hString, '4');

   if(strcmp(my_string_get_data(hString), "4") != 0)
   {
      status = FAILURE;
      printf("Expected 4 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test4\n" "test4 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test4\n", length);
   }

   my_string_destroy(&hString);
   return status;
}


Status test_mrezkall_test5(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("578");

   my_string_pop_back(hString);
   my_string_pop_back(hString);

   if(strcmp(my_string_get_data(hString), "5") != 0)
   {
      status = FAILURE;
      printf("Expected 5 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test5\n" "test5 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test5\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test6(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("6");

   my_string_push_back(hString, '6');

   if(strcmp(my_string_get_data(hString), "66") != 0)
   {
      status = FAILURE;
      printf("Expected 6 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test6\n" "test6 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test6\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test7(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("7");

   if(strcmp(my_string_get_data(hString), "7") != 0)
   {
      status = FAILURE;
      printf("Expected 7 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test7\n" "test7 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test7\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test8(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("8");

   if(my_string_get_size(hString) != 1)
   {
      status = FAILURE;
      printf("Expected 8 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test8\n" "test8 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test8\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test9(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("9");

   my_string_push_back(hString, '9');
   my_string_pop_back(hString);

   if(strcmp(my_string_get_data(hString), "9") != 0)
   {
      status = FAILURE;
      printf("Expected 9 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test9\n" "test9 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test9\n", length);
   }

   my_string_destroy(&hString);
   return status;
}


Status test_mrezkall_test10(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("10");

   my_string_pop_back(hString);
   my_string_pop_back(hString);
   my_string_pop_back(hString);

   if(strcmp(my_string_get_data(hString), "") != 0)
   {
      status = FAILURE;
      printf("Expected nothing but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test10\n" "test10 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test10\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test11(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("11");

   my_string_push_back(hString, '9');

   if(strcmp(my_string_get_data(hString), "119") != 0)
   {
      status = FAILURE;
      printf("Expected 119 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test11\n" "test11 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test11\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test12(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("12");

   my_string_pop_back(hString);

   if(strcmp(my_string_get_data(hString), "1") != 0)
   {
      status = FAILURE;
      printf("Expected 1 but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test12\n" "test12 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test12\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test13(char* buffer, int length)
{
   MY_STRING hString = NULL;
   Status status;

   hString = my_string_init_c_string("13");

   my_string_pop_back(hString);
   my_string_pop_back(hString);
   my_string_pop_back(hString);

   if(my_string_empty(hString) != TRUE)
   {
      status = FAILURE;
      printf("Expected nothing but got %s\n", my_string_get_data(hString));
      strncpy(buffer, "test13\n" "test13 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test13\n", length);
   }

   my_string_destroy(&hString);
   return status;
}

Status test_mrezkall_test14(char* buffer, int length)
{
   MY_STRING hString = NULL;
   MY_STRING hString2 = NULL;
   Status status;

   hString = my_string_init_c_string("b_");
   hString2 = my_string_init_c_string("b_");

   if(my_string_compare(hString, hString2) != 0)
   {
      status = FAILURE;
      printf("Expected 0 but got %d\n", my_string_compare(hString, hString2));
      strncpy(buffer, "test14\n" "test14 failed\n", length);
   }
   else
   {
      status = SUCCESS;
      strncpy(buffer, "test14\n", length);
   }

   my_string_destroy(&hString);
   my_string_destroy(&hString2);
   return status;
}

