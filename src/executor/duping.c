/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:01:01 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/18 10:50:15 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_output(int outpipe, t_pars *pars)
{
	if (pars->out == STDOUT)
	{
		if (pars->index == pars->total_cmd - 1)
			dup2(STDOUT, STDOUT);
		else
			dup2(outpipe, STDOUT);
	}
	else
		dup2(pars->out, STDOUT);
}

void	dup_input(int inpipe, t_pars *pars)
{
	if (pars->in == STDIN)
	{
		if (pars->index == 0)
			dup2(STDIN, STDIN);
		else
			dup2(inpipe, STDIN);
	}
	else
		dup2(pars->in, STDIN);
}

void	smart_close(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 > 2)
		close(fd1);
	if (fd2 > 2)
		close(fd2);
	if (fd3 > 2)
		close(fd3);
	if (fd4 > 2)
		close(fd4);
}
