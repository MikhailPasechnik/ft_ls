/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:01:51 by bnesoi            #+#    #+#             */
/*   Updated: 2019/11/16 14:25:52 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	tab_printer(char tab[][NAME_MAX + 1], char *out, t_list_layout *l)
{
	unsigned short	offset;
	unsigned short	i;
	unsigned short	pos;

	i = 0;
	offset = 0;
	while (i < l->rows)
	{
		pos = i++;
		while (pos < l->n_files)
		{
			offset += ft_sprintf(out + offset, "%-*s ",
				pos + l->rows < l->n_files ? l->maxlen : 1, tab[pos]);
			pos += l->rows;
		}
		ft_strcpy(out + offset++, "\n");
	}
	*(out + offset) = '\0';
	ft_putstr(out);
}

static void	put_file(t_file *f, t_list_layout *l, unsigned int flags)
{
	char			files[l->n_files + 1][NAME_MAX + 1];
	char			out[l->n_files * (l->maxlen + 1) + 1];

	ft_bzero((void *)out, sizeof(l->n_files * (l->maxlen + 1) + 1));
	file_to_tab(files, f);
	tab_printer(files, out, l);
	(void)flags;
}

void		put_file_recursive(t_file *file, unsigned int *flags)
{
	t_file	*tmp;

	while (file)
	{
		if (S_ISDIR(file->stat.st_mode) &&
			!IS_CD(file->name) && !IS_UP(file->name))
		{
			(*flags) |= LSF_DIRS;
			ft_putstr("\n");
			list_dir(file->file_name, *flags);
		}
		tmp = file;
		file = file->next;
		free(tmp);
	}
}

void		put_file_switch(t_file *file, t_list_layout *l, unsigned int flags)
{
	if (flags & LSF_L)
		file_iter(file, l, flags, put_list_file);
	else if (flags & LSF_1)
	{
		while (file)
		{
			ft_printf("%s\n", file->name);
			file = file->next;
		}
	}
	else
	{
		l->cols = l->w.ws_col / (l->maxlen + 1) <= 1 ?
			1 : l->w.ws_col / (l->maxlen + 1) - 1;
		l->rows = l->n_files / l->cols ? l->n_files / l->cols : 1;
		put_file(file, l, flags);
	}
	if (!(flags & LSF_RR))
		file_free(&file);
}
