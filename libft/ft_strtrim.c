#include <stdlib.h>
#include "libft.h"

static int	contains(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i] != '\0' && contains(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	if (s1[i] == 0)
		return (ft_strdup(""));
	while (contains(set, s1[j]))
		j--;
	str = malloc(j - i + 2);
	if (str == 0)
		return (0);
	ft_memcpy(str, s1 + i, j - i + 1);
	str[j - i + 1] = '\0';
	return (str);
}
