#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*dst2;
	unsigned const char	*src2;

	i = 0;
	dst2 = dst;
	src2 = src;
	if (dst == 0 && src == 0)
		return (0);
	while (n > 0 && i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}
