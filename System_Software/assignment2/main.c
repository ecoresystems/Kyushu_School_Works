#include <stdio.h>
typedef struct{
    int previous;
    int left_child;
    int right_sibling;
    int LWo;
    int LRa;
    int RWo;
    int RRa;
}node;

int main() {
    int counter = 0;
    node tree[200];
    tree[0].previous = -1;
    tree[0].right_sibling = -1;
    tree[0].LWo = 0;
    tree[0].LRa = 0;
    tree[0].RWo = 3;
    tree[0].RRa = 3;
    while (1){
        counter++;
        tree[counter].previous = counter - 1;

        if (tree[tree[counter].previous].RWo >= 2){
            tree[counter].LWo +=2;
            if ((tree[tree[counter].previous].RWo>=1) && (tree[tree[counter].previous].RRa >= 1))
                tree[counter].right_sibling = counter +1;
            tree[tree[counter].previous].RWo -= 2;
            counter ++;
        }

        if ((tree[tree[counter].previous].RWo>=1) && (tree[tree[counter].previous].RRa >= 1))
            tree[counter].right_sibling = counter +1;
        tree[counter].
        break;
    }

    printf("Hello, World!\n");
    return 0;
}