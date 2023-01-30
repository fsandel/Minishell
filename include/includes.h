/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:45:31 by fsandel           #+#    #+#             */
/*   Updated: 2023/01/30 16:16:56 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> //write, access, read, close, fork, getcwd, chdir, unlink
						//execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <stdio.h> //printf, strerror, perror
# include <fcntl.h> //open
# include <sys/wait.h> //wait, waitpid, wait3, wait4
# include <signal.h> //signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h> //stat, lstat, fstat
# include <dirent.h> //opendir, readdir, closedir
# include <sys/ioctl.h> //ioctl
# include <termios.h> //tcsetattr tcgetattr
# include <curses.h> // tgetent, tgetflag tgetstr, tgoto, tpus
# include <term.h>

# include "../src/executor/executor.h"
# include "../src/parser/parser.h"
# include "../src/expander/expander.h"
# include "../src/lexer/lexer.h"
# include "../src/parser/parser.h"
# include "../src/rest/rest.h"
# include "../src/utils/utils.h"

# include "defines.h"
# include "structs.h"
# include "macros.h"

# include "../lib/libft/libft.h"
# include "readline/readline.h"
# include "readline/history.h"

//#include <readline/readline.h>
//#include <readline/history.h>

#endif