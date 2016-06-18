#include "ft_estimate.h"

static int read_mileage()
{
	char data[500];
	int first;

	first = 1;
	do
	{
		if (!first)
			printf("Invalid mileage.\nPlease, enter a mileage:\n");
		memset(data, 0, 500);
		if (read(1, data, 499) == -1)
		{
			printf("Error while readed mileage.\nAborting.");
			exit(EXIT_FAILURE);
		}
		first = 0;
	} while (!valid_int(data));
	return (atoi(data));
}

int main()
{
	int theta0 = 0;
	int theta1 = 0;

	get_theta(&theta0, &theta1);
	printf("Please, enter a mileage:\n");
	int mileage = read_mileage();
	printf("Estimated price: %d\n", get_estimated_price(mileage, theta0, theta1));
	return (EXIT_SUCCESS);
}
