/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 19:39:43 by bnesoi            #+#    #+#             */
/*   Updated: 2019/11/14 17:31:43 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
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
# define LS_STATUSST 1
# define LSE_NODIR "ft_ls: %s: No such file or directory\n"

# define MAX(a, b)((a) > (b) ? (a) : (b))
# define IS_CD(s)(((s)[0] == '.' && (s)[1] == '\0'))
# define IS_UP(s)(((s)[0] == '.' && (s)[1] == '.' && (s)[2] == '\0'))
# define IS_DOT(s)(((s)[0] == '.'))
# define LS_L_OUT_SHORT ft_printf("%*lu %-*s  %*ld %.12s %s%s%s\n",\
			l->st_nlink, f->stat.st_nlink, l->gr_name, gr->gr_name,\
			l->st_size, f->stat.st_size,\
			get_time_str(str_time, f->stat.ST_MTIME.tv_sec), f->name,\
			S_ISLNK(f->stat.st_mode) ? " -> " : "",\
			S_ISLNK(f->stat.st_mode) ? link : "")
# define LS_L_OUT_LONG ft_printf("%*lu %-*s  %-*s  %*ld %.12s %s%s%s\n",\
			l->st_nlink, f->stat.st_nlink, l->pw_name, pw->pw_name,\
			l->gr_name, gr->gr_name, l->st_size, f->stat.st_size,\
			get_time_str(str_time, f->stat.ST_MTIME.tv_sec), f->name,\
			S_ISLNK(f->stat.st_mode) ? " -> " : "",\
			S_ISLNK(f->stat.st_mode) ? link : "")

# ifdef __APPLE__
 # define ST_MTIME st_mtimespec
# else
 # define ST_MTIME st_mtim
# endif

/*
** Flags
** NOTE: It is important to keep LSF_ALL order and LSF_* flags order the same
*/
# define LSF_ALL   "lRartSufgd1"
# define LSF_L     (1u << 0u)
# define LSF_RR    (1u << 1u)
# define LSF_A     (1u << 2u)
# define LSF_R     (1u << 3u)
# define LSF_T     (1u << 4u)
# define LSF_S     (1u << 5u)
# define LSF_U     (1u << 6u)
# define LSF_F     (1u << 7u)
# define LSF_G     (1u << 8u)
# define LSF_D     (1u << 9u)
# define LSF_1     (1u << 10u)
# define LSF_HELP  (1u << 11u)
# define LSF_MULTI (1u << 12u)
# define LSF_FILES (1u << 13u)
# define LSF_ATTY (1u << 14u)

typedef struct	s_list_layout
{
	size_t			st_blocks;
	size_t			st_nlink;
	size_t			pw_name;
	size_t			gr_name;
	size_t			st_size;
	size_t			st_rdev_minor;
	size_t			st_rdev_major;
	size_t			st_blocks_sum;
	unsigned short	maxlen;
	unsigned short	n_files;
	unsigned short	cols;
	unsigned short 	rows;
	struct winsize	w;
}				t_list_layout;

typedef struct s_file	t_file;

struct			s_file
{
	char				name[NAME_MAX + 1];
	char				file_name[PATH_MAX];
	struct stat			stat;
	t_file				*next;
};

/*
** List dir function
*/
int		list_dir(char *dir_name, unsigned int flags);

/*
** File struct functions
*/
int				new_file(const char dir_name[PATH_MAX],
		const struct dirent *ent, t_file **file);
void			file_iter(t_file *file, t_list_layout *layout, unsigned int flags,
		void (*f)(t_file *file, t_list_layout *layout, unsigned int flags));
void	        file_free(t_file **file);
void			file_to_tab(char tab[][NAME_MAX + 1], t_file *f);

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
size_t			int_len(int n);
int				ls_put_error(char *error, char *dir_name, int returns);
int				display_help();
int				unrecognized_option(char *option, size_t len);

/*
** Print functions
*/
void			put_list_file(t_file *f, t_list_layout *l,
							unsigned int flags);
void			put_file(t_file *f, t_list_layout *l,
							unsigned int flags);
void			put_file_recursive(t_file *file, unsigned int flags);
void 			put_file_switch(t_file *file, t_list_layout *l,
		unsigned int flags);
/*
** Parse
*/
int				parse_options(char *options, unsigned int *flags);

/*
** Sort
*/
void			sort_list(t_file **list, unsigned int flags);

#endif
