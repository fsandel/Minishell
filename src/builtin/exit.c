/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:23:49 by fsandel           #+#    #+#             */
/*   Updated: 2023/03/07 09:46:35 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_numeric_message(char *arg, t_pars **pars, char **env);

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
	if (pars[i]->cmd[1] && !pars[i]->cmd[1][0])
		exit_numeric_message(pars[0]->cmd[1], pars, env);
	if (pars[i]->cmd[1] && !string_is_digit(pars[i]->cmd[1]))
		exit_numeric_message(pars[0]->cmd[1], pars, env);
	if (pars[i]->amount > 2 && pars[i]->total_cmd > 1)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		free_array(env);
		free_struct(pars);
		ft_exit(1);
	}
	if (pars[i]->amount > 2)
		return (ft_putendl_fd("minishell: exit: too many arguments", STDERR),
			g_error = 1, env);
	if (pars[i]->cmd[1])
		g_error = ft_atoi(pars[0]->cmd[1]);
	free_array(env);
	free_struct(pars);
	exit_message(pars);
	ft_exit(g_error);
	return (NULL);
}

void	exit_numeric_message(char *arg, t_pars **pars, char **env)
{
	ft_err_print("minishell: exit: %s: numeric argument required\n",
		arg, NULL, NULL);
	exit_message(pars);
	free_array(env);
	free_struct(pars);
	ft_exit(255);
}
