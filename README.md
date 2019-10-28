# ft_ls
As simple as listing the files in a directory.

# Usage
`$> ls [-RalrtSufgd] [file ...]`

# *TODO*:
**Main**
- [ ] Basic ls output
- [ ] Optimize list_sort?
- [x] Verify -R
- [x] Verify -a
- [x] Verify -t
- [ ] Verify and update -l (get rid of . and .. in output)
    - [x] Update flag macros to flags actually used in the project "lRartSufgd"
- [x] Check broken files/dir's (checked on restricted access dirs)

**Bonus**
- [ ] Add ACl parameters and extended attributes to '-l' output
- [ ] Basic ls output with responsive column count
- [ ] Flags '-u', '-f', '-g', '-d' (?)
- [ ] (?)Management of terminal colors ('-G')

# Limitations
Allowed standard functions:
- write
- opendir
- readdir
- closedir
- stat
- lstat
- getpwuid
- getgrgid
- listxattr
- getxattr
- time
- ctime
- readlink
- malloc
- free
- perror
- strerror
- exit
