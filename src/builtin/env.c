/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:46 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 13:26:51 by fsandel          ###   ########.fr       */
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
		ft_putendl_fd("minishell: env: no arguments for env", 2);
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
