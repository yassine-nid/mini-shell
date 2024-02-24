/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:29:04 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/24 13:10:00 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

t_token	*get_next_arg(t_token *token)
{
	if (token && token->is_empty && token->type == WORD)
		return (get_next_arg(token->next));
	if (token && token->type == WORD)
		return (token);
	while (token)
	{
		while (token && (token->type == RED_IN || token->type == RED_OUT
				|| token->type == RED_AP_OUT || token->type == H_DOC))
			token = token->next;
		if (token && token->type == WORD)
			token = token->next;
		if (token && token->type == WORD)
			return (token);
		if (!token || (token->type != RED_IN && token->type != RED_OUT
				&& token->type != RED_AP_OUT && token->type != H_DOC))
			break ;
		if (token)
			token = token->next;
	}
	return (NULL);
}

int	m_print_dir_error(bool is_pwd)
{
	if (is_pwd)
		ft_putstr_fd("pwd: error retrieving current directory:", 2);
	else
		ft_putstr_fd("minihell-init: error retrieving current directory:", 2);
	ft_putstr_fd(" getcwd: cannot access parent directories:", 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	return (errno);
}

int	export_add(t_env *env, char *new_val, bool append)
{
	char	*tmp;

	if (!append)
		return (free(env->value), env->value = new_val, 0);
	if (!env->value)
		return (env->value = new_val, 0);
	tmp = ft_strjoin(env->value, new_val);
	if (!tmp)
		return (errno);
	free(env->value);
	free(new_val);
	env->value = tmp;
	return (0);
}

static int	m_cmp(const char *s1, const char *s2)
{
	if (s1 && !s2)
		return (1);
	else if (!s1 && s2)
		return (-1);
	else if (!s1 && !s2)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	env_sort(t_mini *mini, char *old_key, char *old_val)
{
	t_env	*env;
	int		index;
	bool	old_exported;

	env = *mini->env;
	while (env)
	{
		index = 0;
		if (env->next && m_cmp(env->key, env->next->key) > 0)
		{
			old_key = env->key;
			old_val = env->value;
			old_exported = env->is_exported;
			env->key = env->next->key;
			env->value = env->next->value;
			env->is_exported = env->next->is_exported;
			env->next->key = old_key;
			env->next->value = old_val;
			env->next->is_exported = old_exported;
			env = *mini->env;
			continue ;
		}
		env = env->next;
	}
}
