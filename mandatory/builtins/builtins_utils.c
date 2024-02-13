/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzirri <yzirri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:29:04 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/13 15:33:26 by yzirri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_next_arg(t_token *token)
{
	if (token && token->type == WORD && token->word[0] == '\0')
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

// int	export_unset_options_check(t_token *token, bool is_export)
// {
// 	token = get_next_arg(token);
// 	while (token)
// 	{
// 		if (token->word && token->word[0] == '-' && token->word[1])
// 			break ;
// 		token = get_next_arg(token->next);
// 	}
// 	if (!token)
// 			return (0);
// 	if (is_export)
// 		ft_putstr_fd("minishell: export: ", 2);
// 	else
// 		ft_putstr_fd("minishell: unset: ", 2);
// 	write(2, &token->word[0], 1);
// 	write(2, &token->word[1], 1);
// 	ft_putstr_fd(": invalid option\n", 2);
// 	if (is_export)
// 		ft_putstr_fd("export: usage: export [name[=value] ...] or export\n", 2);
// 	else
// 		ft_putstr_fd("unset: usage: unset [name ...]\n", 2);
// 	return (2);
// }

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

// static size_t	calculate_path_len(t_token *token)
// {
// 	size_t	final_size;

// 	final_size = 0;
// 	token = get_next_arg(token);
// 	while (token)
// 	{
// 		if (final_size != 0)
// 			final_size++;
// 		if (token->word)
// 			final_size += ft_strlen(token->word);
// 		token = token->next;
// 		token = get_next_arg(token);
// 	}
// 	return (final_size);
// }

// char	*get_combined_path(t_mini *mini, t_token *token)
// {
// 	char	*final_dst;
// 	size_t	final_size;
// 	int		index;
// 	int		jindex;

// 	final_size = calculate_path_len(token);
// 	final_dst = malloc (sizeof * final_dst * (final_size + 1));
// 	if (!final_dst)
// 		clean_exit(mini, NULL, errno);
// 	index = 0;
// 	token = get_next_arg(token);
// 	while (token)
// 	{
// 		jindex = 0;
// 		if (index != 0)
// 			final_dst[index++] = ' ';
// 		while (token->word && token->word[jindex])
// 			final_dst[index++] = token->word[jindex++];
// 		token = get_next_arg(token->next);
// 	}
// 	final_dst[index] = '\0';
// 	return (final_dst);
// }
