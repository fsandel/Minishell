/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biggerthan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:40:58 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/20 19:31:09 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**biggerthanback(char *content)
{
	char	**res;

	res = ft_split_special(content, '>');
	if (res[1] != NULL)
		res[2] = ft_strdup(res[1]);
	if (counter(content, '>') == 2)
		res[1] = ft_strdup(">>");
	else
		res[1] = ft_strdup(">");
	return (res);
}

char	**biggerthanfront(char *content)
{
	char	**res;

	res = ft_split_special(content, '>');
	res[1] = ft_strdup(res[0]);
	if (counter(content, '>') == 2)
		res[0] = ft_strdup(">>");
	else
		res[0] = ft_strdup(">");
	return (res);
}

char	**biggerthanmid(char *content)
{
	char	**res;

	res = ft_split_special(content, '>');
	res[2] = ft_strdup(res[1]);
	if (counter(content, '>') == 2)
		res[1] = ft_strdup(">>");
	else
		res[1] = ft_strdup(">");
	return (res);
}

char	**biggerthanall(char *content)
{
	char	**res;

	res = ft_split_special(content, '>');
	res[1] = ft_strdup(res[0]);
	if (content[0] == '>' && content[1] == '>')
		res[0] = ft_strdup(">>");
	else
		res[0] = ft_strdup(">");
	if (content[ft_strlen(content)] == '>'
		&&content[ft_strlen(content) - 1] == '>')
		res[1] = ft_strdup(">>");
	else
		res[1] = ft_strdup(">");
	return (res);
}

char	**biggerthan(char *content)
{
	char	**res;

	if (counter(content, '>') != (ft_strlen(content)))
	{
		if (content[0] == '>'
			&& content[ft_strlen(content) - 1] == '>')
			return (res = biggerthanall(content));
		else if (content[0] == '>')
			return (res = biggerthanfront(content));
		else if (content[ft_strlen(content) - 1] == '>')
			return (res = biggerthanback(content));
		else if (content[0] != '>'
			&& content[ft_strlen(content) - 1] != '>')
			return (res = biggerthanmid(content));
	}
	else if (counter(content, '>') == ft_strlen(content))
	res = ft_split_special(content, ' ');
	return (res);
}
