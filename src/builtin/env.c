/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:46 by fsandel           #+#    #+#             */
/*   Updated: 2023/03/01 19:08:47 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_env(t_pars *pars)
{
	int		i;
	char	*ptr;

	i = 0;
	if (pars->amount > 1)
	{
		ft_putendl_fd("minishell: env: no arguments for env", STDERR);
		rl_clear_history();
		exit(1);
	}
	while (pars->env[i])
	{
		ptr = ft_strchr(pars->env[i], '=');
		if (ptr && ptr[0] == '=')
			ft_putendl_fd(pars->env[i], STDOUT);
		i++;
	}
	g_error = 0;
}
