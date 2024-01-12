/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:58:42 by yzirri            #+#    #+#             */
/*   Updated: 2024/01/12 16:12:03 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		s++;
		size++;
	}
	return (size);
}

char	*ft_strdup(const char *s1)
{
	char	*s1_cpy;

	s1_cpy = malloc (sizeof * s1_cpy * (ft_strlen(s1) + 1));
	if (s1_cpy == NULL)
		return (NULL);
	ft_memcpy(s1_cpy, s1, ft_strlen(s1) + 1);
	return (s1_cpy);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	while (n != 0 && n-- > 0)
		*((unsigned char *)s++) = '\0';
}
