#include "../includes/minishell.h"

int	main(void)
{
//	char *tab[] = {"-ndddd", "ICI"};
	char *tab2[] = {"/Users/martincelavie"};
	char *tab3[] = {"/Users/martincelavie/toto"};

//	ft_echo(2, tab, tab);
	//ft_echo(1, tab2, tab2);	
	builtin_cd(1, tab2, tab2);
	builtin_pwd(0, tab2, tab2);
	builtin_cd(1, tab3, tab2);
	builtin_pwd(0, tab3, tab2);
	return (0);
}