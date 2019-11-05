/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:35:30 by caellis           #+#    #+#             */
/*   Updated: 2019/11/05 18:30:20 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_dir_files(char *dir_name, t_file **list, t_list_layout *layout, unsigned int flags)
{
	struct dirent	*ent;
	DIR				*dir;

	if ((dir = opendir(dir_name)) == NULL)
		return (ls_put_error(strerror(errno), dir_name, LS_STATUSST));
	*list = NULL;
	layout ? ft_bzero(layout, sizeof(*layout)) : (void)0;
	errno = 0;
	while ((ent = readdir(dir)) != NULL)
	{
		if (new_file(dir_name, ent, list))
		{
			flags & LSF_L ? update_layout(*list, layout) : (void)0;
			flags & LSF_D ? ft_strcpy((*list)->name, dir_name) : (void)0;
			list = &(*list)->next;
		}
		if (flags & LSF_D)
			break ;
	}
	closedir(dir);
	if (errno == EBADF)
		return (ls_put_error(strerror(errno), dir_name, LS_STATUSST));
	return (LS_STATUSOK);
}

static void put_file_switch(t_file *file, t_list_layout *layout, unsigned int flags)
{
	if (flags & LSF_L)
		file_iter(file, layout, flags, put_list_file);
	else
	{
		// Переписать с учетом win_width и max_name
		while (file)
		{
			put_file(file, layout, flags);
			flags & LSF_1 ? ft_putstr("\n") : (void)0;
			file = file->next;
		}
	}
}

int		list_dir(char *dir_name, unsigned int flags)
{
	t_file			*list;
	t_list_layout	layout;

	if (get_dir_files(dir_name, &list, &layout, flags) != LS_STATUSOK)
		return (0);
	flags & LSF_F ? (void)0 : sort_list(&list, flags);
	(flags & LSF_MULTI && !(flags & LSF_D)) || flags & LSF_RR ? ft_printf("%s:\n", dir_name) : (void)0;
	flags & LSF_L ? ft_printf("total %d\n", layout.st_blocks_sum) : (void)0;
	put_file_switch(list, &layout, flags);
	flags & LSF_RR ? ft_putstr("\n") : (void)0;
	list && flags & LSF_RR ? put_file_recursive(list, flags) : (void)0;
	return (1);
}


int main(int argc, char **argv)
{
	int				i;
	unsigned int	flags;

	i = 1;
	flags = 0;

	while (i < argc && argv[i][0] == '-')
		parse_options(argv[i++], &flags);
	flags |= (i < argc - 1) ? LSF_MULTI : 0;
	if (i >= argc)
		list_dir(".", flags);
	else
		while (i < argc)
		{
			list_dir(argv[i++], flags);
			ft_putstr("\n");
		}
	return (0);
}
