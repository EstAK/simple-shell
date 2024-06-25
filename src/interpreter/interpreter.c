#include "interpreter.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *initialize_node(const char *canonical_name, const char *path) {
    Node *node = malloc(sizeof(Node *));
    node->canonical_name = canonical_name;
    node->path = path;

    return node;
}

ProgramTree *initialize_tree(const char *root_name, const char *root_path) {
    ProgramTree *tree = malloc(sizeof(ProgramTree *));
    tree->root->canonical_name = root_name;
    tree->root->path = root_path;

    return tree;
}

// can return NULL if the program failed to open the directory
ProgramForest *initialize_forest(const char *programs_directory, const char *cwd) {
    ProgramForest *forest = malloc(sizeof(ProgramForest *));
    DIR *d = opendir(programs_directory);
    if (d == NULL)
        return NULL;

    struct dirent *dir;
    char temp[1024] = {0};
    // this is kind of dumb as the path will always be relative and never absolute

    strcat(temp, cwd);
    strcat(temp, "/");
    strcat(temp, programs_directory);
    strcat(temp, "/");
    const unsigned int current = strlen(temp);

    while ((dir = readdir(d)) != NULL) {
        memcpy(temp+current, dir->d_name, strlen(dir->d_name));
        temp[strlen(dir->d_name) + current] = '\0';
        printf("%s\n", temp);
    }
    return forest;
}

int add_program(const char *canonical_name, const char *path);
void __insert_into_tree(ProgramTree *tree, const char canonical_name,
                        const char *path);
int call_program(ProgramForest *forest, char *program_name);
