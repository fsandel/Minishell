/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:06:55 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/28 16:09:10 by pgorner          ###   ########.fr       */
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
	return(i);
}

int	ow(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return(FALSE);
	while (str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '\0')
		return(TRUE);
	else
		return(FALSE);
}

void	splitappend(t_pars **pars, t_x *x, char **split, char *exp)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	if (x->pd == TRUE && exp[0] != ' ')
	{
		//printf("xpd true\n");
		while(split[i][j])
			x->out[last(x->out) - 1] = str_append(x->out[last(x->out) - 1], split[i][j++]);
		i++;
		x->pd = FALSE;
	}
	while (split[i])
	{
		x->out = array_add_line(x->out, split[i]);
		//printf("split%sxout%s\n", split[i], x->out[last(x->out) - 1]);
		i++;
	}
	//printf("CHECK:%c\n", pars[x->s]->cmd[x->n][x->i]);
	if (exp[ft_strlen(exp)] != ' ')
		x->d = TRUE;
	if (pars[x->s]->cmd[x->n][x->i] == '$')
		x->pd = TRUE;
	//printf("CHEKD:%i\n", x->d);
	x->str = NULL;
}

void	make_dollar(t_pars **pars, t_x *x)
{
	char	*expanded;
	char	**split;
	
	split = NULL;
	//printf("MAKEDOLLAR----------\n");
	expanded = find_dollar(pars, x);
	//printf("EXPANDED%s\n", expanded);
	//printf("HERE\n");
	
	if (expanded != NULL && ft_strlen(expanded) && ow(expanded) == FALSE)
	{
			split = ft_split(expanded, ' ');
			splitappend(pars, x, split, expanded);
			if (expanded[0] == ' ')
				x->d = FALSE;
			if (expanded[ft_strlen(expanded) - 1] == ' ')
				x->d = FALSE;
	}
	if (ow(expanded) == TRUE)
	{
		x->str = str_append(x->str, ' ');
	}
/* 	printf("MAKEDOLLAR________\n"); */
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
	while (check(pars[x->s]->cmd[x->n][x->i], "$\n\\\"\'/") == FALSE
		&& is_whitespace(pars[x->s]->cmd[x->n][x->i]) == FALSE
		&& pars[x->s]->cmd[x->n][x->i] != '\0'
		&& check(pars[x->s]->cmd[x->n][x->i], "\"\'") == FALSE)
			tmp[j++] = pars[x->s]->cmd[x->n][x->i++];
	tmp[j] = '\0';
	tmpp = array_get_line(pars[x->s]->env, tmp);
	if (tmpp != NULL && ft_strlen(tmpp) && ow(tmpp) == FALSE)
	{
		x->i--;
		set_str(pars, x);
		x->i++;
	}
	free(tmp);
/* 	if (!ft_strlen(tmpp))
		return(NULL); */
	return(tmpp);
}