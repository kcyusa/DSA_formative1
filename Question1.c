#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_STUDENTS 100

typedef struct {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int grade;
} Student;

// Swap two students
void swap(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for quicksort
int partition(Student arr[], int low, int high) {
    int pivot = arr[high].grade;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].grade < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Quicksort function
void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Read students from file
int readStudents(const char* filename, Student students[]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s %s %d", students[count].firstName,
                  students[count].lastName, &students[count].grade) == 3) {
        count++;
        if (count >= MAX_STUDENTS) break;
    }

    fclose(file);
    return count;
}

// Write students to file
void writeStudents(const char* filename, Student students[], int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to write file");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %d\n", students[i].firstName,
                students[i].lastName, students[i].grade);
    }

    fclose(file);
}

int main() {
    Student students[MAX_STUDENTS];
    int count = readStudents("students.txt", students);

    if (count == 0) {
        printf("No students found or file error.\n");
        return 1;
    }

    quickSort(students, 0, count - 1);

    writeStudents("sorted_students.txt", students, count);

    printf("Sorted records written to 'sorted_students.txt'.\n");
    return 0;
}
