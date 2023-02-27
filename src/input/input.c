/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:03:15 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/25 18:24:45 by fsandel          ###   ########.fr       */
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
	ft_putendl_fd("minishell: input: bad quotes", 2);
	free(input);
	g_error = 1;
}

char	*get_input(char *prompt)
{
	char	*input;

	if (isatty(STDIN))
		input = readline(prompt);
	else
		input = get_next_line(STDIN);
	return (input);
}
