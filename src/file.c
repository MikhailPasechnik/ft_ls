#include "ft_ls.h"

int new_file(const char dir_name[PATH_MAX], const struct dirent *ent, t_file **file)
{
	if (!(*file = ft_memalloc(sizeof(t_file))))
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
