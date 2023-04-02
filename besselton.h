#ifndef BESSELTON_H_
#define BESSELTON_H_

#define PROGRAM_NAME "besselton"
#define PROGRAM_VERSION "0.01"

/* note: there are 4 coefficients for each Besselian elements. */
#define NUMBER_OF_COEFF 4
/* and there are 6 besselian elements in total. */
#define NUMBER_OF_ELEMENTS 6

/* simple macro for eprintf */
#define eprintf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#define LOG(fmt, ...) eprintf("%s:%d: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)


typedef float besselian_element[NUMBER_OF_COEFF];

struct besselian_elements {
    besselian_element x, y, d, l1, l2, m;
};

struct computed_be {
    float x, y, d, l1, l2, m;
};

/* function prototypes */
void print_elements(struct computed_be *cbe, double T);
struct computed_be calculate_elements(struct besselian_elements *be, double T);

#endif
