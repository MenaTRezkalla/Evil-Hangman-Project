#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H
#include "my_string.h"
#include "generic_vector.h"
#include "status.h"

typedef void* TREE;

TREE tree_init_default(void);

Status tree_insert(TREE hTree, MY_STRING key, MY_STRING word);

int tree_depth(TREE hTree);

int tree_node_count(TREE hTree);

void print_pre_order_traversal(TREE hTree);

void print_in_order_traversal(TREE hTree);

void tree_destroy(TREE* phTree);

GENERIC_VECTOR tree_look_up(TREE hTree, MY_STRING key);

Status get_word_key_value(MY_STRING hCurrent_word_family, MY_STRING hNew_key, MY_STRING hWord, char guess);

#endif
