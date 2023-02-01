/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:50:06 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/01 16:48:26 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pipeback(char *content)
{
	char	**res;
	
	res = ft_split_special(content, '|');
	res[1] = ft_strdup("|");
	return(res);
}

char	**pipefront(char *content)
{
	char	**res;
	
	res = ft_split_special(content, '|');
	res[1] = ft_strdup(res[0]);
	ft_bzero(res[0], ft_strlen(res[0]));
	res[0] = ft_strdup("|");
	return(res);
}

char	**pipemid(char *content)
{
	char	**res;

	res = ft_split_special(content, '|');
    res[2] = ft_strdup(res[1]);
	res[1] = ft_strdup("|");
	return(res);
}

char	**pipeall(char *content)
{
	char	**res;
	
	res = ft_split_special(content, '|');
	res[1] = ft_strdup(res[0]);
    res[0] = ft_strdup("|");
	res[2] = ft_strdup("|");
	return(res);
}

char	**haspipe(char *content)
{
	char	**res;

	if ((counter(content, '|')) != (ft_strlen(content) - 1)
		&& (content[0] != '\'' || content[0] != '\"'))
	{
		if (content[0] == '|')
			res = pipefront(content);
		if (content[ft_strlen(content) - 1] == '|')
			res = pipeback(content);
		if (content[0] == '|'
		&& content[ft_strlen(content) - 1] == '|')
			res = pipeall(content);
		if (content[0] != '|'
		&& content[ft_strlen(content) - 1] != '|')
			res = pipemid(content);
	}
	else/* (counter(content, '|') == ft_strlen(content) -1) */
		res = ft_split_special(content, ' ');
	return (res);
}
