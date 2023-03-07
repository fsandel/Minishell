/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:41:05 by fsandel           #+#    #+#             */
/*   Updated: 2023/03/07 11:09:22 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_echo(void)
{
	struct termios	t;

	tcgetattr(STDIN, &t);
	t.c_lflag &= ~(IEXTEN | ECHOCTL);
	tcsetattr(STDIN, TCSANOW, &t);
}
