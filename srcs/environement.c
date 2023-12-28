#include "../includes/minishell.h"

int     exec_env(char **env)
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