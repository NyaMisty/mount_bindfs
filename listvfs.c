#include <libkrw.h>
#include <stdio.h>

int main(int argc, char **argv) {
    uint64_t curbase = 0;
    if (!!kbase(&curbase)) return 1;
    uint64_t vfsconf = 0xFFFFFFF00981D5F8 + (curbase - 0xFFFFFFF007004000);
    while (1) {
        char curvfs[0x60] = {0};
        if (kread(vfsconf, curvfs, 0x60) != 0) {
            break;
        }
        uint64_t vfsop = *(uint64_t *)&curvfs[0];
        char *vfsname = &curvfs[0x8];
        uint64_t nextvfs = *(uint64_t *)&curvfs[0x30];
        printf("vfs: %s, op: %llx, next: %llx\n", vfsname, vfsop, vfsconf);
        if (!nextvfs || !vfsop) break;
        vfsconf = nextvfs;
    }
}

