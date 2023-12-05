#include "../includes/minishell.h"

int	main(void)
{
//	char *tab[] = {"-ndddd", "ICI"};
	char *tab2[] = {"-n"};

//	ft_echo(2, tab, tab);
	//ft_echo(1, tab2, tab2);	
	builtin_pwd(1, tab2, tab2);
	return (0);
}