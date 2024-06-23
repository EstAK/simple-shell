#include "tokenizer.h"
#include "../constants.h"

TokenStream *new_token_stream() {
    TokenStream *token_stream = malloc(sizeof(TokenStream *));
    token_stream->first = NULL;
    return token_stream;
}

Token *new_token(const char *buffer, const id_t id) {
    Token *token = malloc(sizeof(Token *));
    token->id = id;
    token->next = NULL;
    size_t buffer_length = strlen(buffer);
    memcpy(token->content, buffer, buffer_length > SIZE ? SIZE : buffer_length);
    return token;
}

void add_token(TokenStream *token_stream, Token *token) {
    Token *current_token;
    if ((current_token = token_stream->first) == NULL) {
        token_stream->first = token;
    } else {
        while (current_token->next != NULL) {
            current_token = (Token *)current_token->next;
        }
        current_token->next = (struct Token *)token;
    }
}

