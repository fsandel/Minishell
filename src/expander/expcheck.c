/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:01:55 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/21 12:10:09 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_one(t_pars **pars, int set, int num, int i)
{
	if (((pars[set]->cmd[num][i] == '\"'
			&& pars[set]->cmd[num][i - 1] != '\\')
			| (pars[set]->cmd[num][i] == '\''))
			&& pars[set]->cmd[num][i] != '\0')
		return (TRUE);
	else
		return (FALSE);
}

int	check_two(t_pars **pars, int set, int num, int i)
{
	if (pars[set]->cmd[num][i] == '\"'
		&& pars[set]->cmd[num][i - 1] == '\\')
		return (TRUE);
	else
		return (FALSE);
}

int	check_three(t_pars **pars, int set, int num, int i)
{
	if (check(pars[set]->cmd[num][i], "\"\'") == FALSE
			|| (pars[set]->cmd[num][i] == '\"'
			&& pars[set]->cmd[num][i - 1] == '\\'))
		return (TRUE);
	else
		return (FALSE);
}
