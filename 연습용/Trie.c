#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////

#define ASCII_SIZE 128

typedef struct _trienode{
	struct _trienode *childs[ASCII_SIZE];
    int isEOW;
} TrieNode;

///////////////////////// function prototypes ////////////////////////////////////

TrieNode* createNode();
void insertStr(TrieNode *root, char *str);
int search(TrieNode *root, char *str);
int searchStartsWith(TrieNode *root, char *prefix);
int removeStr(TrieNode *root, char *str);
int removeStrRecursive(TrieNode *node, char *str, int idx);
void removeAllStr(TrieNode **root);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
    int c = 1;
    char s[256];
    TrieNode *root = createNode();
    if (root == NULL) {
        printf("Failed to create root node.\n");
        return 1;
    }

    printf("1: Insert string in a Trie.\n");
    printf("2: Search for a string in a Trie.\n");
    printf("3: Search for a string with a given prefix in a Trie.\n");
    printf("4: Delete a string in a Trie.\n");
    printf("0: Quit;\n");

    while(c != 0)
    {
        printf("Please input your choice(1/2/3/4/0): ");
        scanf("%d", &c);

        switch(c)
        {
            case 1:
                printf("Input an string that you want to add to the Trie: ");
                scanf("%s", s);
                insertStr(root, s);
                break;
            case 2:
                printf("Input an string that you want to search in the Trie: ");
                scanf("%s", s);
                if (search(root, s))
                    printf("'%s' is found in the Trie.\n", s);
                else
                    printf("'%s' is not found in the Trie.\n", s);
                break;
            case 3:
                printf("Input an prefix that you want to search in the Trie: ");
                scanf("%s", s);
                if (searchStartsWith(root, s))
                    printf("A word with the prefix '%s' exists in the Trie.\n", s);
                else
                    printf("No word with the prefix '%s' exists in the Trie.\n", s);
                break;
            case 4:
                printf("Input an string that you want to remove in the Trie: ");
                scanf("%s", s);
                if (removeStr(root, s))
                    printf("'%s' has been removed from the Trie.\n", s);
                else 
                    printf("'%s' could not be removed (not found).\n", s);
                break;
            case 0:
                removeAllStr(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

TrieNode* createNode()
{
    TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
    if (node == NULL) return NULL;
    for (int i=0; i<ASCII_SIZE; i++)
        node->childs[i] = NULL;
    node->isEOW = 0;
    return node;
}

void insertStr(TrieNode *root, char *str)
{
    if (root == NULL || str == NULL)
        return;
    TrieNode *cur = root;
    for (int i=0; str[i]!='\0'; i++)
    {
        if (cur->childs[str[i]] == NULL)
            cur->childs[str[i]] = createNode();
        cur = cur->childs[str[i]];
    }
    cur->isEOW = 1;
}

int search(TrieNode *root, char *str)
{
    if (root == NULL || str == NULL)
        return 0;
    TrieNode *cur = root;
    for (int i=0; str[i]!='\0'; i++)
    {
        if (cur->childs[str[i]] == NULL)
            return 0;
        cur = cur->childs[str[i]];
    }
    return cur->isEOW;
}

int searchStartsWith(TrieNode *root, char *str)
{
    if (root == NULL || str == NULL)
        return 0;
    TrieNode *cur = root;
    for (int i=0; str[i]!='\0'; i++)
    {
        if (cur->childs[str[i]] == NULL)
            return 0;
        cur = cur->childs[str[i]];
    }
    return 1;
}

int hasChild(TrieNode *node)
{
    if (node == NULL) return 0;
    for (int i=0; i<ASCII_SIZE; i++)
        if (node->childs[i] != NULL)
            return 1;
    return 0;
}

int removeStr(TrieNode *root, char *str)
{
    if (root == NULL || str == NULL)
        return 0;
    return removeStrRecursive(root, str, 0);
}

int removeStrRecursive(TrieNode *node, char *str, int idx)
{
    if (idx == strlen(str))
    {
        if (!node->isEOW)
            return 0;
        node->isEOW = 0;
        return 1;
    }

    char c = str[idx];
    TrieNode *child = node->childs[c];
    if (child == NULL)
        return 0; 

    int is_deleted = removeStrRecursive(child, str, idx+1);
    if (is_deleted && !child->isEOW && !hasChild(child))
    {
        node->childs[c] = NULL;
        free(child);
    }
    return is_deleted;
}

void removeAllStr(TrieNode **root)
{
    if (root == NULL) return;
    for (int i=0; i<ASCII_SIZE; i++)
        if ((*root)->childs[i] != NULL)
            removeAllStr(&((*root)->childs[i]));
    free(*root);
    *root = NULL;
}