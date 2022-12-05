#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long int	i;

	i = n;
	if (i < 0)
	{
		write (fd, "-", 1);
		i = i * -1;
	}		
	if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
		i = i % 10 + '0';
		write (fd, &i, 1);
	}
	else
	{
		i = i + '0';
		write (fd, &i, 1);
	}
	return ;
}
