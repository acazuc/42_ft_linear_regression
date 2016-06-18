#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>

int get_estimated_price(int mileage, int theta0, int theta1);
void get_theta(int *theta0, int *theta1);
void get_theta_from_data(char *data, int *theta0, int *theta1);
int valid_int(char *n);

#endif
