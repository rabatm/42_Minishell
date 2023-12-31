/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrabat <mrabat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 01:17:54 by mrabat            #+#    #+#             */
/*   Updated: 2023/12/31 01:18:05 by mrabat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define RST	"\033[0m"
# define RED	"\033[1;31m"
# define G		"\033[1;32m"
# define Y		"\033[1;33m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"

# define TK_TYPE_AND 42
# define TK_TYPE_OR 43
# define TK_TYPE_PIPE 44
# define TK_TYPE_RED_OUT 45
# define TK_TYPE_RED_OUT_APPEND 46
# define TK_TYPE_RED_IN 47
# define TK_TYPE_RED_IN_DELIM 48
# define TK_TYPE_PAR_O 49
# define TK_TYPE_PAR_C 50
# define TK_TYPE_STR 40

typedef struct s_token
{
	int				type;
	char			*val;
	int				change_env_var;
	int				space_before;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char	**env;
	char	*line;
	t_token	**tokens;
	int		exit;
	int		last_exit_status;
	int		current_stdin;
	int		original_stdin;
	int		current_stdout;
	int		original_stdout;
	int		heredoc_handled;
	int		nb_pipes;
}	t_data;

#endif
