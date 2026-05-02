#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

#include "sync.h"
#include "types.h"

typedef unsigned long counter;

struct rwlock_t {
	pthread_mutex_t mutex;
	pthread_cond_t reader_cv;
	pthread_cond_t writer_cv;
	counter readers;
	counter writers;
};

rwlock rwlock_create(void) {
	rwlock lock = malloc(sizeof(*lock));
	pthread_mutexattr_t mutexattr;
	pthread_condattr_t condattr;

	if (lock == NULL) {
		return (NULL);
	}

	lock->readers = 0;
	lock->writers = 0;

	if (pthread_mutexattr_init(&mutexattr)) {
		goto out1;
	}

	if (pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_NORMAL)) {
		goto out2;
	}

	if (pthread_condattr_init(&condattr)) {
		goto out2;
	}

	if (pthread_mutex_init(&lock->mutex, &mutexattr)) {
		goto out3;
	}

	if (pthread_cond_init(&lock->reader_cv, &condattr)) {
		goto out4;
	}

	if (pthread_cond_init(&lock->writer_cv, &condattr)) {
		goto out5;
	}

	pthread_condattr_destroy(&condattr);
	pthread_mutexattr_destroy(&mutexattr);

	return (lock);

out5:
	pthread_cond_destroy(&lock->reader_cv);
out4:
	pthread_mutex_destroy(&lock->mutex);
out3:
	pthread_condattr_destroy(&condattr);
out2:
	pthread_mutexattr_destroy(&mutexattr);
out1:
	free(lock);
	return (NULL);
}

void rwlock_read_lock(rwlock lock) {
	pthread_mutex_lock(&lock->mutex);
	while (lock->writers) {
		pthread_cond_wait(&lock->reader_cv, &lock->mutex);
	}
	lock->readers++;
	pthread_mutex_unlock(&lock->mutex);
}

void rwlock_read_unlock(rwlock lock) {
	pthread_mutex_lock(&lock->mutex);
	counter readers = --lock->readers;
	if (lock->writers && !readers) {
		pthread_cond_signal(&lock->writer_cv);
	}
	pthread_mutex_unlock(&lock->mutex);
}

void rwlock_write_lock(rwlock lock) {
	pthread_mutex_lock(&lock->mutex);
	lock->writers++;
	while (lock->readers) {
		pthread_cond_wait(&lock->writer_cv, &lock->mutex);
	}
}

void rwlock_write_unlock(rwlock lock) {
	if (--lock->writers) {
		pthread_cond_signal(&lock->writer_cv);
	} else {
		pthread_cond_broadcast(&lock->reader_cv);
	}
	pthread_mutex_unlock(&lock->mutex);
}

void rwlock_destroy(rwlock lock) {
	pthread_mutex_destroy(&lock->mutex);
	pthread_cond_destroy(&lock->reader_cv);
	pthread_cond_destroy(&lock->writer_cv);
	free(lock);
}
