#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int grade;
    struct Student* left;
    struct Student* right;
} Student;

// Create a new student node
Student* createStudent(char* firstName, char* lastName, int grade) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy(newStudent->firstName, firstName);
    strcpy(newStudent->lastName, lastName);
    newStudent->grade = grade;
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

// Insert student into BST based on last name
Student* insert(Student* root, char* firstName, char* lastName, int grade) {
    if (root == NULL)
        return createStudent(firstName, lastName, grade);

    int cmp = strcmp(lastName, root->lastName);
    if (cmp < 0)
        root->left = insert(root->left, firstName, lastName, grade);
    else
        root->right = insert(root->right, firstName, lastName, grade);
    
    return root;
}

// Search for a student by last name
Student* search(Student* root, char* lastName) {
    if (root == NULL || strcmp(lastName, root->lastName) == 0)
        return root;

    if (strcmp(lastName, root->lastName) < 0)
        return search(root->left, lastName);
    else
        return search(root->right, lastName);
}

// Free tree
void freeTree(Student* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Load from file
Student* loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("File error");
        return NULL;
    }

    Student* root = NULL;
    char fname[MAX_NAME_LEN], lname[MAX_NAME_LEN];
    int grade;

    while (fscanf(file, "%s %s %d", fname, lname, &grade) == 3) {
        root = insert(root, fname, lname, grade);
    }

    fclose(file);
    return root;
}

int main() {
    Student* root = loadFromFile("students.txt");

    if (!root) {
        printf("BST could not be built.\n");
        return 1;
    }

    char targetLastName[MAX_NAME_LEN];
    printf("Enter last name to search: ");
    scanf("%s", targetLastName);

    Student* result = search(root, targetLastName);
    if (result)
        printf("Found: %s %s, Grade: %d\n", result->firstName, result->lastName, result->grade);
    else
        printf("Student with last name '%s' not found.\n", targetLastName);

    freeTree(root);
    return 0;
}
