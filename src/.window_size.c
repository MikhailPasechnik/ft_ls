#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/acl.h>

int main () {
    acl_t acl = NULL;
    acl_entry_t dummy;
    ssize_t xattr = 0;
    char chr;
    char * filename = "Makefile";

    // Getting ACL and extended attributes
    acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
    if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
        acl_free(acl);
        acl = NULL;
    }
    xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
    if (xattr < 0)
        xattr = 0;

    if (xattr > 0)
        chr = '@';
    else if (acl != NULL)
        chr = '+';
    else
        chr = ' ';

    printf("%c\n", chr);


    // Getting lines and columns of terminal
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
    return 0;
 }