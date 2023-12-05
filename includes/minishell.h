/*

Creer 2 .h (pour plus de lisibilite)

-	minishell_define.h 	(avec les strutures et les "define")
-	minishell.h 		(avec seulement les prototypes des functions)

Inclure "minishell_define.h" et "../libft/libft.h" dans minishell.h
et inclure seulement minishell.h dans les autres fichiers

*/
#ifndef MINISHEL_H
# define MINISHEL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

#include <stdio.h>
#include "./minishell_define.h"

// * types des differents token:


# define TK_TYPE_AND 42				//	"&&" (Bonus only)
# define TK_TYPE_OR 43				//	"||" (Bonus only)
# define TK_TYPE_PIPE 44			//	"|"
# define TK_TYPE_RED_OUT 45			//	">"
# define TK_TYPE_RED_OUT_APPEND 46	//	">>"
# define TK_TYPE_RED_IN 47			//	"<"
# define TK_TYPE_RED_IN_DELIM 48	//	"<<"
# define TK_TYPE_PAR_O 49			//	"("
# define TK_TYPE_PAR_C 50			//	")"
# define TK_TYPE_STR 40				//	anything else (echo  OU -n  OU "hello $USER"     OU 'hello $USER'   )






#endif