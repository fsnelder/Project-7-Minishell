#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;
	unsigned const char	*s1a;
	unsigned const char	*s2a;

	i = 0;
	s1a = (unsigned const char *)s1;
	s2a = (unsigned const char *)s2;
	if (n == 0)
		return (0);
	while (s1a[i] != '\0' && s2a[i] != '\0' && n - 1 > 0 && s1a[i] == s2a[i])
	{
		i++;
		n--;
	}
	return (s1a[i] - s2a[i]);
}
