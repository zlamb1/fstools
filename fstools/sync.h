#ifndef FSTOOLS_SYNC_H
#define FSTOOLS_SYNC_H 1

typedef struct rwlock_t* rwlock;

rwlock rwlock_create(void);
void rwlock_read_lock(rwlock);
void rwlock_read_unlock(rwlock);
void rwlock_write_lock(rwlock);
void rwlock_write_unlock(rwlock);
void rwlock_destroy(rwlock);

#endif