#include "../includes/minishell.h"

int ft_echo(int argc, char** argv, char **env)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;

	printf("");
	while (i < argc)
	{
		if (argv[i] != "-n")
			printf("%s", argv[i]);
		i++;
	}
	if (argv[0] == '-n')
		printf("\n");
	// TODO

	return (ret);
	// return (1 ou 0)
}