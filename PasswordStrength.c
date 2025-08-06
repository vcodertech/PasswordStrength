#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char digits[] = "0123456789";
const char symbols[] = "!@#$%^&*()-_=+[{]}|;:',<.>/?";

void shuffle(char *array, int length) {
    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void generatePassword(char *password, int length) {
    if (length < 10) {
        printf("Password length must be at least 10 characters to be strong.\n");
        password[0] = '\0';
        return;
    }

    int index = 0;
    password[index++] = lowercase[rand() % strlen(lowercase)];
    password[index++] = uppercase[rand() % strlen(uppercase)];
    password[index++] = digits[rand() % strlen(digits)];
    password[index++] = symbols[rand() % strlen(symbols)];

    const char *all_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[{]}|;:',<.>/?";
    int total_chars = strlen(all_chars);

    while (index < length) {
        password[index++] = all_chars[rand() % total_chars];
    }

    shuffle(password, length);
    password[length] = '\0';
}

void checkStrength(char *password) {
    int has_lower = 0, has_upper = 0, has_digit = 0, has_symbol = 0;
    int length = strlen(password);

    for (int i = 0; i < length; i++) {
        if (islower(password[i])) has_lower = 1;
        else if (isupper(password[i])) has_upper = 1;
        else if (isdigit(password[i])) has_digit = 1;
        else has_symbol = 1;
    }

    int score = has_lower + has_upper + has_digit + has_symbol;

    printf("\nPassword Strength: ");
    if (length < 6 || score < 2) {
        printf("Weak\n");
    } else if (length < 10 || score == 2 || score == 3) {
        printf("Medium\n");
    } else if (length >= 10 && score == 4) {
        printf("Strong\n");
    } else {
        printf("Undetermined\n");
    }
}

int main() {
    int choice;
    char password[100];
    int length;

    srand(time(NULL));

    while (1) {
        printf("\n----- Password Generator & Strength Checker -----\n");
        printf("1. Generate a Strong Password\n");
        printf("2. Check Password Strength\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter desired password length (min 10): ");
                scanf("%d", &length);
                getchar();
                if (length < 6 || length >= 100) {
                    printf("Invalid length. Please enter a value between 6 and 99.\n");
                    break;
                }
                generatePassword(password, length);
                if (strlen(password) > 0)
                    printf("Generated Password: %s\n", password);
                break;

            case 2:
                printf("Enter the password to check: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = 0;
                checkStrength(password);
                break;

            case 3:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
