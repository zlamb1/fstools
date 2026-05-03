#ifndef FSTOOLS_SYNC_H
#define FSTOOLS_SYNC_H 1

typedef struct FST_rwlock_t* FST_rwlock;

FST_rwlock fst_rwlock_create(void);
void fst_read_lock(FST_rwlock);
void fst_read_unlock(FST_rwlock);
void fst_write_lock(FST_rwlock);
void fst_write_unlock(FST_rwlock);
void fst_rwlock_destroy(FST_rwlock);

#endif