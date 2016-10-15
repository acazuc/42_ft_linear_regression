#include "common.h"

double get_estimated_price(int mileage, double theta0, double theta1)
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
	while (n[0])
	{
		if (n[0] < '0' || n[0] > '9')
			return (0);
		n++;
	}
	return (1);
}

void get_theta_from_data(char *data, double *theta0, double *theta1)
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
	*theta0 = atof(n1);
	*theta1 = atof(n2);
}

void get_theta(double *theta0, double *theta1)
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

static int init(char **line, char **buff)
{
	if (!(*line = malloc(sizeof(**line))))
		return (0);
	(*line)[0] = '\0';
	if (!(*buff = malloc(sizeof(**buff) * 2)))
	{
		free(*line);
		return (0);
	}
	(*buff)[0] = '\0';
	(*buff)[1] = '\0';
	return (1);
}

char *read_next_line(int fd)
{
	char *tmp;
	char *line;
	char *buff;
	int rd;

	if (!init(&line, &buff))
		return (NULL);
	while ((rd = read(fd, buff, 1)) > 0 && buff[0] != '\n')
	{
		if (!(tmp = malloc(strlen(line) + strlen(buff) + 1)))
		{
			free(buff);
			return (NULL);
		}
		memset(tmp, 0, strlen(line) + strlen(buff) + 1);
		strcat(tmp, line);
		strcat(tmp, buff);
		free(line);
		line = tmp;
	}
	free(buff);
	if (rd == -1 || strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
