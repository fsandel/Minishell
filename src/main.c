/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/30 17:16:33 by pgorner          ###   ########.fr       */
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
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		lexing(input);
		//ft_printf("%s\n", input);
		free(input);
	}
	free(prompt);
	return (0);
}
