/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:12:42 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/20 19:12:51 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	char_at(const char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int			parse_options(char *options, unsigned int *flags)
{
	int		i;
	int		at;

	if (options[0] == '-' && options[1] == '-')
	{
		if (ft_strcmp(options, "--help") == 0)
			display_help();
		unrecognized_option(options, ft_strlen(options));
	}
	i = 1;
	while (options[i])
	{
		at = char_at(LSF_ALL, options[i]);
		if (at < 0)
			unrecognized_option(options, 1);
		*flags |= (1u << at);
		i++;
	}
	return (0);
}
