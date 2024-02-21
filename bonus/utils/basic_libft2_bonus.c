/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_libft2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:09:54 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 15:36:57 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static int	calc_alloc_size(int nbr)
{
	int	allocate_size;

	allocate_size = 0;
	if (nbr <= 0)
		allocate_size++;
	while (nbr != 0)
	{
		nbr /= 10;
		allocate_size++;
	}
	return (allocate_size);
}

static void	fill_str(char *str, int current, int nbr, int isnegative)
{
	int	n;

	if (isnegative && current == 0)
		return ;
	if (current != 0)
		fill_str(str, current - 1, nbr / 10, isnegative);
	n = nbr % 10;
	if (n < 0)
		n *= -1;
	str[current] = n + '0';
}

char	*ft_itoa(int n)
{
	int		alloc_size;
	char	*resut;

	alloc_size = calc_alloc_size(n);
	resut = malloc(sizeof(char) * (alloc_size + 1));
	if (resut == NULL)
		return (NULL);
	if (n < 0)
	{
		resut[0] = '-';
		fill_str(resut, alloc_size - 1, n, 1);
	}
	else
		fill_str(resut, alloc_size - 1, n, 0);
	resut[alloc_size] = '\0';
	return (resut);
}

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	int	islower;
	int	isupper;

	islower = c >= 'a' && c <= 'z';
	isupper = c >= 'A' && c <= 'Z';
	return (islower || isupper);
}
