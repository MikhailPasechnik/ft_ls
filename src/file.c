/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ch3rryhq <ch3rryhq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:12:57 by bnesoi            #+#    #+#             */
/*   Updated: 2019/11/13 19:18:37 by ch3rryhq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		new_file(const char dir_name[PATH_MAX],
	const struct dirent *ent, t_file **file)
{
	if (!(*file = (t_file *)ft_memalloc(sizeof(t_file))))
		return (0);
	if (!(full_path(dir_name, ent->d_name, (*file)->file_name)) ||
		lstat((*file)->file_name, &(*file)->stat) < 0)
	{
		*file ? free(*file) : 0;
		return (0);
	}
	ft_strcpy((*file)->name, ent->d_name);
	return (1);
}

void	file_to_tab(char tab[][NAME_MAX + 1], t_file *f)
{
	unsigned short	i;

	i = 0;
	while (f)
	{
		ft_strcpy(tab[i], f->name);
		tab[i][NAME_MAX] = '\0';
		i++;
		f = f->next;
	}
	return ;
}

void	file_iter(t_file *file, t_list_layout *layout, unsigned int flags,
				void (*f)(t_file *file, t_list_layout *layout, unsigned int flags))
{
	while (file && f)
	{
		f(file, layout, flags);
		file = file->next;
	}
}

void	file_free(t_file **file)
{
	t_file	*tmp;

	while (file && *file)
	{
		tmp = *file;
		*file = (*file)->next;
		free(tmp);
	}
	*file = NULL;
    return ;
}