#ifndef FT_LS_H
#define FT_LS_H
# include "libft.h"
# include "ft_printf.h"

# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <dirent.h>
# include <limits.h>
# include <uuid/uuid.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <time.h>
# include <errno.h>

# define LS_STATUSOK 0
# define LS_STATUSMP 1
# define LS_STATUSST 2
# define LSE_NODIR "ft_ls: cannot access '%s': No such file or directory\n"

# define MAX(a, b)((a) > (b) ? (a) : (b))
# define IS_CD(s)(((s)[0] == '.' && (s)[1] == '\0'))
# define IS_UP(s)(((s)[0] == '.' && (s)[1] == '.' && (s)[2] == '\0'))


# define LSF_ALL "lRartSgd1"
# define LSF_L     (1u << 0u)
# define LSF_RR    (1u << 1u)
# define LSF_A     (1u << 2u)
# define LSF_R     (1u << 3u)
# define LSF_T     (1u << 4u)
# define LSF_S     (1u << 5u)
# define LSF_F     (1u << 6u)
# define LSF_G     (1u << 7u)
# define LSF_D     (1u << 8u)
# define LSF_1     (1u << 9u)
# define LSF_HELP  (1u << 10u)
# define LSF_MULTI  (1u << 11u)

typedef struct	s_list_layout
{
	int	st_blocks;
	int	st_nlink;
	int	pw_name;
	int	gr_name;
	int	st_size;
	int	st_rdev_minor;
	int	st_rdev_major;
	int	st_blocks_sum;
}				t_list_layout;

typedef struct	s_file t_file;

struct			s_file
{
	char				name[NAME_MAX + 1];
	char				file_name[PATH_MAX];
	struct stat			stat;
	t_file				*next;
};

/*
** File struct functions
*/
int				new_file(const char dir_name[PATH_MAX],
		const struct dirent *ent, t_file **file);

/*
** File info
*/
char			*get_chmod_str(char *str, mode_t mode);
char			*get_time_str(char str[12], time_t time);
int				full_path(
		const char dir_name[PATH_MAX],
		const char name[NAME_MAX + 1],
		char result[PATH_MAX]);
void			update_layout(t_file *file, t_list_layout *l);

/*
** Utils
*/
int				int_len(int n);
int				ls_put_error(char *error, char *dir_name, int returns);
int				display_help();
int				unrecognized_option(char *option, size_t len);

/*
** Print functions
*/
void			put_list_file(t_file *file, t_list_layout *lay,
		unsigned int flags);

/*
** Parse
*/
int		parse_options(char *options, unsigned int *flags);

/*
** Sort
*/
void	sort_list(t_file **list, unsigned int flags);

#endif
