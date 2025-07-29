#include "../../../includes/tokenizer.h"

static int isescaped(const char *input, size_t i)
{
    int backslash;

    backslash = 0;
    while(i > 0 && input[--i] == '\\')
        backslash++;
    if (backslash % 2 == 0)
        return (0);
    else
        return (1);
}

int handle_double_quote(const char *input, size_t *i, t_token **tokens)
{
    int start;
    char *word;
    char *processedword;

    start = ++(*i);

    while (input[(*i)])
    {
        if (input[*i] == '"' && isescaped(input, *i) == 0)
            break ;
        (*i)++;
    }
    if (input[*i] != '"')
        return (0);
    word = ft_strndup(&input[start], *i - start);
    if (!word)
    {
        printf("Malloc failed");
        return (0);
    }
    processedword = handle_quoted_esc_chars(word, *i - start);
    if (!processedword)
        return (0);
    free(word);
    add_token(tokens, create_token(TOKEN_WORD, processedword));
    free(processedword);
    (*i)++;
    return (1);
}


int handle_single_quote(const char *input, size_t *i, t_token **tokens)
{
    int start;

    start = ++(*i);
    while (input[*i] && input[*i] != '\'')
        (*i)++;
    if (input[*i] != '\'')  //descriptive message quote not closed
        return (0);
    char *word;

    word = ft_strndup(&input[start], *i - start);
    add_token(tokens, create_token(TOKEN_WORD, word));
    free(word);
    (*i)++;
    return (1);
}