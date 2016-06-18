#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <math.h>

double get_estimated_price(int mileage, double theta0, double theta1);
void get_theta(double *theta0, double *theta1);
void get_theta_from_data(char *data, double *theta0, double *theta1);
int valid_int(char *n);
char *read_next_line(int fd);

#endif
