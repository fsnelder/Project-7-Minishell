#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	int				i;

	i = 0;
	str = s;
	while (n > 0)
	{	
		*str++ = i;
		n--;
	}
}
