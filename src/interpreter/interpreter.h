#define ALPHABET_SIZE 26

// using a tree to build a list of commands to use each : a node parent is its
// closest prefix
typedef struct Node {
    const char *canonical_name;
    const char *path;
    struct Node *children;
} Node;

typedef struct {
    Node *root;

} ProgramTree;

// this should work like a hashmap
typedef struct ProgramForest {
    ProgramTree tree[ALPHABET_SIZE];
} ProgramForest;

Node *initialize_node(const char *canonical_name, const char *path);
ProgramTree *initialize_tree(const char *root_name, const char *root_path);
ProgramForest *initialize_forest(const char *programs_directory, const char *cwd);

int add_program(const char *canonical_name, const char *path);
void __insert_into_tree(ProgramTree *tree, const char canonical_name,
                        const char *path);
int call_program(ProgramForest *forest, char *program_name);
