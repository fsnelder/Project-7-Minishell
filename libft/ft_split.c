#include <stdlib.h>
#include "libft.h"

static int	count_strings(const char *s, char c)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			wordcount++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (wordcount);
}

static int	wordsize(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static int	str_cpy(const char *src, int c, char **str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	size = wordsize(&src[i], c);
	*str = malloc(size + 1);
	if (str == 0)
		return (0);
	ft_strlcpy(*str, src, size + 1);
	i = i + size;
	while (src[i] == c)
		i++;
	return (1);
}

static char	**free_string(int j, char **str)
{
	while (j > 0)
	{
		j--;
		free(str[j]);
	}
	free(str);
	str = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	count = count_strings(s, c);
	str = ft_calloc((count + 1), sizeof (*str));
	if (str == 0)
		return (0);
	while (s[i] != '\0' && count > 0)
	{
		while (s[i] == c)
			i++;
		if (str_cpy(s + i, c, str + j) == 0)
			return (free_string(j, str));
		j++;
		while (s[i] != c && s[i] != '\0')
			i++;
		count--;
	}
	return (str);
}
