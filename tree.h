// node size
#define MAXSIZE 1000
#include <ctype.h>
#include <stdlib.h>

/************************************************/
/*        Type Definition part                 */
/**********************************************/

typedef struct stack
{
    char stk[MAXSIZE];
    int top;
} STACK;
//STACK s;    // Stack s: store the path

typedef struct node {
    int id;
    int value;
    char letter;
    struct node *left, *right, *parent;
} NODE;

// tree
typedef struct tree {
    char letter[256];
    int num; //number of node
    NODE root;
} TREE;


/************************************************/
/*        Function Declaration part            */
/**********************************************/

void show () ;
char pop(STACK *s);
void push (STACK *s, char num);
TREE CreateTree(void);
NODE CreateNode(int i, int v, char c);
NODE *Create(int i, int v, char c);
void Update(NODE *node);
int Search(NODE *t, STACK *s, char c);
int max(int a, int b);
int maxHeight(NODE *node);
void visit(int data);
void Updateid(NODE *root);
NODE * SearchNode(NODE * n, char c);
void display (STACK *s);
void  _Swapleaf(NODE *n,NODE *ar[], int value,int * p, int mode);
NODE * Swapleaf(TREE *r, NODE *n);
NODE * findPosition(NODE * n, char c);
void SHOW(NODE *p, int level);
void printLevelOrder(struct node* root);
void printGivenLevel(NODE * root, int level, int *max);
void count(NODE * root, int level, int * max);
void Build(TREE * t, char c);

/************************************************/
/*             Function part                   */
/**********************************************/
TREE CreateTree(void) {

    TREE tree;
    NODE nyt = CreateNode(256, 0, '\0');
    tree.root = nyt;
    strcpy(tree.letter, "");
    tree.root.left = NULL;
    tree.root.right = NULL;
    tree.root.parent = NULL;
    tree.num = 0;

    return tree;
}

// create new node
NODE CreateNode(int i, int v, char c) {

    NODE node;
    node.id = i;
    node.value = v;
    node.letter = c;
    return node;
}

NODE *Create(int i, int v, char c)
{
    NODE *p = NULL;
    p = (NODE *)malloc(sizeof(NODE));
    p->letter = c;
    p->id = i;
    p->value = v;
    p->left = NULL;
    p->right = NULL;
    p->parent = NULL;
    return p;
}

/*********************************************************/
/*                key function                          */
/*******************************************************/

void Transfer(TREE *t, STACK *s, char c) {
    int flag = 0;
    NODE *leaf_to_increment =  NULL;
    NODE *p;
    char *asc;
    int a = c;
    int i = 0;
    int j = 0;
    for (i = 0; i < t->num; ++i) {
        if (c == t->letter[i]) {
            flag = 1;
        }
    }
    if(flag == 1) {
        Search(&t->root, s, c);
        for (i = 0; i <= s->top; i++) {
            printf("%c", s->stk[i]);
        }
        p = findPosition(&t->root, c);
    }
    else {
        if(t->root.value == 0){
            asc = DecimalToBinary(a);
            for (i = 7; i >= 0; i--)
            {
                printf("%c",*(asc + i));
            }
            for (i = 7; i >= 0; i--)
            {
                *(asc + i) = '0';
            }
        }
        else {
            Search(&t->root, s, '\0');
            for (i = 0; i <= s->top; i++) {
                printf("%c", s->stk[i]);
            }
            asc = DecimalToBinary(a);
            for (i = 7; i >= 0; i--)
            {
                printf("%c",*(asc + i));
            }
            for (i = 7; i >= 0; i--)
            {
                *(asc + i) = '0';
            }
        }

        p = findPosition(&t->root, '\0');
    }
    //new node
    if (p->value ==0 && p->letter == '\0' && p->left == NULL) {

        int num = p->id;
        p->left = Create(num - 2, 0, '\0');
        p->right = Create(num - 1, 0, c);
        p->left->parent = p;
        p->right->parent = p;
        leaf_to_increment = p->right;
        char str1[2] = {c , '\0'}; //convert to string
        // create new node
        strcat(t->letter, str1); //copy they letter
        t->num++;
    }
    else {
        NODE *ptn[MAXSIZE];
        for (i = 0; i < MAXSIZE; i++) {
            ptn[i] = NULL;
        }

        int max = 0;
        int size = 0;
        int *s = &size;

        if (p->left == NULL && p->right == NULL) {
            _Swapleaf(&(t->root), ptn, p->value, s, 0);
        }
        else {
            _Swapleaf(&(t->root), ptn, p->value, s, 1);
        }
        //find largest number
        for (j = 0; j < *s; ++j) {
            if (ptn[j]->id > max) {
                max = ptn[j]->id;
            }
        }
        //swap
        for (j = 0; j < *s; ++j) {
            if (ptn[j]->id == max) {
                if (p->parent != ptn[j] && p->left != ptn[j] && p->right != ptn[j]) {
                    NODE *p1;
                    NODE *p2;
                    p1 = ptn[j]->parent;
                    p2 = p->parent;
                    if (p1->left == ptn[j]) {
                        p1->left = p;
                        p->parent = p1;
                    }
                    else {
                        p1->right = p;
                        p->parent = p1;
                    }

                    if (p2->left == p) {
                        p2->left = ptn[j];
                        ptn[j]->parent = p2;
                    }
                    else {
                        p2->right = ptn[j];
                        ptn[j]->parent = p2;
                    }

                }
            }
        }
        printLevelOrder(&t->root);
        //if q is the sibling of the 0-node then
        if (p->parent->left->value == 0 && p->parent->left->left == NULL && p->parent->left->letter == '\0') {
            leaf_to_increment = p;
            p = p->parent;
        }

    }
    while (p->id != 256 ) {
        p = Swapleaf(t,p);
        printLevelOrder(&t->root);
    }
    p->value = p->value + 1;
    if(leaf_to_increment != 0) {
        Swapleaf(t, leaf_to_increment);
    }
}





