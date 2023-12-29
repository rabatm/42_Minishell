#include "../includes/minishell.h"

void	ft_cr_newlist(int *token_count, t_token ***token_arrays, int array_count, t_token_list *temp_list)
{
	t_token **current_array;
	int	i;

	i = 0;
	current_array = malloc(sizeof(t_token *) * (*token_count + 1));
	while (i < *token_count)
    {
		current_array[i] = temp_list->token;
		t_token_list *next = temp_list->next;
		free(temp_list);
		temp_list = next;
	}
	current_array[*token_count] = NULL; // Terminer le tableau avec NULL
	token_arrays[array_count++] = current_array;
	temp_list = NULL;
	*token_count = 0;
	i++;
}

void	add_token_tolist(t_token_list **temp_list, t_token *tokens)
{
	t_token_list *new_node;

	new_node = malloc(sizeof(t_token_list));
	new_node->token = tokens;
	new_node->next = *temp_list;
	*temp_list = new_node;
}

t_token ***create_token_arrays(t_token *tokens, int nbpipes)
{
    t_token_list *temp_list;
    t_token ***token_arrays;
    int array_count;
    int token_count;

	token_arrays = malloc(sizeof(t_token **) * (nbpipes + 2));
	temp_list = NULL;
	array_count = 0;
	token_count = 0;
	while (tokens)
	{
		if (tokens->type == TK_TYPE_PIPE || !tokens->next)
		{
			ft_cr_newlist(&token_count, token_arrays, array_count, temp_list);
		}
		else
		{
			add_token_tolist(&temp_list, tokens);
			token_count++;
		}
			fprintf(stderr, "token_ c = %d\n", token_count);
		tokens = tokens->next;
	}
	fprintf(stderr, "token_arrays[i] = %d\n", 2);
	token_arrays[array_count] = NULL; // Terminer token_arrays avec NULL
	return token_arrays;
}