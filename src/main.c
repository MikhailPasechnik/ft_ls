/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ch3rryhq <ch3rryhq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:35:30 by caellis           #+#    #+#             */
/*   Updated: 2019/10/30 12:44:43 by ch3rryhq         ###   ########.fr       */
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
		put_list_file(file, layout, flags);
	else
    {
        put_file(file, layout, flags);
        flags & LSF_1 ? ft_putstr("\n") : (void)0;
    }
}

// TODO: Simplify!
int		list_dir(char *dir_name, unsigned int flags)
{
	t_file			*list;
	t_file			*tmp;
	t_list_layout	layout;

	if (get_dir_files(dir_name, &list, &layout, flags) != LS_STATUSOK)
		return (0);
	tmp = list;
	flags & LSF_F ? (void)0 : sort_list(&list, flags);
	(flags & LSF_MULTI && !(flags & LSF_D)) || flags & LSF_RR ? ft_printf("%s:\n", dir_name) : (void)0;
	flags & LSF_L ? ft_printf("total %d\n", layout.st_blocks_sum) : (void)0;
    while (list)
	{
		put_file_switch(list, &layout, flags);
		list = list->next;
	}
	ft_putstr("\n");
	list = tmp;
	while (list && flags & LSF_RR)
	{
		if (flags & LSF_RR && S_ISDIR(list->stat.st_mode) && !IS_CD(list->name) && !IS_UP(list->name))
		{
			ft_putstr("\n");
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
		{
			list_dir(argv[i++], flags);
			ft_putstr("\n");
		}
	return (0);
}
