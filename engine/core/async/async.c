#ifdef CONFIG_H
#include CONFIG_H
#endif

#ifdef ASYNC_C
#pragma once
#define ATOMIC_C
#define CHANNEL_C
#define CONDV_C
#define LFQ_C
#define MUTEX_C
#define REALLOC_C
#define SEMAPHORE_C
#define SLEEP_C
#define SYSTEM_C
#define THREAD_C
#define TLS_C
#endif

#include "../detect/detect.c"
#include "../memory/memory.c" // realloc

#include "async_atomic.c"
#include "async_channel.c"
#include "async_condv.c"
#include "async_lfq.c"
#include "async_mutex.c"
#include "async_semaphore.c"
#include "async_sleep.c"
#include "async_thread.c"
#include "async_tls.c"
