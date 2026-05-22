/* Question 2 - doubly linked list bus route */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define NAME_LEN 50

typedef struct Node {
    char name[NAME_LEN];
    int num;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Route;

void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

Node *createNode(const char *name, int num) {
    Node *p = (Node *)malloc(sizeof(Node));
    if (p == NULL)
        return NULL;
    strncpy(p->name, name, NAME_LEN - 1);
    p->name[NAME_LEN - 1] = '\0';
    p->num = num;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

int insertAtEnd(Route *route, const char *name, int num) {
    Node *p = createNode(name, num);
    if (p == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }
    if (route->head == NULL) {
        route->head = route->tail = p;
    } else {
        route->tail->next = p;
        p->prev = route->tail;
        route->tail = p;
    }
    return 1;
}

void freeRoute(Route *route) {
    Node *t = route->head;
    while (t != NULL) {
        Node *nxt = t->next;
        free(t);
        t = nxt;
    }
    route->head = NULL;
    route->tail = NULL;
}

void delay3Seconds(void) {
#ifdef _WIN32
    Sleep(3000);
#else
    sleep(3);
#endif
}

void traverseForward(Route *route) {
    Node *p = route->head;
    if (p == NULL) {
        printf("Route is empty.\n");
        return;
    }
    printf("\nForward (home -> campus):\n");
    while (p != NULL) {
        printf("Bus stop %d: %s\n", p->num, p->name);
        if (p == route->tail)
            break;
        delay3Seconds();
        p = p->next;
    }
    printf("Reached last stop.\n");
}

void traverseBackward(Route *route) {
    Node *p = route->tail;
    if (p == NULL) {
        printf("Route is empty.\n");
        return;
    }
    printf("\nBackward (campus -> home):\n");
    while (p != NULL) {
        printf("Bus stop %d: %s\n", p->num, p->name);
        if (p == route->head)
            break;
        delay3Seconds();
        p = p->prev;
    }
    printf("Reached first stop.\n");
}

void addStopAtEnd(Route *route) {
    char name[NAME_LEN];
    int num;

    clearInput();
    printf("New bus stop name: ");
    if (fgets(name, NAME_LEN, stdin) == NULL)
        return;
    name[strcspn(name, "\n")] = '\0';

    printf("New bus stop number: ");
    if (scanf("%d", &num) != 1) {
        clearInput();
        printf("Invalid number.\n");
        return;
    }
    clearInput();

    if (insertAtEnd(route, name, num))
        printf("Stop added at end of route.\n");
}

void readInitialRoute(Route *route) {
    int n, i;
    char name[NAME_LEN];
    int num;

    printf("How many bus stops? ");
    if (scanf("%d", &n) != 1 || n < 0) {
        clearInput();
        return;
    }
    clearInput();

    for (i = 0; i < n; i++) {
        printf("Stop %d name: ", i + 1);
        if (fgets(name, NAME_LEN, stdin) == NULL)
            break;
        name[strcspn(name, "\n")] = '\0';

        printf("Stop %d number: ", i + 1);
        if (scanf("%d", &num) != 1) {
            clearInput();
            i--;
            continue;
        }
        clearInput();
        insertAtEnd(route, name, num);
    }
}

void showMenu(void) {
    printf("\n--- Menu ---\n");
    printf("1. Move forward (home -> campus)\n");
    printf("2. Move backward (campus -> home)\n");
    printf("3. Add bus stop at end of route\n");
    printf("4. Exit\n");
    printf("Choice: ");
}

int main(void) {
    Route route = {NULL, NULL};
    int choice;

    printf("Bus Route Navigation\n");
    readInitialRoute(&route);

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            clearInput();
            printf("Invalid input.\n");
            continue;
        }
        clearInput();

        if (choice == 1)
            traverseForward(&route);
        else if (choice == 2)
            traverseBackward(&route);
        else if (choice == 3)
            addStopAtEnd(&route);
        else if (choice == 4)
            break;
        else
            printf("Invalid choice.\n");
    } while (1);

    freeRoute(&route);
    printf("Program ended. All memory freed.\n");
    return 0;
}
