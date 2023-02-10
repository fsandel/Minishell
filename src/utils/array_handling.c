/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:12:04 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 16:17:07 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**array_add_line(char **arr, char *nl)
{
	char	**ret;
	int		line;

	line = 0;
	ret = ft_calloc(array_size(arr) + 2, sizeof(char *));
	while (arr[line])
	{
		ret[line] = ft_strdup(arr[line]);
		line++;
	}
	ret[line++] = ft_strdup(nl);
	ret[line] = NULL;
	free_array(arr);
	return (ret);
}

char	**arr_del_line(char **arr, char *ln)
{
	int		line;
	char	**ret;
	int		ret_line;

	if (!ln)
		return (arr);
	ret_line = 0;
	line = 0;
	ret = ft_calloc(array_size(arr) + 1, sizeof(char *));
	while (arr[line])
	{
		if (!ft_strncmp(arr[line], ln, ft_strlen(ln))
			&& arr[line][ft_strlen(ln)] == '=')
			line++;
		else
			ret[ret_line++] = ft_strdup(arr[line++]);
	}
	ret[ret_line] = NULL;
	free_array(arr);
	return (ret);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**copy_arr(char **arr)
{
	char	**ret;
	int		i;

	if (!arr)
		return (NULL);
	i = 0;
	ret = ft_calloc(array_size(arr) + 1, sizeof(char *));
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	array_size(char **arr)
{
	int	size;

	size = 0;
	while (arr && arr[size])
		size++;
	return (size);
}
