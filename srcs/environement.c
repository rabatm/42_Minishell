#include "../includes/minishell.h"

int     exec_env(t_data *data)
{
    int     i;

    i = 0;
    while (data->env[i])
    {
        printf("%s \n", data->env[i]);
        i++;
    }
    return (0);
}

/*
{
    int     i;

    i = 0;
    while (env[i])
    {
        printf("%s \n", env[i]);
        i++;
    }
    return (0);
}
*/