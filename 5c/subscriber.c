#include "subscriber.h"
#include <stdlib.h>

void sub_free(Sub *s) {
    if (!s) return;
    free(s->full_name);
    free(s->number);
    s->full_name = NULL;
    s->number = NULL;
}
