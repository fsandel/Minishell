/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:58:18 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/20 19:18:52 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**special(char *content)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_calloc(sizeof(char), 3);
	if (content[0] != '\'' && content[0] != '\"')
	{
		if (ft_strchr(content, '|'))
			str = haspipe(content);
		if (ft_strchr(content, '<'))
			str = smallerthan(content);
		if (ft_strchr(content, '>'))
			str = biggerthan(content);
		else
		{
		str[0] = ft_strdup(content);
		str[1] = NULL;
		}
	}
	else
	{
		str[0] = ft_strdup(content);
		str[1] = NULL;
	}
	return (str);
}

t_list	*lstspecial(t_list *lst)
{
	t_list	*new;
	t_list	*out;
	t_list	*tail;
	char	**res;
	int		i[2];

	i[0] = 0;
	out = NULL;
	while (lst)
	{
		i[1] = -1;
		res = special(lst->content);
		while (res[++i[1]] != NULL)
		{
			new = ft_lstnew(res[i[1]]);
			if (i[0] == 0)
			{
				ft_lstadd_back(&out, new);
				tail = out;
			}
			else
			{
				ft_lstadd_back(&tail, new);
				tail = tail->next;
			}
		}
		i[0]++;
		lst = lst ->next;
	}
	return (out);
}
