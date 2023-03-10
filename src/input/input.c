/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:03:15 by fsandel           #+#    #+#             */
/*   Updated: 2023/03/07 10:08:57 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input(char *str)
{
	int	esc;
	int	sgl;
	int	dbl;
	int	i;

	esc = 0;
	sgl = 0;
	dbl = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dbl)
			sgl = (sgl + 1) % 2;
		if (str[i] == '\\')
			esc = (esc + 1) % 2;
		if (str[i] == '\"' && !esc && !sgl)
			dbl = (dbl + 1) % 2;
		if (str[i] && str[i] != '\\')
			esc = 0;
		i++;
	}
	if (sgl || dbl)
		return (ERROR);
	else
		return (SUCCESS);
}

void	empty_input_handler(char *input)
{
	free(input);
	g_error = 0;
}

void	bad_quote_handler(char *input)
{
	ft_putendl_fd("minishell: input: bad quotes", STDERR);
	add_history(input);
	free(input);
	g_error = 1;
}

char	*get_input(char *prompt)
{
	char	*input;
	char	buf;
	int		bytes;

	if (isatty(STDIN))
		input = readline(prompt);
	else
	{
		input = NULL;
		buf = 0;
		bytes = read(STDIN, &buf, 1);
		if (bytes < 1)
			return (NULL);
		while (bytes && buf != '\n')
		{
			input = str_append(input, buf);
			bytes = read(STDIN, &buf, 1);
			if (bytes < 0)
				return (free(input), NULL);
		}
	}
	return (input);
}

int	check_empty(t_pars **pars)
{
	int	i;
	int	trigger;

	i = pars[0]->total_cmd;
	trigger = 0;
	while (i--)
	{
		if (pars[i] && pars[i]->cmd && !pars[i]->cmd[0])
		{
			if (pars[i]->in == STDIN && pars[i]->out == STDOUT)
				return (free_struct(pars), g_error = 258,
					ft_putendl_fd("minishell: syn\
tax error near unexpected token '|'", STDERR), 1);
		}
	}
	return (0);
}
