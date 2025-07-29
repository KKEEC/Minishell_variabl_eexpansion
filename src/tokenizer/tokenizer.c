#include "../../includes/tokenizer.h"
#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"
#include "../../includes/parser.h"
#include "../../includes/executor.h"

void    free_tokens(t_token *head)
{
    t_token *tmp;

    while(head)
    {
        tmp = head;
        head = head->next;
        free(tmp->value);
        free(tmp);
    }
}

void    add_token(t_token **head, t_token *new_token)
{
    t_token *cur;

    if (!*head)
        *head = new_token;
    else
    {
        cur = *head;
        while (cur->next)
            cur = cur->next;
        cur->next = new_token; 
    }
}

t_token *create_token(t_token_type type, const char *input)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = ft_strdup(input);
    token->next = NULL;
    return token;
}

char *slice(int i, char *str)
{
    int j = i;
    char *res;
    int len;
    while (str[j])
    {
        len++;
        j++;
    }
    res = malloc(len + 1);
    j = 0;
    while(str[i])
    {
        res[j] = str[i];
        j++;
        i++;
    }
    res[j] = '\0';
    return res;
}

t_token *tokenize(const char *input, t_env *env_list)
{
    t_token *tokens = NULL;
    size_t i = 0;

    if (!input)
        return NULL;
    while (input[i])
    {
        if (ft_isspace(input[i]))
        {
            i++;
            continue;
        }

        // Handle combined export-style key="value with spaces"  /////
        if (!ft_isspecialchar(input[i]) && input[i] != '\'' && input[i] != '"')
        {
            size_t start = i;
            while (input[i] && !ft_isspace(input[i]))
            {
                if (input[i] == '=' && (input[i + 1] == '"' || input[i + 1] == '\''))
                {
                    char quote = input[i + 1];
                    i += 2; // Skip over = and opening quote
                    while (input[i] && input[i] != quote)
                        i++;
                    if (input[i] == quote)
                        i++; // include closing quote
                    break;
                }
                i++;
            }
            char *token_val = ft_strndup(&input[start], i - start);
            printf("\n\n\n");
            printf("token_val: %s\n", token_val);
            int j = 0;
            //int k = 0;
            while (token_val[j])
            {
                if (token_val[j] == '$')
                    break;
                j++;
            }
            j++;
            printf("index j: %d", j);
            char *key = slice(j, token_val);
            printf("key: %s and value: %s\n", key, get_env_value(env_list, key));
            if (!get_env_value(env_list, key))
                add_token(&tokens, create_token(TOKEN_WORD, token_val));
            else
                add_token(&tokens, create_token(TOKEN_WORD, get_env_value(env_list, key)));
            free(token_val);
            continue;
        }

        if (input[i] == '\'')
        {
            if (handle_single_quote(input, &i, &tokens) == 0)
                return free_tokens(tokens), NULL;
            continue;
        }

        if (input[i] == '"')
        {
            if (handle_double_quote(input, &i, &tokens) == 0)
                return free_tokens(tokens), NULL;
            continue;
        }

        if (ft_isspecialchar(input[i]))
            handle_special(input, &i, &tokens);
        else
            handle_word(input, &i, &tokens);
        i++;
    }

    return tokens;
}
