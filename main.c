#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "my_string.h" 
#include "generic_vector.h"
#include "associative_array.h"

ITEM integer_init_copy(ITEM hInt);
void integer_destroy(ITEM* phInt);

void display_game_state(int number_of_guesses, MY_STRING guessed_letters, MY_STRING guessed_word, int words_remaining, int remaining_toggle);

Boolean guessed_already(MY_STRING guessed_letters, char guess);

Status process_guess(TREE word_tree, MY_STRING guessed_word, MY_STRING temp_string, MY_STRING largest, GENERIC_VECTOR word_list, char guess);

void clear_keyboard_buffer(void);
 
int main(int argc, char* argv[]) 
{ 
	GENERIC_VECTOR vectors[30];
	FILE* dictionary;
	MY_STRING reader;
	int i;

	dictionary = fopen("dictionary.txt", "r");
	if(dictionary == NULL)
	{
		printf("Failed to open file object.\n");
		exit(1);
	}

	reader = my_string_init_default();
	if(reader == NULL)
	{
		printf("Failed to allocate space for my_string object\n");
		exit(1);
	}

	for(i = 0; i < 30; i++)
	{
		vectors[i] = generic_vector_init_default(my_string_init_copy, my_string_destroy);
		if(vectors[i] == NULL)
		{
			printf("Failed to initialize generic vector\n");
			exit(1);
		}
	}
	
	while (my_string_extraction(reader, dictionary))
	{
		if(generic_vector_push_back(vectors[my_string_get_size(reader)], reader) == FAILURE)
		{
			printf("Failed to push back.\n");
			exit(1);
		}
	}

	int word_length = -1;
	int number_of_guesses = -1;
	int remaining_toggle = 0;
	char yes_no = '\0';
	int noc;
	char guess = '\0';
	int won = 0;

	GENERIC_VECTOR word_list = NULL;
	MY_STRING guessed_word = NULL;
	MY_STRING guessed_letters = NULL;
	MY_STRING temp_string = NULL;
	MY_STRING largest = NULL;
	MY_STRING old_word = NULL;
	TREE word_tree = NULL;

	printf("Welcome to Evil Hangman!\n");
	
	printf("What length of words you would like? (2-29): ");
	while(word_length < 2 || word_length > 29)
	{
		noc = scanf("%d", &word_length);
		
		if(noc != 1 || (word_length < 2 || word_length > 29))
		{
			printf("Try again (2-29): "); 
			word_length = -1;
		}
		else
		{
			if(generic_vector_get_size(vectors[word_length]) <= 0)
                        {
                                printf("I'm sorry, there are no words of that length.\n");
				printf("Try again (2-29): ");
				word_length = -1;
                        }
		}

		clear_keyboard_buffer();
	}

	word_list = generic_vector_init_default(my_string_init_copy, my_string_destroy); 
	if(word_list == NULL)
	{
		printf("Failed to initialize word list\n");
		exit(1);
	}

	if(generic_vector_assignment(word_list, vectors[word_length]) == FAILURE)
	{
		printf("Failed to copy word list\n");
		exit(1);
	}

	printf("How many guesses would you like? (must be bigger than 0): ");
	while(number_of_guesses <= 0)
        {
                noc = scanf("%d", &number_of_guesses);
                if(noc != 1 || (number_of_guesses <= 0))
                {
                        printf("Try again (must be bigger than 0): ");
                        number_of_guesses = -1;
                }
                clear_keyboard_buffer();
        }

	printf("Would you like to know the number of words remaining? (y/n): ");
        while(yes_no != 'y' && yes_no != 'n')
        {
                noc = scanf("%c", &yes_no);
                if(noc != 1 || (yes_no != 'y' && yes_no != 'n'))
                {
                        printf("Try again (y/n): ");
                        yes_no = '\0';
                }
                clear_keyboard_buffer();
        }

	if(yes_no == 'y')
	{
		remaining_toggle = 1;
	}

	guessed_word = my_string_init_default();
	if(guessed_word == NULL)
	{
		printf("Failed to allocate space for guessed word.\n");
		exit(1);
	}

	for(i = 0; i < word_length; i++)
	{
		if(my_string_push_back(guessed_word, '_') == FAILURE)
		{
			printf("Failed to push back.\n");
			exit(1);
		}
	}

	guessed_letters = my_string_init_default();
        if(guessed_letters == NULL)
        {
                printf("Failed to allocate space for guessed letters.\n");
                exit(1);
        }

	temp_string = my_string_init_default();
        if(temp_string == NULL)
        {
                printf("Failed to allocate space for temp.\n");
                exit(1);
        }

	if(my_string_assignment(temp_string, guessed_word) == FAILURE)
	{
		printf("Failed to copy guessed word.\n");
		exit(1);
	}

	largest = my_string_init_default();
        if(largest == NULL)
        {
                printf("Failed to allocate space for largest.\n");
                exit(1);
        }

	old_word = my_string_init_copy(guessed_word);
        if(old_word == NULL)
        {
                printf("Failed to allocate space for old word.\n");
                exit(1);
        }

	while(number_of_guesses > 0)
	{
		printf("==============================\n");

		word_tree = tree_init_default();
        	if(word_tree == NULL)
        	{
                	printf("Failed to allocate space for word tree\n");
        	        exit(1);
        	}

		display_game_state(number_of_guesses, guessed_letters, guessed_word, generic_vector_get_size(word_list), remaining_toggle);
		
		printf("Guess a letter: ");
		noc = scanf("%c", &guess);
		while(noc != 1 || !isalpha(guess) || guessed_already(guessed_letters, guess) == TRUE)
		{
			printf("Try again. Guess a letter: ");
			clear_keyboard_buffer();
			noc = scanf("%c", &guess);
		}
		clear_keyboard_buffer();

		if(process_guess(word_tree, guessed_word, temp_string, largest, word_list, guess) == FAILURE)
		{
			printf("FATAL ERROR\n");
			exit(1);
		}


		if(generic_vector_get_size(word_list) <= 1)
		{
			if(my_string_compare(guessed_word, *generic_vector_at(word_list, 0)) == 0)
			{
				break;
			}
		}

		if(my_string_compare(guessed_word, old_word) == 0)
		{
			number_of_guesses--;
		}

		if(my_string_assignment(old_word, guessed_word) == FAILURE)
        	{
                	printf("Failed to assign string.\n");
			exit(1);
       		}	

		if(my_string_push_back(guessed_letters, guess) == FAILURE)
		{
			printf("Failed to push back.\n");
			exit(1);
		}

		tree_destroy(&word_tree);

		printf("==============================\n");
	}

	printf("==============================\n");
	printf("==============================\n");

	if(generic_vector_get_size(word_list) <= 1)
        {
		if(my_string_compare(guessed_word, *generic_vector_at(word_list, 0)) == 0)
		{
			won = 1;
			printf("You Win! Your word was: %s\n", my_string_c_str(guessed_word));
		}
        }

	if(won == 0)
	{
		printf("You Lose! Your word was: %s\n", my_string_c_str(*generic_vector_at(word_list, 0)));
	}

	printf("==============================\n");
        printf("==============================\n");

	for(i = 0; i < 30; i++)
        {
                generic_vector_destroy(&(vectors[i]));
        }

	if(word_tree == NULL)
	{
		word_tree = tree_init_default();
        	if(word_tree == NULL)
		{
			printf("Failed to allocate space for word tree\n");
			exit(1);
		}
	}

	generic_vector_destroy(&word_list);
	my_string_destroy(&reader);
	my_string_destroy(&guessed_word);
	my_string_destroy(&guessed_letters);
	my_string_destroy(&temp_string);
	my_string_destroy(&largest);
	my_string_destroy(&old_word);
	tree_destroy(&word_tree);
	fclose(dictionary);

	return 0;	
} 

