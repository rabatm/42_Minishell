#include "../includes/minishell.h"

int ft_echo(int argc, char** argv, char **env)
{
	int	i;

	i = 1;
	(void)env;
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	if (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
		i++;
	while (i < argc)
	{
		if (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			if (i + 1 < argc)
				printf(" ");
		}
		i++;
	}
	if (argc == 1 || (argc > 1 && ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) != 0))
		printf("\n");
	return (0);
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

int	builtin_cd(int argc, char **argv, char **env)
{
	int	ret;

	(void)env;
	ret = 0;
	if (argc == 2)
	{
		errno = 0;
		if (chdir(argv[1]) != 0)
		{
			ret = 1;
			if (errno == ENOENT)
				printf(RED"cd: no such file or directory: %s\n"RST, argv[1]);
			else
				printf(RED"cd: erro\n"RST);
		}
	}
	if (argc > 2)
	{
		if (opendir(argv[1]))
			chdir(argv[1]);
		else
			printf(RED"cd: too many arguments\n"RST);
	}
	return (ret);
}
