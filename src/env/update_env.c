#include "../../includes/env.h"

void    update_env(t_env **env_list, const char *key, const char *value)
{
    t_env   *current;
    t_env   *new_node;

    if (!key)
        return ;
    current = *env_list;
    if (!*env_list)
    {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
            return;
        new_node->key = ft_strdup(key);
        if (value)
            new_node->value = ft_strdup(value);
        new_node->next = NULL;
        *env_list = new_node;
        return ;
    }
    current = *env_list;
    while (current)
    {
        if (isstrequal(current->key, key))
        {
            free(current->value);
            if (value)
                current->value = ft_strdup(value);
            return ;
        }
        if (!current->next)
            break ;
        current = current->next;
    }
    //if not found add it to the end

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return ;
    new_node->key = ft_strdup(key);
    if (value)
        new_node->value = ft_strdup(value);
    new_node->next = NULL;
    current->next = new_node;
}