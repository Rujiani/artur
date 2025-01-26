#include <stdlib.h>

#include "point.h"

int main(int argc, char **argv) {
    Point arr[] = {
        point_new(10, 20),
        point_new(20, 12),
        point_new(11, 10),
        point_new(11, 40),
    };
    point_array_print("Before sort:\n", arr, 4);
    qsort(arr, 4, sizeof(Point),
          (int (*)(const void *, const void *)) point_cmp_x);
    point_array_print("After sort:\n", arr, 4);
    return 0;
}
