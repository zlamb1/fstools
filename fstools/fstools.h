#ifndef FSTOOLS_H
#define FSTOOLS_H 1

#include <stddef.h>
#include <stdint.h>

#define FST_OK 0
#define FST_ENOTDIR 0x1
#define FST_ENOENT 0x2
#define FST_ENOMEM 0x3
#define FST_EIO 0x4
#define FST_EISDIR 0x5
#define FST_EINVAL 0x6
#define FST_EOVERFLOW 0x7
#define FST_EOPNOTSUPP 0x8
#define FST_ENOTEMPTY 0x9
#define FST_EUNKNOWN 0xFF

#define FST_FT_REG 0
#define FST_FT_DIR 1
#define FST_FT_CHR 2
#define FST_FT_BLK 3
#define FST_FT_LNK 4
#define FST_FT_FIFO 5
#define FST_FT_SOCK 6

typedef void* fst_dir;
typedef uint64_t fst_off;
typedef uint64_t fst_size;
typedef int fst_status;
typedef unsigned int fst_type;

typedef struct {
	fst_type type;
	char* name;
} fst_dnode;

typedef struct {
	fst_type type;
	fst_size size;
} fst_inode;

typedef struct fst_volume {
	fst_status (*create)(struct fst_volume* volume,
						 const char* path,
						 fst_type type);
	fst_status (*opendir)(struct fst_volume* volume,
						  const char* path,
						  fst_dir** dir);
	fst_status (*readdir)(struct fst_volume* volume,
						  fst_dir* dir,
						  fst_dnode** dnode);
	fst_status (*rmdir)(struct fst_volume* volume, fst_dir* dir);
	fst_status (*closedir)(struct fst_volume* volume, fst_dir* dir);
	fst_status (*open)(struct fst_volume* volume,
					   const char* path,
					   fst_inode** ino);
	fst_status (*read)(struct fst_volume* volume,
					   fst_inode* ino,
					   fst_off off,
					   fst_size size,
					   void* buf);
	fst_status (*write)(struct fst_volume* volume,
						fst_inode* ino,
						fst_off off,
						fst_size size,
						void* buf);
	fst_status (*truncate)(struct fst_volume* volume,
						   fst_inode* ino,
						   fst_size size);
	fst_status (*unlink)(struct fst_volume* volume, fst_inode* ino);
	fst_status (*close)(struct fst_volume* volume, fst_inode* ino);
	fst_status (*getuuid)(struct fst_volume* volume,
						  unsigned long* size,
						  void** buf);
} fst_volume;

#endif