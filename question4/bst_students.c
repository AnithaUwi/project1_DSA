

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 60
#define LINE_LEN 128

typedef struct {
    char first[MAX];
    char last[MAX];
    int grade;
} Student;

typedef struct Node {
    Student s;
    struct Node *left;
    struct Node *right;
} Node;

void trim(char *s) {
    int i = 0, j;
    while (s[i] && isspace((unsigned char)s[i]))
        i++;
    if (i > 0)
        memmove(s, s + i, strlen(s + i) + 1);
    j = (int)strlen(s) - 1;
    while (j >= 0 && isspace((unsigned char)s[j]))
        s[j--] = '\0';
}

void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

Node *createNode(Student st) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL)
        return NULL;
    n->s = st;
    n->left = n->right = NULL;
    return n;
}

Node *bstInsert(Node *r, Student st) {
    int cmp;
    if (r == NULL)
        return createNode(st);
    cmp = strcmp(st.last, r->s.last);
    if (cmp < 0)
        r->left = bstInsert(r->left, st);
    else
        r->right = bstInsert(r->right, st); /* duplicate last name -> right */
    return r;
}

Node *bstSearch(Node *r, char *last) {
    int cmp;
    if (r == NULL)
        return NULL;
    cmp = strcmp(last, r->s.last);
    if (cmp == 0)
        return r;
    if (cmp < 0)
        return bstSearch(r->left, last);
    return bstSearch(r->right, last);
}

void printMatches(Node *r, char *last) {
    if (r == NULL)
        return;
    printMatches(r->left, last);
    if (strcmp(r->s.last, last) == 0)
        printf("  %s | %s | %d\n", r->s.first, r->s.last, r->s.grade);
    printMatches(r->right, last);
}

void freeTree(Node *r) {
    if (r == NULL)
        return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

int parseLine(char *line, Student *st) {
    char *a, *b, *c;
    char buf[LINE_LEN];

    strncpy(buf, line, LINE_LEN - 1);
    buf[LINE_LEN - 1] = '\0';
    buf[strcspn(buf, "\r\n")] = '\0';

    a = strtok(buf, "|");
    b = strtok(NULL, "|");
    c = strtok(NULL, "|");
    if (a == NULL || b == NULL || c == NULL)
        return 0;

    trim(a);
    trim(b);
    trim(c);
    if (strlen(a) == 0 || strlen(b) == 0)
        return 0;

    st->grade = atoi(c);
    if (st->grade < 0 || st->grade > 100)
        return 0;

    strncpy(st->first, a, MAX - 1);
    st->first[MAX - 1] = '\0';
    strncpy(st->last, b, MAX - 1);
    st->last[MAX - 1] = '\0';
    return 1;
}

Node *loadStudents(const char *filename, int *count) {
    FILE *f = fopen(filename, "r");
    char line[LINE_LEN];
    Student st;
    Node *root = NULL;
    long size;

    *count = 0;
    if (f == NULL) {
        printf("Error: cannot open %s\n", filename);
        return NULL;
    }

    if (fseek(f, 0, SEEK_END) == 0) {
        size = ftell(f);
        if (size == 0) {
            printf("Error: file is empty.\n");
            fclose(f);
            return NULL;
        }
    }
    rewind(f);

    while (fgets(line, sizeof(line), f) != NULL) {
        if (line[0] == '\n' || line[0] == '\r')
            continue;
        if (!parseLine(line, &st)) {
            printf("Warning: skipped bad line.\n");
            continue;
        }
        root = bstInsert(root, st);
        if (root == NULL) {
            printf("Error: memory allocation failed.\n");
            fclose(f);
            freeTree(root);
            return NULL;
        }
        (*count)++;
    }
    fclose(f);

    if (*count == 0) {
        printf("Error: no valid records in file.\n");
        freeTree(root);
        return NULL;
    }
    return root;
}

void searchByLastName(Node *root, char *last) {
    if (bstSearch(root, last) == NULL) {
        printf("No student with last name '%s'.\n", last);
        return;
    }
    printf("Records for '%s':\n", last);
    printMatches(root, last);
}

int main(void) {
    Node *root = NULL;
    int n = 0, choice;
    char last[MAX];

    root = loadStudents("students.txt", &n);
    if (root == NULL)
        return 1;

    printf("Loaded %d student(s) into BST.\n", n);
    printf("Key: last name. Duplicates go to the right subtree.\n");

    do {
        printf("\n1. Search by last name\n");
        printf("2. Quit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInput();
            printf("Invalid input.\n");
            continue;
        }
        clearInput();

        if (choice == 1) {
            printf("Enter last name: ");
            if (scanf("%59s", last) != 1) {
                clearInput();
                printf("Invalid input.\n");
                continue;
            }
            clearInput();
            searchByLastName(root, last);
        } else if (choice == 2)
            break;
        else
            printf("Invalid choice.\n");
    } while (1);

    freeTree(root);
    printf("BST deleted. Program ended.\n");
    return 0;
}
