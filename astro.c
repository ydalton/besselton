#include <stdio.h>
#include "besselton.h"
#include <stdint.h>
#include <math.h>

const char *element_names[NUMBER_OF_ELEMENTS] = {"x", "y", "d", "l1", "l2", "m"};

/* calculate a single element */
static float calculate_element(besselian_element a, double T) {
    float result = 0;
    for(int i = 0; i < NUMBER_OF_COEFF; i++)
        result += a[i] * powf(T, i);
    return result;
}

/* calculate besselian_elements be at time T*/
struct computed_be calculate_elements(struct besselian_elements *be, double T) {
    struct computed_be cbe = {0, 0, 0, 0, 0, 0};
    besselian_element a;
    float *f;
    for(int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
        /* quite possibly the most pointery code i've written */
        f = (float *) be + (i * NUMBER_OF_COEFF);
        for(int j = 0; j < NUMBER_OF_COEFF; j++)
            a[j] = f[j];
        /* why */
        *(((float*)(&cbe))+i) = calculate_element(a, T);
    }
    return cbe;
}

/* print a row of elements once, to be used in print_elements later */
static void print_elements_once(struct besselian_elements *be, double T) {
    struct computed_be cbe = calculate_elements(be, T);
    printf("%f\t", T);
    /* once again invoking the magic of the pointer gods */
    for(int i = 0; i < NUMBER_OF_ELEMENTS; i++)
        printf("%f\t", *(((float*)(&cbe))+i));
    putchar('\n');
}

/* print besselian_elements be at time T incrementing increment n times. */
void print_elements(struct besselian_elements *be, double T, double increment, unsigned int n) {
    printf("T\t\t");
    for(int i = 0; i < NUMBER_OF_ELEMENTS; i++)
        printf("%s\t\t", element_names[i]);
    putchar('\n');
    for(int i = 0; i < 16 * (NUMBER_OF_ELEMENTS + 1); i++)
        putchar('-');
    putchar('\n');
    for(int j = 0; j < n; j++) {
        print_elements_once(be, T);
        T += increment;
    }
}
