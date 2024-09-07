#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Check if a character is a delimiter
int isDelimiter(char ch) {
    return isspace(ch) || ch == ',' || ch == '.' || ch == '!' || ch == '?' || ch == ';' || ch == ':' || ch == '-';
}

int main(int argc, char *argv[]) {
    //Check if the correct number of arguments are provided
    if (argc != 3) {
        //Error text message if number of arguments is different than 3
        printf("Usage: ./textfile-ops input-file.txt output-file-name.txt\n");
        return 1;
    }

    // Open the input file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error: The input file \"%s\" does not exist or cannot be opened.\n", argv[1]);
        return 1;
    }
    printf("The input file \"%s\" was opened successfully!\n", argv[1]);

    // Open the output file
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("Error: The output file \"%s\" cannot be created.\n", argv[2]);
        // if issue with output file, close inputfile.
        fclose(inputFile);
        return 1;
    }

    char ch;
    char word[256];
    int wordCount = 0;
    int index = 0;

    // Read each character from the input file
    while ((ch = fgetc(inputFile)) != EOF) {
        // If the character is not a delimiter, add it to the word
        if (!isDelimiter(ch)) {
            word[index++] = ch;
        } else {
            // If the character is a delimiter and a word has been formed
            if (index > 0) {
                word[index] = '\0'; // Null-terminate the word
                fprintf(outputFile, "%s\n", word); // Write the word to the output file
                wordCount++;
                index = 0; // Reset the index for the next word
            }
        }
    }

    // Check if the last word was not followed by a delimiter
    if (index > 0) {
        word[index] = '\0';
        fprintf(outputFile, "%s\n", word);
        wordCount++;
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    // Print the word count
    printf("The total number of words is %d.\n", wordCount);
    printf("The output file \"%s\" was created successfully.\n", argv[2]);

    return 0;
}
