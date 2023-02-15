/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:05 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/15 10:57:49 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	**fill_struct(t_list *list, t_pars **pars);

t_pars	**parser(t_list *list, char **env)
{
	t_pars	**pars;

	pars = setup_struct(list, env);
	pars = fill_struct(list, pars);
	//display_pars(pars);
	return (pars);
}

t_list	*err_to_out(t_pars *pars, t_list *list)
{
	pars->err = pars->out;
	if (list->next)
		return (list->next);
	else
		return (list);
}

t_pars	**fill_struct(t_list *list, t_pars **pars)
{
	t_c	c;

	c = (t_c){.i = 0, .line = 0};
	while (list)
	{
		if (list && list->content && !ft_strncmp(list->content, "|", 2))
			c = (t_c){.i = 0, .line = c.line + 1};
		else if (list && list->content && !ft_strncmp(list->content, ">", 2))
			list = redirect_out(list, pars[c.line]);
		else if (list && list->content && !ft_strncmp(list->content, ">>", 3))
			list = append_out(list, pars[c.line]);
		else if (list && list->content && !ft_strncmp(list->content, "<", 2))
			list = redirect_in(list, pars[c.line]);
		else if (list && list->content && !ft_strncmp(list->content, "<<", 3))
		{
			list = here_doc(list, pars[c.line]);
			if (pars[c.line])
				return (free_struct(pars), NULL);
		}
		else
			if (list && list->content)
				pars[c.line]->cmd[pars[c.line]->amount++] = ft_strdup(list->content);
		if (list)
		list = list->next;
	}
	return (pars);
}
