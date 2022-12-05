#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	k;
	unsigned int	j;

	i = ft_strlen(dst);
	j = ft_strlen(src) + i;
	k = 0;
	if (i >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (src[k] != '\0' && i + k < dstsize - 1)
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = '\0';
	return (j);
}
