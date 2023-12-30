/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chbouthe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:24:44 by chbouthe          #+#    #+#             */
/*   Updated: 2023/12/30 20:24:46 by chbouthe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define TK_TYPE_AND 42//	"&&" (Bonus only)
# define TK_TYPE_OR 43//	"||" (Bonus only)
# define TK_TYPE_PIPE 44//	"|"
# define TK_TYPE_RED_OUT 45//	">"
# define TK_TYPE_RED_OUT_APPEND 46//	">>"
# define TK_TYPE_RED_IN 47//	"<"
# define TK_TYPE_RED_IN_DELIM 48//	"<<"
# define TK_TYPE_PAR_O 49//	"("
# define TK_TYPE_PAR_C 50//	")"
# define TK_TYPE_STR 40//	anything else (echo  OU -n  OU "hello $USER)

typedef struct s_token
{
	int				type;	// TK_TYPE_.... (voir defines)
	char			*val;	// ex: echo OU -n OU >>
	int				change_env_var;
	int				space_before;
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
	int		current_stdin; // descriptor du stdin courant
	int		original_stdin; // descriptor du stdin original pour le reset
	int		current_stdout; // descriptor du stdout courant
	int		original_stdout; // descriptor du stdout original pour le reset
	int		heredoc_handled; // 1 si on est dans un heredoc, 0 sinon
	int		nb_pipes;
}	t_data;

#endif
