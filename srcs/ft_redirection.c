#include "../includes/minishell.h"

int ft_check_redirection(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if (i == 1 && ft_strncmp(argv[i], "<", 1) == 0)
			return (3);
		if (argv[i + 1] != NULL && ft_strncmp(argv[i], ">>", 2) == 0)
			return (2);
		i++;
	}
	return (0);
}