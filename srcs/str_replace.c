/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarie <mmarie@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:39:29 by svanmarc          #+#    #+#             */
/*   Updated: 2023/12/30 14:05:30 by mmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void    copy_first_part(char *str, char *new_str, int start)
{
    int     i;

    i = 0;
    while (i < start)
    {
        new_str[i] = str[i];
        i++;
    }
}

static int    insert_new_val(char *new_str, char *new_val, int start)
{
    int     i;
    int     j;

    i = start;
    j = 0;
    while (new_val[j])
    {
        new_str[i] = new_val[j];
        i++;
        j++;
    }
    return (i);
}

static void    copy_last_part(char *str, char *new_str, int end, int new_pos)
{
    int     k;

    k = end;
    while (str[k])
    {
        new_str[new_pos] = str[k];
        new_pos++;
        k++;
    }
}

char    *ft_str_replace(char *str, char *new_val, int start, int end)
{
    char    *new_str;
    int     new_pos;

    if (!str || !new_val)
        return (NULL); //????????????????????
    new_str = (char *)ft_calloc(ft_strlen(str) + ft_strlen(new_val) + 1, sizeof(char));
    if (!new_str)
        return (NULL);
    copy_first_part(str, new_str, start);
    new_pos = insert_new_val(new_str, new_val, start);
    copy_last_part(str, new_str, end, new_pos);
    free(str);
    free(new_val);
    return (new_str);
}

char    *ft_str_replace_version_2(char *str, char *new_val, int start, int end)
{

    char *part1 = ft_substr(str, 0, start);
    char *part3 = ft_substr(str, end, ft_strlen(str) - end);

    char *part12 = ft_strjoin(part1, new_val);
    char *part123 = ft_strjoin(part12, part3);

    free(part1);
    free(part3);
    free(part12);

    return (part123);
}




char *ft_strjoin_x3(char *part1,char *part2,char *part3)
{
    char *part12 = ft_strjoin(part1, part2);
    char *part123 = ft_strjoin(part12, part3);
    free(part12);
    return (part123);

}

/*
ft_strjoin_x3_and_free(part1,part2,part3)
{
    ft_strjoin_x3(part1,part2,part3)
    free(part1);
    free(part2);
    free(part3);

    return (part123);

}
*/

char    *ft_str_replace_version_3(char *str, char *new_val, int start, int end)
{
    // end : index du char d'apres !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    char *part1;
    char *part3;
    char *part123;

    part1 = ft_substr(str, 0, start);
    part3 = ft_substr(str, end, ft_strlen(str) - end);
    /*
    char *part3 = ft_substr(str,  8 ,  8       -8);
    char *part3 = ft_substr(str,  8 ,  0);
*/
    if (new_val != NULL)
        part123 = ft_strjoin_x3(part1, new_val, part3);
    else
        part123 = ft_strjoin(part1, part3);

    free(part1);
    free(part3);
   // free(str);
   // free(new_val); // ????

    return (part123);
}




void test_ft_str_replace()
{
    printf("*************** TEST : test_ft_str_replace ***************\n");

    printf ("[%s]  should be [%s]   \n" ,  ft_str_replace_version_3("ABCDEF", "xxx", 1, 3),  "AxxxEF");
    printf ("[%s]  should be [%s]   \n" ,  ft_str_replace_version_3("ABCDEF", "xxx", 0, 2),  "xxxDEF");
    printf ("[%s]  should be [%s]   \n" ,  ft_str_replace_version_3("ABCDEF", "xxx", 3, 6),  "ABCxxx");
    printf ("[%s]  should be [%s]   \n" ,  ft_str_replace_version_3("ABCDEF", "xxxxxx", 1, 3),  "AxxxxxxEF");
    printf ("[%s]  should be [%s]   \n" ,  ft_str_replace_version_3("ABCDEF", "", 0, -1),  "ABCDEF");
    printf ("[%s]  should be [%s]   \n" ,  ft_str_replace_version_3("ABCDEF", "xxx", 1, 3),  "AxxxEF");
    printf ("[%s]  should be [%s]   \n" ,  ft_str_replace_version_3("ABCDEF", "xxx", 1, 3),  "AxxxEF");
    printf ("[%s]  should be [%s]   \n" ,  ft_str_replace_version_3("ABCDEF", "xxx", 1, 3),  "AxxxEF");


    printf("*************** FIN TEST : test_ft_str_replace ***************\n");
}





