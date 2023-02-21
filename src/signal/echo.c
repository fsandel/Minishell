/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:22:51 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 13:26:50 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_echo(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void	enable_echo(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
