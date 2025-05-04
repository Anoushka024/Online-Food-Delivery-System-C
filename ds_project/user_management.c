#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define USER_FILE "users.txt"

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char name[MAX_LEN];
    char address[MAX_LEN];
    char contact[MAX_LEN];
} User;

void registerUser();
int loginUser();
void forgotPassword();
void changePassword();
int checkCredentials(char username[], char password[]);
int userExists(char username[]);



void registerUser() {
    User user;
    FILE *fp = fopen(USER_FILE, "a");

    printf("Enter Username: ");
    fgets(user.username, MAX_LEN, stdin);
    user.username[strcspn(user.username, "\n")] = 0;

    if (userExists(user.username)) {
        printf("Username already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Password: ");
    fgets(user.password, MAX_LEN, stdin);
    user.password[strcspn(user.password, "\n")] = 0;

    printf("Enter Full Name: ");
    fgets(user.name, MAX_LEN, stdin);
    user.name[strcspn(user.name, "\n")] = 0;

    printf("Enter Address: ");
    fgets(user.address, MAX_LEN, stdin);
    user.address[strcspn(user.address, "\n")] = 0;

    printf("Enter Contact: ");
    fgets(user.contact, MAX_LEN, stdin);
    user.contact[strcspn(user.contact, "\n")] = 0;

    fprintf(fp, "%s|%s|%s|%s|%s\n", user.username, user.password, user.name, user.address, user.contact);
    fclose(fp);

    printf("User registered successfully!\n");
}

int loginUser() {
    char username[MAX_LEN], password[MAX_LEN];

    printf("Enter Username: ");
    fgets(username, MAX_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    if (checkCredentials(username, password)) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Login failed. Invalid username or password.\n");
        return 0;
    }
}

int checkCredentials(char username[], char password[]) {
    FILE *fp = fopen(USER_FILE, "r");
    User user;

    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", user.username, user.password, user.name, user.address, user.contact) != EOF) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int userExists(char username[]) {
    FILE *fp = fopen(USER_FILE, "r");
    User user;

    if (!fp) return 0;

    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", user.username, user.password, user.name, user.address, user.contact) != EOF) {
        if (strcmp(user.username, username) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void forgotPassword() {
    char username[MAX_LEN];
    FILE *fp = fopen(USER_FILE, "r");

    if (!fp) {
        printf("No user data found!\n");
        return;
    }

    printf("Enter your username: ");
    fgets(username, MAX_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    User user;
    int found = 0;
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", user.username, user.password, user.name, user.address, user.contact) != EOF) {
        if (strcmp(user.username, username) == 0) {
            printf("Your password is: %s\n", user.password);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Username not found.\n");
    }
}

void changePassword() {
    char username[MAX_LEN], newPassword[MAX_LEN];
    FILE *fp = fopen(USER_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("File error.\n");
        return;
    }

    printf("Enter your username: ");
    fgets(username, MAX_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter new password: ");
    fgets(newPassword, MAX_LEN, stdin);
    newPassword[strcspn(newPassword, "\n")] = 0;

    User user;
    int found = 0;

    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", user.username, user.password, user.name, user.address, user.contact) != EOF) {
        if (strcmp(user.username, username) == 0) {
            strcpy(user.password, newPassword);
            found = 1;
        }
        fprintf(temp, "%s|%s|%s|%s|%s\n", user.username, user.password, user.name, user.address, user.contact);
    }

    fclose(fp);
    fclose(temp);

    remove(USER_FILE);
    rename("temp.txt", USER_FILE);

    if (found) {
        printf("Password updated successfully!\n");
    } else {
        printf("Username not found.\n");
    }
}