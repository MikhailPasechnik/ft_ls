# ft_ls
As simple as listing the files in a directory.

# Usage
`$> ls [-RalrtSufgd] [file ...]`

# *TODO*:
**Main**
- [ ] Basic ls output
    - [x] Update get_dir_files() to drop '.'-files on '-a' flag
    - [x] Update list_dir() to store current terminal width in layout->w
    - [x] Update update_layout() to calculate layout->max_name being the current longest name
    - [ ] Rewrite put_file() to pretty print determing on termina window width  
- [ ] Optimize list_sort?
- [x] Verify -a (current basic bahaviour)
    - [ ] Fix on basic ls output completion
- [x] Verify -R
- [x] Verify -t
- [x] Verify and update -l
    - [x] Update flag macros to flags actually used in the project "lRartSufgd"
- [x] Check broken files/dir's (checked on restricted access dirs)
- [ ] Clean up memory on finish
- [ ] NORMalize

**Bonus**
- [ ] Add ACl parameters and extended attributes to '-l' output
- [ ] Flag '-u'
- [x] Flag '-f'
- [ ] Flag '-g' (ommit owner)
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
