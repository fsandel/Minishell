/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:02:46 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/27 13:05:41 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//				██╗  ██╗███████╗ █████╗ ██████╗ ███████╗██████╗
//				██║  ██║██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
//				███████║█████╗  ███████║██║  ██║█████╗  ██████╔╝
//				██╔══██║██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗
//				██║  ██║███████╗██║  ██║██████╔╝███████╗██║  ██║
//				╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝

#ifndef LEXER_H
# define LEXER_H

//==============================================================================
//---------------------------------LEXER.c--------------------------------------
//==============================================================================
int		check(char input, char const *it);
int		check_null(t_lx *lex, char *input, t_list *tokens);
void	assign_checks(t_lx *lex);
void	token(t_lx *lex, char *input, t_list *tokens);
t_list	*lexer(char *input);
void	check_pird(t_lx *lex, char *input, t_list *tokens);
void	check_quote(t_lx *lex, char *input);
void	check_space(t_lx *lex, char *input, t_list *tokens);
void	check_dollar(t_lx *lex, char *input, t_list *tokens);
void	check_pirdnw(t_lx *lex, char *input, t_list *tokens);
void	ft_lstprint(t_list *list);
//==============================================================================
//------------------------------SMALLERTHAN.c-----------------------------------
//==============================================================================
char	**smallerthan(char *content);
char	**smallerthanall(char *content);
char	**smallerthanmid(char *content);
char	**smallerthanback(char *content);
char	**smallerthanfront(char *content);
//==============================================================================
//-------------------------------BIGGERTHAN.c-----------------------------------
//==============================================================================
char	**biggerthan(char *content);
//==============================================================================
//---------------------------------PIPE.c---------------------------------------
//==============================================================================
char	**haspipe(char *content);
char	**pipeall(char *content);
char	**pipemid(char *content);
char	**pipeback(char *content);
char	**pipefront(char *content);
//==============================================================================
//--------------------------------SPECIAL.c-------------------------------------
//==============================================================================
char	**special(char *content);
t_list	*lstspecial(t_list *lst);

#endif
