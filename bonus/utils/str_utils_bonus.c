/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:39:45 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 15:37:08 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

int	ft_tolower(int c)
{
	if (c <= 'Z' && c >= 'A')
		return (c + ('a' - 'A'));
	return (c);
}

bool	ft_strcmp_no_case(const char *s1, const char *s2)
{
	if (!s1 && s2)
		return (false);
	if (s1 && !s2)
		return (false);
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return (false);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 == (unsigned char)*s2);
}

int	ft_putstr_fd(char *s, int fd)
{
	char	c;
	int		return_val;

	if (s == NULL)
		return (write(fd, "", 0));
	return_val = 0;
	while (*s)
	{
		c = *s;
		return_val += write(fd, &c, 1);
		s++;
	}
	return (return_val);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*p;
	size_t	i;

	if (!s1 || !s2)
		return (ft_strdup(""));
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *) malloc (size * sizeof (char));
	if (!p)
		return (0);
	i = 0;
	while (*s1)
	{
		p[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		p[i++] = *s2;
		s2++;
	}
	p[i] = '\0';
	return (p);
}
