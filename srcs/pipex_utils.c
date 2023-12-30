#include "../includes/minishell.h"

void ft_print_token_array(t_token **token_array)
{
	int i;
	t_token *tmp;

	i = 0;
	while (token_array[i])
	{
		printf("Pointer _array[%d] = %p\n", i, token_array[i]);
		tmp = token_array[i];
		while (tmp)
		{
			printf("liste du p token_array %s \n", tmp->val);

				tmp = tmp->next;
		}
		i++;
	}
}

t_token **create_token_arrays(t_token **tokens, int nbpipes)
{
    t_token *current_token;
	t_token **token_arrays;
	t_token *tmp;
    int i;

	current_token = *tokens;
	i = 0;
	token_arrays = malloc(sizeof(t_token *) * (nbpipes + 1));
	while (current_token)
	{
		token_arrays[i] = current_token;
		while (current_token && current_token->type != TK_TYPE_PIPE)
			current_token = current_token->next;
		i++;
		if (current_token && current_token->next)
		{
			tmp = current_token->next;
			current_token->previous->next = NULL;
			free(current_token);
			current_token = tmp;
		}
	}
	token_arrays[i] = NULL;
	return token_arrays;
}