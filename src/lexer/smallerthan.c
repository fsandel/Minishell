/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallerthan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:22:13 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/01 16:47:23 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**smallerthanback(char *content)
{
	char	**res;

	res = ft_split_special(content, '<');
	if (res[1] != NULL)
		res[2] = ft_strdup(res[1]);
	if (counter(content, '<') == 2)
		res[1] = ft_strdup("<<");
	else
		res[1] = ft_strdup("<");
	return(res);
}
char	**smallerthanfront(char *content)
{
	char	**res;

	res = ft_split_special(content, '<');
	res[1] = ft_strdup(res[0]);
	if (counter(content, '<') == 2)
		res[0] = ft_strdup("<<");
	else
		res[0] = ft_strdup("<");
	return(res);
}
char	**smallerthanmid(char *content)
{
	char	**res;

	res = ft_split_special(content, '<');
    res[2] = ft_strdup(res[1]);
	if (counter(content, '<') == 2)
		res[1] = ft_strdup("<<");
	else
		res[1] = ft_strdup("<");
	return(res);
}
char	**smallerthanall(char *content)
{
	char	**res;

	res = ft_split_special(content, '<');
	res[1] = ft_strdup(res[0]);
	if (content[0] == '<' && content[1] == '<')
		res[0] = ft_strdup("<<");
    else
        res[0] = ft_strdup("<");
	if (content[ft_strlen(content)] == '<'
        &&content[ft_strlen(content) - 1] == '<')
		res[1] = ft_strdup("<<");
    else
		res[1] = ft_strdup("<");
	return(res);
}

char	**smallerthan(char *content)
{
	char	**res;
/* 	printf("--------------------------------------------------\n");
	printf("CONTENT:%s:\n", content);
	printf("COUNTER: %zu STRLEN: %zu\n", counter(content, '<'), ft_strlen(content)); */
	if ((counter(content, '<')) != (ft_strlen(content))
		&& (content[0] != '\'' || content[0] != '\"'))
	{
		if (content[0] == '<'
		&& content[ft_strlen(content) - 1] == '<')
			res = smallerthanall(content);
		else if (content[0] == '<')
			res = smallerthanfront(content);
		else if (content[ft_strlen(content) - 1] == '<')
			res = smallerthanback(content);
		else if (content[0] != '<'
		&& content[ft_strlen(content) - 1] != '<')
			res = smallerthanmid(content);
	}
	else if (counter(content, '<') == ft_strlen(content))
		res = ft_split_special(content, ' ');
	return (res);
}