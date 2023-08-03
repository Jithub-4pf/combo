#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
/*----------------------------------------------------------------

                    Combolist Generator
                    Author(s): rmiller
                    Usage: generate a combolist given a size
                    specified by a command line argument (n)
                    of valid email:password combos. this can
                    use trends in the future so the combo is
                    more likely to work.

              (
               )
              (
        /\  .-"""-.  /\
       //\\/  ,,,  \//\\
       |/\| ,;;;;;, |/\|
       //\\\;-"""-;///\\
      //  \/   .   \/  \\
     (| ,-_| \ | / |_-, |)
       //`__\.-.-./__`\\
      // /.-(() ())-.\ \\
     (\ |)   '---'   (| /)
      ` (|           |) `
        \)           (/
----------------------------------------------------------------*/

// TODO : implement trends in email:password combos

#define FILENAME "output.txt"

const char* endings[] = {"@gmail.com", "@hotmail.com", "@live.co.uk", "@mail.com", "@outlook.com"};
#define endings_array_length (sizeof(endings) / sizeof(endings[0]))
#define MAX_LEN_EMAIL 15
#define MIN_LEN_EMAIL 5
#define MIN_LEN_PASSW 8
#define MAX_LEN_PASSW 20

char getRandomChar(const char charset[], int maxIndex) {
    return charset[rand() % maxIndex];
}

char* getRandomString(const char charset[], int n) {
    char* randomString = (char*)malloc((n + 1) * sizeof(char));
    if (randomString == NULL) {
        printf("error: memory could not be allocated.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        randomString[i] = getRandomChar(charset, strlen(charset));
    }
    randomString[n] = '\0';

    return randomString;
}

void generateCombos(int count) {
    FILE* output;
    output = fopen(FILENAME, "w");
    if (output == NULL) {
        printf("error: output file could not be created... aborting...\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        // email
        int endings_index = rand() % endings_array_length;
        const char* ending = endings[endings_index];
        int len = MIN_LEN_EMAIL + rand() % (MAX_LEN_EMAIL - MIN_LEN_EMAIL + 1);
        char* email_start = getRandomString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", len);

        char email[MAX_LEN_EMAIL + 1];
        sprintf(email, "%s%s", email_start, ending);
        free(email_start);

        // password
        int plen = MIN_LEN_PASSW + rand() % (MAX_LEN_PASSW - MIN_LEN_PASSW + 1);
        char* password = getRandomString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.!*&@_-", plen);

        // final
        fprintf(output, "%s:%s\n", email, password);
        free(password);
    }

    fclose(output);
    printf("successfully generated \"%s\" with %d email:password combos!\n", FILENAME, count);
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("usage: gencombos (n)\n");
        return 1;
    } else {
        char* n = argv[1];
        int comboAmount = atoi(n);
        if (comboAmount == 0) {
            printf("error: amount given must be an integer... aborting...\n");
            return 1;
        } else {
            srand(time(NULL)); // Move srand to main to ensure proper seeding
            generateCombos(comboAmount);
            return 0;
        }
    }
    return 0;
}
