#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (s[i] != (char)c && i > 0)
		i--;
	if ((char) s[i] == (char) c)
		return ((char *)s + i);
	return (0);
}
