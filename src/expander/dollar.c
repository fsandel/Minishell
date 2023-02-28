/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:06:55 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/28 18:39:12 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar(t_pars **pars, t_x *x)
{
	if (ft_isalpha(pars[x->s]->cmd[x->n][x->i + 1]) == TRUE
		||check(pars[x->s]->cmd[x->n][x->i + 1], "_") == TRUE)
	{
		x->i++;
		make_dollar(pars, x);
	}
	else
	{
		if (pars[x->s]->cmd[x->n][x->i + 1] == '?')
			pute(x);
		else if (!check(pars[x->s]->cmd[x->n][x->i + 1], "\"\'"))
			app(pars, x);
		else if (check(pars[x->s]->cmd[x->n][x->i + 1], "\"\'")
					&& check(pars[x->s]->cmd[x->n][x->i - 1], "\"\'"))
			app(pars, x);
		else
			x->i++;
	}
}

void	splitappend(t_pars **pars, t_x *x, char **s, char *exp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (x->pd == TRUE && exp[0] != ' ')
	{
		while (s[i][j])
			x->o[last(x->o) - 1] = str_append(x->o[last(x->o) - 1], s[i][j++]);
		free(s[i]);
		i++;
		x->pd = FALSE;
	}
	while (s[i])
	{
		x->o = array_add_line(x->o, s[i]);
		free(s[i]);
		i++;
	}
	free (s);
	if (exp[ft_strlen(exp)] != ' ')
		x->d = TRUE;
	if (pars[x->s]->cmd[x->n][x->i] == '$')
		x->pd = TRUE;
	x->str = NULL;
}

int	checkbrk(t_pars **pars, t_x *x)
{
	if (check(pars[x->s]->cmd[x->n][x->i], "$\n\\\"\'/?") == FALSE
		&& is_whitespace(pars[x->s]->cmd[x->n][x->i]) == FALSE
		&& pars[x->s]->cmd[x->n][x->i] != '\0')
		return (FALSE);
	else
		return (TRUE);
}

char	*find_dollar(t_pars **pars, t_x *x)
{
	char	*tmp;
	char	*tmpp;
	int		j;
	int		i;

	j = 0;
	i = 0;
	tmp = ft_calloc(sizeof(char), ft_strlen(pars[x->s]->cmd[x->n]));
	while (checkbrk(pars, x) == FALSE)
			tmp[j++] = pars[x->s]->cmd[x->n][x->i++];
	tmp[j] = '\0';
	tmpp = array_get_line(pars[x->s]->env, tmp);
	if (tmpp != NULL && ft_strlen(tmpp) && ow(tmpp) == FALSE)
	{
		x->i--;
		set_str(x);
		x->i++;
	}
	free (tmp);
	return (tmpp);
}

void	make_dollar(t_pars **pars, t_x *x)
{
	char	*expanded;
	char	**split;

	split = NULL;
	expanded = find_dollar(pars, x);
	if (expanded != NULL && ft_strlen(expanded) && ow(expanded) == FALSE)
	{
		split = ft_split(expanded, ' ');
		splitappend(pars, x, split, expanded);
		if (expanded[ft_strlen(expanded) - 1] == ' ')
			x->d = FALSE;
	}
	if (ow(expanded) == TRUE)
		x->str = str_append(x->str, ' ');
	free(expanded);
}
