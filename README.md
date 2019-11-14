# ft_ls
As simple as listing the files in a directory.

# Usage
`$> ls [-RalrtSufgd] [file ...]`

# *TODO*:
**Main**
- [ ] Color management of LSCOLORS env-defined colors ('-G' flag)
- [ ] **Optimize list_sort?**
- [ ] NORMalize

**Bonus**
- [ ] Add ACl parameters and extended attributes to '-l' output
- [ ] Flag '-u'

# *Legacy Edits*
- Basic ls output
    - [x] **BUG_FIX_NEEDED** : weird '&' sign appearing on basic output if symbolic link is in 
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
- [X] Clean up memory on finish at put_file_switch()

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

# LSCOLORS ls Color Management 
As described in BSD General Commands Manual (May 19, 2002):
LSCOLORS
The value of this variable describes what color to use for which attribute when colors are enabled with CLICOLOR. This string is a concatenation of pairs of the format fb, where f is the foreground color and b is the background color.

The color designators are as follows:

a     black
b     red
c     green
d     brown
e     blue
f     magenta
g     cyan
h     light grey
A     bold black, usually shows up as dark grey
B     bold red
C     bold green
D     bold brown, usually shows up as yellow
E     bold blue
F     bold magenta
G     bold cyan
H     bold light grey; looks like bright white
x     default foreground or background
Note that the above are standard ANSI colors. The actual display may differ depending on the color capabilities of the terminal in use.

The order of the attributes are as follows:

1.   directory
2.   symbolic link
3.   socket
4.   pipe
5.   executable
6.   block special
7.   character special
8.   executable with setuid bit set
9.   executable with setgid bit set
10.  directory writable to others, with sticky bit
11.  directory writable to others, without sticky bit

The default is exfxcxdxbxegedabagacad (my default: Gxfxcxdxbxegedabagacad), i.e. blue foreground and default background for regular directories, black foreground and red background for setuid executables, etc.
