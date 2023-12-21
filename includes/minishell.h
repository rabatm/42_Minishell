
#ifndef MINISHEL_H
# define MINISHEL_H

# include "../libft/libft.h"
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
# include <sys/param.h>
# include <stddef.h>
# include <unistd.h>

# include <stdio.h>
# include "./minishell_define.h"

# define COLOR_RED     "\x1b[31m"
# define COLOR_GREEN   "\x1b[32m"
# define COLOR_YELLOW  "\x1b[33m"
# define COLOR_BLUE    "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN    "\x1b[36m"
# define COLOR_RESET   "\x1b[0m"

// init_data
t_data  *init_data(char **env);
void    free_data(t_data *data);

//tokens
//listes chainees
t_token	*create_new_token(char *val, int type);
void	add_token_back(t_token **tokens, t_token *new_token);
void	free_tokens(t_token **tokens);
int	make_list_tokens(t_token **tokens, char *line, int type, int space_before);
t_token	*its_last_token(t_token **tokens);

//tokeniser
t_token	**tokenize_line(char *line);
//tokenizer tools
int	get_and_or_type(char *line, int i);
int	get_redirection_type(char *line, int i);
int	get_token_type(char *line, int i);
int	get_id_of_closing_quote(char *line, int opening_quote_id);
int	get_end_str_id(char *line, int i);

//replace_env_var
void	replace_env_var(t_data *data);
char	*get_value_of_env_var(t_data *data, char *env_var);

//tab_strs_tools
char        **ft_tab_dup(char **src);
int        ft_tab_size(char **tab);
void        ft_free_tab(char **tab);
int        ft_str_starts_with(char *str, char *start);
int        ft_str_ends_with(char *str, char *end);
int        ft_strs_equals(char *s1, char *s2);
int        ft_strcmp(char *s1, char *s2);
char    *ft_str_replace(char *str, char *new, int start, int end);
void    ft_print_tab(char **tab);
char    **ft_add_str_to_tab(t_data *data, char *entry);
char    **free_tab_and_return_null(char **tab);

//tools
int        ft_is_white_space(char c);
char    *ft_strtrim_whitespaces(const char *str);

//signals
int	handle_signal(void);

//builtins
int 	ft_echo(int argc, char** argv, char **env);
int		builtin_pwd(int argc, char **argv, char **env);
int		builtin_cd(int argc, char **argv, char **env);
int     exec_unset(int argc, char **argv, t_data *data);
int     exec_export(int argc, char **argv, t_data *data);

//exec_cmd
int		ft_arg_error(char **argv);
int		ft_check_file_exist(char *fd);
char	*ft_getcmd(char *arg);
char    **ft_getenvpath(char **envp);
int		ft_tokensize(t_token **lst);
char    **get_cmd_array(t_token **tokens);

void		ft_exec_ext_command(char **argv, t_data *data);
int		ft_exec(t_data *data);
char	*ft_checkexe(char *for_exe, char **envp);

//redirections
int    apply_redirections(t_data *data, t_token **tokens);
void    reset_redirections(t_data *data);
int    apply_redirection_in_delim(t_data *data, t_token *token);
int     apply_redirection_in(t_data *data, t_token *token);

//redirections tools
int    ft_rediretion_error(t_data *data, t_token *token);
int    handle_error_fd(t_data *data, t_token *token, int fd);
void    reset_redirections(t_data *data);


#endif
