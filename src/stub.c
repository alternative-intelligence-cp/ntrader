#include <stddef.h>
#include <stdbool.h>

bool __atomic_is_lock_free(size_t size, void *ptr) {
    return true;
}
