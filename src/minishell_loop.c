#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
#include "../includes/parser.h"
#include "../includes/executor.h"

static void execute_pipechaining(t_ast *ast, t_env **env_list)
{
    (void)ast;
    (void)env_list;

    printf("...executing pipe\n");
}

static t_ast *handle_input(t_env *env_list)
{
    t_token *tokens;
    char *input = readline("minishell$ ");
    if (!input)
    {
        printf("exit\n");
        exit(0);
    }
    if (*input)
        add_history(input);
    tokens = tokenize(input, env_list);
    if (!tokens)
    {
        free(input);
        return (NULL);
    }
    if (is_syntax_error(tokens))
    {
        free_tokens(tokens);
        free(input);
        return NULL;
    }
    t_ast *ast = parse_tokens(tokens);
    free_tokens(tokens);
    return (ast);
}
void    minishell_loop(t_env *env_list)
{
    t_ast *ast;

    while(1)
    {
        ast = handle_input(env_list);
        if (!ast)
            continue ;
        if(ast)
        {
            print_ast(ast, 3);
            if (ast->type != NODE_PIPE && ast->type != NODE_REDIR)
                execute_ast(ast, &env_list);
            else
                execute_pipechaining(ast, &env_list);
            free_ast(ast);
        }
    }
}
