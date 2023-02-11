/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:41:27 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/11 16:03:46 by pgorner          ###   ########.fr       */
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
	printf("TOKEN IS:%s:\n with ls->te %i\n", token, lex->te);
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
	int c;

	c = 0;
	while(it[c])
	{
		//printf("COMPARING :%c: & :%c:\n", input, it[i]);
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
	printf("JERE? at lex-%i\n", lex->i);
		if (lex->i - 1 != lex->te
		&& (is_whitespace(input[lex->i - 1]) == FALSE)
		&& ft_strlen(input) != lex->te
		&& lex->i != 0)
		{
			printf("--:%i != %i:--\n", lex->i - 1, lex->te);
			printf("token made in null\n");
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
			lex->i++;;
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
	printf("CHECK AT %i\n", lex->i);
	if (input[lex->i] == '2')
		doub(lex, input, tokens);
	if (input[lex->i] == '&')
		and(lex, input, tokens);
	if (check(input[lex->i], "|><") == TRUE)
	{
		lex->q--;
		//printf("inpird at %i with %c\n", lex->i, input[lex->i]);
		if (lex->te != lex->i 
			&& (is_whitespace(input[lex->i - 1]) == FALSE)
			&& lex->i != 0
			&& check(input[lex->i - 1], "|><") == FALSE)
		{
			lex->i--;
			//printf("previous token made in pird\n");
			token(lex, input, tokens);
			lex->i++;
		}
		if (input[lex->i + 1] == input[lex->i])
			lex->i++;
		//printf("token made in pird with %i:%c:\n", lex->i, input[lex->i]);
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
		if (lex->te != lex->i - 1
			&& lex->i != 0
			&&is_whitespace(input[lex->i - 1]) == FALSE)
		{
			lex->i--;
			token(lex, input, tokens);
			lex->i++;
		}
		lex->i++;
		while (input[lex->i])
		{
			if (input[lex->i] == '\"'
				&& input[lex->i - 1] == '\\') //escapecounter
				lex->i++;
			if (input[lex->i] == lex->c)
				break;
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
	printf("--------\n");
	ft_lstprint(tokens);
	return(tokens);
}
