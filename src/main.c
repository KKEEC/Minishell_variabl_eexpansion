// minishell/src/main.c
#include "../includes/minishell.h"
#include "../includes/env.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *cwd;
    t_env   *env_list = init_env_list(envp);
    if (!get_env_value(env_list, "PWD"))
    {
        cwd = getcwd(NULL, 0);
        if (cwd)
        {
            update_env(&env_list, "PWD", cwd);
            free(cwd);
        }
    }
    /* t_env *temp = env_list;
    while (temp)
    {
        printf("ENV: %s=%s\n", temp->key, temp->value);
        temp = temp->next;
    } */
    minishell_loop(env_list);

    return 0;
}