ITEM integer_init_copy(ITEM hInt)
{
	int* pInt;
	int* pArg = (int*)hInt;
	pInt = (int*)malloc(sizeof(int));
	if (pInt != NULL)
	{
		*pInt = *pArg;
	}
	return pInt;
}

void integer_destroy(ITEM* phInt)
{
	int* pInt = (int*)*phInt;
	free(pInt);
	*phInt = NULL;
}

void display_game_state(int number_of_guesses, MY_STRING guessed_letters, MY_STRING guessed_word, int words_remaining, int remaining_toggle)
{
	int i;
	printf("Number of Guesses: %d\n", number_of_guesses);
	printf("Guessed Letters: ");
	for(i = 0; i < my_string_get_size(guessed_letters); i++)
	{
		printf("%c ", *my_string_at(guessed_letters, i));
	}
	printf("\n");

	printf("Guessed Word: %s\n", my_string_c_str(guessed_word));

	if(remaining_toggle == 1)
	{
		printf("Remaining Words: %d\n", words_remaining);
	}
}

Boolean guessed_already(MY_STRING guessed_letters, char guess)
{
	int i;
	for(i = 0; i < my_string_get_size(guessed_letters); i++)
	{
		if(*my_string_at(guessed_letters, i) == guess)
		{
			printf("You guessed that already.\n");
			return TRUE;
		}
	}

	return FALSE;
}

Status process_guess(TREE word_tree, MY_STRING guessed_word, MY_STRING temp_string, MY_STRING largest, GENERIC_VECTOR word_list, char guess)
{
	int i;
	int size_of_largest_list = 0;

	for(i = 0; i < generic_vector_get_size(word_list); i++)
	{
		if(get_word_key_value(guessed_word, temp_string, *generic_vector_at(word_list, i), guess) == FAILURE)
			{	
			return FAILURE;
			}		
		if(tree_insert(word_tree, temp_string, *generic_vector_at(word_list, i)) == FAILURE)
			{
			return FAILURE;
			}
	}

	for(i = 0; i < generic_vector_get_size(word_list); i++)
        {
                if(get_word_key_value(guessed_word, temp_string, *generic_vector_at(word_list, i), guess) == FAILURE)
                {
                        return FAILURE;
                }


		if(generic_vector_get_size(tree_look_up(word_tree, temp_string)) > size_of_largest_list)
		{
			size_of_largest_list = generic_vector_get_size(tree_look_up(word_tree, temp_string));
			
			if(my_string_assignment(largest, temp_string) == FAILURE)
        		{
                		return FAILURE;
        		}
		}
	}

	if(my_string_assignment(guessed_word, largest) == FAILURE)
	{
		return FAILURE;
	}

	if(my_string_assignment(temp_string, guessed_word) == FAILURE)
        {
                return FAILURE;
        }

	if(generic_vector_assignment(word_list, tree_look_up(word_tree, guessed_word)) == FAILURE)
        {
                return FAILURE;
        }

	return SUCCESS;
	
}

void clear_keyboard_buffer(void)
{
	char c;
	int noc;
	noc = scanf("%c", &c);
	while (noc == 1 && c != '\n')
	{
		noc = scanf("%c", &c);
	}
}
