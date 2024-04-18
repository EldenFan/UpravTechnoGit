#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_STR_LEN 100

// Function to detect the naming convention used in a string
int format(const char* str) {
    bool hasUpperCase = false;
    bool hasUnderscore = false;
    bool previousUnderscore = false;

    // Check the first character of the string
    if (!isalpha(str[0])) {
        return -1; // Doesn't start with a letter, not camelCase or snake_case
    }

    // Iterate through the string to analyze its characters
    for (int i = 0; str[i]; i++) {
        if (isupper(str[i])) {
            hasUpperCase = true; // Check if there are uppercase letters
        }
        else if (str[i] == '_') {
            if (previousUnderscore || str[i + 1] == '\0' || !islower(str[i + 1])) {
                return -1; // Two consecutive underscores or underscore at the end or after a digit, not snake_case
            }
            hasUnderscore = true; // Check if there are underscores
            previousUnderscore = true;
        }
        else if (!isalnum(str[i])) {
            return -1; // Found an invalid character, not camelCase or snake_case
        }
        else {
            previousUnderscore = false;
        }
    }

    // Determine the naming convention based on the analysis
    if (hasUpperCase && hasUnderscore) {
        return -1; // Neither camelCase nor snake_case
    }
    else if (hasUpperCase) {
        return 0; // camelCase
    }
    else if (hasUnderscore) {
        return 1; // snake_case
    }
    else {
        return -1; // Neither camelCase nor snake_case
    }
}

// Function to convert a camelCase string to snake_case
char* camel_to_snake(const char* str) {
    int length = strlen(str);
    char* result = (char*)malloc((2 * length) * sizeof(char)); // Allocate memory for the result

    if (result == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    int j = 0; // Index for the resulting string

    // Iterate through the string, adding '_' before each uppercase letter
    for (int i = 0; i < length; i++) {
        if (isupper(str[i]) && i != 0) {
            result[j++] = '_'; // Add '_' before uppercase letters
            result[j++] = tolower(str[i]); // Convert uppercase letter to lowercase and add to the result
        }
        else if (isupper(str[i]) && i == 0) {
            result[j++] = tolower(str[i]); // Convert uppercase letter to lowercase and add to the result
        }
        else {
            result[j++] = str[i]; // Simply copy the character if it's not uppercase
        }
    }
    result[j] = '\0'; // Add the null terminator

    return result;
}

// Function to convert a snake_case string to camelCase
char* snake_to_camel(const char* str) {
    int length = strlen(str);
    char* result = (char*)malloc((length + 1) * sizeof(char)); // Allocate memory for the result

    if (result == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    int j = 0; // Index for the resulting string

    // Iterate through the string, skipping '_' and making the next letter uppercase
    for (int i = 0; i < length; i++) {
        if (str[i] == '_') {
            result[j++] = toupper(str[++i]); // Make the next letter uppercase
        }
        else {
            result[j++] = str[i]; // Copy the character if it's not '_'
        }
    }
    result[j] = '\0'; // Add the null terminator

    return result;
}

int main() {
    FILE* input_file = fopen("input.txt", "r"); // Open file for reading
    FILE* output_file = fopen("output.txt", "w"); // Open file for writing

    // Check if file opening was successful
    if (input_file == NULL || output_file == NULL) {
        printf("File open error\n");
        return 1;
    }

    char line[MAX_STR_LEN]; // Array to store the input string

    // Read from the file, perform conversion, and write to the output file
    while (fscanf(input_file, "%[^\n]\n", line) == 1) {
        switch (format(line)) {
        case -1:
            fprintf(output_file, "error\t\t\t(%s)\n", line);
            break;
        case 0:
            fprintf(output_file, "%s\n", camel_to_snake(line));
            break;
        case 1:
            fprintf(output_file, "%s\n", snake_to_camel(line));
            break;
        }
    }

    // Close the files
    fclose(input_file);
    fclose(output_file);

    return 0;
}
