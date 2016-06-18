#include "common.h"

int get_estimated_price(int mileage, int theta0, int theta1)
{
	return (theta0 + mileage * theta1);
}

int valid_int(char *n)
{
	if (n[0] == '-')
		n++;
	while (n[0] == '0')
		n++;
	if (strlen(n) > 10)
		return (0);
	if (atol(n) > INT_MAX || atol(n) < INT_MIN)
		return (0);
	return (1);
}

void get_theta_from_data(char *data, int *theta0, int *theta1)
{
	char *n1;
	char *n2;

	n1 = data;
	if ((n2 = strchr(data, ';')) == data || n2 != strrchr(data, ';'))
	{
		printf("Invalid theta file value.\ntheta0 = theta1 = 0\n");
		return;
	}
	*n2 = '\0';
	n2++;
	if (!valid_int(n1) || !valid_int(n2))
	{
		printf("Invalid theta file value.\ntheta0 = theta1 = 0\n");
		return;
	}
	*theta0 = atoi(n1);
	*theta1 = atoi(n2);
}

void get_theta(int *theta0, int *theta1)
{
	FILE *theta_file;
	if (!(theta_file = fopen("theta", "r")))
	{
		printf("theta file can't be open. Please run ft_train first.\ntheta0 = theta1 = 0\n");
		return;
	}
	char tmp[24];
	memset(tmp, 0, 24);
	if (fread(tmp, 1, 24, theta_file) == 24)
	{
		printf("Invalid theta file value.\ntheta0 = theta1 = 0\n");
		fclose(theta_file);
		return;
	}
	if (ferror(theta_file))
	{
		printf("Failed to read theta file.\ntheta0 = theta1 = 0\n");
		fclose(theta_file);
		return;
	}
	fclose(theta_file);
	get_theta_from_data(tmp, theta0, theta1);
}
