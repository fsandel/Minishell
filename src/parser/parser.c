/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:05 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 16:05:22 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	**fill_struct(t_list *list, t_pars **pars);

t_pars	**parser(t_list *list, char **env)
{
	t_pars	**pars;

	pars = setup_struct(list, env);
	pars = fill_struct(list, pars);
	display_pars(pars);
	return (pars);
}

t_pars	**fill_struct(t_list *list, t_pars **pars)
{
	int	line;
	int	fd;
	int	i;

	i = 0;
	line = 0;
	while (list)
	{
		if (list->content && !ft_strncmp(list->content, "|", 2))
		{
			i = 0;
			line++;
		}
		else if (list->content && !ft_strncmp(list->content, ">", 2))
		{
			if (!list->next)
				return (pars);
			redirect_out(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "2>", 3))
		{
			if (!list->next)
				return (pars);
			redirect_err(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "2>&1", 5))
		{
			if (!list->next)
				return (pars);
			pars[line]->err = pars[line]->out;
			list = list->next;
		}
		//implement > file 2>&1
		else if (list->content && !ft_strncmp(list->content, "&>", 3))
		{
			if (!list->next)
				return (pars);
			list = list->next;
			redirect_both(list, pars[line]);
		}
		else if (list->content && !ft_strncmp(list->content, ">>", 3))
		{
			if (!list->next)
				return (pars);
			append_out(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "2>>", 4))
		{
			if (!list->next)
				return (pars);
			append_err(list, pars[line]);
			list = list->next;
		}
		//implement >> file 2>&1
		else if (list->content && !ft_strncmp(list->content, "&>>", 4))
		{
			if (!list->next)
				return (pars);
			append_both(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "&>>", 4))
		{
			if (!list->next)
				return (pars);
			append_both(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "&>>", 4))
		{
			if (!list->next)
				return (pars);
			append_both(list, pars[line]);
			list = list->next;
		}
		else if (list->content && !ft_strncmp(list->content, "<", 2))
		{
			if (!list->next)
				return (pars);
			redirect_in(list, pars[line]);
			list = list->next;
			ft_printf("here\n");
		}
		else if (list->content && !ft_strncmp(list->content, "<<", 3))
		{
			if (!list->next)
				return (pars);
			here_doc(list, pars[line]);
			list = list->next;
		}
		else
		{
			if (list->content)
				pars[line]->cmd[pars[line]->amount++]
					= ft_strdup(list->content);
		}
		list = list->next;
	}
	return (pars);
}
