/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:03:46 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/31 17:31:34 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_H
# define UTILS_H

void	ft_free(void **arg, char *loc);

void	ft_puttarr_fd(char **arr, int fd);
void	ft_putcube_fd(char ***cube, int fd);
char	**ft_split_special(char const *s, char c);

#endif