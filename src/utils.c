/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:12:35 by bnesoi            #+#    #+#             */
/*   Updated: 2019/11/13 16:37:22 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	int_len(int n)
{
	size_t		len;

	len = 1;
	while (n / 10)
	{
		n /= 10;
		++len;
	}
	return (len);
}

int		ls_put_error(char *error, char *dir_name, int returns)
{
	ft_fprintf(STDERR_FILENO, "ft_ls: %s: %s\n", dir_name, error);
	return (returns);
}

int		display_help(void)
{
	ft_printf(
	"Usage: ft_ls [OPTION]... [FILE]...\n"
	"List information about the FILEs (the current directory by default).\n"
	"Sort entries alphabetically if none of -tu nor --sort is specified.\n\n"
	"  -l      use a long listing format\n"
	"  -R      list subdirectories recursively\n"
	"  -a      do not ignore entries starting with .\n"
	"  -r      reverse order while sorting\n"
	"  -t      sort by modification time, newest first\n"
	"  -u      with -lt: sort by, and show, access time;\n"
	"            with -l: show access time and sort by name;\n"
	"            otherwise: sort by access time, newest first\n"
	"  -f      do not sort\n"
	"  -g      like -l, but do not list owner\n"
	"  -d      list directories themselves, not their contents\n"
	"  -1      list one file per line.\n"
	"  --help  display this help and exit\n");
	exit(LS_STATUSOK);
}

int		unrecognized_option(char *option, size_t len)
{
	ft_fprintf(STDERR_FILENO,
	"ls: unrecognized option '%.*s'\n"
	"Try 'ft_ls --help' for more information.\n",
	len, option);
	exit(LS_STATUSST);
}
