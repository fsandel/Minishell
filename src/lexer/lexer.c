/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:41:27 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/10 19:38:27 by pgorner          ###   ########.fr       */
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
	lex->te = lex->i++;
	token = ft_calloc(sizeof(char), lex->te - lex->ts + 2);
	if (lex->ts == lex->i)
		token[i] = input[lex->i];
	else
		while (lex->ts <= lex->te)
			token[i++] = input[lex->ts++];
	token[i + 1] = '\0';
	lex->ts = lex->te + 1;
	//printf("TOKEN IS:%s:\n", token);
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

int	check_null(t_lx *lex, char *input, t_list *tokens)
{
	if (input[lex->i] == '\0')
	{
		if (lex->i - 1 != lex->te)
		{
			//printf("--:%i != %i:--\n", lex->i, lex->te);
			//printf("token made in null\n");
			//printf("te:%ii:%its%i\n", lex->te, lex->i, lex->ts);
			token(lex, input, tokens);
		}
		return (TRUE);
	}
	else
		return (FALSE);
}

void doub(t_lx *lex, char *input, t_list *tokens)
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
					lex->i--;
					token(lex, input, tokens);
					lex->i += 4;
					token(lex, input, tokens);
				}
		}
		else
		{
			lex->i--;
			token(lex, input, tokens);
			lex->i += 2;
			token(lex, input, tokens);
		}
	}
}

void and(t_lx *lex, char *input, t_list *tokens)
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

void check_pird(t_lx *lex, char *input, t_list *tokens)
{
	if (check(input[lex->i], "|><") == TRUE
		&& lex->q == FALSE)
	{
		//printf("inpird at %i with %c\n", lex->i, input[lex->i]);
		if (lex->te != lex->i 
			&& (is_whitespace(input[lex->i - 1]) == FALSE))
		{
			lex->i--;
			//printf("previous token made in pird\n");
			token(lex, input, tokens);
		}
		if (input[lex->i + 1] == input[lex->i])
			lex->i++;
		//printf("token made in pird with %i:%c:\n", lex->i, input[lex->i]);
		token(lex, input, tokens);
	}
	if (input[lex->i] == '2')
		doub(lex, input, tokens);
	if (input[lex->i] == '&')
		and(lex, input, tokens);
}

void	check_quote(t_lx *lex, char *input, t_list *tokens)
{
	if (check(input[lex->i], "\'\"") == TRUE)
	{
		lex->c = input[lex->i];
		//printf("QUOTE?\n");
		if (lex->te != lex->i - 1
			&& lex->i != 0)
		{
			lex->i--;
			token(lex, input, tokens);
			lex->i++;
		}
		while (input[lex->i])
		{
			lex->i++;
			if (input[lex->i] == '\"'
				&& input[lex->i - 1] == '\\')
				lex->i++;
			if (input[lex->i] == lex->c)
				break;
		}
		while (input[lex->i]
				&&is_whitespace(input[lex->i]) == FALSE
				&& check(input[lex->i], "|><") == FALSE)
				lex->i++;
		//printf("token made in quote\n");
		token(lex, input, tokens);
		lex->i++;
	}
}

void	check_dollar(t_lx *lex, char *input, t_list *tokens)
{
	if (input[lex->i] == '$')
	{
		printf("I found a dollar\n");
		lex->i++;
	}
}

/* void	check_pirdnw(t_lx *lex, char * input, t_list *tokens)
{
	if (check(input[lex->i], lex->quot) == TRUE)
	{
		if (lex->ts != -1)
		{
			lex->i--;
			token(lex, input, tokens);
			lex->i++;
			lex->ts = lex->i;
			if (input[lex->i + 1] == input[lex->i])
				lex->te = lex->i + 1;
			token(lex, input, tokens);
			lex->i++;
		}
		if (lex->ts == 0
			&& input[lex->i] == input[lex->ts]
			&& input[lex->ts - 1] != '\\')
		{
			token(lex, input, tokens);
			lex->i++;
		}
	}
} */

void	check_space(t_lx *lex, char *input, t_list *tokens)
{
	if (is_whitespace(input[lex->i]) == TRUE)
		//printf("SPAACE at %i\n", lex->i);
		{
		if (lex->te != lex->i - 1
			&& (is_whitespace(input[lex->i - 1]) == FALSE))
		{
			lex->i--;
			token(lex, input, tokens);
			lex->i++;
		}
		while (is_whitespace(input[lex->i]) == TRUE)
			lex->i++;
		lex->ts = lex->i;
		}
}

void	check_left(t_lx *lex, char *input, t_list *tokens)
{
	if (input[lex->i]
		&& lex->q == FALSE)
		lex->i++;
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
/* 		if (i == 20)
			break; */
		i++;
	}
	//ft_lstprint(tokens);
	ft_lstclear(&tokens, free);
	return(tokens);
}
