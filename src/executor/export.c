/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:29:06 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/25 15:06:55 by fsandel          ###   ########.fr       */
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

int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	**export(char **env, char *str)
{
	int		i;
	char	*copy;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	copy = ft_calloc(i + 1, sizeof(char));
	ft_memmove(copy, str, i);
	env = arr_del_line(env, copy);
	env = array_add_line(env, str);
	free(copy);
	return (env);
}

char	**b_export(t_pars *pars)
{
	int	i;

	g_error = 0;
	i = 1;
	if (pars->amount == 1)
		return (export_error(pars->env), pars->env);
	while (pars->cmd[i])
	{
		if (valid_identifier(pars->cmd[i]))
			pars->env = export(pars->env, pars->cmd[i]);
		else
		{
			ft_err_print("minishell: export: '%s': not a valid identifier\n",
				pars->cmd[i], NULL, NULL);
			g_error = 1;
		}
		i++;
	}
	return (pars->env);
}
