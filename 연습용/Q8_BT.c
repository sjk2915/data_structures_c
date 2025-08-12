//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;


///////////////////////// Function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int hasGreatGrandchild(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stack, BTNode *node);
BTNode* pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int hasGreatGrandchild(BTNode *node)
{
    if (node == NULL) return 0;
    BTNode *left_left_left = NULL, *left_left_right = NULL,
           *left_right_left = NULL, *left_right_right = NULL,
           *right_left_left = NULL, *right_left_right = NULL,
           *right_right_left = NULL, *right_right_right = NULL;

    BTNode *left = node->left;
    if (left != NULL)
    {
        BTNode *left_left = left->left;
        if (left_left != NULL)
        {
            left_left_left = left_left->left;
            left_left_right = left_left->right;

        }
        BTNode *left_right = left->right;
        if (left != NULL)
        {
            left_right_left = left_right->left;
            left_right_right = left_right->right;
        }
    }
    BTNode *right = node->right;
    if (right != NULL)
    {
        BTNode *right_left = left->left;
        if (right_left != NULL)
        {
            right_left_left = right_left->left;
            right_left_right = right_left->right;
        }
        BTNode *right_right = left->right;
        if (left != NULL)
        {
            right_right_left = right_right->left;
            right_right_right = right_right->right;
        }
    }
    if (left_left_left != NULL || left_left_right != NULL ||
        left_right_left != NULL || left_right_right != NULL ||
        right_left_left != NULL || right_left_right != NULL ||
        right_right_left != NULL || right_right_right != NULL)
        print("%d ",node->item);
        
    hasGreatGrandchild(node->left);
    hasGreatGrandchild(node->right);
}