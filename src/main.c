/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:08:34 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/22 15:05:39 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell(char *old_env[]);
char	**command(char *input, char **old_env);
int		g_error;

int	main(int argc, char *argv[], char *old_env[])
{
	(void)argc;
	(void)argv;
	g_error = 0;
	ft_putendl_fd("\nThe default interactive shell is now minishell.", 2);
	ft_putendl_fd("If you dont want to, feels bad, you are trapped here.", 2);
	ft_putendl_fd("forever", 2);
	minishell(old_env);
	return (g_error);
}
