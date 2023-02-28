/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:49 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 15:13:44 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_message(t_pars **pars)
{
	if (isatty(STDIN))
	{
		if (pars[0]->total_cmd == 1)
			ft_putstr_fd("exit\n", STDOUT);
	}
}

char	**b_exit(t_pars **pars, char **env, int i)
{
	if (pars[i]->cmd[1] && !string_is_digit(pars[i]->cmd[1]))
	{
		ft_err_print("minishell: exit: %s: numeric argument required\n",
			pars[0]->cmd[1], NULL, NULL);
		exit_message(pars);
		free_array(env);
		free_struct(pars);
		exit(255);
	}
	if (pars[i]->amount > 2 && pars[i]->total_cmd > 1)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		free_array(env);
		free_struct(pars);
		exit(1);
	}
	if (pars[i]->amount > 2)
		return (ft_putendl_fd("minishell: exit: too many arguments", STDERR),
			g_error = 1, env);
	if (pars[i]->cmd[1])
		g_error = ft_atoi(pars[0]->cmd[1]);
	free_array(env);
	free_struct(pars);
	exit_message(pars);
	exit(g_error);
}
