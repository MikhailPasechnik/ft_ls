#include "ft_ls.h"

static inline char			get_type_char(mode_t mode)
{
	char	type;

	type = '-';
	mode = mode & S_IFMT;

	if (S_ISREG(mode))
		type = '-';
	else if (S_ISDIR(mode))
		type = 'd';
	else if (S_ISCHR(mode))
		type = 'c';
	else if (S_ISLNK(mode))
		type = 'l';
	else if (S_ISBLK(mode))
		type = 'b';
	else if (S_ISSOCK(mode))
		type = 's';
	else if (S_ISFIFO(mode))
		type = 'p';
	return (type);
}


inline char					*get_chmod_str(char *str, mode_t mode)
{
	str[0] = get_type_char(mode);
	str[1] = (mode & S_IRUSR) ? 'r' : '-';
	str[2] = (mode & S_IWUSR) ? 'w' : '-';
	str[3] = (mode & S_IXUSR) ? 'x' : '-';
	if (S_ISUID & mode)
		str[3] = 's' - 32 * (str[3] == '-');
	str[4] = (mode & S_IRGRP) ? 'r' : '-';
	str[5] = (mode & S_IWGRP) ? 'w' : '-';
	str[6] = (mode & S_IXGRP) ? 'x' : '-';
	if (S_ISGID & mode)
		str[6] = 's' - 32 * (str[6] == '-');
	str[7] = (mode & S_IROTH) ? 'r' : '-';
	str[8] = (mode & S_IWOTH) ? 'w' : '-';
	str[9] = (mode & S_IXOTH) ? 'x' : '-';
	if (S_ISVTX & mode)
		str[9] = 't' - 32 * (str[9] == '-');

	str[10] = ' ';  // TODO: get file acl: "@" or "+" or " "
	str[11] = '\0';
	return (str);
}


int		full_path(
		const char dir_name[PATH_MAX],
		const char name[NAME_MAX + 1],
		char result[PATH_MAX])
{
	int	i;

	i = ft_strlen(dir_name);
	if (i < PATH_MAX)
	{
		ft_strncpy(result, dir_name, i);
		if (!(i == 1 && *dir_name == '/' ))
			result[i++] = '/';
		while (*name && i < PATH_MAX)
			result[i++] = *name++;
		if (i < PATH_MAX)
		{
			result[i] = '\0';
			return (1);
		}
	}
	errno = ENAMETOOLONG;
	return (0);
}

inline char *get_time_str(char str[12], time_t time)
{
	ft_strncpy(str, ctime(&time) + 4, 12);
	return (str);
}

void update_layout(t_file *file, t_list_layout *l)
{
	l->st_blocks = MAX(int_len(file->stat.st_blocks), l->st_blocks);
	l->st_nlink = MAX(int_len(file->stat.st_nlink), l->st_nlink);
	l->pw_name = MAX(ft_strlen(getpwuid(file->stat.st_uid)->pw_name), l->pw_name);
	l->gr_name = MAX(ft_strlen(getgrgid(file->stat.st_gid)->gr_name), l->gr_name);
	if (!S_ISCHR(file->stat.st_mode))
		l->st_size = MAX(int_len(file->stat.st_size), l->st_size);
	else
	{
		l->st_rdev_major = MAX(int_len(major(file->stat.st_rdev)),
							   l->st_rdev_major);
		l->st_rdev_minor = MAX(int_len(minor(file->stat.st_rdev)),
							   l->st_rdev_minor);
	}
	l->st_blocks_sum += file->stat.st_blocks;
}
