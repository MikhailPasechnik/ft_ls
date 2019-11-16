/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_list_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:01:51 by bnesoi            #+#    #+#             */
/*   Updated: 2019/11/16 14:25:52 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_chmod_gr(t_file *f, t_list_layout *l, unsigned int flags)
{
	char			str_chmod[12];
	struct passwd	*pw;
	struct group	*gr;

	pw = getpwuid(f->stat.st_uid);
	gr = getgrgid(f->stat.st_gid);
	ft_printf("%s ", get_chmod_str(str_chmod, f->stat.st_mode));
	if (flags & LSF_G)
		ft_printf("%*lu %-*s  ",
				l->st_nlink, f->stat.st_nlink, l->gr_name, gr->gr_name);
	else
		ft_printf("%*lu %-*s  %-*s  ",
			l->st_nlink, f->stat.st_nlink, l->pw_name, pw->pw_name,
			l->gr_name, gr->gr_name);
}

void		put_list_file(t_file *f, t_list_layout *l, unsigned int flags)
{
	char			str_time[12];
	char			str_dev[12];
	char			link[NAME_MAX + 1];

	put_chmod_gr(f, l, flags);
	ft_printf("%*s%s %*ld %.12s %s",
		l->st_rdev_major, S_ISCHR(f->stat.st_mode) ?
		ft_itoa_base_ext(str_dev, major(f->stat.st_rdev), 10, 0) : "",
		S_ISCHR(f->stat.st_mode) ? "," : "",
		S_ISCHR(f->stat.st_mode) ? l->st_rdev_minor : l->st_size,
		S_ISCHR(f->stat.st_mode) ? minor(f->stat.st_rdev) : f->stat.st_size,
		get_time_str(str_time, f->stat.ST_MTIME.tv_sec), f->name);
	if (S_ISLNK(f->stat.st_mode))
	{
		ft_bzero(link, NAME_MAX + 1);
		readlink(f->file_name, link, NAME_MAX);
		ft_printf(" -> %s\n", link);
	}
	else
		ft_printf("\n");
}
