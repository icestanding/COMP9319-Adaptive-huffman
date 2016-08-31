/* Adaptive Huffman coder written by z3492794 Chenyu Li */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "head.h"
#include "tree.h"

int main(int argc, char *argv[]) {

    char c;
    char mode[] = "-s";

    STACK s;
    STACK *ps;
    ps = &s;
    CreateStack(ps);
    TREE t = CreateTree();


    /*
    * normal mode without '-s'
    */
    if (argc == 1)
    {
        while ((c = getchar()) != EOF)
        {
            if (c != '\n')
            {
                Transfer(&t, ps, c);
                ps->top = -1;
            }
            else
            {

                //refresh the tree
                NODE nyt = CreateNode(256, 0, '\0');
                t.root = nyt;
                strcpy(t.letter, "");
                t.root.left = NULL;
                t.root.right = NULL;
                t.root.parent = NULL;
                t.num = 0;
                printf("\n");
            }
        }
    }

    /* if "-s" is given */
    if (argc == 2)
    {
        int flag = 0;
        if (strcpy(argv[1],mode))
        {
            c = getchar();
            while ((c != EOF))
            {
                if (c != '\n')
                {

                    Transfer(&t, ps, c);
                    ps->top = -1;
                }
                else
                {
                    //refresh the tree
                    NODE nyt = CreateNode(256, 0, '\0');
                    t.root = nyt;
                    strcpy(t.letter, "");
                    t.root.left = NULL;
                    t.root.right = NULL;
                    t.root.parent = NULL;
                    t.num = 0;
                    printf("\n");
                    flag = 1;
                }
                c = getchar();
                if (c != EOF && c != '\n' && flag == 0)
                {
                    printf(" ");
                }
                if (flag == 1) {
                    flag = 0;
                }
            }
        }
    }
    return 0;
}