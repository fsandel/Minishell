/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:29:06 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/18 13:29:48 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_line(char *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (line[i] && line[i] != '=')
		ft_putchar_fd(line[i++], 1);
	if (line[i])
	{
		ft_putchar_fd('"', 1);
		ft_putstr_fd(&line[i++], 1);
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

void	export_error(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		display_line(env[i++]);
}

char	**b_export(t_pars *pars)
{
	int	i;
	int	error;

	error = 0;
	i = 1;
	if (pars->amount == 1)
		return (export_error(pars->env), pars->env);
	while (pars->cmd[i])
	{
		if (ft_isalpha(pars->cmd[i][0]))
		{
			pars->env = arr_del_line(pars->env, pars->cmd[i]);
			pars->env = array_add_line(pars->env, pars->cmd[i]);
		}
		else
		{
			ft_err_print("minishell: export: '%s': not a valid identifier\n",
				pars->cmd[i], NULL, NULL);
			error = 1;
		}
		i++;
	}
	g_error = error;
	return (pars->env);
}
