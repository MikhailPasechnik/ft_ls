/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:35:30 by caellis           #+#    #+#             */
/*   Updated: 2019/10/28 15:16:39 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_dir_files(char *dir_name, t_file **list, t_list_layout *layout, unsigned int flags)
{
	struct dirent	*ent;
	DIR				*dir;

	if ((dir = opendir(dir_name)) == NULL)
		return (ls_put_error(LSE_NODIR, dir_name, LS_STATUSST));
	*list = NULL;
	layout ? ft_bzero(layout, sizeof(*layout)) : 0;
	// To distinguish between an end-of-directory condition or an error,
	// you must set errno to zero before calling readdir.
	errno = 0;
	while ((ent = readdir(dir)) != NULL)
	{
		if (new_file(dir_name, ent, list))
		{
			(flags & LSF_L) ? update_layout(*list, layout) : 0;
			list = &(*list)->next;
		}
	}
	if (errno == EBADF)
		return (ls_put_error(LSE_NODIR, dir_name, LS_STATUSST));
	return (LS_STATUSOK);
}

static void put_file_switch(t_file *file, t_list_layout *layout, unsigned int flags)
{
	if (flags & LSF_L)
		put_list_file(file, layout, flags);
	else
		put_file(file, layout, flags);
}

// TODO: Simplify!
int		list_dir(char *dir_name, unsigned int flags)
{
	t_file			*list;
	t_file			*tmp;
	t_list_layout	layout;

	if (get_dir_files(dir_name, &list, &layout, flags) != LS_STATUSOK)
		return (0);
	sort_list(&list, flags);
	flags & LSF_MULTI || flags & LSF_RR ? ft_printf("%s:\n", dir_name) : 0;
	if (flags & LSF_L)
		ft_printf("total %d\n", layout.st_blocks_sum);
	tmp = list;
	while (list)
	{
		put_file_switch(list, &layout, flags);
		list = list->next;
	}
	list = tmp;
	while (list && flags & LSF_RR)
	{
		if (flags & LSF_RR && S_ISDIR(list->stat.st_mode) && !IS_CD(list->name) && !IS_UP(list->name))
		{
			ft_printf("\n");
			list_dir(list->file_name, flags);
		}
		tmp = list;
		list = list->next;
		free(tmp);
	}
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
			list_dir(argv[i++], flags);
	return (0);
}
