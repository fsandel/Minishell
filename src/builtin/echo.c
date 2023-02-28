/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:44 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 13:24:11 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_echo(t_pars *pars)
{
	int	line;
	int	i;

	i = 1;
	line = 1;
	while (pars->cmd[i] && !ft_strncmp(pars->cmd[i], "-n", 3))
	{
		line = 0;
		i++;
	}
	while (pars->cmd[i])
	{
		ft_putstr_fd(pars->cmd[i++], STDOUT);
		if (pars->cmd[i])
			ft_putchar_fd(' ', STDOUT);
	}
	if (line)
		ft_putchar_fd('\n', STDOUT);
	g_error = 0;
}
