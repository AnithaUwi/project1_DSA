

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_ID 20
#define MAX_STUDENTS 500

typedef struct {
    char first[MAX_NAME];
    char last[MAX_NAME];
    char id[MAX_ID];
    int grade;
} Student;

Student list[MAX_STUDENTS];
int n = 0;

int compare(Student a, Student b) {
    if (a.grade != b.grade)
        return a.grade - b.grade;
    return strcmp(a.last, b.last);
}

void swap(Student *a, Student *b) {
    Student t = *a;
    *a = *b;
    *b = t;
}

int partition(int low, int high) {
    Student pivot = list[high];
    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        if (compare(list[j], pivot) <= 0) {
            i++;
            swap(&list[i], &list[j]);
        }
    }
    swap(&list[i + 1], &list[high]);
    return i + 1;
}

void quickSort(int low, int high) {
    if (low < high) {
        int p = partition(low, high);
        quickSort(low, p - 1);
        quickSort(p + 1, high);
    }
}

int main() {
    FILE *fp;
    char line[200];
    FILE *out;

    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Could not open students.txt\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL && n < MAX_STUDENTS) {
        if (sscanf(line, "%s %s %s %d",
                   list[n].first, list[n].last, list[n].id, &list[n].grade) == 4)
            n++;
    }
    fclose(fp);

    if (n == 0) {
        printf("No students loaded.\n");
        return 1;
    }

    quickSort(0, n - 1);

    out = fopen("sorted_students.txt", "w");
    if (out == NULL) {
        printf("Could not create output file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        fprintf(out, "%s %s %s %d\n",
                list[i].first, list[i].last, list[i].id, list[i].grade);

    fclose(out);
    printf("Sorting finished. %d records saved to sorted_students.txt\n", n);
    return 0;
}
