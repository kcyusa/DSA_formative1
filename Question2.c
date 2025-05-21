#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for sleep()

#define MAX_NAME_LEN 100

// Doubly linked list node
typedef struct BusStop {
    char name[MAX_NAME_LEN];
    struct BusStop* next;
    struct BusStop* prev;
} BusStop;

// Create a new bus stop
BusStop* createBusStop(char* name) {
    BusStop* newStop = (BusStop*)malloc(sizeof(BusStop));
    strcpy(newStop->name, name);
    newStop->next = NULL;
    newStop->prev = NULL;
    return newStop;
}

// Add bus stop at the end
void addBusStop(BusStop** head, char* name) {
    BusStop* newStop = createBusStop(name);

    if (*head == NULL) {
        *head = newStop;
        return;
    }

    BusStop* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newStop;
    newStop->prev = temp;
}

// Move forward with 3-second delay
void moveForward(BusStop* head) {
    BusStop* temp = head;
    while (temp != NULL) {
        printf("Bus Stop: %s\n", temp->name);
        sleep(3);
        temp = temp->next;
    }
}

// Move backward with 3-second delay
void moveBackward(BusStop* head) {
    // Go to the last stop
    BusStop* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    while (temp != NULL) {
        printf("Bus Stop: %s\n", temp->name);
        sleep(3);
        temp = temp->prev;
    }
}

// Free memory
void freeList(BusStop* head) {
    while (head != NULL) {
        BusStop* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    BusStop* head = NULL;

    // Example bus stops
    addBusStop(&head, "Home");
    addBusStop(&head, "Market Street");
    addBusStop(&head, "Central Library");
    addBusStop(&head, "University Gate");
    addBusStop(&head, "Campus");

    int choice;
    printf("Choose direction:\n1. Move Forward (Home to Campus)\n2. Move Backward (Campus to Home)\nYour choice: ");
    scanf("%d", &choice);

    printf("\nStarting journey...\n\n");

    if (choice == 1)
        moveForward(head);
    else if (choice == 2)
        moveBackward(head);
    else
        printf("Invalid choice.\n");

    freeList(head);
    return 0;
}
