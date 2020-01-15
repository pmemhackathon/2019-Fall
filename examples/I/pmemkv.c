#include <libpmemkv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pmemkv_db *must_open_or_create(const char *path);

int kv_print(const char *key, size_t keybytes, const char *value,
             size_t valuebytes, void *arg) {
    printf("%s = %s\n", key, value);
    return 0;
}

void v_print(const char *value, size_t valuebytes, void *arg) {
    printf("%s\n", value);
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "usage: %s kvfile [key [value]]\n", argv[0]);
        exit(1);
    }

    pmemkv_db *db_handle = must_open_or_create(argv[1]);

    if (argc == 2) {
        // iterate through the key-value store, printing them
        pmemkv_get_all(db_handle, kv_print, NULL);
    } else if (argc == 3) {
        int ret = pmemkv_get(db_handle, argv[2], strlen(argv[2]), v_print, NULL);
        if (ret != PMEMKV_STATUS_OK) {
            fprintf(stderr, "%s\n", pmemkv_errormsg());
            exit(1);
        }
    } else {
        if (pmemkv_put(db_handle,argv[2], strlen(argv[2]), argv[3], strlen(argv[3])) != PMEMKV_STATUS_OK) {
            fprintf(stderr, "%s\n", pmemkv_errormsg());
            exit(1);
        }
    }

    pmemkv_close(db_handle);

    return 0;
}
