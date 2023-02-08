/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:01:01 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/08 11:21:30 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_output(int outpipe, t_pars *pars)
{
	if (pars->out == STDOUT)
	{
		if (pars->index == pars->total_cmd - 1)
		{
			dup2(STDOUT, STDOUT);
			ft_putendl_fd("duping out to out", 2);
		}
		else
		{
			dup2(outpipe, STDOUT);
			ft_putendl_fd("duping pipe to out\n", 2);
		}
	}
	else
	{
		dup2(pars->out, STDOUT);
		ft_putendl_fd("duping outfile to out", 2);
	}
}

void	dup_input(int inpipe, t_pars *pars)
{
	if (pars->in == STDIN)
	{
		if (pars->index == 0)
		{
			dup2(STDIN, STDIN);
			ft_putendl_fd("duping in to in", 2);
		}
		else
		{
			dup2(inpipe, STDIN);
			ft_putendl_fd("duping pipe to in", 2);
		}
	}
	else
	{
		dup2(pars->in, STDIN);
		ft_putendl_fd("infile outfile to in", 2);
	}
}

void	dup_error(t_pars *pars)
{
	if (pars->err != STDERR)
		dup2(pars->err, STDERR);
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
