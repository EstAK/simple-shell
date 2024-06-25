#include "constants.h"
#include "tokenizer/tokenizer.h"
#include "interpreter/interpreter.h"

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char current_working_directory[SIZE];
char user[SIZE];
struct passwd *meta_data;

// this function will read size from the stdin
void read_input(char *buffer) {
    // tokenize here
    TokenStream *token_stream = new_token_stream();
    char *token_content;
    id_t curr = 0;

    token_content = strtok(buffer, " ");
    while (token_content != NULL) {
        add_token(token_stream, new_token(token_content, curr));
        curr++;
        token_content = strtok(NULL, " ");
    }
}

void print_prefix() {

    char *cwd = malloc(SIZE);

    getcwd(cwd, SIZE);
    memcpy(current_working_directory, cwd, strlen(meta_data->pw_dir));
    current_working_directory[strlen(meta_data->pw_dir)] = '\0';

    if (strcmp(current_working_directory, meta_data->pw_dir) == 0) {
        current_working_directory[0] = '~';
        memcpy(current_working_directory + 1, cwd + strlen(meta_data->pw_dir),
               SIZE - strlen(meta_data->pw_dir));
    }

    printf("%s %s %% ", user, current_working_directory);
}

void run() {
    char c;
    unsigned int position = 0;
    unsigned int n_blocks = 1;
    char *buffer = calloc(SIZE, sizeof(char));

    while (1) {
        c = getchar();
        if (c == '\n' || c == '\0') {
            buffer[position] = '\0';
            read_input(buffer);
            buffer[0] = '\0';
            position = 0;
            n_blocks = 1;
            print_prefix();
        }
        if (position >= SIZE) {
            n_blocks++;
            char *new_ptr;
            if ((new_ptr = realloc(buffer, n_blocks * SIZE)) == NULL) {
                printf("cannot allocate more space\n");
                buffer[0] = '\0';
                position = 0;
                n_blocks = 1;
                print_prefix();
            } else {
                buffer = new_ptr;
            }
        }
        buffer[position] = c;
        position++;
    }
    return;
}

int main(int __attribute__((unused)) argc,
         char __attribute__((unused)) * *argv) {
    if ((meta_data = getpwuid(getuid())) == NULL) {
        return EXIT_FAILURE;
    }
    strncpy(user, meta_data->pw_name, SIZE);
    getcwd(current_working_directory, SIZE);
    system("clear");
    print_prefix();

    run();
    return EXIT_SUCCESS;
}
