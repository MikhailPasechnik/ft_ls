/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:01:51 by bnesoi            #+#    #+#             */
/*   Updated: 2019/10/20 19:47:19 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_list_file(t_file *file, t_list_layout *lay, unsigned int flags)
{
	char			str_chmod[12];
	char			str_time[12];
	struct passwd	*pw;
	struct group	*gr;

	(void)flags;
	pw = getpwuid(file->stat.st_uid);
	gr = getgrgid(file->stat.st_gid);
	ft_printf("%s ", get_chmod_str(str_chmod, file->stat.st_mode));
	ft_printf(
			"%*lu %*s %*s %*ld %.12s %s\n",
			lay->st_nlink, file->stat.st_nlink, lay->pw_name, pw->pw_name,
			lay->gr_name, gr->gr_name, lay->st_size, file->stat.st_size,
			get_time_str(str_time, file->stat.ST_MTIME.tv_sec),
			file->name);
}
