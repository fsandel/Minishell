/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_no_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:44:44 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/22 11:39:20 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_alpha_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i++]))
			return (1);
	}
	return (0);
}

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

void	exit_message(t_pars **pars)
{
	if (pars[0]->total_cmd == 1)
		ft_putstr_fd("exit\n", 1);
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
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		free_array(env);
		free_struct(pars);
		exit(1);
	}
	if (pars[i]->amount > 2)
		return (ft_putendl_fd("minishell: exit: too many arguments", 2),
			g_error = 1, env);
	if (pars[i]->cmd[1])
		g_error = ft_atoi(pars[0]->cmd[1]);
	free_array(env);
	free_struct(pars);
	exit_message(pars);
	exit(g_error);
}
