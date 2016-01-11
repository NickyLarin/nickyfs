#include <stdlib.h>
#include <stdio.h>

#include "disk.h"
#include "superblock.h"
#include "fs_block.h"
#include "freespace.h"

int main(void) {
    diskOpen("disk.dat");
    createSuperBlock(1024*1024*1024, 4096);
    initFreeSpace();
    createFreeSpaceList();
    disposeFreeSpace();
    diskClose();
    return 0;
}
