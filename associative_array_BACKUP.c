#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "associative_array.h"

struct node;
typedef struct node Node;

struct node
{
	MY_STRING key;
	GENERIC_VECTOR word_family;
	Node* left;
	Node* right;
	int depth;
};

struct tree
{
	Node* root;
};
typedef struct tree Tree;

Node* tree_insert_helper(Node* root, MY_STRING key, MY_STRING word, Status* pStatus);

Boolean is_word_in_family(Node* root, MY_STRING word);

int tree_depth_helper(Node* root);

int tree_node_count_helper(Node* root);

void print_pre_order_traversal_helper(Node* root);

void print_in_order_traversal_helper(Node* root);

void tree_destroy_helper(Node* root);

GENERIC_VECTOR tree_look_up_helper(Node* root, MY_STRING key);

TREE tree_init_default(void)
{
	Tree* pTree = (Tree*)malloc(sizeof(Tree));
	if (pTree == NULL)
	{
		return NULL;
	}
	pTree->root = NULL;
	return pTree;
}

Status tree_insert(TREE hTree, MY_STRING key, MY_STRING word)
{	
	Tree* pTree = (Tree*)hTree;
	Status pStatus = FAILURE;
	pTree->root = tree_insert_helper(pTree->root, key, word, &pStatus);
	return pStatus;
}

Node* tree_insert_helper(Node* root, MY_STRING key, MY_STRING word, Status* pStatus)
{
	if (root == NULL)
	{
		root = (Node*)malloc(sizeof(Node));
		if (root == NULL)
		{
			*pStatus = FAILURE;
			return NULL;
		}
		
		root->key = my_string_init_copy(key);
		if(root->key == NULL)
		{
			free(root);
			*pStatus = FAILURE;
                        return NULL;
		}

		root->word_family = generic_vector_init_default(my_string_init_copy, my_string_destroy);
		if(root->word_family == NULL)
		{
			free(root->key);
			free(root);
			*pStatus = FAILURE;
			return NULL;
		}

		if(word != NULL)
		{
			if(is_word_in_family(root, word) == FALSE)
			{

			if(generic_vector_push_back(root->word_family, word) == FAILURE)
			{
				*pStatus = FAILURE;
			}

			}
		}

		root->left = NULL;
		root->right = NULL;
		root->depth = 0;
	}
	else
	{
		if (my_string_compare(key, root->key) < 0)
		{
			root->left = tree_insert_helper(root->left, key, word, pStatus);
		}
		else if (my_string_compare(key, root->key) > 0)
		{
			root->right = tree_insert_helper(root->right, key, word, pStatus);
		}
		else
		{
			if(word != NULL)
			{
				if(is_word_in_family(root, word) == FALSE)
				{
				
				if(generic_vector_push_back(root->word_family, word) == FAILURE)
				{
                        
					*pStatus = FAILURE;
				
				}

				}
			}
		}
	}
	*pStatus = SUCCESS;
	return root;
}

Boolean is_word_in_family(Node* root, MY_STRING word)
{
	int i;
	for(i = 0; i < generic_vector_get_size(root->word_family); i++)
	{
		if(my_string_compare(*generic_vector_at(root->word_family, i), word) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

int tree_depth(TREE hTree)
{
	Tree* pTree = (Tree*)hTree;
	return tree_depth_helper(pTree->root);
}

int tree_depth_helper(Node* root)
{
	int depth_of_left_subtree = 0;
	int depth_of_right_subtree = 0;
	if (root == NULL)
	{
		return 0;
	}

	depth_of_left_subtree = tree_depth_helper(root->left);
	depth_of_right_subtree = tree_depth_helper(root->right);

	return 1 +
		((depth_of_left_subtree > depth_of_right_subtree) ?
			depth_of_left_subtree : depth_of_right_subtree);
}

int tree_node_count(TREE hTree)
{
	Tree* pTree = (Tree*)hTree;
	return tree_node_count_helper(pTree->root);
}

int tree_node_count_helper(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}

	return 1 + tree_node_count_helper(root->left) + tree_node_count_helper(root->right);
}

void print_pre_order_traversal(TREE hTree)
{
	Tree* pTree = (Tree*)hTree;
	print_pre_order_traversal_helper(pTree->root);
}

void print_pre_order_traversal_helper(Node* root)
{
	//SLR

	if (root != NULL)
	{
		printf("Key: %s.   Word Family: ", my_string_c_str(root->key));
                for(int i = 0; i < generic_vector_get_size(root->word_family); i++)
                {
                        printf("%s ", my_string_c_str(*generic_vector_at(root->word_family, i)));
                }
                printf(" Size of List: %d\n", generic_vector_get_size(root->word_family));
		print_pre_order_traversal_helper(root->left);
		print_pre_order_traversal_helper (root->right);
	}
}

void print_in_order_traversal(TREE hTree)
{
	Tree* pTree = (Tree*)hTree;
	print_in_order_traversal_helper(pTree->root);
}

void print_in_order_traversal_helper(Node* root)
{
	//LSR

	if (root != NULL)
	{
		print_in_order_traversal_helper(root->left);
		printf("Key: %s   Word Family: ", my_string_c_str(root->key));
		for(int i = 0; i < generic_vector_get_size(root->word_family); i++)
		{
			printf("%s ", my_string_c_str(*generic_vector_at(root->word_family, i)));
		}
		printf("\n");
		print_in_order_traversal_helper(root->right);
	}
}

void tree_destroy(TREE* phTree)
{
	Tree* pTree = (Tree*)*phTree;
	tree_destroy_helper(pTree->root);
	free(pTree);
	*phTree = NULL;
}

void tree_destroy_helper(Node* root)
{
	if (root != NULL)
	{
		tree_destroy_helper(root->left);
		tree_destroy_helper(root->right);

		my_string_destroy(&(root->key));
		generic_vector_destroy(&(root->word_family));

		free(root);
	}
}

GENERIC_VECTOR tree_look_up(TREE hTree, MY_STRING key)
{
	 Tree* pTree = (Tree*)hTree;
	 return tree_look_up_helper(pTree->root, key);
}

GENERIC_VECTOR tree_look_up_helper(Node* root, MY_STRING key)
{
/*
	if(my_string_compare(root->key, key) == 0)
	{
		return root->word_family;
	}
	else
	{
		if(root->left != NULL)
		{
			return tree_look_up_helper(root->left, key);
		}
		
		if (root->right != NULL)
		{
			return tree_look_up_helper(root->right, key);
		}

		return NULL;
	}
	*/

	GENERIC_VECTOR left = NULL;
	GENERIC_VECTOR right = NULL;

	if (root != NULL)
        {
		if(my_string_compare(root->key, key) == 0)
        	{
                	return root->word_family;
        	}
		
		left = tree_look_up_helper(root->left, key);
                right = tree_look_up_helper(root->right, key);
        }

	if(left != NULL)
	{
		return left;
	}

	if(right != NULL)
	{
		return right;
	}

	return NULL;
}

Status get_word_key_value(MY_STRING hCurrent_word_family, MY_STRING hNew_key, MY_STRING hWord, char guess)
{
	int i;

	if(my_string_assignment(hNew_key, hCurrent_word_family) == FAILURE)
	{
		return FAILURE;
	}

	for(i = 0; i < my_string_get_size(hNew_key); i++)
	{
		if(tolower(*my_string_at(hWord, i)) == tolower(guess))
		{
			*my_string_at(hNew_key, i) = tolower(guess);
		}
	}

	return SUCCESS;
}
