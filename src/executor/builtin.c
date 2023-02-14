/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:46:36 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/13 20:38:59 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(t_pars *pars)
{
	if (!pars || !pars->cmd[0])
		return ;
	if (!ft_strncmp(pars->cmd[0], "echo", 5))
		b_echo(pars);
	if (!ft_strncmp(pars->cmd[0], "cd", 3))
		b_cd(pars);
	if (!ft_strncmp(pars->cmd[0], "pwd", 4))
		b_pwd(pars);
	if (!ft_strncmp(pars->cmd[0], "export", 7))
		b_export(pars);
	if (!ft_strncmp(pars->cmd[0], "unset", 6))
		b_unset(pars);
	if (!ft_strncmp(pars->cmd[0], "env", 4))
		b_env(pars);
	if (!ft_strncmp(pars->cmd[0], "exit", 5))
		exit(0);
}
