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

int	builtin_cd(int argc, char **argv, char **env)
{
	int	ret;

	(void)env;
	ret = 1;
	if (argc == 1)
	{
		errno = 0;
		if (chdir(argv[0]) != 0)
		{
			if (errno == ENOENT)
				printf("cd: no such file or directory: %s\n", argv[0]);
			else
				printf("cd: erro\n");
		}
	}
	if (argc > 2)
	{
		if (opendir(argv[0]))
			chdir(argv[0]);
		else
			printf("cd: too many arguments\n");
	}
	return (ret);
}

int	exec_unset(int argc, char **argv, char **env, t_data *data)
{
	(void)argc;
	(void)argv;
	(void)env;

	

int	ft_export(int argc, char **argv, char **env)
{
	
}