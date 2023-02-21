/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:33:26 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 12:09:44 by pgorner          ###   ########.fr       */
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
}			t_pars;

typedef struct lex
{
	t_list	*tokens;	// output list coming out of lexer 
	int		i;			// current position in iteration of input
	int		ts;			// token start
	int		te;			// (last) token end
	int		q;			// quotes = TRUE/FALSE
	char	c;			// char comparison
}			t_lx;

typedef struct t_qu{
	int		i;
	int		r;
	int		j;
	int		last;
	char	*str;
}			t_qu;

#endif