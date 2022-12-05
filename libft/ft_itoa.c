/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 13:44:50 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/05 13:44:51 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 13:44:50 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/05 13:44:51 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_word(long int n)
{
	int	numbers;

	numbers = 0;
	if (n < 0)
		numbers++;
	if (n == 0)
		numbers++;
	while (n != 0)
	{
		numbers++;
		n = n / 10;
	}
	return (numbers);
}

static char	*reverse(long int n, char *str, int count)
{
	count--;
	if (n < 0)
		n = n * -1;
	while (count >= 0)
	{
		str[count] = n % 10 + '0';
		n = n / 10;
		count--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			count;
	long int	num;

	num = n;
	count = count_word(num);
	str = malloc (count + 1 * sizeof (*str));
	if (str == 0)
		return (NULL);
	reverse(num, str, count);
	if (num < 0)
		str[0] = '-';
	str[count] = '\0';
	return (str);
}
