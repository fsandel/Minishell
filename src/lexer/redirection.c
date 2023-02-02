/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:10:44 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/01 17:38:57 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
char **front(char *content, char *sign)
{
    char **res;
    
    res = ft_split_special(content, sign);
    res[1] = ft_strdup(res[0]);
	if (counter(content, '>') == 2)
		res[0] = ft_strdup(">>");
	else
		res[0] = ft_strdup(">");
	return(res);
}

char    **redirection(char *content)
{
    char **res;

    if (ft_strchr(content, "2>") 
        && ft_strchr(content, "2>>"))
        res = two(content);
    else if(ft_strchr(content, "&>") 
        && ft_strchr(content, "&>>"))
        res = and(content);
    else if(ft_strchr(content, "2&>1"))
        res = twoandone(content);
    return(res);
} */