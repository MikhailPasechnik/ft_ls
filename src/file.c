/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:12:57 by bnesoi            #+#    #+#             */
/*   Updated: 2019/11/05 17:42:23 by caellis          ###   ########.fr       */
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

void	file_iter(t_file *file, t_list_layout *layout, unsigned int flags,
				void (*f)(t_file *file, t_list_layout *layout, unsigned int flags))
{
	while (file && f)
	{
		f(lst);
		file = file->next;
	}
}
