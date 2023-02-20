/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexercheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:35:34 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/20 21:20:28 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_null(t_lx *lex, char *input, t_list *tokens)
{
	if (input[lex->i] == '\0')
	{
		if (lex->i - 1 != lex->te
			&& (is_whitespace(input[lex->i - 1]) == FALSE)
			&& ft_strlen(input) != lex->te
			&& lex->i != 0)
			token(lex, input, tokens);
		return (TRUE);
	}
	else
		return (FALSE);
}

void	check_pird(t_lx *lex, char *input, t_list *tokens)
{
	if (check(input[lex->i], "|><") == TRUE)
	{
		lex->q--;
		if (lex->te != lex->i
			&& (is_whitespace(input[lex->i - 1]) == FALSE)
			&& lex->i != 0
			&& check(input[lex->i - 1], "|><") == FALSE)
		{
			lex->i--;
			token(lex, input, tokens);
			lex->i++;
		}
		if (input[lex->i + 1] == input[lex->i])
			lex->i++;
		token(lex, input, tokens);
		lex->i++;
	}
}

void	check_quote(t_lx *lex, char *input, t_list *tokens)
{
	if (check(input[lex->i], "\'\"") == TRUE)
	{
		lex->q--;
		lex->c = input[lex->i];
		lex->i++;
		while (input[lex->i])
		{
			if (input[lex->i] == '\"'
				&& input[lex->i - 1] == '\\')
				lex->i++;
			if (input[lex->i] == lex->c)
				break ;
			lex->i++;
		}
		while (input[lex->i]
			&&is_whitespace(input[lex->i + 1]) == FALSE
			&& check(input[lex->i], "|><") == FALSE)
				lex->i++;
		token(lex, input, tokens);
		lex->i++;
	}
}
