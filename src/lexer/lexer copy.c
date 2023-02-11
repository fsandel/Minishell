/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:41:27 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/11 13:49:09 by pgorner          ###   ########.fr       */
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
	lex->q = 0;
	lex->quot = ft_strdup("\'\"");
	lex->pird = ft_strdup("|><");
	lex->space = ft_strdup(" \t\v\f\r");

}

void	ft_lstprint(t_list *list)
{
	int i;

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
	int	i;
	char *token;

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
	printf("TOKEN IS:%s:\n", token);
	if (tokens->content == NULL)
		tokens->content = token;
	else
		ft_lstadd_back(&tokens, ft_lstnew(token));
	tokens = tokens->next;
	//printf("finat %i\n", lex->i);
	//ft_lstprint(tokens);
}

int	check(char input, char const *it)
{
	int i;

	i = 0;
	while(it[i])
	{
		//printf("COMPARING :%c: & :%c:\n", input, it[i]);
		if (it[i] == input)
			return (TRUE);
		i++;
	}
	return (FALSE);
}


t_list	*lexer(char *input)
{
	t_lx	*lex;
	t_list	*tokens;
	
	lex = ft_calloc(1,  sizeof(t_lx));
	assign_checks(lex);
	int i = 0;
	
	tokens = ft_lstnew(NULL);
	//printf("START WHILE LOOP\n");
	//printf("INPUT:%s:\n", input);
	while (TRUE)
	{
		//printf("STATUS:\n lex->i = %i\n round: %i\n", lex->i, i);
		if (check_null(lex, input, tokens) == TRUE) //checks for null character
			break;
		check_pird(lex, input, tokens);				//checks for pipe and redirects
		check_quote(lex, input, tokens);			//checks for single and double quotes
		//check_dollar(lex, input, tokens);			//checks for expansion
		//check_pirdnw(lex, input, tokens);			//checks for pipe/redirects/newline
		check_space(lex, input, tokens);			//checks for whitespace
		check_left(lex, input, tokens);				//checks for leftovers
		if (i == 20)
			break;
		i++;
	}
	ft_lstprint(tokens);
	//ft_lstclear(&tokens, free);
	return(tokens);
}
