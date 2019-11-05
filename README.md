# ft_ls
As simple as listing the files in a directory.

# Usage
`$> ls [-RalrtSufgd] [file ...]`

# *TODO*:
**Main**
- [ ] Basic ls output
    - [ ] Update get_dir_files() to drop '.'-files on '-a' flag
    - [ ] Update list_dir() to store current terminal width in layout->win_width
    - [ ] Update update_layout() to calculate layout->max_name being the current longest name
    - [ ] Rewrite put_file() to pretty print determing on termina window width  
- [ ] Optimize list_sort?
- [x] Verify -a (current basic bahaviour)
    - [ ] Fix on basic ls output completion
- [x] Verify -R
- [x] Verify -t
- [x] Verify and update -l
    - [x] Update flag macros to flags actually used in the project "lRartSufgd"
- [x] Check broken files/dir's (checked on restricted access dirs)

**Bonus**
- [ ] Add ACl parameters and extended attributes to '-l' output
- [ ] Basic ls output with responsive column count
- [ ] Flag '-u'
- [x] Flag '-f'
- [ ] Flag '-g'
- [ ] Flag '-d'
    - [ ] Fix newlines / spaces (should be auto-fixed on basic ls output)
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

# Flags
- '-f' flag force turns on '-a' flag
