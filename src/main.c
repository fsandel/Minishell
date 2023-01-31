/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/31 13:57:51 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_prompt(void)
{
	char	*path;
	char	*prompt;

	path = getcwd(NULL, 0);
	prompt = ft_strjoin(path, ": ");
	free(path);
	return (prompt);
}

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
		return (-1);
	else
		return (0);
}

int	main(void)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt();
	while (1)
	{
		input = readline(prompt);
		add_history(input);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		check_input(input);
		//lexing(input);
		//ft_printf("%s\n", input);
		free(input);
	}
	free(prompt);
	return (0);
}
