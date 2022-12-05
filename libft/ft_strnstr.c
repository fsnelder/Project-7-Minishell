#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int				i;
	unsigned int	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)&haystack[i]);
	while (haystack[i] != '\0' && len > 0)
	{
		j = 0;
		if (ft_strlen(needle) > ft_strlen(haystack))
			return (0);
		while (haystack[i + j] == needle[j] && len > 0 + j)
		{
			if (haystack[j + 1] == '\0' || needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
		len--;
	}
	return (0);
}
