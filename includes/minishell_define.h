#ifndef MINISHEL_DEFINE_H
# define MINISHEL_DEFINE_H

# define RST	"\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G		"\033[1;32m"   /* Bold Green */
# define Y		"\033[1;33m"   /* Bold Yellow */
# define B		"\033[1;34m"   /* Bold Blue */
# define M		"\033[1;35m"   /* Bold Magenta */
# define C		"\033[1;36m"   /* Bold Cyan */
# define W		"\033[1;37m"   /* Bold White */
typedef struct s_token
{
	int				type;	// TK_TYPE_.... (voir defines)
	char			*val;	// ex: echo OU -n OU >>
	int				escape_env_var;
	int				must_be_merge_with_previous; // faculatatif ?
	struct s_token	*previous;
	struct s_token	*next;

}	t_token;
typedef struct s_data
{
	char	**env;		// copie de env
	char	*line;		// la ligne lue par readline
	t_token	**tokens;		// line decoupee en [tableau ou liste] de tokens
	int		exit;		// exit minishell si egal a 1
	int		last_exit_status; // le status de la commande precedente (pour $?)
	int		stdin;
	int		stdout;

}	t_data;

typedef struct s_pipex
{
	int		pid1;
	int		pid2;
	char	*file_out;
	char	*file_in;
	int		file_outfd;
	int		file_infd;
	int		fd[2];
	char	*cmd1;
	char	*cmd2;
    char **splitarg1;
    char **splitarg2;
	char **path_exe;
}				t_pipex;

#endif
