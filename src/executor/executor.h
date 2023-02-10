/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:01:41 by fsandel           #+#    #+#             */
/*   Updated: 2023/02/10 15:51:21 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//				██╗  ██╗███████╗ █████╗ ██████╗ ███████╗██████╗
//				██║  ██║██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
//				███████║█████╗  ███████║██║  ██║█████╗  ██████╔╝
//				██╔══██║██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗
//				██║  ██║███████╗██║  ██║██████╔╝███████╗██║  ██║
//				╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
//==============================================================================
//--------------------------------EXECUTOR.c------------------------------------
//==============================================================================
t_pars	**executor(t_pars **pars);

//==============================================================================
//--------------------------------DUPING.c--------------------------------------
//==============================================================================
void	smart_close(int fd1, int fd2, int fd3, int fd4);
void	dup_output(int outpipe, t_pars *pars);
void	dup_input(int inpipe, t_pars *pars);
void	dup_error(t_pars *pars);

//==============================================================================
//--------------------------------BUILTIN.c-------------------------------------
//==============================================================================
void	builtin(t_pars *pars);

//==============================================================================
//--------------------------------BUILTIN_IN_EXEC.c-----------------------------
//==============================================================================
int		b_echo(t_pars *pars);
int		b_pwd(t_pars *pars);
int		b_env(t_pars *pars);

//==============================================================================
//--------------------------------BUILTIN_NO_EXEC.c-----------------------------
//==============================================================================
int		b_cd(t_pars *pars);
char	**b_export(t_pars *pars);
char	**b_unset(t_pars *pars);
int		b_exit(t_pars **pars);

//==============================================================================
//--------------------------------PATH.c----------------------------------------
//==============================================================================
char	**get_path(char **env);
char	*check_path(t_pars *pars, char **path);

#endif