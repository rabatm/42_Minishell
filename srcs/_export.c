/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:17:27 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/11 10:47:06 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_str_starts_with(char *str, char *start);
char **ft_tab_dup(char **tab);
void ft_free_tab(char **tab);
char **free_tab_and_return_null(char **tab);
char **ft_add_str_to_tab(t_data *data, char *entry);
char *ft_strdup(const char *str);
void *ft_calloc(size_t nmemb, size_t size);
char *ft_strchr(const char *s, int c);

char *extract_key_from_arg(char *arg)
{
    char *key;
    char *value;
    char    *copy;

    copy = ft_strdup(arg);
    if (!copy)
        return (NULL);

    value = ft_strchr(copy, '=');
    if (value)
    {
        *value = '\0';
        key = ft_strdup(copy);
        *value = '=';
    }
    else
        key = ft_strdup(copy);
    return (key);
}

void    add_new_env_var(t_data *data, char *arg)
{
    int     env_id;

    env_id = 0;
    while (data->env[env_id])
        env_id++;
    data->env = ft_add_str_to_tab(data, arg);
    data->env[env_id] = ft_strdup(arg);
    if (!data->env[env_id])
        return ;
    data->env[env_id + 1] = NULL;
}

int     update_existing_var(t_data *data, char *arg, char *key, char *update_value)
{
    int env_id;

    env_id = 0;
    while (data->env[env_id])
    {
        if (ft_str_starts_with(data->env[env_id], key))
        {
            if (update_value)
            {
                free(data->env[env_id]);
                data->env[env_id] = ft_strdup(arg);
            }
            return (1);
        }
        env_id++;
    }
    return (0);
}

void    update_env(t_data *data, char *arg)
{
    char *key;
    char *value;
    int updated;

    key = extract_key_from_arg(arg);
    value = ft_strchr(arg, '=');
    if (value)
        value++;
    if (!data || !data->env || !key || !arg)
    {
        free(key);
        return ;
    }
    updated = update_existing_var(data, arg, key, value);
    if (!updated)
        add_new_env_var(data, arg);
    free(key);
}

int     exec_export(int argc, char **argv, t_data *data)
{
    int arg_id;
    int i;

    if (!data || !data->env)
        return (0);
    if (argc == 1)
    {
        i = 0;
        while (data->env[i])
        {
            printf("export %s\n", data->env[i]);
            i++;
        }
    }
    else
    {
        arg_id = 1;
        while (arg_id < argc)
        {
            update_env(data, argv[arg_id]);
            arg_id++;
        }
    }
    return (0);
}


/*
int    main()
{
    char    *test_env[] = {"VAR1=original1", "VAR2=original2", "VAR3", NULL};
    t_data  data;
    data.env = ft_tab_dup(test_env);

    printf("\nafficher une variable sans value\n");
    int i = 0;
    printf("avant export:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    char    *args3[] = {"export", "VAR3", NULL};
    exec_export(2, args3, &data);
    i = 0;
    printf("apres export:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }

    i = 0;

    printf("\najouter nouvelle variable:\n");
    printf("avant export:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    char    *args1[] = {"export", "VAR4=new4", NULL};
    exec_export(2, args1, &data);
    i = 0;
    printf("apres export:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    i = 0;

    printf("\n\nmodifier variable existante:\n");
    printf("avant export:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }
    char    *args2[] = {"export", "VAR1=new1", NULL};
    exec_export(2, args2, &data);
    i = 0;
    printf("apres export:\n");
    while (data.env[i])
    {
        printf("%s\n", data.env[i]);
        i++;
    }




    printf("\nafficher toutes les variables exportees:\n");
    exec_export(1, (char *[]){"export"}, &data);

    ft_free_tab(data.env);
    return (0);
}

int     ft_str_starts_with(char *str, char *start)
{
    int i;

    i = 0;
    while (str[i] && start[i])
    {
        if (str[i] != start[i])
            return (0);
        i++;
    }
    if (start[i])
        return (0);
    return (1);
}

char    **ft_tab_dup(char **tab)
{
    int i;
    int j;
    char **new;

    if (!tab)
        return (NULL);
    i = 0;
    while (tab[i])
        i++;
    new = (char **)ft_calloc(i + 1, sizeof(char *));
    if (!new)
        return (NULL);
    j = 0;
    while (j < i)
    {
        new[j] = ft_strdup(tab[j]);
        if (!new[j])
            return (free_tab_and_return_null(new));
        j++;
    }
    return (new);
}

void    ft_free_tab(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return ;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

char    **free_tab_and_return_null(char **tab)
{
    ft_free_tab(tab);
    return (NULL);
}

char    **ft_add_str_to_tab(t_data *data, char *entry)
{
    int i;
    char **new;

    i = 0;
    while (data->env[i])
        i++;
    new = (char **)ft_calloc(i + 2, sizeof(char *));
    if (!new)
        return (NULL);
    i = 0;
    while (data->env[i])
    {
        new[i] = ft_strdup(data->env[i]);
        if (!new[i])
            return (free_tab_and_return_null(new));
        i++;
    }
    new[i] = ft_strdup(entry);
    if (!new[i])
        return (free_tab_and_return_null(new));
    return (new);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (i < size - 1 && i < src_len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = 0;
}

size_t	ft_strlen(const char *s)
{
    size_t	len;

    len = 0;
    while (*s++)
        len++;
    return (len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((total_size / size) != nmemb)
		return (0);
	ptr = (void *)malloc(total_size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, total_size);
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*p;

	len = ft_strlen(s) + 1;
	p = malloc(len);
	if (p != 0)
		ft_strlcpy(p, s, len);
	return (p);
}
*/

