/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:22:51 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 15:28:34 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_echo(void)
{
	struct termios	t;

	tcgetattr(STDIN, &t);
	//t.c_lflag &= ~ECHO;
	t.c_lflag &= ~(IEXTEN | ECHOCTL);
	tcsetattr(STDIN, TCSANOW, &t);
}

void	enable_echo(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
