#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hoge_private.h"
#include "hoge.h"

// private definitions

enum spy_hoge_id {
    API_INC_X,
    API_INC_10,
    API_GE,
    API_NUM
};
static const char *
spy_hoge_id2str(enum spy_hoge_id id)
{
    switch (id) {
    case API_INC_X:     return "API_INC_X";
    case API_INC_10:    return "API_INC_10";
    case API_GE:        return "API_GE";
    default: return "UNKNOWN";
    }
}

typedef struct spy_hoge_struct {
    struct hoge_struct spy;
    struct hoge_struct orig;
    int call_count[API_NUM];
} *spy_hoge_ptr;

// prototypes of private functions
static void spy_destroy(struct hoge_struct *self);
static void spy_inc_x(struct hoge_struct *self, int x);
static void spy_inc_10(struct hoge_struct *self);
static bool spy_ge_x(struct hoge_struct *self, int x);

// public functions

void *
spy_hoge_new(void)
{
    void *orig;
    orig = hoge_new();
    if (!orig) {
        return NULL;
    }
    spy_hoge_ptr spy_hoge;
    spy_hoge = realloc(orig, sizeof(*spy_hoge));
    if (!spy_hoge) {
        free(orig);
        return NULL;
    }
    memcpy(&spy_hoge->orig, orig, sizeof(spy_hoge->orig));
    memset(spy_hoge->call_count, 0, sizeof(spy_hoge->call_count));
    spy_hoge->spy.self_destroy = spy_destroy;
    spy_hoge->spy.inc_x = spy_inc_x;
    spy_hoge->spy.inc_10 = spy_inc_10;
    spy_hoge->spy.ge_x = spy_ge_x;

    return spy_hoge;
}

int
spy_hoge_count_inc_x(void *spy)
{
    spy_hoge_ptr spy_hoge = (spy_hoge_ptr)spy;
    return spy_hoge->call_count[API_INC_X];
}

int
spy_hoge_count_inc_10(void *spy)
{
    spy_hoge_ptr spy_hoge = (spy_hoge_ptr)spy;
    return spy_hoge->call_count[API_INC_10];
}

int
spy_hoge_count_ge(void *spy)
{
    spy_hoge_ptr spy_hoge = (spy_hoge_ptr)spy;
    return spy_hoge->call_count[API_GE];
}

// private functions

static void
spy_destroy(struct hoge_struct *self)
{
    if (!self) {
        return;
    }
    spy_hoge_ptr spy_hoge = (spy_hoge_ptr)self;
    for (int idx = 0; idx < API_NUM; idx++) {
        printf("idx:%s, count:%d\n",
                spy_hoge_id2str(idx), spy_hoge->call_count[idx]);
    }
    // you fall into infinite loop unless you use an original function.
    spy_hoge->spy.self_destroy = spy_hoge->orig.self_destroy;
    hoge_destroy(spy_hoge);
}

static void
spy_inc_x(struct hoge_struct *self, int x)
{
    spy_hoge_ptr spy_hoge = (spy_hoge_ptr)self;
    spy_hoge->call_count[API_INC_X]++;
    return hoge_inc(&spy_hoge->orig, x);
}

static void
spy_inc_10(struct hoge_struct *self)
{
    spy_hoge_ptr spy_hoge = (spy_hoge_ptr)self;
    spy_hoge->call_count[API_INC_10]++;
    return hoge_inc10(&spy_hoge->orig);
}

static bool
spy_ge_x(struct hoge_struct *self, int x)
{
    spy_hoge_ptr spy_hoge = (spy_hoge_ptr)self;
    spy_hoge->call_count[API_GE]++;
    return hoge_ge(&spy_hoge->orig, x);
}
