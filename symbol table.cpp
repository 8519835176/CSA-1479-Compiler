#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Define a structure for each entry in the symbol table
typedef struct Entry {
    char symbol[50];
    int address;
    struct Entry* next;
} Entry;

// Define a hash table
Entry* symbolTable[TABLE_SIZE];

// Hash function to map symbols to table indices
unsigned int hash(char* symbol) {
    unsigned int hashValue = 0;
    while (*symbol) {
        hashValue = (hashValue << 5) + *symbol++;
    }
    return hashValue % TABLE_SIZE;
}

// Function to insert a symbol into the table
void insertSymbol(char* symbol, int address) {
    unsigned int index = hash(symbol);
    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    strcpy(newEntry->symbol, symbol);
    newEntry->address = address;
    newEntry->next = symbolTable[index];
    symbolTable[index] = newEntry;
    printf("Symbol '%s' inserted with address %d.\n", symbol, address);
}

// Function to search for a symbol in the table
Entry* searchSymbol(char* symbol) {
    unsigned int index = hash(symbol);
    Entry* current = symbolTable[index];
    while (current != NULL) {
        if (strcmp(current->symbol, symbol) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to delete a symbol from the table
void deleteSymbol(char* symbol) {
    unsigned int index = hash(symbol);
    Entry* current = symbolTable[index];
    Entry* previous = NULL;
    while (current != NULL && strcmp(current->symbol, symbol) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Symbol '%s' not found.\n", symbol);
        return;
    }
    if (previous == NULL) {
        symbolTable[index] = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
    printf("Symbol '%s' deleted.\n", symbol);
}

// Function to display the symbol table
void displaySymbolTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* current = symbolTable[i];
        if (current != NULL) {
            printf("Index %d: ", i);
            while (current != NULL) {
                printf("(%s, %d) ", current->symbol, current->address);
                current = current->next;
            }
            printf("\n");
        }
    }
}

int main() {
    int choice;
    char symbol[50];
    int address;
    Entry* result;

    while (1) {
        printf("\nSymbol Table Operations:\n");
        printf("1. Insert Symbol\n");
        printf("2. Search Symbol\n");
        printf("3. Delete Symbol\n");
        printf("4. Display Symbol Table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter symbol: ");
                scanf("%s", symbol);
                printf("Enter address: ");
                scanf("%d", &address);
                insertSymbol(symbol, address);
                break;
            case 2:
                printf("Enter symbol to search: ");
                scanf("%s", symbol);
                result = searchSymbol(symbol);
                if (result != NULL) {
                    printf("Symbol '%s' found at address %d.\n", result->symbol, result->address);
                } else {
                    printf("Symbol '%s' not found.\n", symbol);
                }
                break;
            case 3:
                printf("Enter symbol to delete: ");
                scanf("%s", symbol);
                deleteSymbol(symbol);
                break;
            case 4:
                displaySymbolTable();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
