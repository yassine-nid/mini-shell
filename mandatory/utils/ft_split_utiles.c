/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 08:26:59 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/01/28 08:29:03 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			t_size;

	t_size = count * size;
	p = (unsigned char *) malloc (t_size);
	if (p != NULL)
	{
		while (t_size--)
			p[t_size] = 0;
	}
	else
	{
		errno = ENOENT;
		return (NULL);
	}
	return ((void *)p);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (--dstsize > 0 && *src)
	{
		*(dst++) = *(src++);
	}
	*dst = '\0';
	return (src_len);
}
