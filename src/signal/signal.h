/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:33:08 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/28 14:03:09 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void	signal_interactive(void);
void	signal_bash(void);
void	signal_handler_interactive(int sig);
void	signal_handler_bash(int sig);
void	set_g_error(int status);

void	disable_echo(void);
void	enable_echo(void);

#endif