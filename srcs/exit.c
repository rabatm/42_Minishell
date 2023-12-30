#include "../includes/minishell.h"

/*

int     ft_exit(t_data *data)
{
    int i;

    i = 0;
    if (data->tokens)
    {
        while (data->tokens[i])
        {
            free(data->tokens[i]);
            data->tokens[i]->val = NULL;
            free(data->tokens[i]->val);
            i++;
        }
    }
    return (0);
}

*/

int ft_exit(t_data *data)
{
    data->exit = 1;
    return (0);
}