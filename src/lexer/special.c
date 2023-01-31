/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:57:47 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/31 17:00:36 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	counter(char *content, char c)
{
	int i;
	int c;

	while(content[i] != '\0')
	{
		if (content[i] == c)
			c++;
		i++;
	}
	return(c);
}

char	hassmol(char *content)
{
	char	*str;
	char	**res;
	int		i;
	int		c;
	
	i = 0;
	c = 0;
	res = ft_calloc(sizeof(char), 3);
	res = ft_split(content, '<');
	res[2] = res[1];
	free(res[1]);
	if (counter(content, '<') == 2)
		res[1] = ft_strdup('<<');
	else
		res[1] = ft_strdup('<');
	return(res);
}

/* char	hassmol(char *content)
{
	char	*str;
	char	**res;
	int		i;
	int		c;
	
	i = 0;
	c = 0;
	res = ft_calloc(sizeof(char), 3);
	while (content[i] != '<')
	{
		str[c] = content[i];
		i++;
		c++;
	}
	str[c] = '\0';
	res[0] = ft_strdup(str);
	ft_bzero(str, ft_strlen(str));
	i++;
	if (content[i] == '<')
	{
		res[1] = ft_strdup('<<');
		i++;
	}
	else
		res[1] = ft_strdup('<');
	c = 0;
	if (content[i] == '\0')
		return(res);
	while (content[i] != '\0')
	{
		str[c] = content[i];
		i++;
		c++;
	}
	str[c] = '\0';
	res[2] = ft_strdup(str);
	return(res);
} */

char	haspip(char *content)
{
	char	*str;
	char	**res;
	int		i;
	int		c;
	
	i = 0;
	c = 0;
	res = ft_calloc(sizeof(char), 3);
	while (content[i] != '|')
	{
		str[c] = content[i];
		i++;
		c++;
	}
	str[c] = '\0';
	res[0] = ft_strdup(str);
	res[1] = ft_strdup('|');
	ft_bzero(str, ft_strlen(str));
	i++;
	c = 0;
	if (content[i] == '\0')
		return(res);
	while (content[i] != '\0')
	{
		str[c] = content[i];
		i++;
		c++;
	}
	str[c] = '\0';
	res[2] = ft_strdup(str);
	return(res);
}

char	**special(char *content)
{
	char	**str;
	int		pos;

	str = ft_calloc(sizeof(char), 3);
	pos = 0;
	if (strchr(content, '|'))
		str = haspip(content);
	if (strchr(content, '<'))
		str = hassmol(content);
	if (strchr(content, '>'))
		str = hasbig(content);
	else
		str[0] = ft_strdup(content);
	return(str);
}

t_list	*lstspecial(t_list *lst)
{
	t_list	*new;
	t_list	*out;
	t_list	*tail;
	char	**res;
	int		i;
	
	i = 0;
	out = NULL;
	new = ft_lstnew(f(lst->content));
	ft_lstadd_back(&out, new);
	tail = out;
	lst = lst ->next;
	while (lst)
	{
		res = special(lst->content);
		while(res[i] != '\0')
		{
			new = ft_lstnew(res[i]);
			ft_lstadd_back(&tail, new);
			tail = tail->next;
			i++;
		}
		free(res);
		lst = lst ->next;
	}
	return (out);
}
