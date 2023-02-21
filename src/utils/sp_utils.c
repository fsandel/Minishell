/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:28:07 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/21 21:04:07 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	counter(char *content, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (content[i] != '\0')
	{
		if (content[i] == c)
		{
			j++;
		}
		i++;
	}
	return (j);
}

int	check(char input, char const *it)
{
	int	c;

	c = 0;
	while (it[c])
	{
		if (it[c] == input)
			return (TRUE);
		c++;
	}
	return (FALSE);
}

int	errorput(t_pars **pars, int set, int num, t_ph *ph)
{
	char *c;
	char *tmp;
	
	c = ft_itoa(g_error);
	free(pars[set]->cmd[num]);
	tmp = ft_strjoin(ph->pre, c);
	pars[set]->cmd[num] = ft_strjoin(tmp, ph->post);
	free(c);
	free(tmp);
	free(ph->str);
	free(ph->pre);
	free(ph->post);
	return (1);
}
