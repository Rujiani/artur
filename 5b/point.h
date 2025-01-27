#ifndef POINT_H
#define POINT_H

typedef struct {
    int x, y;
} Point;

Point point_new(int x, int y);
void point_print(const Point *p);
int point_cmp_x(const Point *p1, const Point *p2);
int point_cmp_y(const Point *p1, const Point *p2);

void point_array_print(const char *msg, const Point *arr, int len);
#endif
