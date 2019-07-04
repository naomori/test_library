#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <jansson.h>

// private definitions
#include "hoge_private.h"

// prototypes of private functions
static void self_destroy(struct hoge_struct *self);
static void inc_x(struct hoge_struct *self, int x);
static void inc_10(struct hoge_struct *self);
static bool ge_x(struct hoge_struct *self, int x);

// public functions

void *
hoge_new(void)
{
    void *h;
    h = calloc(1, sizeof(struct hoge_struct));
    if (!h) {
        fprintf(stderr, "failed to calloc: %m");
        return NULL;
    }
    hoge_ptr hoge = (hoge_ptr)h;
    hoge->self_destroy = self_destroy;
    hoge->inc_x = inc_x;
    hoge->inc_10 = inc_10;
    hoge->ge_x = ge_x;
    hoge->total = 0;
    return h;
}

void
hoge_destroy(void *self)
{
    hoge_ptr hoge = (hoge_ptr)self;
    if (!hoge->self_destroy)
        return;
    (*hoge->self_destroy)(hoge);
}

void
hoge_inc(void *self, int x)
{
    hoge_ptr hoge = (hoge_ptr)self;
    if (!hoge->inc_x)
        return;
    (*hoge->inc_x)(hoge, x);
}

void
hoge_inc10(void *self)
{
    hoge_ptr hoge = (hoge_ptr)self;
    if (!hoge->inc_10)
        return;
    (*hoge->inc_10)(hoge);
}

bool
hoge_ge(void *self, int x)
{
     hoge_ptr hoge = (hoge_ptr)self;
    if (!hoge->ge_x)
        return false;
    return (*hoge->ge_x)(hoge, x);
}

// private functions

static void
self_destroy(struct hoge_struct *self)
{
    if (!self) {
        return;
    }
    free(self);
}

static void
inc_x(struct hoge_struct *self, int x)
{
    self->total += x;
}

static void
inc_10(struct hoge_struct *self)
{
    self->total += 10;
}

static bool
ge_x(struct hoge_struct *self, int x)
{
    return (self->total >= x) ? true : false;
}
