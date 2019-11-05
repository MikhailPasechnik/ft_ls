/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:01:51 by bnesoi            #+#    #+#             */
/*   Updated: 2019/11/05 18:30:05 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_list_file(t_file *f, t_list_layout *l, unsigned int flags)
{
	char			str_chmod[12];
	char			str_time[12];
	struct passwd	*pw;
	struct group	*gr;

	(void)flags;
	pw = getpwuid(f->stat.st_uid);
	gr = getgrgid(f->stat.st_gid);
	ft_printf("%s ", get_chmod_str(str_chmod, f->stat.st_mode));
	ft_printf(
			"%*lu %*s %*s %*ld %.12s %s\n",
			l->st_nlink, f->stat.st_nlink, l->pw_name, pw->pw_name,
			l->gr_name, gr->gr_name, l->st_size, f->stat.st_size,
			get_time_str(str_time, f->stat.ST_MTIME.tv_sec),
			f->name);
}

void	put_file(t_file *f, t_list_layout *l, unsigned int flags)
{
	(void)l;
	(void)flags;
	ft_printf("%s ", f->name);
}

void	put_file_recursive(t_file *file, unsigned int flags)
{
	t_file	*tmp;

	while (file)
	{
		if (S_ISDIR(file->stat.st_mode) && !IS_CD(file->name) && !IS_UP(file->name))
		{
			ft_putstr("\n");
			list_dir(file->file_name, flags);
		}
		tmp = file;
		file = file->next;
		free(tmp);
	}
}