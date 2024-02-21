/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:29:04 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 15:31:28 by ynidkouc         ###   ########.fr       */
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
