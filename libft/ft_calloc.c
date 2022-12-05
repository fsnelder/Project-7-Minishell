#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	int				i;
	int				j;
	unsigned char	*str;

	i = 0;
	j = 0;
	str = malloc(size * count);
	if (str == 0)
		return (NULL);
	size = size * count;
	while (size > 0)
	{
		str[j] = i;
		size--;
		j++;
	}
	if (size != '\0')
		return (str + i);
	else
		return (str);
}
