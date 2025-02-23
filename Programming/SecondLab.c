#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 

struct node {
    int data;
    struct node *next;
    struct node *secondExit;
};
typedef struct node strnode;

void *addNode(int dat, strnode **head) {
    strnode *new_node = (strnode*)(malloc(sizeof(strnode)));
    new_node->data = dat;
    new_node->next = NULL;
    new_node->secondExit = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        struct node *last = *head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
}

int max(int n, int k) {
    return (n > k) ? n : k;
}

int min(int n, int k) {
    return (n < k) ? n : k;
}

void printer(struct node *head) {
    strnode *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void generateDotFile(strnode *head, strnode *head2, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Ошибка открытия файла для записи!\n");
        return;
    }

    fprintf(fp, "digraph LinkedList {\n");
    fprintf(fp, "node [shape=circle];\n");
    fprintf(fp, "rankdir=LR;\n");

    strnode *current = head;
    strnode *current2 = head2;
    int node_id = 1;
    int *nodeslist1 = malloc(sizeof(int) * 100); 
    int *nodeslist2 = malloc(sizeof(int) * 100);
    int cnt1 = 0, cnt2 = 0;

    fprintf(fp, "node0 [label=\"S\"]\nnode0 -> node1;\n");

    while (current != NULL) {
        fprintf(fp, "node%d [label=\"%d\"]\n", node_id, current->data);
        if (current->next != NULL) {
            fprintf(fp, "node%d -> node%d;\n", node_id, node_id + 1);
        }
        nodeslist1[cnt1++] = node_id;
        current = current->next;
        node_id++;
    }

    while (current2 != NULL) {
        fprintf(fp, "node%d [label=\"%d\"]\n", node_id, current2->data);
        if (current2->next != NULL) {
            fprintf(fp, "node%d -> node%d;\n", node_id, node_id + 1);
        }
        nodeslist2[cnt2++] = node_id;
        current2 = current2->next;
        node_id++;
    }

    for (int i = 0; i < min(cnt1, cnt2); i++) {
        fprintf(fp, "node%d -> node%d;\n", nodeslist1[i], nodeslist2[i]);
    }

    fprintf(fp, "}\n");

    fclose(fp);
    printf("DOT-файл '%s' успешно создан.\n", filename);

    free(nodeslist1);
    free(nodeslist2);
}

void navigateList(strnode *S) {
    strnode *current = S->next;
    char input;

    while (1) {
        printf("Текущее значение: %d\n", current->data);
        if (current->next != NULL) {
            printf("1 выход (D): %d\n", current->next->data);
        } else {
            printf("1 выход (D): NULL\n");
        }
        if (current->secondExit != NULL) {
            printf("2 выход (W): %d\n", current->secondExit->data);
        } else {
            printf("2 выход (W): NULL\n");
        }
        printf("Введите команду (W/A/S/D или 2/4/6/8 для навигации, Q для выхода): ");
        scanf(" %c", &input);

        switch (input) {
            case 'W':
            case '6':
                if (current->next != NULL) {
                    current = current->next;
                } else {
                    printf("Достигнут конец списка. Вернуться в начало? (Y/N): ");
                    scanf(" %c", &input);
                    if (input == 'Y' || input == 'y') {
                        current = S->next;
                    }
                }
                break;

            case 'A':
            case '4':
                printf("Навигация влево не поддерживается в односвязном списке.\n");
                break;

            case 'D':
            case '8':
                if (current->secondExit != NULL) {
                    current = current->secondExit;
                } else {
                    printf("Нет второго выхода (secondExit).\n");
                }
                break;

            case 'S':
            case '2':
                printf("Навигация вниз не поддерживается.\n");
                break;

            case 'Q':
            case 'q':
                printf("Выход из навигации.\n");
                return;

            default:
                printf("Неизвестная команда. Используйте W/A/S/D или 2/4/6/8.\n");
                break;
        }
    }
}

void freeList(strnode *head) {
    strnode *current;
    while (head != NULL) {
        current = head;
        head = head->next;
        free(current);
    }
}

void var4(strnode *head, strnode *head2, int N, int K) {
    strnode *current = head;
    strnode *current2 = head2;
    for (int i = 0; i < min(N, K); i++) {
        if (current != NULL && current2 != NULL) {
            current->secondExit = current2;
            current = current->next;
            current2 = current2->next;
        }
    }
}

int main() {
    strnode *S = (strnode*)malloc(sizeof(strnode));
    S->next = NULL;
    S->secondExit = NULL;

    strnode *head = NULL;
    strnode *head2 = NULL;

    int input;
    int input2;
    int K = 0, N = 0;

    printf("Введите числа для списков N и K (0 для завершения):\n");

    printf("список N: \n");
    scanf("%d", &input);
    while (input != 0) {
        N += 1;
        addNode(input, &head);
        scanf("%d", &input);
    }

    printf("список K: \n");
    scanf("%d", &input2);
    while (input2 != 0) {
        K += 1;
        addNode(input2, &head2);
        scanf("%d", &input2);
    }


    const char *dot_filename = "linked_list.dot";
    generateDotFile(head, head2, dot_filename);


    var4(head, head2, N, K);


    S->next = head;
    navigateList(S);


    freeList(head);
    freeList(head2);
    free(S);

    return 0;
}//dot -Tpng linked_list.dot -o linked_list.png для картинки