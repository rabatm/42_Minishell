#include "../includes/minishell.h"

int ft_echo(int argc, char** argv, char **env)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;

	(void)env;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) != 0)
			printf("%s", argv[i]);
		i++;
	}
	if (ft_strncmp(argv[0], "-n", ft_strlen(argv[0])) != 0)
		printf("\n");
	return (ret);
}

int	builtin_pwd(int argc, char **argv, char **env)
{
	char	chemin[PATH_MAX];

	(void)argc;
	(void)argv;
	(void)env;

	getcwd(chemin, PATH_MAX);
	printf("%s\n", chemin);
	return (0);
}