/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/01 16:26:58 by pgorner          ###   ########.fr       */
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
		if (check_input(input))
			ft_putendl_fd("bad quotes", 2);
		else
			lexer(input);
		free(input);
	}
	free(prompt);
	return (0);
}
