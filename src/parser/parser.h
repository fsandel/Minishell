/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:08 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/21 13:26:13 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//				██╗  ██╗███████╗ █████╗ ██████╗ ███████╗██████╗
//				██║  ██║██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
//				███████║█████╗  ███████║██║  ██║█████╗  ██████╔╝
//				██╔══██║██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗
//				██║  ██║███████╗██║  ██║██████╔╝███████╗██║  ██║
//				╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_q
{
	int	i;
	int	sgl;
	int	dbl;
	int	esc;
}	t_q;

typedef struct s_c
{
	int	i;
	int	line;
}	t_c;

//==============================================================================
//--------------------------------parser.c--------------------------------------
//==============================================================================
t_pars	**parser(t_list *list, char **env);

//==============================================================================
//--------------------------------redirect_out.c--------------------------------
//==============================================================================
t_list	*redirect_out(t_list *list, t_pars *pars);
t_list	*redirect_err(t_list *list, t_pars *pars);
t_list	*redirect_both(t_list *list, t_pars *pars);
int		unexpected_token(char *str);

//==============================================================================
//--------------------------------redirect_append.c-----------------------------
//==============================================================================
t_list	*append_out(t_list *list, t_pars *pars);
t_list	*append_err(t_list *list, t_pars *pars);
t_list	*append_both(t_list *list, t_pars *pars);

//==============================================================================
//--------------------------------redirect_in.c---------------------------------
//==============================================================================
t_list	*redirect_in(t_list *list, t_pars *pars);

//==============================================================================
//--------------------------------heredoc.c-------------------------------------
//==============================================================================
t_list	*here_doc(t_list *list, t_pars *pars, t_pars **pars_full);

//==============================================================================
//--------------------------------parser_utils.c--------------------------------
//==============================================================================
void	free_struct(t_pars **pars);
void	display_pars(t_pars **pars);
int		count_commands(t_list *list);

//==============================================================================
//--------------------------------parser_setup.c--------------------------------
//==============================================================================
t_pars	**setup_struct(t_list *list, char **env);

//==============================================================================
//--------------------------------heredoc_utils.c-------------------------------
//==============================================================================
int		replace(char *line, char **env, int fd);
void	expand(char *line, char **env, int fd);
char	*rm_quote(char *str);

#endif