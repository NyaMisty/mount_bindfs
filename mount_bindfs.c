//#include <sys/param.h>
#include <sys/mount.h>

#include <err.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mntopts.h"

#define BINDFS_MOUNT_TYPE   "bindfs"

void    usage __P((void));

struct mntopt mopts[] = {
    MOPT_STDOPTS,
    { NULL }
};

int main(int argc, char **argv) {
    int mntflags;
    char target[MAXPATHLEN], canon_dir[MAXPATHLEN];

    int ch;
    while ((ch = getopt(argc, argv, "o:")) != -1)
        switch(ch) {
        case 'o':
            getmntopts(optarg, mopts, &mntflags, 0);
            break;
        case '?':
        default:
            usage();
        }
    argc -= optind;
    argv += optind;

    //mntflags = 0;
    //argc--;
    //argv++;

    if (argc != 2)
        usage();

    if (realpath(argv[0], target) == NULL)
        err(1, "realpath %s", argv[0]);
    if (strncmp(argv[0], target, MAXPATHLEN)) {
        //warnx("\"%s\" is a relative path.", argv[0]);
        //warnx("using \"%s\" instead.", target);
    }

    if (realpath(argv[1], canon_dir) == NULL)
        err(1, "realpath %s", argv[1]);
    if (strncmp(argv[1], canon_dir, MAXPATHLEN)) {
        //warnx("\"%s\" is a relative path.", argv[1]);
        //warnx("using \"%s\" instead.", canon_dir);
    }

    if (strcmp(target, canon_dir) == 0)
        errx(1, "%s (%s) and %s (%s) are identical paths",
            argv[0], target, argv[1], canon_dir);

    if (mount(BINDFS_MOUNT_TYPE, canon_dir, mntflags, (void*)target) == -1)
        err(1, "%s on %s", target, canon_dir);
    exit(0);
}

void usage() {
    (void)fprintf(stderr,
        "usage: mount_bindfs [-o options] target mount_point\n");
    exit(1);
}
