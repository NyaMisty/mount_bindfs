
#include <sys/mount.h>

int main(int argc, char **argv) {
    mount("bindfs", argv[1], MNT_UPDATE, argv[2]);
}
