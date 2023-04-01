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
           "If latitude or longitude is not specified, they are set to zero.\n");
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
};

int main(int argc, char **argv) {
#ifdef DEBUG
    eprintf("Using arguments:\n");
    for(int i = 0; i < argc; i++)
        eprintf("%s\n", argv[i]);
#endif
    invoked_name = argv[0];
    int oi, c;
    double latitude = 0;
    double longitude = 0;
    while(1) {
        oi = -1;
        c = getopt_long(argc, argv, "hvl:p:", long_options, &oi);
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
                    eprintf("Please specify a valid latitude value!\n");
                    exit(-1);
                }
                eprintf("Using %f as latitude...\n", latitude);
                break;
            case 'l':
                longitude = atof(optarg);
                if(!longitude) {
                    eprintf("Please specify a valid latitude value!\n");
                    exit(-1);
                }
                eprintf("Using %f as longitude...\n", longitude);
                break;
            default:
                break;
        }
    }
}
