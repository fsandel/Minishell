/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:02:28 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 18:40:19 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//				██╗  ██╗███████╗ █████╗ ██████╗ ███████╗██████╗
//				██║  ██║██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
//				███████║█████╗  ███████║██║  ██║█████╗  ██████╔╝
//				██╔══██║██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗
//				██║  ██║███████╗██║  ██║██████╔╝███████╗██║  ██║
//				╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct t_x
{
	int		b;
	int		i;
	int		p;
	int		s;
	int		n;
	int		d;
	int		pd;
	char	**o;
	char	*str;
}			t_x;

//==============================================================================
//--------------------------------EXPANDER.c------------------------------------
//==============================================================================
t_pars	**expander(t_pars **pars);
void	cmd_expand(t_pars **pars, char **cmds, int set);

//==============================================================================
//--------------------------------EXPCHECK.c------------------------------------
//==============================================================================
int		check_one(t_pars **pars, int set, int num, int i);
int		check_two(t_pars **pars, int set, int num, int i);
int		check_three(t_pars **pars, int set, int num, int i);
//==============================================================================
//------------------------------------PATH.c------------------------------------
//==============================================================================
int		errorput(t_pars **pars, int set, int num);
int		path(t_pars **pars, int set, int num);
void	make_dollar(t_pars **pars, t_x *x);
char	*find_dollar(t_pars **pars, t_x *x);
int		last(char **str);
void	set_str(t_x *x);
void	app(t_pars **pars, t_x *x);
void	pute(t_x *x);
void	addtocmds(t_pars **pars, t_x *x);
void	end_cmd(t_pars **pars, t_x *x);
void	cmd_expand(t_pars **pars, char **cmds, int s);
t_pars	**expander(t_pars **pars);
void	dollar(t_pars **pars, t_x *x);
void	backslash(t_pars **pars, t_x *x);
void	qq(t_pars **pars, t_x *x);
void	q(t_pars **pars, t_x *x);
void	set_str(t_x *x);
void	quotes(t_pars **pars, t_x *x);
void	normalstring(t_pars **pars, t_x *x);
void	expanding(t_pars **pars, t_x *x);
int		ow(char *str);
#endif