//decoder
void Build(TREE * t, char c){
    int flag = 0;
    NODE *leaf_to_increment =  NULL;
    NODE *p;
    int i = 0;
    int j = 0;

    for (i = 0; i < t->num; ++i) {
        if (c == t->letter[i]) {
            flag = 1;
        }
    }
    if(flag == 1) {

        p = findPosition(&t->root, c);
    }
    else {

        p = findPosition(&t->root, '\0');
    }
    //new node
    if (p->value ==0 && p->letter == '\0' && p->left == NULL) {

        int num = p->id;
        p->left = Create(num - 2, 0, '\0');
        p->right = Create(num - 1, 0, c);
        p->left->parent = p;
        p->right->parent = p;
        leaf_to_increment = p->right;
        char str1[2] = {c , '\0'}; //convert to string
        // create new node
        strcat(t->letter, str1); //copy they letter
        t->num++;
    }
    else {
        NODE *ptn[MAXSIZE];
        for (i = 0; i < MAXSIZE; i++) {
            ptn[i] = NULL;
        }

        int max = 0;
        int size = 0;
        int *s = &size;

        if (p->left == NULL && p->right == NULL) {
            _Swapleaf(&(t->root), ptn, p->value, s, 0);
        }
        else {
            _Swapleaf(&(t->root), ptn, p->value, s, 1);
        }
        //find largest number
        for (j = 0; j < *s; ++j) {
            if (ptn[j]->id > max) {
                max = ptn[j]->id;
            }
        }
        //swap
        for (j = 0; j < *s; ++j) {
            if (ptn[j]->id == max) {
                if (p->parent != ptn[j] && p->left != ptn[j] && p->right != ptn[j]) {
                    NODE *p1;
                    NODE *p2;
                    p1 = ptn[j]->parent;
                    p2 = p->parent;
                    if (p1->left == ptn[j]) {
                        p1->left = p;
                        p->parent = p1;
                    }
                    else {
                        p1->right = p;
                        p->parent = p1;
                    }

                    if (p2->left == p) {
                        p2->left = ptn[j];
                        ptn[j]->parent = p2;
                    }
                    else {
                        p2->right = ptn[j];
                        ptn[j]->parent = p2;
                    }

                }
            }
        }
        printLevelOrder(&t->root);
        //if q is the sibling of the 0-node then
        if (p->parent->left->value == 0 && p->parent->left->left == NULL && p->parent->left->letter == '\0') {
            leaf_to_increment = p;
            p = p->parent;
        }

    }
    while (p->id != 256 ) {
        p = Swapleaf(t,p);
        printLevelOrder(&t->root);
    }
    p->value = p->value + 1;
    if(leaf_to_increment != 0) {
        Swapleaf(t, leaf_to_increment);
    }
}



