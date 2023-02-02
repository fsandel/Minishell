/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:58:18 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/01 17:28:50 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**special(char *content)
{
	char	**str;
	int		pos;

	pos = 0;
	str = ft_calloc(sizeof(char), 3);
	if (ft_strchr(content, '|'))
		return(str = haspipe(content));
	else if (ft_strchr(content, '<'))
		return(str = smallerthan(content));
	if (ft_strchr(content, '>'))
		return(str = biggerthan(content));
	else
		return(str = ft_split(content, ' '));
}

t_list	*lstspecial(t_list *lst)
{
	t_list	*new;
	t_list	*out;
	t_list	*tail;
	char	**res;
	int		i;
	int		c;
	
	i = 0;
	c = 0;
	out = NULL;
	while (lst)
	{
		i = 0;
		res = special(lst->content);
		while(res[i] != NULL)
		{
			new = ft_lstnew(res[i]);
			if (c == 0)
			{
			ft_lstadd_back(&out, new);
			tail = out;
			}
			else
			{
			ft_lstadd_back(&tail, new);
			tail = tail->next;
			}
			i++;
		}
		c++;
		lst = lst ->next;
	}
	return (out);
}
