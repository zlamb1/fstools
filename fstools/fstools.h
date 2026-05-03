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

struct FST_inode;
struct FST_dnode;
struct FST_fs;

typedef struct FST_list {
	struct FST_list *prev, *next;
} FST_list;

typedef struct {
	int (*lookup)(struct FST_inode* parent, struct FST_dnode* dnode);
} FST_inode_ops;

typedef struct {
	FST_rwlock lock;
	uint32_t count;
	uint32_t type;
	uint32_t nlinks;
	uint64_t size;
	int64_t ctime;
	int64_t atime;
	int64_t mtime;
	uint64_t ino;
	const FST_inode_ops* ops;
	void* private;
} FST_inode;

typedef struct FST_dnode {
	FST_rwlock lock;
	uint32_t count;
	struct {
		uint32_t len;
		uint32_t hash;
		char* str;
	} name;
	FST_inode* inode;
	struct FST_dnode* parent;
	FST_list children;
	FST_list siblings;
	void* private;
} FST_dnode;

typedef struct FST_fs {
	struct {
		uint32_t size;
		void* data;
	} uuid;
	FST_dnode* root;
	void* private;
} FST_fs;

#endif