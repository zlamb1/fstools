#ifndef FSTOOLS_H
#define FSTOOLS_H 1

#include <stddef.h>
#include <stdint.h>

#include "sync.h"

#define FST_OK 0x0
#define FST_ERR_NOMEM 0x1
#define FST_ERR_ARG 0x2
#define FST_ERR_FS 0x3

#define FST_FT_REG 0
#define FST_FT_DIR 1
#define FST_FT_CHR 2
#define FST_FT_BLK 3
#define FST_FT_LNK 4
#define FST_FT_FIFO 5
#define FST_FT_SOCK 6

#ifndef FST_INODE_CACHE_CAP
#define FST_INODE_CACHE_CAP 32
#endif

typedef void* fst_dir;
typedef uint64_t fst_off;
typedef uint64_t fst_size;
typedef uint64_t fst_ino;
typedef int fst_status;
typedef int64_t fst_time;
typedef unsigned int fst_type;
typedef _Atomic unsigned long fst_ref_count;

typedef struct fst_inode {
	rwlock lock;
	char* name;
	fst_ino ino;
	fst_type type;
	fst_size size;
	fst_time ctime;
	fst_time atime;
	fst_time mtime;
	struct fst_inode* prev;
	struct fst_inode* next;
} fst_inode;

struct fst_volume;

typedef struct fst_volume_ops {
	fst_status (*create)(struct fst_volume* volume,
						 fst_inode* dir,
						 const char* name);
	fst_status (*opendir)(struct fst_volume* volume,
						  const char* path,
						  fst_dir** dir);
	fst_status (*readdir)(struct fst_volume* volume,
						  fst_dir* dir,
						  fst_inode** ino);
	fst_status (*closedir)(struct fst_volume* volume, fst_dir* dir);
	fst_status (*mkdir)(struct fst_volume* volume,
						fst_inode* parent_dir,
						const char* name);
	fst_status (*rmdir)(struct fst_volume* volume, fst_inode* dir);
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
} fst_volume_ops;

typedef struct fst_volume {
	const fst_volume_ops* ops;
	struct {
		rwlock lock;
		unsigned long capacity;
		fst_inode** table;
	} ino_cache;
} fst_volume;

fst_volume* fst_volume_create(const fst_volume_ops* ops);
void fst_volume_destroy(fst_volume* volume);

#endif