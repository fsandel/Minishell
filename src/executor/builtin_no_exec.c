/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_no_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:44:44 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/18 13:30:59 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**b_unset(t_pars *pars)
{
	int	i;

	i = 1;
	while (pars->cmd[i])
		pars->env = arr_del_line(pars->env, pars->cmd[i++]);
	return (pars->env);
}

int	string_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

char	**b_exit(t_pars **pars, char **env)
{
	if (pars[0]->cmd[1] && !string_is_digit(pars[0]->cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(pars[0]->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_array(env);
		free_struct(pars);
		exit(255);
	}
	if (pars[0]->amount > 2)
		return (ft_putendl_fd("minishell: exit: too many arguments", 2),
			g_error = 1, env);
	if (pars[0]->cmd[1])
		g_error = ft_atoi(pars[0]->cmd[1]);
	free_array(env);
	free_struct(pars);
	exit(g_error);
}
