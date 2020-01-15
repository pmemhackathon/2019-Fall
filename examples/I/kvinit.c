#include <assert.h>
#include <libpmemkv.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// default size for this example: 10MB
static const int SIZE = 10 * 1024 * 1024;

int print_pmemkv_error() {
    fprintf(stderr, "%s\n", pmemkv_errormsg());
    exit(1);
}

pmemkv_db *must_open_or_create(const char *path) {
    pmemkv_config *cfg = pmemkv_config_new();
    pmemkv_db *db = NULL;

    if (pmemkv_config_put_string(cfg, "path", path) != PMEMKV_STATUS_OK) {
        print_pmemkv_error();
    }
    if (pmemkv_config_put_int64(cfg, "size", SIZE) != PMEMKV_STATUS_OK) {
        print_pmemkv_error();
    }
    if (access(path, R_OK | W_OK)) {
        if (pmemkv_config_put_int64(cfg, "force_create", 1) != PMEMKV_STATUS_OK) {
            print_pmemkv_error();
        }
    }

    if (pmemkv_open("cmap", cfg, &db) != PMEMKV_STATUS_OK) {
        print_pmemkv_error();
    }

    assert(db != NULL);

    return db;
}
