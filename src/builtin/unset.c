/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:58 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 18:41:23 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**b_unset(t_pars *pars)
{
	int	i;

	g_error = 0;
	i = 1;
	while (pars->cmd[i])
	{
		if ((ft_isalpha(pars->cmd[i][0]) || pars->cmd[i][0] == '_')
			&& !str_is_alpha_num(pars->cmd[i]) && pars->cmd[i][0])
			pars->env = arr_del_line(pars->env, pars->cmd[i]);
		else
		{
			ft_err_print("minishell: unset: '%s': not a valid identifier\n",
				pars->cmd[i], NULL, NULL);
			g_error = 1;
		}
		i++;
	}
	return (pars->env);
}
