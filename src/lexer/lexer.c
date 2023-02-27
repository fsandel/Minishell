/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:41:27 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/21 17:31:35 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_checks(t_lx *lex)
{
	lex->i = 0;
	lex->te = -2;
	lex->ts = 0;
	lex->q = 1;
}

void	check_space(t_lx *lex, char *input, t_list *tokens)
{
	if (is_whitespace(input[lex->i]) == TRUE)
	{
		lex->q--;
		if (lex->te != lex->i - 1
			&& (is_whitespace(input[lex->i - 1]) == FALSE)
			&& lex->i != 0)
		{
			lex->i--;
			token(lex, input, tokens);
			lex->i++;
		}
		while (is_whitespace(input[lex->i]) == TRUE
			&& input[lex->i] != '\0')
			lex->i++;
		lex->ts = lex->i;
	}
}

void	check_left(t_lx *lex, char *input)
{
	if (lex->q > 1 && input[lex->i] != '\0')
		lex->i++;
	if (lex->q == 1)
		lex->q++;
	else
		lex->q = 1;
}

t_list	*lexer(char *input)
{
	t_lx	*lex;
	t_list	*tokens;

	lex = ft_calloc(1, sizeof(t_lx));
	assign_checks(lex);
	tokens = ft_lstnew(NULL);
	while (TRUE)
	{
		if (check_null(lex, input, tokens) == TRUE)
			break ;
		check_pird(lex, input, tokens);
		check_quote(lex, input, tokens);
		check_space(lex, input, tokens);
		check_left(lex, input);
	}
	free(lex);
	return (tokens);
}
