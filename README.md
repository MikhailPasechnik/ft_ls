# ft_ls
As simple as listing the files in a directory.

# Usage
`$> ls [-RalrtSufgd] [file ...]`

0.64s user 1.64s system 26% cpu 8.624 total

# *TODO*:
**Main**
- Basic ls output
    - [ ] **BUG_FIX_NEEDED** : weird '&' sign appearing on basic output if symbolic link is in directory (see maintest on ls)
- [ ] **Optimize list_sort?**
- [ ] Clean up memory on finish at put_file_switch()
- [ ] NORMalize

**Bonus**
- [ ] Add ACl parameters and extended attributes to '-l' output
- [ ] Flag '-u'
- [ ] Color management of LSCOLORS env-defined colors ('-G' flag)


# *Legacy Edits*
- Basic ls output
    - [x] Read and output symbolic link reference
    - [x] Update get_dir_files() to drop '.'-files on '-a' flag
    - [x] Update list_dir() to store current terminal width in layout->w
    - [x] Update update_layout() to calculate layout->max_name being the current longest name
    - [x] Rewrite put_file() to pretty print determing on terminal window width
    - [x] Fix joint work with -R flag (dividing by zero somewhere AGAIN)
    - [x] gimme back the '-1' flag
- Verify and update -l
    - [x]  Read and output symbolic link reference
    - [x] Update flag macros to flags actually used in the project "lRartSufgd"
- Verify -a (current basic bahaviour)
    - [x] Fix on basic ls output completion
- Verify -R
- Verify -t
- Check broken files/dir's (checked on restricted access dirs)
- Bonuses
    - [x] Responsive basic output
    - [x] Flag '-S'
    - [x] Flag '-f'
    - [x] Flag '-g' (ommit owner)
    - [x] Flag '-d'
        - [x] Fix newlines / spaces (should be auto-fixed on basic ls output)

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
