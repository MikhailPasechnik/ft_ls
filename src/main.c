#include "ft_ls.h"


int		list_dir(char *dir_name, unsigned int flags)
{
	struct dirent	*ent;
	t_file			*list;
	t_file			*tmp;
	t_file			**it;
	t_list_layout	layout;
	DIR				*dir;

	if ((dir = opendir(dir_name)) == NULL)
		return (ls_put_error(LSE_NODIR, dir_name, LS_STATUSST));
	list = NULL;
	it = &list;
	ft_bzero(&layout, sizeof(layout));
	while ((ent = readdir (dir)) != NULL) {
		if (new_file(dir_name, ent, it))
		{
			update_layout(*it, &layout);
			it = &(*it)->next;
		}
	}
	flags & LSF_MULTI ? ft_printf("%s:\n", dir_name) : 0;
	ft_printf("total %d\n", layout.st_blocks_sum);
	while (list)
	{
		put_list_file(list, &layout, flags);
		if (flags & LSF_RR && S_ISDIR(list->stat.st_mode) && !IS_CD(list->name) && !IS_UP(list->name))
			list_dir(list->file_name, flags);
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
	while (i < argc)
		list_dir(argv[i++], flags);
	return (0);
}
