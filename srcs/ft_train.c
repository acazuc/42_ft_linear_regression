#include "ft_train.h"

static void parse_line(char *line, int *n1, int *n2)
{
	char *tmp1;
	char *tmp2;

	tmp1 = line;
	if ((tmp2 = strchr(line, ',')) == line || tmp2 != strrchr(line, ','))
	{
		printf("Invalid csv line: %s\n", line);
		exit(EXIT_FAILURE);
	}
	*tmp2 = '\0';
	tmp2++;
	if (!valid_int(tmp1) || !valid_int(tmp2))
	{
		printf("Invalid csv line: %s\n", line);
		exit(EXIT_FAILURE);
	}
	*n1 = atoi(tmp1);
	*n2 = atoi(tmp2);
}

static void push_datas(double ***datas, int n1, int n2)
{
	size_t len = 0;
	double **new;

	while ((*datas)[len])
		len++;
	if (!(new = malloc(sizeof(*new) * (len + 2))))
	{
		printf("Failed to malloc\n");
		exit(EXIT_FAILURE);
	}
	len = 0;
	while ((*datas)[len])
	{
		new[len] = (*datas)[len];
		len++;
	}
	if (!(new[len] = malloc(sizeof(***datas) * 2)))
	{
		printf("Failed to malloc\n");
		exit(EXIT_FAILURE);
	}
	new[len][0] = n1;
	new[len][1] = n2;
	new[++len] = NULL;
	*datas = new;
}

static void get_datas(double ***datas)
{
	if (!(*datas = malloc(sizeof(**datas))))
	{
		printf("Failed to malloc\n");
		exit(EXIT_FAILURE);
	}
	(*datas)[0] = NULL;
	char *line;
	int n1;
	int n2;
	int first = 1;
	int fd;
	if ((fd = open("data.csv", O_RDONLY)) == -1)
	{
		printf("Failed to open data.csv");
		exit(EXIT_FAILURE);
	}
	while ((line = read_next_line(fd)))
	{
		if (!first)
		{
			parse_line(line, &n1, &n2);
			push_datas(datas, n1, n2);
		}
		first = 0;
	}
	close(fd);
}

static void scale_datas(double **datas, int *scale)
{
	double min = 0;
 	double max = 0;
	int min_unset = 1;
	int max_unset = 1;
	int i = 0;

	while (datas[i])
	{
		if (datas[i][0] < min || min_unset)
		{
			min = datas[i][0];
			min_unset = 0;
		}
		if (datas[i][0] > max || max_unset)
		{
			max = datas[i][0];
			max_unset = 0;
		}
		i++;
	}
	*scale = max - min;
	i = 0;
	while (datas[i])
	{
		datas[i][0] = (datas[i][0] - min) / (max - min);
		i++;
	}
}

static void calc_thetas(double **datas, double *theta0, double *theta1)
{
	double delta0;
	double delta1;
	double tmp0;
	double tmp1;
	int i;
	int len = 0;

	while (datas[len])
		len++;
	do
	{
		i = 0;
		tmp0 = 0;
		tmp1 = 0;
		while (datas[i])
		{
			tmp0 += (*theta1 * datas[i][0] + *theta0) - (double)datas[i][1];
			tmp1 += ((*theta1 * datas[i][0] + *theta0) - (double)datas[i][1]) * (double)datas[i][0];
			i++;
		}
		delta0 = LEARNING_RATE * tmp0 / len;
		delta1 = LEARNING_RATE * tmp1 / len;
		*theta0 -= delta0;
		*theta1 -= delta1;
	} while (fabs(delta0) > 0.001 && fabs(delta1) > 0.001);
}

static void print_thetas(double theta0, double theta1)
{
	FILE *file;

	if (!(file = fopen("theta", "w")))
	{
		printf("Failed to open theta file\n");
		exit(EXIT_FAILURE);
	}
	if (!fprintf(file, "%f;%f", theta0, theta1))
		printf("Failed to write to theta file\n");
	fclose(file);
}

int main()
{
	double theta0 = 0;
	double theta1 = 0;
	double **datas;
	int scale;

	get_datas(&datas);
	scale_datas(datas, &scale);
	calc_thetas(datas, &theta0, &theta1);
	theta1 /= scale;
	printf("theta0: %f, theta1: %f\n", theta0, theta1);
	print_thetas(theta0, theta1);
	return (EXIT_SUCCESS);
}