NODE * findPosition(NODE * n, char c) {


    if (c == '\0' && n->value == 0 && n->letter == c) {
        return n;
    }
    else if (c != '\0' && n->letter == c) {
        return n;
    }
    else {
        if(n->left!=NULL)
        {
            NODE *r = findPosition(n->left, c);
            if (r != NULL){
                return r;
            }
        }
        if(n->right!=NULL)
        {
            NODE *r = findPosition(n->right, c);
            if (r != NULL){
                return r;
            }
        }
    }
    return NULL;


}


//including update, including internal node
NODE * Swapleaf(TREE *r, NODE *n) {
    int i = 0;
    // leaf node
    int k = 0;
    int j = 0;
    if(n->left == NULL && n->right == NULL) {
        NODE *ptn[MAXSIZE];
        for (i = 0; i < MAXSIZE; i++) {
            ptn[i] = NULL;
        }
        int size = 0;
        int *p = &size;
        //find internal node
        _Swapleaf(&(r->root), ptn, n->value, p, 1);
        //sort the internal node
        if(size != 0)
        {
            //sort the array
            if(size > 1) {
                for (i = 0; i < size; i++) {
                    for (j = 0; j < size - i - 1; j++)
                        if (ptn[j]->id > ptn[j + 1]->id) {
                            NODE *t = ptn[j];
                            ptn[j] = ptn[j + 1];
                            ptn[j + 1] = t;
                        }
                }
            }

            //slide
            NODE *pre = n->parent;
            int dir = 0; //0 mean left 1 mean right
            if(pre->left == n) {
                dir = 0;
            }
            else {
                dir = 1;
            }

            for (k = 0; k < size; k++) {
                int dir1 = 0;
                if (ptn[k]->parent->left ==ptn[k]) {
                    dir1 = 0;
                }
                else {
                    dir1 = 1;
                }
                if (dir == 0) {
                    pre->left = ptn[k];
                    NODE * t = ptn[k]->parent;
                    ptn[k]->parent = pre;
                    pre = t;
                }
                else {
                    pre->right = ptn[k];
                    NODE * t = ptn[k]->parent;
                    ptn[k]->parent = pre;
                    pre = t;
                }
                dir = dir1;

            }

            if (dir == 0) {
                pre->left = n;
                n->parent = pre;
            }
            else {
                pre->right = n;
                n->parent = pre;
            }
            n->value = n->value + 1;
            n = n->parent;
        }
        else
        {
            n->value = n->value + 1;
            n = n->parent;
        }

    }
        //
    else {
        NODE *np = n->parent;
        NODE *ptn[MAXSIZE];
        for (i = 0; i < MAXSIZE; i++) {
            ptn[i] = NULL;
        }
        int size = 0;
        int *p = &size;
        //find leaf node
        _Swapleaf(&(r->root), ptn, n->value + 1, p, 0);
        //sort the internal node
        if(size != 0)
        {
            //sort the array
            if (size > 1) {
                for (i = 0; i < size; i++) {
                    for (j = 0; j < size - i -1; j++)
                        if (ptn[j]->id > ptn[j + 1]->id) {
                            NODE *t = ptn[j];
                            ptn[j] = ptn[j + 1];
                            ptn[j + 1] = t;
                        }
                }
            }

            //slide
            NODE *pre = n->parent;
            int dir = 0; //0 mean left 1 mean right
            if(pre->left == n) {
                dir = 0;
            }
            else {
                dir = 1;
            }

            for (k = 0; k < size; k++) {
                int dir1 = 0;
                if (ptn[k]->parent->left ==ptn[k]) {
                    dir1 = 0;
                }
                else {
                    dir1 = 1;
                }
                if (dir == 0) {
                    pre->left = ptn[k];
                    NODE * t = ptn[k]->parent;
                    ptn[k]->parent = pre;
                    pre = t;
                }
                else {
                    pre->right = ptn[k];
                    NODE * t = ptn[k]->parent;
                    ptn[k]->parent = pre;
                    pre = t;
                }
                dir = dir1;

            }

            if (dir == 0) {
                pre->left = n;
                n->parent = pre;
            }
            else {
                pre->right = n;
                n->parent = pre;
            }
            n->value = n->value + 1;
            n = np;
        }
        else
        {
            n->value = n->value + 1;
            n = n->parent;
        }
    }

    return n;
}


