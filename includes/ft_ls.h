#ifndef FT_LS_H
#define FT_LS_H
# include "libft.h"

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

# include <stdio.h> // TODO: Use ft_printf

# define LSF_RR (1u << 0u);
# define LSF_L (1u << 1u);
# define LSF_A (1u << 2u);
# define LSF_R (1u << 3u);
# define LSF_T (1u << 4u);
# define LSF_U (1u << 5u);
# define LSF_F (1u << 6u);
# define LSF_G (1u << 7u);
# define LSF_D (1u << 8u);

typedef struct	s_file t_file;

struct	s_file
{
	char				name[NAME_MAX + 1];
	char				file_name[PATH_MAX];
	struct stat			stat;
	t_file				*next;
};

#endif
