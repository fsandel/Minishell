/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:41:39 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/28 18:43:55 by pgorner          ###   ########.fr       */
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
		check_quote(lex, input);
		check_space(lex, input, tokens);
		check_left(lex, input);
	}
	free(lex);
	return (tokens);
}
