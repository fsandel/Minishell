/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/03/07 10:42:16 by fsandel          ###   ########.fr       */
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
	disable_echo();
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
