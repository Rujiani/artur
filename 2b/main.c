#include <stdio.h>
#include <math.h>

double calculate_ln_series(double x, double alpha, double eps) {
    double sum = 0.0;
    double term;
    double power_of_x = x;
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

    printf("Введите |x| <= 1: ");
    scanf("%lf", &x);
    printf("Введите alpha: ");
    scanf("%lf", &alpha);
    printf("Введите требуемую точность (eps): ");
    scanf("%lf", &epsilon);

    double series_result = calculate_ln_series(x, alpha, epsilon);
    double lib_result    = log(1.0 - 2.0 * x * cos(alpha) + x * x);

    printf("%.15f\n", series_result);
    printf("%.15f\n", lib_result);

    return 0;
}
