#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mock_osal.hpp"

// private definitions
static MockOsal *mock_osal;

void
MockOsal_set(MockOsal *obj)
{
    mock_osal = obj;
}

// public functions

void
osal_free(void *ptr)
{
    if (!mock_osal)
        return;
    mock_osal->osal_free(ptr);
}

void *
osal_calloc(size_t nmemb, size_t size)
{
    if (!mock_osal)
        return NULL;
    mock_osal->osal_calloc(nmemb, size);
}
