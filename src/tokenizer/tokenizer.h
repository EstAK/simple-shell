#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct Token {
    id_t id;
    char *content;
    struct Token *next;
} Token;

typedef struct {
    Token *first;
} TokenStream;

TokenStream *new_token_stream();
Token *new_token(const char *buffer, const id_t id);
void add_token(TokenStream *token_stream, Token *token);
