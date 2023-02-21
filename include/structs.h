/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:33:26 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 17:33:07 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//				██╗  ██╗███████╗ █████╗ ██████╗ ███████╗██████╗
//				██║  ██║██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
//				███████║█████╗  ███████║██║  ██║█████╗  ██████╔╝
//				██╔══██║██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗
//				██║  ██║███████╗██║  ██║██████╔╝███████╗██║  ██║
//				╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_pars
{
	char	**cmd;
	int		in;
	int		err;
	int		out;
	int		total_cmd;
	int		index;
	int		amount;
	char	**env;
	int		error;
	int		heredoc;
	pid_t	pid;
	t_list	*list;
}			t_pars;

typedef struct lex
{
	t_list	*tokens;
	size_t	i;
	size_t	ts;
	size_t	te;
	int		q;
	char	c;
}			t_lx;

typedef struct t_qu
{
	size_t		i;
	int			r;
	int			j;
	int			last;
	char		*str;
}				t_qu;

typedef struct t_bs
{
	int		b;
	int		i;
	int		j;
	int		r;
	char	*str;
}			t_bs;

typedef struct t_ph
{
	int		i;
	int		j;
	char	*str;
	char	*pre;
	char	*post;
}			t_ph;

typedef struct t_lt
{
	t_list	*new;
	t_list	*out;
	t_list	*tail;
	char	**res;
	int		i;
	int		j;
}			t_lt;

#endif