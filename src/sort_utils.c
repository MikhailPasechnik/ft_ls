/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:36:11 by caellis           #+#    #+#             */
/*   Updated: 2019/11/15 15:36:38 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		name_cmp(t_file *a, t_file *b)
{
	return (ft_strcmp(a->name, b->name));
}

int		size_cmp(t_file *a, t_file *b)
{
	if (a->stat.st_size != b->stat.st_size)
		return (a->stat.st_size > b->stat.st_size ? -1 : 1);
	return (name_cmp(a, b));
}

int		time_cmp(t_file *a, t_file *b)
{
	int cmp_;

	cmp_ = 0;
	if (a->stat.ST_MTIME.tv_sec != b->stat.ST_MTIME.tv_sec)
		cmp_ = a->stat.ST_MTIME.tv_sec >
			b->stat.ST_MTIME.tv_sec ? -1 : 1;
	if (a->stat.ST_MTIME.tv_nsec != b->stat.ST_MTIME.tv_nsec)
		cmp_ = a->stat.ST_MTIME.tv_nsec >
			b->stat.ST_MTIME.tv_nsec ? -1 : 1;
	return (cmp_);
}
