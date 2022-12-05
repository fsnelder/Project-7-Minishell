#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	i;
	unsigned char	*s1;

	i = ((unsigned char)c);
	s1 = ((unsigned char *)s);
	while (n > 0)
	{
		if (*s1 == i)
			return (s1);
		s1++;
		n--;
	}
	return (0);
}
