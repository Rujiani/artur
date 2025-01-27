#include <stdio.h>

#include "point.h"

Point point_new(int x, int y) {
    Point p = {x, y};
    return p;
}

void point_print(const Point *p) {
    printf("{%d, %d}", p->x, p->y);
}

int point_cmp_x(const Point *p1, const Point *p2) {
    return p1->x - p2->x;
}

int point_cmp_y(const Point *p1, const Point *p2) {
    return p1->y - p2->y;
}

void point_array_print(const char *msg, const Point *arr, int len) {
    printf("%s", msg);
    for (int i = 0; i < len; ++i) {
        printf("a[%d] = ", i);
        point_print(arr + i);
        printf("\n");
    }
}
