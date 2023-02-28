/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:12:04 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 13:51:31 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*array_get_line(char **arr, char *ln)
{
	int		line;

	if (!ln)
		return (NULL);
	line = 0;
	while (arr[line])
	{
		if (!ft_strncmp(arr[line], ln, ft_strlen(ln))
			&& arr[line][ft_strlen(ln)] == '=')
			return (ft_strdup(&arr[line][ft_strlen(ln) + 1]));
		line++;
	}
	return (NULL);
}

char	**array_add_line(char **arr, char *nl)
{
	char	**ret;
	int		line;

	line = 0;
	if (!nl)
		return (arr);
	if (!arr)
		return (ret = ft_calloc(2, sizeof(char *)),
			ret[0] = ft_strdup(nl), ret[1] = NULL, arr = ret, ret);
	ret = ft_calloc(array_size(arr) + 2, sizeof(char *));
	while (arr[line])
	{
		ret[line] = ft_strdup(arr[line]);
		line++;
	}
	ret[line++] = ft_strdup(nl);
	ret[line] = NULL;
	free_array(arr);
	return (arr = ret, ret);
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
			&& (arr[line][ft_strlen(ln)] == '=' || !arr[line][ft_strlen(ln)]))
			line++;
		else
			ret[ret_line++] = ft_strdup(arr[line++]);
	}
	ret[ret_line] = NULL;
	free_array(arr);
	return (ret);
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
