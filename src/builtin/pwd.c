/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:55 by fsandel           #+#    #+#             */
/*   Updated: 2023/03/01 19:08:33 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_pwd(t_pars *pars)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
	{
		ft_putstr_fd("minishell: ", STDERR);
		perror(pars->cmd[0]);
		rl_clear_history();
		exit(1);
	}
	else
	{
		ft_putendl_fd(wd, STDOUT);
		free(wd);
	}
	g_error = 0;
}
