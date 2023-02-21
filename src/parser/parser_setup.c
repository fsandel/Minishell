/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:00:18 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 14:59:58 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*setup_single_pars(char **env, t_list *list)
{
	t_pars	*pars;

	pars = ft_calloc(1, sizeof(t_pars));
	pars->env = env;
	pars->err = 2;
	pars->in = 0;
	pars->out = 1;
	pars->amount = 0;
	pars->error = 0;
	pars->heredoc = 0;
	pars->list = list;
	return (pars);
}

t_pars	**setup_struct(t_list *list, char **env)
{
	t_pars	**pars;
	int		commands;
	int		i;
	int		len;

	commands = count_commands(list);
	pars = ft_calloc(commands, sizeof(t_pars *));
	i = 0;
	while (i < commands)
	{
		pars[i] = setup_single_pars(env, list);
		pars[i]->total_cmd = commands;
		pars[i]->index = i;
		len = 0;
		while (list && ft_strncmp(list->content, "|", 2))
		{
			list = list->next;
			len++;
		}
		if (list)
			list = list->next;
		pars[i]->cmd = ft_calloc(len + 1, sizeof(char *));
		i++;
	}
	return (pars);
}
