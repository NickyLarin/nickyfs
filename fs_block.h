#ifndef FS_BLOCK_H
#define FS_BLOCK_H
int writeFsBlock(int position, int next, void *data, int _size);
int readFsBlock(int position, int *next, void *data, int _size);
#endif
