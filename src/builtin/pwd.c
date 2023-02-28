/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:55 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 13:26:35 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_pwd(t_pars *pars)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(pars->cmd[0]);
		exit(1);
	}
	else
	{
		ft_putendl_fd(wd, STDOUT);
		free(wd);
	}
	g_error = 0;
}
