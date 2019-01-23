

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int KEY_TYPE;


#if 1

struct bstree_node {

	KEY_TYPE key;

	struct bstree_node *left;
	struct bstree_node *right;

};

struct bstree {
	struct bstree_node *root;
};

#else

#define BSTREE_ENTRY(name, type) 	\
	struct name {					\
		struct type *left;			\
		struct type *right;			\
	}

struct bstree_node {
	KEY_TYPE key;

	BSTREE_ENTRY(, bstree_node) bst;
}

#endif



struct bstree_node* bstree_create_node(KEY_TYPE key) {

	struct bstree_node *node = (struct bstree_node*)calloc(1, sizeof(struct bstree_node));
	if (node == NULL) assert(0);

	node->key = key;
	node->left = node->right = NULL;

	return node;

}

void bstree_destory_node(struct bstree_node *node) {

	if (node == NULL) return ;

	node->left = node->right = NULL;
	free(node);

}

// bstree_node *node

int bstree_insert(struct bstree *T, KEY_TYPE key) {

	assert(T != NULL);

	if (T->root == NULL) {
		T->root = bstree_create_node(key);
		return 0;
	}

	struct bstree_node *node = T->root;
	struct bstree_node *tmp = T->root;

	while (node != NULL) {
		tmp = node;

		if (key < node->key) {
			node = node->left;
		} else {
			node = node->right;
		}
	}

	if (key < tmp->key) {
		tmp->left = bstree_create_node(key);
	} else {
		tmp->right = bstree_create_node(key);
	}

	return 0;
	
}


int bstree_traversal(struct bstree_node *node) {

	if (node == NULL) return 0;
	
	bstree_traversal(node->left);
	printf("%4d", node->key);
	bstree_traversal(node->right);
}

#define ARRAY_LENGTH		10

int main() {

	KEY_TYPE key_array[ARRAY_LENGTH] = {23, 45, 56, 32, 41, 90, 21, 43, 87, 76};

	struct bstree T = {0};
	int i = 0;

	for (i = 0;i < ARRAY_LENGTH;i ++) {
		bstree_insert(&T, key_array[i]);
	}

	bstree_traversal(T.root);

	printf("\n");
	
}



