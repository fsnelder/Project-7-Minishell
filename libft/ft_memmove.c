#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;

	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	if (dst <= src)
	{	
		while (len > 0 && i < len)
		{	
			((unsigned char *) dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}	
	}
	return (dst);
}
