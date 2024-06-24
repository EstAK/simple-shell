#include "interpreter.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

Node *initialize_node(const char *canonical_name, const char *path) {
    Node *node = malloc(sizeof(*Node));
    node->canonical_name = canonical_name;
    node->path = path;

    return node;
}

ProgramTree *initialize_tree(const char *root_name, const char *root_path) {
    ProgramTree *tree = malloc(sizeof(*ProgramTree));
    tree->root->canonical_name = root_name;
    tree->root->path = root_path;

    return tree;
}

// can return NULL if the program failed to open the directory
ProgramForest *initialize_forest(const char *programs_directory) {
    ProgramForest *forest = malloc(sizeof(*ProgramForest));

    DIR *d;
    struct dirent dir;
    if ((d = opendir(programs_directory))) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
    } else {
        return NULL;
    }
}

int add_program(const char *canonical_name, const char *path);
void __insert_into_tree(ProgramTree *tree, const char canonical_name,
                        const char *path);
int call_program(ProgramForest *forest, char *program_name);
