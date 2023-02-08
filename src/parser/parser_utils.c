/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:07:20 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/08 14:43:08 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_pars **pars)
{
	int	total;
	int	i;
	int	j;

	if (!pars)
		return ;
	total = pars[0]->total_cmd;
	i = 0;
	while (i < total)
	{
		j = 0;
		while (pars[i]->cmd[j])
			free(pars[i]->cmd[j++]);
		free(pars[i]->cmd);
		free(pars[i]);
		i++;
	}
	free(pars);
}
