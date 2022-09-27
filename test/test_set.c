#include <fdsac/set.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static const uint64_t KEYS[] = {4329, 23,   23894823,    3272,   5320, 2589372,
                                5348, 4593, 5437892,     263478, 345,  342879543589,
                                238,  3,    59893413489, 34589,  120,  2359};

static const char *KEYS2[] = {
    "abc", "bca", "cba", "hello", "test", "the quick brown fox jumps over the lazy dog",
};

uint64_t ror64(uint64_t v, int r) { return (v >> r) | (v << (64 - r)); }

uint64_t u64_hasher(const void *data) {
    uint64_t v = *(uint64_t *)data;
    v ^= ror64(v, 25) ^ ror64(v, 50);
    v *= 0xA24BAED4963EE407UL;
    v ^= ror64(v, 24) ^ ror64(v, 49);
    v *= 0x9FB21C651E98DF25UL;
    return v ^ v >> 28;
}

uint64_t str_hasher(const void *data) {
    const char *str = *(void **)data;
    uint64_t hash = 5381;

    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int str_cmp(const void *a, const void *b) { return strcmp(*(char **)a, *(char **)b); }

int main() {
    fds_set set;
    fds_set_init(&set, sizeof(uint64_t), u64_hasher, NULL, NULL);

    for (size_t i = 0; i < sizeof(KEYS) / sizeof(KEYS[0]); i++) {
        assert(!fds_set_contains(&set, &KEYS[i]));
        fds_set_insert(&set, &KEYS[i]);
        assert(fds_set_contains(&set, &KEYS[i]));
    }

    for (size_t i = 0; i < sizeof(KEYS) / sizeof(KEYS[0]); i++) {
        assert(fds_set_contains(&set, &KEYS[i]));
        fds_set_remove(&set, &KEYS[i]);
        assert(!fds_set_contains(&set, &KEYS[i]));
    }

    fds_set_destroy(&set);

    /* ----------------- */

    fds_set_init(&set, sizeof(char *), str_hasher, str_cmp, free);

    for (size_t i = 0; i < sizeof(KEYS2) / sizeof(KEYS2[0]); i++) {
        assert(!fds_set_contains(&set, &KEYS2[i]));
        fds_set_insert(&set, &(char *){strdup(KEYS2[i])});
        assert(fds_set_contains(&set, &KEYS2[i]));
    }

    for (size_t i = 0; i < sizeof(KEYS2) / sizeof(KEYS2[0]); i++) {
        assert(fds_set_contains(&set, &KEYS2[i]));
        fds_set_remove(&set, &KEYS2[i]);
        assert(!fds_set_contains(&set, &KEYS2[i]));
    }

    fds_set_destroy(&set);

    return 0;
}
