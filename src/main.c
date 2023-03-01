/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/03/01 19:09:21 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell(char *old_env[]);
void	welcome_message(void);

int		g_error = 0;

int	main(int argc, char *argv[], char *old_env[])
{
	(void)argc;
	(void)argv;
	welcome_message();
	minishell(old_env);
	rl_clear_history();
	return (g_error);
}

void	welcome_message(void)
{
	if (isatty(STDIN))
	{
		ft_putendl_fd("\nThe default interactive shell is now minishell.", 2);
		ft_putendl_fd("If you dont want to, feels bad, \
you are trapped here.", 2);
		ft_putendl_fd("forever", 2);
	}
}
