/*

buitin


avec ce genre de prototype (argc, argv, env, comme pour un main),
si vous travaillez en groupe, celui qui s'occupe de ft_echo
sait exactement ce qu'il recoit en parametres et ce qu'il doit en faire


pas besoin de savoir comment marche le reste de minishell
pas besoin d'attendre que ton pote finisse le parsing avant d'attaquer les builtins



Si il y a des variables d'environement a remplacer, ca a deja ete fait en amont !


INFO : env est une copie faite au debut de minishell, mais comme precise plus haut,
c'est pas votre probleme qund vous faites un builtin




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




c



int	builtin_pwd(int argc, char **argv, char **env)


 Pour certains il faut des trucs en plus
int	exec_unset(int argc, char **argv, char **env, t_data *data)





	execve a a peu pres le meme proto : 	execve(execpath, argv, env);



*/