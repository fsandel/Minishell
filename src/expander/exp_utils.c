/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:26:12 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/28 18:38:39 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ow(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || ft_strlen(str) == 0)
		return (FALSE);
	while (str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

void	app(t_pars **pars, t_x *x)
{
	x->str = str_append(x->str, pars[x->s]->cmd[x->n][x->i++]);
}

void	pute(t_x *x)
{
	char	*tmp;
	char	*tmpp;

	x->i += 2;
	tmp = ft_strdup(ft_itoa(g_error));
	if (x->str == NULL)
		x->str = ft_strdup(tmp);
	else
	{
		tmpp = ft_strjoin(x->str, tmp);
		free(x->str);
		x->str = ft_strdup(tmpp);
		free(tmpp);
	}
	free(tmp);
}
