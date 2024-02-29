/**
 * Andre Barrett
 * 11/8/2023
 * Rail Fence Cypher program that allows user to encrypt and decrypt a message
 * User can also decrypt a message saved on a file
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#define MAX_SIZE 200
#define SECOND 1000

void railFenceEncrypt(char* msg, char* encrypted, int numRails);
void railFenceDecrypt(char* msg, char* decrypted, int numRails);
void clearInputStream();

int main() {
    char input[MAX_SIZE], encrypted[MAX_SIZE], decrypted[MAX_SIZE], encryptedFile[MAX_SIZE], reference[MAX_SIZE];
    int choice, numRails, numRailsFile;

    while (1) {
        // Display main menu
        printf("Welcome to the Rail Fence Cypher Program!\n\n");
        printf("Please select the number of the option you want:\n");
        printf("1.) Encrypt a Message\n");
        printf("2.) Decrypt a Message\n");
        printf("3.) Decrypt from a File\n");
        printf("4.) Encrypt to a File and Check against Reference\n");
        printf("5.) Exit Program\n\n");
        // Prompt user for their choice
        printf("Option: ");
        int numScanned = scanf("%d", &choice);
        printf("\n");

        // Switch case executes an option based on the user's choice
        switch(choice) {
            // Option 1: Encrypt a Message
            case 1:
                // Prompt user for message
                printf("Please enter your message to be encrypted:\n");
                scanf("\n");
                fgets(input, MAX_SIZE, stdin);
                input[strlen(input)-1] = '\0'; // Gets rid of the '\n' tacked on to the input

                // Prompt user for valid number of rails until they enter a valid answer
                while(1) {
                    printf("Please enter the number of rails: ");
                    numScanned = scanf("%d", &numRails);
                    if((numRails >= 2) && (numRails <= 10)) {
                        break;
                    }
                    else {
                        // If the user input was not properly scanned (happens when they input characters),
                        if(numScanned <= 0) {
                            // Clear input stream to prevent an infinite loop
                            clearInputStream();
                        }
                        printf("\nError: Invalid number of rails. Must be between 2 and 10\n\n");
                    }
                }

                // Encrypt the message
                railFenceEncrypt(input, encrypted, numRails);

                // Display the result
                printf("\nYour encrypted message is:\n%s\n\n", encrypted);
                Sleep(2*SECOND);
                break;

            // Option 2: Decrypt a Message
            case 2:
                // Prompt user for message
                printf("Please enter your message to be decrypted:\n");
                scanf("\n");
                fgets(input, MAX_SIZE, stdin);
                input[strlen(input)-1] = '\0'; // Gets rid of the '\n' tacked on to the input

                // Prompt user for valid number of rails until they enter a valid answer
                while(1) {
                    printf("Please enter the number of rails: ");
                    numScanned = scanf("%d", &numRails);
                    if((numRails >= 2) && (numRails <= 10)) {
                        break;
                    }
                    else {
                        // If the user input was not properly scanned (happens when they input characters),
                        if(numScanned <= 0) {
                            // Clear input stream to prevent an infinite loop
                            clearInputStream();
                        }
                        printf("\nError: Invalid number of rails. Must be between 2 and 10\n\n");
                    }  
                }

                // Decrypt the message
                railFenceDecrypt(input, decrypted, numRails);

                // Display the result
                printf("\nYour decrypted message is:\n%s\n\n", decrypted);
                Sleep(2*SECOND);
                break;

            // Option 3: Decrypt from a File
            case 3:
                // Prompt user for the name of the file
                printf("Please enter the name of the file to be encrypted:\n");
                scanf("\n");
                fgets(input, MAX_SIZE, stdin);
                input[strlen(input)-1] = '\0'; // Gets rid of the '\n' tacked on to the input

                // Open the file
                FILE* inputFile = fopen(input, "r");

                // Handle any errors with opening the file
                if(inputFile == NULL) {
                    printf("\nError: Could not open file.\n\n");
                    Sleep(SECOND);
                    break;
                }

                // Read the number of rails from the first line
                numScanned = fscanf(inputFile, "%d\n", &numRailsFile);

                // Handle any errors with an invalid number of rails scanned from the file
                if(numScanned <= 0 || !(numRailsFile >= 2 && numRailsFile <= 10)) {
                    printf("\nError: Invalid number of rails. Must be between 2 and 10\n\n");
                    fclose(inputFile);
                    Sleep(SECOND);
                    break;
                }

                // Read the encrypted message from the file and handle any errors with reading the encrypted message
                if(fgets(encryptedFile, MAX_SIZE, inputFile) == NULL) {
                    printf("\nError: Could not read encrypted message from file.\n\n");
                    fclose(inputFile);
                    Sleep(SECOND);
                    break;
                }

                // Decrypt the message
                railFenceDecrypt(encryptedFile, decrypted, numRailsFile);

                // Display the result
                printf("\nThe file's decrypted message is:\n%s\n\n", decrypted);

                // Close the file
                fclose(inputFile);
                Sleep(2*SECOND);
                break;

            // Option 4: Encrypt to a File and Check against Reference
            case 4:
                // Prompt user for message
                printf("Please enter your message to be encrypted:\n");
                scanf("\n");
                fgets(input, MAX_SIZE, stdin);
                input[strlen(input)-1] = '\0'; // Gets rid of the '\n' tacked on to the input

                // Prompt user for valid number of rails until they enter a valid answer
                while(1) {
                    printf("Please enter the number of rails: ");
                    numScanned = scanf("%d", &numRails);
                    if((numRails >= 2) && (numRails <= 10)) {
                        break;
                    }
                    else {
                        // If the user input was not properly scanned (happens when they input characters),
                        if(numScanned <= 0) {
                            // Clear input stream to prevent an infinite loop
                            clearInputStream();
                        }
                        printf("\nError: Invalid number of rails. Must be between 2 and 10\n\n");
                    }  
                }

                // Prompt user for the name of reference file
                printf("Please enter the name of the reference file:\n");
                scanf("\n");
                fgets(reference, MAX_SIZE, stdin);
                reference[strlen(reference)-1] = '\0'; // Gets rid of the '\n' tacked on to the filename

                // Open files
                FILE* resultFile = fopen("result.txt", "w");
                FILE* referenceFile = fopen(reference, "r");
                
                // Handle any errors with opening the files
                if(resultFile == NULL || referenceFile == NULL) {
                    printf("\nError: Could not open file.\n\n");
                    Sleep(SECOND);
                    break;
                }

                // Encrypt message and save to result file
                railFenceEncrypt(input, encrypted, numRails);
                fprintf(resultFile, "%s", encrypted);
                fclose(resultFile);
                printf("\nEncrypted message saved to 'result.txt'\n");

                // Compare the result with the reference
                resultFile = fopen("result.txt", "r");
                fgets(encryptedFile, MAX_SIZE, resultFile);
                fgets(reference, MAX_SIZE, referenceFile);
                if(strcmp(encryptedFile, reference) == 0) {
                    printf("Encrypted message matches reference\n\n");
                }
                else {
                    printf("Encrypted message does not match reference\n\n");
                }

                // Close files
                fclose(resultFile);
                fclose(referenceFile);
                Sleep(2*SECOND);
                break;

            // Option 5: Exit program
            case 5:
                printf("Exiting program...");
                return 1;
            
            // User entered invalid input
            default:
                // If the user input was not properly scanned (happens when they input characters),
                if(numScanned <= 0) {
                    // Clear input stream to prevent an infinite loop
                    clearInputStream();
                }
                // Go back to main menu
                printf("Error: You entered an invalid choice\n\n");
                Sleep(SECOND);
                break;
        }
    }
}

void railFenceEncrypt(char* msg, char* encrypted, int numRails) {
    // Initialize the rail fence as a 2d array of characters:
    // First, the rows are initialized as an array of chars
    int msgLen = strlen(msg);
    char** railFence = (char**) malloc(numRails * sizeof(char*));
    // Then, each row is allocated space based on the length of the message
    for(int i = 0; i < numRails; i++) {
        railFence[i] = (char*) calloc(msgLen, sizeof(char));
    }

    // Fill in the rail fence in a zig-zag pattern:
    // If dir = 1, we are moving down the fence; if dir = -1, we are moving up the fence
    int row = 0, dir = 1; 
    for(int i = 0; i < msgLen; i++){
        railFence[row][i] = msg[i];
        // If we are on the last rail and still moving downwards,
        if ((row == numRails - 1) && (dir == 1)) {
            // change the direction to upwards
            dir = -1;
        }
        // Otherwise, if we are on the first rail and still moving upwards,
        else if ((row == 0) && (dir == -1)) {
            // change the dirction to downwards
            dir = 1;
        }
        // Go the the next rail based on the direction
        row += dir;
    }

    // The rail fence should have the message encoded in a zig-zag pattern with any character
        // that is not in the zig-zag being a '\0'
    // Now, set the encrypted message based on the rail fence
    int idx = 0;
    for(int row = 0; row < numRails; row++) {
        for(int col = 0; col < msgLen; col++) {
            char c = railFence[row][col];
            if (c != '\0') {
                encrypted[idx] = c;
                idx++;
            }
        }
    }
    encrypted[idx] = '\0'; // to end the encrypted string
}
void railFenceDecrypt(char* msg, char* decrypted, int numRails) {
    // Initialize the rail fence as a 2d array of characters:
    // First, the rows are initialized as an array of chars
    int msgLen = strlen(msg);
    char** railFence = (char**) malloc(numRails * sizeof(char*));
    // Then, each row is allocated space based on the length of the message
    for(int i = 0; i < numRails; i++) {
        railFence[i] = (char*) calloc(msgLen, sizeof(char));
    }

    // Fill in the rail fence in a zig-zag pattern,
      //but each space in the zig-zag is filled with a placeholder #:
    // If dir = 1, we are moving down the fence; if dir = -1, we are moving up the fence
    int row = 0, dir = 1; 
    for(int i = 0; i < msgLen; i++){
        // Fill the space on the zig-zag with a placeholder #
        railFence[row][i] = '#';
        // If we are on the last rail and still moving downwards,
        if ((row == numRails - 1) && (dir == 1)) {
            // change the direction to upwards
            dir = -1;
        }
        // Otherwise, if we are on the first rail and still moving upwards,
        else if ((row == 0) && (dir == -1)) {
            // change the dirction to downwards
            dir = 1;
        }
        // Go the the next rail based on the direction
        row += dir;
    }

    // Now fill in the placeholders with the encrypted message from left to right, top to bottom
    int idx = 0;
    for(int row = 0; row < numRails; row++) {
        for(int col = 0; col < msgLen; col++) {
            // If the current space on the rail fence is a placeholder,
            if(railFence[row][col] == '#') {
                // Then fill it with the next character of the encoded message
                railFence[row][col] = msg[idx];
                idx++;
            }
        }
    }

    // Lastly, decrypt the message by reading the rail-fence in a zig-zag pattern
    row = 0, dir = 1, idx = 0;
    for(int i = 0; i < msgLen; i++){
        // Set the current character in decrypted to the current character on the zig-zag
        decrypted[idx] = railFence[row][i];
        idx++;
        // If we are on the last rail and still moving downwards,
        if ((row == numRails - 1) && (dir == 1)) {
            // change the direction to upwards
            dir = -1;
        }
        // Otherwise, if we are on the first rail and still moving upwards,
        else if ((row == 0) && (dir == -1)) {
            // change the dirction to downwards
            dir = 1;
        }
        // Go the the next rail based on the direction
        row += dir;
    }

    decrypted[idx] = '\0'; // to end the encrypted string
}
void clearInputStream() {
    char c = getchar();
    while (c != '\n') {
        c = getchar();
    }
}
