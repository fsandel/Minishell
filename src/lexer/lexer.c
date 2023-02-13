/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:41:27 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/13 13:55:39 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' | c == '\n' | c == '\t' | c == '\v' | c == '\f' | c == '\r')
		return (TRUE);
	else
		return (FALSE);
}

void	assign_checks(t_lx *lex)
{
	lex->i = 0;
	lex->te = -2;
	lex->ts = 0;
	lex->q = 1;
}

void	ft_lstprint(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("LIST ITEM:%i:%s:\n", i, list->content);
		list = list->next;
		i++;
	}
}

void	token(t_lx *lex, char *input, t_list *tokens)
{
	int		i;
	char	*token;

	i = 0;
	lex->te = lex->i;
	token = ft_calloc(sizeof(char), lex->te - lex->ts + 2);
	if (lex->ts == lex->i)
		token[i] = input[lex->i];
	else
		while (lex->ts <= lex->te)
			token[i++] = input[lex->ts++];
	token[i + 1] = '\0';
	lex->ts = lex->te + 1;
	//printf("TOKEN IS:%s:\n with ls->te %i\n", token, lex->te);
	if (tokens->content == NULL)
		tokens->content = token;
	else
		ft_lstadd_back(&tokens, ft_lstnew(token));
	tokens = tokens->next;
}

int	check(char input, char const *it)
{
	int	c;

	c = 0;
	while (it[c])
	{
		if (it[c] == input)
			return (TRUE);
		c++;
	}
	return (FALSE);
}

int	check_null(t_lx *lex, char *input, t_list *tokens)
{
	if (input[lex->i] == '\0')
	{
		if (lex->i - 1 != lex->te
			&& (is_whitespace(input[lex->i - 1]) == FALSE)
			&& ft_strlen(input) != lex->te
			&& lex->i != 0)
		{
			//printf("--:%i != %i:--\n", lex->i - 1, lex->te);
			//printf("token made in null\n");
			token(lex, input, tokens);
		}
		return (TRUE);
	}
	else
		return (FALSE);
}

void	doub(t_lx *lex, char *input, t_list *tokens)
{
	if (input[lex->i + 1] == '>')
	{
		if (input[lex->i + 2] == '>')
		{
			if (lex->i != 0)
			{
				lex->i--;
				token(lex, input, tokens);
			}
			else
			{
				lex->i += 2;
				token(lex, input, tokens);
			}
		}
		else if (input[lex->i + 2] == '&')
		{
			if (input[lex->i + 3] == '1')
			{
				if (lex->ts != lex->i
					&& lex->i != 0)
				{
					lex->i--;
					token(lex, input, tokens);
					lex->i++;
				}
				lex->i += 3;
				token(lex, input, tokens);
			}
		}
		else
		{
			if (lex->ts != lex->i
				&& lex->i != 0)
			{
				lex->i--;
				token(lex, input, tokens);
				lex->i++;
			}
			lex->i++;
			token(lex, input, tokens);
		}
	}
}

void	and(t_lx *lex, char *input, t_list *tokens)
{
	if (input[lex->i + 1] == '>')
	{
		if (input[lex->i + 2] == '>')
		{
			if (lex->i != 0)
			{
				lex->i--;
				token(lex, input, tokens);
			}
			else
			{
				lex->i += 2;
				token(lex, input, tokens);
			}
		}
	}
}

void	check_pird(t_lx *lex, char *input, t_list *tokens)
{
	if (input[lex->i] == '2')
		doub(lex, input, tokens);
	if (input[lex->i] == '&')
		and(lex, input, tokens);
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
/* 		if (lex->te != lex->i - 1
			&& lex->i != 0
			&&is_whitespace(input[lex->i - 1]) == FALSE)
		{
			lex->i--;
			token(lex, input, tokens);
			lex->i++;
		} */
		lex->i++;
		while (input[lex->i])
		{
			if (input[lex->i] == '\"'
				&& input[lex->i - 1] == '\\') //escapecounter
				lex->i++;
			if (input[lex->i] == lex->c)
				break ;
			lex->i++;
		}
		while (input[lex->i]
			&&is_whitespace(input[lex->i + 1]) == FALSE
			&& check(input[lex->i], "|><") == FALSE
			&& check(input[lex->i + 1], "\'\"") == FALSE)
				lex->i++;
		token(lex, input, tokens);
		lex->i += 2;
	}
}

void	check_dollar(t_lx *lex, char *input, t_list *tokens)
{
	if (input[lex->i] == '$')
	{
		lex->q--;
		printf("I found a dollar\n");
		lex->i++;
	}
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

void	check_left(t_lx *lex, char *input, t_list *tokens)
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
		//printf("STATUS:\n lex->i = %i\n round: %i\n", lex->i, i);
		if (check_null(lex, input, tokens) == TRUE)
			break ;
		check_pird(lex, input, tokens);
		check_quote(lex, input, tokens);
		//check_dollar(lex, input, tokens);
		check_space(lex, input, tokens);
		check_left(lex, input, tokens);
	}
	printf("-----------------------------------------------------\n");
	//ft_lstprint(tokens);
	free(lex);
	return (tokens);
}
