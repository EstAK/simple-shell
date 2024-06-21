#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256

// this function will read size from the stdin
char *read_input(size_t size) {
    char *buffer = calloc(size, sizeof(char));
    if (fgets(buffer, SIZE, stdin) != NULL) {
        return buffer;
    };
    return NULL;
}

void run() {
    char c;
    unsigned int position = 0;
    char *buffer = calloc(SIZE, sizeof(char));

    while (1) {
        c = getchar();
        if (c == '\n' || c == '\0') {
            buffer[0] = '\0'; 
        }
    }
    return;
}

int main(int __attribute__((unused)) argc,
         char __attribute__((unused)) * *argv) {
    return EXIT_SUCCESS;
}
