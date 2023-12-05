
/*
 *	escape_env_var:
 *		seulement pour les type: TK_TYPE_STR
 *		est-ce qu'on doit echapper les variable d'environnement (ou les remplacer)
 *		ex:
 *			echo "hello $USER"  >>  escape_env_var = 0  >>  hello dfleury
 *			echo 'hello $USER'  >>  escape_env_var = 1  >>  hello &USER
 *
 *
 *	must_be_merge_with_previous
 *		ex:
 *			echo "hello $USER"'salut $USER'  >>  hello dfleurysalut $USER (sans espace avant salut)
 */
typedef struct s_token
{
	int				type;	// TK_TYPE_.... (voir defines)
	char			*val;	// ex: echo OU -n OU >>
	int				escape_env_var;
	int				must_be_merge_with_previous; // faculatatif ?
	//...

}	t_token;





typedef struct s_data
{
	char	**env;		// copie de env
	char	*line;		// la ligne lue par readline
	//t_token	? tokens ?;	// line decoupee en [tableau ou liste] de tokens
	int		exit;		// exit minishell si egal a 1
	int		last_exit_status; // le status de la commande precedente (pour $?)
	int		stdin;
	int		stdout;

}	t_data;