/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:34:28 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 08:32:58 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_protect(long old, long new, int *isnegative)
{
	if (new < old && *isnegative < 0)
		return (1);
	else if (new < old && *isnegative > 0)
		return (2);
	else
		return (0);
}

static char	*skip_begining(char *str, int *isnegative)
{
	while (*str && is_space(*str))
		str++;
	if (*str == '-')
	{
		*isnegative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

static char	get_nbr(char **str, bool *error, int *isnegative, long *nb)
{
	while (**str && ft_isdigit(**str))
	{
		*error = true;
		if (ft_protect(*nb, *nb * 10 + **str - '0', isnegative) == 1)
			return ((unsigned char)255);
		else if (ft_protect(*nb, *nb * 10 + **str - '0', isnegative) == 2)
			return ((unsigned char)255);
		*error = false;
		*nb = *nb * 10 + **str - '0';
		*str = *str + 1;
	}
	return (0);
}

char	ft_atoi(t_token *token, bool *error)
{
	int		isnegative;
	long	nb;
	char	*str;

	*error = false;
	if (!token || !token->word)
		return (0);
	nb = 0;
	isnegative = 1;
	str = skip_begining(token->word, &isnegative);
	if (!ft_isdigit(*str))
	{
		*error = true;
		return ((char)255);
	}
	if (get_nbr(&str, error, &isnegative, &nb) != 0)
		return ((char)255);
	if (*str && !ft_isdigit(*str))
	{
		*error = true;
		return ((char)255);
	}
	return (nb * isnegative);
}

int	do_exit(t_mini *mini, t_token *token, int lvl)
{
	unsigned char	exit_code;
	bool			error;

	if (token)
		token = token->next;
	token = get_next_arg(token);
	error = false;
	exit_code = ft_atoi(token, &error);
	if (error || (token && get_next_arg(token->next)))
	{
		if (error)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(token->word, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
		else
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	if (lvl == 0)
		ft_putstr_fd("exit\n", 1);
	cleanup_exit(mini, exit_code);
	return (exit_code);
}
