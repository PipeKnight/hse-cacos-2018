#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *left;
    struct Node *right;
    int value;
};


void insert(struct Node *vert, int value) {
    if (vert->value < value) {
        if (vert->left == NULL) {
            vert->left = calloc(1, sizeof(vert));
            vert->left->value = value;
        } else {
            insert(vert->left, value);
        }
    }
    if (vert->value > value) {
        if (vert->right == NULL) {
            vert->right = calloc(1, sizeof(vert));
            vert->right->value = value;
        } else {
            insert(vert->right, value);
        }
    }
}

void print_and_free(struct Node *vert) {
    if (vert != NULL) {
        print_and_free(vert->left);
        printf("%i ", vert->value);
        print_and_free(vert->right);
        free(vert);
    }
}

int main() {
    struct Node* head = NULL;
    int cur_numb = 0;
    int is_first = 1;
    int empty = 1;
    while (scanf("%d", &cur_numb) != EOF) {
        empty = 0;
        if (cur_numb == 0) {
            if (is_first == 1) {
                is_first = 0;
            } else {
                printf(" ");
            }
            print_and_free(head);
            printf("%d", 0);
            head = NULL;
        } else {
            if (head == NULL) {
                head = calloc(1, sizeof(head));
                head->value = cur_numb;
            } else {
                insert(head, cur_numb);
            }
        }
    }
    if (head != NULL) {
        print_and_free(head);
        printf("%d", 0);
    }
    if (empty != 1) {
        printf("\n");
    }
}
