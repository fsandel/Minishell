/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:57:47 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/31 17:52:49 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	counter(char *content, char c)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(content[i] != '\0')
	{
		if (content[i] == '<')
			j++;
		i++;
	}
	return(j);
}

char	**hassmol(char *content)
{
	char	**res;
	int i = counter(content, '<');

	res = ft_splitspec(content, '<');
	if (res[1] != NULL)
		res[2] = ft_strdup(res[1]);
	if (counter(content, '<') == 2)
		res[1] = ft_strdup("<<");
	else
		res[1] = ft_strdup("<");
/* 	printf("----------prereturn\n");
	printf("0:%s\n", res[0]);
	printf("1:%s\n", res[1]);
	printf("2:%s\n", res[2]); */
	return (res);
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

char	**haspip(char *content)
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
	res[1] = ft_strdup("|");
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
/* 	printf("1:%s\n", res[0]);
	printf("2:%s\n", res[1]);
	printf("3:%s\n", res[2]); */
	return(res);
}

char	**special(char *content)
{
	char	**str;
	int		pos;

/* 	if (ft_strlen(content) > 1)
	{ */
	str = ft_calloc(sizeof(char), 3);
	pos = 0;
	if (ft_strchr(content, '|'))
		str = haspip(content);
	if (ft_strchr(content, '<'))
		str = hassmol(content);
/* 	if (ft_strchr(content, '>'))
		str = hasbig(content); */
	else
		str[0] = ft_strdup(content);
/* 	}
	else
		str = ft_split(content, ' '); */
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
	new = ft_lstnew(lst->content);
	ft_lstadd_back(&out, new);
	tail = out;
	lst = lst ->next;
	while (lst)
	{
		i = 0;
		res = special(lst->content);
		while(res[i] != NULL)
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
