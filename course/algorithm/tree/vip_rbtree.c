


#define RED			1
#define BLACK		2

typedef int KEY_TYPE;

#if 1

typedef struct _rbtree_node {

	unsigned char color;

	struct _rbtree_node *right;
	struct _rbtree_node *left;
	struct _rbtree_node *parent;

	KEY_TYPE key;
	void *value;
	
} rbtree_node;

typedef struct _rbtree {

	rbtree_node *root;
	rbtree_node *nil;
	
} rbtree;

#else

#define RBTREE_ENTRY(name, type) 	\
	struct name {					\
		unsigned char color;		\
		struct type *right;			\
		struct type *left;			\
		struct type *parent;		\
	}

#endif


void rbtree_left_rotate(rbtree *T, rbtree_node *x) {

	rbtree_node *y = x->right;

	x->right = y->left;  //1 1
	if (y->left != T->nil) {
		y->left->parent = x; //1 2
	}

	y->parent = x->parent;  //1 3
	if (x->parent == T->nil) { //1 4
		T->root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->left = x; //1 5
	x->parent = y; //1 6
 
}

// left --> right
// right --> left
// x --> y
// y --> x

void rbtree_right_rotate(rbtree *T, rbtree_node *y) {

	rbtree_node *x = y->left;

	y->left = x->right;  //1 1
	if (x->right != T->nil) {
		x->right->parent = y; //1 2
	}

	x->parent = y->parent;  //1 3
	if (y->parent == T->nil) { //1 4
		T->root = x;
	} else if (y == y->parent->right) {
		y->parent->right = x;
	} else {
		y->parent->left = x;
	}

	x->right = y; //1 5
	y->parent = x; //1 6
 
}

/// 
int rbtree_insert(rbtree *T, rbtree_node *z) {

	rbtree_node *y = T->nil;
	rbtree_node *x = T->root;

	while (x != T->nil) {

		y = x;
		if (z->key < x->key) {
			x = x->left;
		} else if (z->key > x->key) {
			x = x->right;
		} else { //1 Exist
			return -1;
		}
	}

	z->parent = y;
	if (y == T->nil) {
		T->root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}

	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;

	//

}




