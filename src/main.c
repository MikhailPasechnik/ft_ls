#include <time.h>
#include <assert.h>
#include <errno.h>
#include "ft_ls.h"
#include <libexplain/lstat.h>
//static char		get_file_acl(char path[PATH_MAX])
//{
//	acl_t	tmp;
//	char	buf[101];
//
//	if (listxattr(path, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
//		return ('@');
//	if ((tmp = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
//	{
//		acl_free(tmp);
//		return ('+');
//	}
//	return (' ');
//}

static inline char		type_from_mode(mode_t mode)
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


static char *get_chmod(char str[12], mode_t mode)
{
	str[0] = type_from_mode(mode);
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

static char *get_time(char str[12], time_t time)
{
	ft_strncpy(str, ctime(&time) + 4, 12);
	return (str);
}

static int		full_path(
		const char dir_name[PATH_MAX],
		const char name[NAME_MAX + 1],
		char result[PATH_MAX])
{
	int	i;

	i = ft_strlen(dir_name);
	ft_strncpy(result, dir_name, i);
	if (!(*dir_name == '/' && i == 1 && i < PATH_MAX))
	 	result[i++] = '/';
	while (*name && i < PATH_MAX)
		result[i++] = *name++;
	if (i < PATH_MAX)
	{
		result[i] = '\0';
		return (1);
	}
	errno = ENAMETOOLONG;
	return (0);
}

int new_file(const char dir_name[PATH_MAX], const struct dirent *ent, t_file **file, int stat)
{
	if (!(*file = ft_memalloc(sizeof(t_file))))
		return (0);
	if (!(full_path(dir_name, ent->d_name, (*file)->file_name)) ||
		(!stat || lstat((*file)->file_name, &(*file)->stat) < 0))
	{
		*file ? free(*file) : 0;
		return (0);
	}
	ft_strcpy((*file)->name, ent->d_name);
	return (1);
}

int		walk_dir(char *dir_name, unsigned int flags)
{
	struct dirent 	*ent;
	struct passwd	*pw;
	struct group 	*gr;
	t_file	*list;
	t_file	**it;
	char str_chmod[12];
	char str_time[12];
	DIR *dir;
	list = NULL;
	it = &list;
	if ((dir = opendir(dir_name)) == NULL)
		return (0);
	while ((ent = readdir (dir)) != NULL) {
		if (new_file(dir_name, ent, it, 1))
			it = &(*it)->next;
	}
	while (list)
	{
		pw = getpwuid(list->stat.st_uid);
		gr = getgrgid(list->stat.st_gid);
		printf("%s ", get_chmod(str_chmod, list->stat.st_mode));
		printf ("%lu %s %s %ld %.12s %s\n", list->stat.st_nlink, pw->pw_name, gr->gr_name, list->stat.st_size, get_time(str_time, list->stat.st_ctime), list->name);
		list = list->next;
	}
	return (1);
}

int		ls(char *dir_name)
{
	walk_dir(dir_name, 0);
	return (1);
}


int main(int argc, char **argv)
{
	struct stat 	st;
	if (lstat("./libft/Makefile", &st) < 0)
	{
		int err = errno;
		fprintf(stderr, "%s", explain_errno_lstat(err, "./libft/Makefile", &st));
		exit(EXIT_FAILURE);
	}
	ls("/");
	(void)argv;
	(void)argc;
//	write
//	opendir
//	readdir
//	closedir
//	stat
//	lstat
//	getpwuid
//	getgrgid
//	listxattr
//	getxattr
//	time
//	ctime
//	readlink
//	malloc
//	free
//	perror
//	strerror
//	exit
	return (0);
}
