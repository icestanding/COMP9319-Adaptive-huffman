/* Adaptive Huffman coder written by z3492794 Chenyu Li */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "head.h"
#include "tree.h"
#include <math.h>

int main(int argc, char *argv[]) {

    char c;
    char mode[] = "-s";

    STACK s;
    STACK *ps;
    ps = &s;
    CreateStack(ps);
    TREE t = CreateTree();
    NODE *n = &t.root;
    int count = 0; //count the number of letter maximum is 8
    char binary[8] = {'0','0','0','0','0','0','0','0'};
    int flag = 0;
    int i = 0;
    int j = 0;

    /*
    * normal mode without '-s'
    */
    if (argc == 1)
    {
        while ((c = getchar()) != EOF)
        {
            if (c == '\n') {
                NODE nyt = CreateNode(256, 0, '\0');
                t.root = nyt;
                strcpy(t.letter, "");
                t.root.left = NULL;
                t.root.right = NULL;
                t.root.parent = NULL;
                t.num = 0;
                printf("\n");
                continue;
            }
            if (n->left != NULL && n->right != NULL) {
                if (c == '0') {
                    n = n->left;
                }
                else {
                    n = n->right;
                }
            }

            if (n->left == NULL && n->right == NULL)
            {
                if(n->value==0 && n->letter == '\0')
                {
                    //first time
                    if(t.root.value == 0) {
                        binary[count] = c;
                        count += 1;
                        if(count == 8)
                        {
                            int sum = 0;
                            for (i = 7; i >=0 ; i--) {
                                if (binary[i] == '0') {
                                    continue;
                                }
                                else {
                                    sum += pow(2,(7-i));
                                }
                            }

                            char a = sum;
                            printf("%c",a);
                            Build(&t,a);
                            n = &t.root;
                            count = 0;
                            for (j = 0; j <=7 ; ++j) {
                                binary[j] = '0';
                            }
                        }
                    }
                    else {
                        if(flag == 0){
                            flag = 1;
                            continue;
                        }
                        else
                        {
                            binary[count] = c;
                            count += 1;
                            if(count == 8)
                            {
                                int sum = 0;
                                for (i = 7; i >=0 ; i--) {
                                    if (binary[i] == '0') {
                                        continue;
                                    }
                                    else {
                                        sum += pow(2,(7-i));
                                    }
                                }

                                char a = sum;
                                printf("%c",a);
                                Build(&t,a);
                                n = &t.root;
                                count = 0;
                                flag = 0;
                                for (j = 0; j <=7 ; ++j) {
                                    binary[j] = '0';
                                }
                            }

                        }
                    }
                }
                else
                {
                    printf("%c",n->letter);
                    Build(&t,n->letter);
                    n = &t.root;
                }
            }

        }
    }
    if (argc == 2 && strcpy(argv[1],mode))
    {
        while ((c = getchar()) != EOF)
        {
            if (c == ' '){
                continue;
            }
            if (c == '\n') {
                NODE nyt = CreateNode(256, 0, '\0');
                t.root = nyt;
                strcpy(t.letter, "");
                t.root.left = NULL;
                t.root.right = NULL;
                t.root.parent = NULL;
                t.num = 0;
                printf("\n");
                continue;
            }
            if (n->left != NULL && n->right != NULL) {
                if (c == '0') {
                    n = n->left;
                }
                else {
                    n = n->right;
                }
            }

            if (n->left == NULL && n->right == NULL)
            {
                if(n->value==0 && n->letter == '\0')
                {
                    //first time
                    if(t.root.value == 0) {
                        binary[count] = c;
                        count += 1;
                        if(count == 8)
                        {
                            int sum = 0;
                            for (i = 7; i >=0 ; i--) {
                                if (binary[i] == '0') {
                                    continue;
                                }
                                else {
                                    sum += pow(2,(7-i));
                                }
                            }

                            char a = sum;
                            printf("%c",a);
                            Build(&t,a);
                            n = &t.root;
                            count = 0;
                            for (j = 0; j <=7 ; ++j) {
                                binary[j] = '0';
                            }
                        }
                    }
                    else {
                        if(flag == 0){
                            flag = 1;
                            continue;
                        }
                        else
                        {
                            binary[count] = c;
                            count += 1;
                            if(count == 8)
                            {
                                int sum = 0;
                                for (i = 7; i >=0 ; i--) {
                                    if (binary[i] == '0') {
                                        continue;
                                    }
                                    else {
                                        sum += pow(2,(7-i));
                                    }
                                }

                                char a = sum;
                                printf("%c",a);
                                Build(&t,a);
                                n = &t.root;
                                count = 0;
                                flag = 0;
                                for (j = 0; j <=7 ; ++j) {
                                    binary[j] = '0';
                                }
                            }

                        }
                    }
                }
                else
                {
                    printf("%c",n->letter);
                    Build(&t,n->letter);
                    n = &t.root;
                }
            }

        }

    }
    return 0;
}