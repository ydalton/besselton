/*
 * Copyright (c) 2023 ydalton
 *
 * I write this program in spite of C#, where I could not parse
 * command line arguments without resorting to a third party package.
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "besselton.h"

static const char *invoked_name = NULL;

void usage() {
    printf("%s: a command line astronomical calculator\n"
           "usage: %s [options] file\n", (char*) PROGRAM_NAME, invoked_name);
    printf("options:\n"
           "    -h, --help            print this message and exit\n"
           "    -v, --version         print the program version\n"
           "    -p, --latitude        specify the latitude\n"
           "    -l, --longitude       specity the longitude\n"
           "    -t, --time            specity the time\n"
           "If latitude, longitude or time is not specified, they are set to zero.\n");
    exit(0);
}

void print_version() {
    printf("%s %s\n", PROGRAM_NAME, PROGRAM_VERSION);
    exit(0);
}

static struct option const long_options[] = {
    {"version", no_argument, NULL, 'v'},
    {"help", no_argument, NULL, 'h'},
    {"latitude", required_argument, NULL, 'p'},
    {"longitude", required_argument, NULL, 'l'},
    {"time", required_argument, NULL, 't'},
    /* you must specify this last one otherwise you will get a segfault. */
    {NULL, 0, 0, 0},
};

int main(int argc, char **argv) {
    invoked_name = argv[0];
    /* for getopt_long */
    int oi, c;
    double latitude = 0;
    double longitude = 0;
    double T = 0;
    /* parse command line arguments */
    while(1) {
        oi = -1;
        c = getopt_long(argc, argv, "hvl:p:t:", long_options, &oi);
        if(c == -1)
            break;
        switch(c) {
            case 'h':
                usage();
                break;
            case 'v':
                print_version();
                break;
            case 'p':
                latitude = atof(optarg);
                if(!latitude) {
                    LOG("Please specify a valid latitude value!\n");
                    exit(-1);
                }
                break;
            case 'l':
                longitude = atof(optarg);
                if(!longitude) {
                    LOG("Please specify a valid longitude value!\n");
                    exit(-1);
                }
                break;
            case 't':
                T = atof(optarg);
                if(!T) {
                    LOG("Please specify a valid time value!\n");
                    exit(-1);
                }
                break;
            default:
                exit(0);
                break;
        }
    }
    struct besselian_elements test = {{0.6931820, 0.4646490, -0.0000101, -0.0000055},
                                      {-0.9222000,0.2285195,-0.0000259,-0.0000029},
                                      {11.4196396,0.0137730,-0.0000030,0},
                                      {0.5626270,0.0000781,-0.0000102,0},
                                      {0.0164080,0.0000777,-0.0000102,0},
                                      {30.247351,15.003350,0,0}};
    /* LOG("latitude: %f, longitude: %f, time: %f\n", latitude, longitude, T); */
    struct computed_be cbe = calculate_elements(&test, T);
    print_elements(&cbe, T);
    return 0;
}
