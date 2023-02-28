/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:58 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 13:35:51 by fsandel          ###   ########.fr       */
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
		if (ft_isalpha(pars->cmd[i][0]) && !str_is_alpha_num(pars->cmd[i]))
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
