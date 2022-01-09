/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalsami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:03:09 by ebalsami          #+#    #+#             */
/*   Updated: 2022/01/09 15:03:10 by ebalsami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	ft_get_time(void)
{
	struct timeval	tv;
	time_t			res;

	gettimeofday(&tv, 0);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	*ft_calloc(long int count, int size)
{
	char	*mem;

	count *= size;
	mem = (char *)malloc(count);
	if (!mem)
		return (0);
	while (--count >= 0)
		mem[count] = 0;
	return (mem);
}

int	ft_atoi_philo(const char *str)
{
	int	i;
	int	result;
	int	result_tmp;

	i = 0;
	result = 0;
	result_tmp = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result < result_tmp)
			return (-1);
		result_tmp = result;
	}
	if (!str[i])
		return (result);
	return (-1);
}

void	ft_putstr_err(char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	write(2, str, count);
}
