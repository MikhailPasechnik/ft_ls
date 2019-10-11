#include "ft_ls.h"


int		list_dir(char *dir_name, unsigned int flags)
{
	struct dirent	*ent;
	t_file			*list;
	t_file			**it;
	t_list_layout	layout;
	DIR				*dir;

	if ((dir = opendir(dir_name)) == NULL)
		return (ls_put_error(LSE_NODIR, dir_name, LS_STATUSST));
	list = NULL;
	it = &list;
	ft_bzero(&layout, sizeof(layout));
	while ((ent = readdir (dir)) != NULL) {
		if (new_file(dir_name, ent, it, 1))
		{
			update_layout(*it, &layout);
			it = &(*it)->next;
		}
	}
	ft_printf("total %d\n", layout.st_blocks_sum);
	while (list)
	{
		put_list_file(list, &layout, flags);
		list = list->next;
	}
	return (1);
}


int main(int argc, char **argv)
{
	struct stat 	st;
	if (lstat("./libft/Makefile", &st) < 0)
	{
		int err = errno;
//		fft_printf(stderr, "%s", explain_errno_lstat(err, "./libft/Makefile", &st));
		exit(EXIT_FAILURE);
	}
	list_dir("/", 0);
	(void)argv;
	(void)argc;
	return (0);
}
