#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

struct my_string
{
	int size;
	int capacity;
	char* data;
};
typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
	My_string* pString;
	
	pString = malloc(sizeof(My_string));
	if (pString != NULL)
	{
		pString->size = 0;
		pString->capacity = 20;

		pString->data = malloc(sizeof(char) * pString->capacity);
		if (pString->data == NULL)
		{
			free(pString);
			return NULL;
		}
	}
	return pString;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
        My_string* pString;

        pString = malloc(sizeof(My_string));
        if (pString != NULL)
        {
		int i = 0;

		while (c_string[i] != '\0')
		{
			i++;
		}

		pString->size = i;

                pString->capacity = i + 1;

                pString->data = malloc(sizeof(char) * pString->capacity);
                if (pString->data == NULL)
                {
                        free(pString);
                        return NULL;
                }

		for (i = 0; i < pString->capacity; i++)
		{
			pString->data[i] = c_string[i];
		}
        }
        return pString;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string* pString = (My_string*)hMy_string;
	return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
	My_string* pString = (My_string*)hMy_string;
        return pString->size;
}

char* my_string_get_data(MY_STRING hMy_string)
{
	My_string* pString = (My_string*)hMy_string;
        return pString->data;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string* pLeft_string = (My_string*)hLeft_string;
	My_string* pRight_string = (My_string*)hRight_string;
	
	int i = 0;
	int j = 0;
	while (pLeft_string->data[i] == pRight_string->data[j] && pLeft_string->data[i] != '\0' && pRight_string->data[j] != '\0')
	{
	
		if (pLeft_string->data[i] != '\0')
		{
			i++;  
		}

		if (pRight_string->data[j] != '\0')
		{
			j++;  
		}
	}
	return pLeft_string->data[i] - pRight_string->data[j];
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	
	char c;
	int noc;
	int i = 0;

	noc = fscanf(fp, " %c", &c);
	if (noc != 1)
	{
		return FAILURE;
	}

	pMy_string->data[i] = c;
	pMy_string->size = i;
	i++;

	noc = fscanf(fp, "%c", &c);
        while (noc == 1 && !isspace(c))
        {
		pMy_string->data[i] = c;
		pMy_string->size = i;
		i++;

		if (i > pMy_string->capacity - 1)
		{
			if (my_string_double_capacity(hMy_string) == FAILURE)
			{
				return FAILURE;
			}

		}
                noc = fscanf(fp, "%c", &c);
	}

	if (noc != 1)
	{
		pMy_string->data[i] = '\0';
		pMy_string->size = i;
		return SUCCESS;
	}

	if (isspace(c))
	{
		ungetc(c, fp);
		pMy_string->data[i] = '\0';
		pMy_string->size = i;
                return SUCCESS;
	}

	return FAILURE;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
        My_string* pMy_string = (My_string*)hMy_string;

        if (fp == NULL)
        {
                return FAILURE;
        }

        fprintf(fp, "%s", pMy_string->data);

        return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
	My_string* pMy_string = (My_string*)hMy_string;

	if(pMy_string->size > pMy_string->capacity - 1)
	{
		if(my_string_double_capacity(hMy_string) == FAILURE)
		{
			return FAILURE;
		}
	}

	pMy_string->data[pMy_string->size] = item;
	pMy_string->data[pMy_string->size + 1] = '\0';
	pMy_string->size++;

	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	
	if(my_string_empty(hMy_string) == TRUE)
	{
		return FAILURE;
	}
	
	pMy_string->size--;
	pMy_string->data[pMy_string->size] = '\0';
	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if(index < 0 || index >= pMy_string->size)
	{
		return NULL;
	}

	return pMy_string->data + index;
}

char* my_string_c_str(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->data;
}


Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string* pResult = (My_string*)hResult;
	My_string* pAppend = (My_string*)hAppend;
	int i = 0;
	
	while(pResult->size + pAppend->size > pResult->capacity)
	{
		if(my_string_double_capacity(hResult) == FAILURE)
		{
			return FAILURE;
		}
	}

	for(i = 0; i < pAppend->size; i++)
	{
		my_string_push_back(hResult, pAppend->data[i]);
	}

	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	return (pMy_string->size <= 0) ? TRUE : FALSE;
}

Status my_string_assignment(MY_STRING hLeft, MY_STRING hRight)
{
	My_string* pLeft = (My_string*)hLeft;
	My_string* pRight = (My_string*)hRight;
	
	int i = 0;

	while(pLeft->capacity < pRight->size)
	{
 		if(my_string_double_capacity(hLeft) == FAILURE)
                {
                        return FAILURE;
                }
	}

	while(my_string_empty(hLeft) == FALSE)
	{
		my_string_pop_back(hLeft);
	}

	for(i = 0; i < pRight->size; i++)
	{
		my_string_push_back(hLeft, pRight->data[i]);
	}

	return SUCCESS;
}

MY_STRING my_string_init_copy(MY_STRING hMy_string)
{
	My_string* temp = NULL;

	temp = my_string_init_c_string(my_string_c_str(hMy_string));
	if(temp == NULL)
	{
		return NULL;
	}

	return temp;
}

void my_string_swap(MY_STRING hLeft, MY_STRING hRight)
{
	My_string* pLeft = (My_string*)hLeft;
        My_string* pRight = (My_string*)hRight;
	
	int temp_size = 0;
	int temp_capacity = 0;
	char* temp_data = NULL;
	
	temp_size = pLeft->size;
	temp_capacity = pLeft->capacity;
	temp_data = pLeft->data;

	pLeft->size = pRight->size;
	pLeft->capacity = pRight->capacity;
	pLeft->data = pRight->data;

	pRight->size = temp_size;
	pRight->capacity = temp_capacity;
	pRight->data = temp_data;	
}

Status my_string_double_capacity(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	char* temp = NULL;
	int i = 0;

	temp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2);
	if (temp == NULL)
	{
		return FAILURE;
	}

	for (i = 0; i < pMy_string->size; i++)
	{
		temp[i] = pMy_string->data[i];
	}

	free(pMy_string->data);
	pMy_string->data = temp;
	pMy_string->capacity *= 2;

	return SUCCESS;
}	

void my_string_destroy(MY_STRING* phString)
{
	My_string* pString = (My_string*)*phString;

	free(pString->data);

	free(pString);
	*phString = NULL;
}
