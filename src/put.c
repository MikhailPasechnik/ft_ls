/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:01:51 by bnesoi            #+#    #+#             */
/*   Updated: 2019/11/11 14:55:14 by caellis          ###   ########.fr       */
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
	char			files[l->n_files + 1][NAME_MAX + 1];
	char			out[l->n_files * (l->max_name + 1) + 1];
	char			*tmp;
	unsigned short	i;
	unsigned short	pos;
	unsigned short	offset;

	ft_bzero((void *)out, sizeof(l->n_files * (l->max_name + 1) + 1));
	i = 0;
	tmp = out;
	(void)flags;
	while (f)
	{
		ft_strcpy(files[i], f->name);
		files[i][NAME_MAX] = '\0';
		i++;
		f = f->next;
	}
	i = 0;
	//ft_printf("win width is %lu\nmax_name is..%lu\ncols is..%lu\nrows is..%lu\nnum of files is..%lu\n", l->w.ws_col, l->max_name, l->cols, l->rows, l->n_files);
	offset = 0;
	while (i < l->rows)
	{
		pos = i;
		while (pos <= l->n_files)
		{
			offset += ft_sprintf(tmp + offset, "%-*s ", l->max_name, files[pos]);
			pos += l->rows;
		}
		
		ft_strcpy(tmp + offset, "\n");
		offset++;
		i++;
	}
	ft_putstr(out);
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

void put_file_switch(t_file *file, t_list_layout *l, unsigned int flags)
{
	if (flags & LSF_L)
		file_iter(file, l, flags, put_list_file);
	else
	{
		l->cols = l->w.ws_col / (l->max_name + 1) == 0 ? 1 : l->w.ws_col / (l->max_name + 1) - 1;
		l->rows = l->n_files / l->cols ? l->n_files / l->cols : 1;
		//ft_printf("win width is %lu\nmax_name is..%lu\ncols is..%lu\nrows is..%lu\nnum of files is..%lu\n", l->w.ws_col, l->max_name, l->cols, l->rows, l->n_files);
		put_file(file, l, flags);
	}
	// Clean up here
}