// search node of same value
//mode 1:search internal , mode 0 search leaves
void  _Swapleaf(NODE *n,NODE *ar[], int value,int * p, int mode) {
    int i = 0;
    if (n->value == value && n->id != 256) {
        for (i = 0; i < MAXSIZE; ++i) {
            //searching leaves
            if (ar[i] == NULL  && n->left ==NULL && n->right ==NULL && mode == 0) {
                ar[i] = n;
                *p = *p + 1;
                break;
            }
            //searching internal
            if (ar[i] == NULL  && mode == 1 && n->left !=NULL && n->right !=NULL) {
                ar[i] = n;
                *p = *p + 1;
                break;
            }
        }
    }
    if (n) {
        if (n->left != NULL) {
            _Swapleaf(n->left, ar, value,p,mode);
        }
        if (n->right != NULL) {
            _Swapleaf(n->right, ar, value,p,mode);
        }
    }

}


int Search(NODE *t, STACK *s, char c) {

    if (t->letter == c && t->id != 256) {
        char str1[2] = {c , '\0'};
        char empty[2] = "";
        if(strcmp(str1,empty) == 0 && t->value == 0) {
            return 1;
        }
        else if(strcmp(str1,empty)!=0) {
            return 1;
        }
    }
    if (t) {
        if (t->left != NULL) {
            push(s, '0');
            if(Search(t->left, s, c)) {
                return 1;
            };
            pop(s);

        }
        if (t->right != NULL) {
            push(s, '1');
            if(Search(t->right, s, c)) {
                return 1;
            };
            pop(s);

        }
    }
    return 0;


}
//update value of node
void Update(NODE *node) {
    if (node)
    {
        // int value = node->value;
        if (node->left != NULL && node->right != NULL)
        {
            node->value = node->left->value + node->right->value;
        }
        Update(node->left);
        Update(node->right);
    }
}

/**********************************************************/
/*             Basic operation of Stack                  */
/********************************************************/


void CreateStack (STACK *s) {
    s->top = -1;
}

void push (STACK *s, char num) {

    if (s->top == (MAXSIZE - 1))
    {
        return;
    }
    else
    {
        s->top = s->top + 1;
        s->stk[s->top] = num;
    }
}

char pop(STACK *s) {
    if (s->top != -1) {
        char c = s->stk[s->top];
        s->top = s->top - 1;
        return c;
    }
    else {
        printf("out of stack");
        return '0';
    }
}

// void display (STACK *s) {
//     for (int i = s->top; i >= 0; i--) {
//         printf("%c",s->stk[i]);
//     }
//     s->top = -1;
// }

/*****************************************************************/
/*                        Preorder Search                       */
/***************************************************************/
void printLevelOrder(struct node* root);
void printGivenLevel(NODE * root, int level, int *max);

void printLevelOrder(NODE *root) {
    int h = maxHeight(root);
    int i;
    int max = 256;
    int min = 256;
    int * p = &max;
    for (i = 1; i <= h; i++) {
        int num = 0;
        int * pn = &num;
        if (i == 1)
        {
            root->id = max;
        }
        else {
            count(root, i, pn);
            max = min - num;
            min = max;
            printGivenLevel(root, i, p);
        }

    }
}

/* Print nodes at a given level */
void printGivenLevel(NODE * root, int level, int * max)
{
    if (root == NULL)
        return;
    if (level == 1)
    {
        root->id = *max;
        *max = *max +1 ;
    }
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1, max);
        printGivenLevel(root->right, level-1, max);
    }
}


void count(NODE * root, int level, int * max)
{
    if (root == NULL)
        return;
    if (level == 1)
    {
        *max = *max + 1;
    }
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1, max);
        printGivenLevel(root->right, level-1, max);
    }
}



int maxHeight(NODE *node) {

    if (!node) {
        return 0;
    }
    else {

        return max(maxHeight(node->left), maxHeight(node->right)) + 1;
    }

}

void visit(int data) {
    printf("%d ", data);
}


int max(int a, int b)
{
    if(a>b) return a;

    return b;

}

void SHOW(NODE *p, int level)
{
    if (!p) return;
    if (level == 0) {
        if (p->left != NULL) {
            p->left->id = p->id - 2;
        }
        if (p->right != NULL) {
            p->right->id = p->id - 1;
        }
    } else {
        SHOW(p->left, level-1);
        SHOW(p->right, level-1);
    }

}
