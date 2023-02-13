/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:32:55 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/13 13:32:53 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_b(int sig);
void	ctrl_c(int sig);

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		return ;
	else if (sig == SIGQUIT)
		return ;
}

void	all_signal(void)
{
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	ft_printf("in signal\n");
	return ;
}

void	ctrl_c(int sig)
{
	(void)sig;
}

void	ctrl_b(int sig)
{
	//ft_printf("control backslash\n");
	(void)sig;
}