/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:57:17 by ynidkouc          #+#    #+#             */
/*   Updated: 2024/02/21 15:37:00 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static int	ft_countwords(char const *s, char c)
{
	int	nb;

	nb = 0;
	if (!s || !*s)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			nb++;
		while (*s && *s != c)
			s++;
	}
	return (nb);
}

static size_t	ft_getsize(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (*s && *s != c)
	{
		s++;
		size++;
	}
	return (size);
}

static char	**ft_free_s(char **p, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(p[j]);
		j++;
	}
	free(p);
	return (NULL);
}

static char	**ft_spliiit(char const *s, char c, size_t cw, size_t i)
{
	char	**p;

	if (!s)
		return (NULL);
	cw = ft_countwords(s, c);
	p = (char **) ft_calloc((cw + 1), sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	while (*s && i < cw)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			p[i] = (char *) malloc ((ft_getsize(s, c) + 1) * sizeof(char));
			if (!p[i])
				return (ft_free_s(p, i));
			ft_strlcpy(p[i++], s, ft_getsize(s, c) + 1);
		}
		while (*s && *s != c)
			s++;
	}
	return (p);
}

char	**ft_split(char const *s, char c)
{
	size_t	cw;
	size_t	i;

	cw = 0;
	i = 0;
	return (ft_spliiit(s, c, cw, i));
}
