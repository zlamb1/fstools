#include <stdlib.h>

#include "fstools.h"

fst_volume* fst_volume_create(const fst_volume_ops* ops) {
	fst_volume* volume = malloc(sizeof(*volume));
	if (volume == NULL) {
		return NULL;
	}
	volume->ops = ops;
	volume->ino_cache.lock = rwlock_create();
	if (volume->ino_cache.lock == NULL) {
		goto out1;
	}
	volume->ino_cache.capacity = FST_INODE_CACHE_CAP;
	volume->ino_cache.table = malloc(sizeof(fst_inode*) * FST_INODE_CACHE_CAP);
	if (volume->ino_cache.table == NULL) {
		goto out2;
	}
	return volume;
out2:
	rwlock_destroy(volume->ino_cache.lock);
out1:
	free(volume);
	return NULL;
}

void fst_volume_destroy(fst_volume* volume) {
	rwlock_destroy(volume->ino_cache.lock);
	free(volume->ino_cache.table);
	free(volume);
}