/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:32:55 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 21:10:35 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_interactive(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\r\x1b[2K", 6);
		rl_on_new_line();
		rl_redisplay();
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, ">", 1);
		write(STDOUT_FILENO, "\r\x1b[2K", 6);
		rl_on_new_line();
		rl_redisplay();
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	signal_handler_bash(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_error = 130;
// 		exit(130);
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

// void	signal_interactive(void)
// {
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, signal_handler_interactive);
// 	return ;
// }

void	set_g_error(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			g_error = 130;
		else
			g_error = 131;
	}
	else
		g_error = WEXITSTATUS(status);
}
