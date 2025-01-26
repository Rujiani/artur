#include <stdio.h>
#include <math.h>

double calculate_ln_series(double x, double alpha, double eps) {
    double sum = 0.0;
    double power_of_x = x;
    double term;
    int n = 1;

    do {
        term = (cos(n * alpha) * power_of_x) / n;
        if (fabs(term) >= eps) {
            sum += term;
        }
        n++;
        power_of_x *= x;
    } while (fabs(term) >= eps);

    return -2.0 * sum;
}

int main() {
    double x, alpha, epsilon;
    scanf("%lf %lf %lf", &x, &alpha, &epsilon);

    double series_result = calculate_ln_series(x, alpha, epsilon);
    double lib_result = log(1.0 - 2.0 * x * cos(alpha) + x * x);

    printf("Результат по ряду:      %.15f\n", series_result);
    printf("Результат через log(...): %.15f\n", lib_result);

    return 0;
}
