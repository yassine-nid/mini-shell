/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynidkouc <ynidkouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:15:41 by yzirri            #+#    #+#             */
/*   Updated: 2024/02/21 15:33:47 by ynidkouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

static t_env	*is_env(t_mini *mini, char *word, int index, int *skip)
{
	t_env	*env;

	if (!word || !word[index++])
		return (NULL);
	env = *mini->env;
	while (env)
	{
		*skip = 0;
		while (env->key && env->key[*skip] && word[index + *skip])
		{
			if (env->key[*skip] != word[index + *skip])
				break ;
			*skip = *skip + 1;
		}
		if (env->key && !env->key[*skip] && !is_alpha_num(word[index + *skip]))
			return (env);
		env = env->next;
	}
	*skip = 0;
	while (word[index + *skip] && is_alpha_num(word[index + *skip]))
		*skip = *skip + 1;
	return (NULL);
}

static char	*alloc(t_mini *mini, int len, char *env_value, bool free_src)
{
	int		alloc_size;
	int		ind;
	char	*new_word;

	alloc_size = len;
	ind = 0;
	while (env_value && env_value[ind++])
		alloc_size++;
	new_word = malloc(sizeof * new_word * (alloc_size + 1));
	if (!new_word)
	{
		if (free_src)
			free(env_value);
		clean_exit(mini, NULL, errno);
	}
	new_word[alloc_size] = '\0';
	while (--alloc_size >= 0)
		new_word[alloc_size] = 'o';
	return (new_word);
}

void	m_expand_word(t_mini *mini, t_token *token, int index)
{
	t_env	*env;
	int		skip_l;
	int		ind;
	char	*n_w;

	env = is_env(mini, token->word, index, &skip_l);
	if (env)
		n_w = alloc(mini, ft_strlen(token->word) - (skip_l + 1), env->value, 0);
	else
		n_w = alloc(mini, ft_strlen(token->word) - (skip_l + 1), NULL, false);
	ind = -1;
	while (++ind < index)
		n_w[ind] = token->word[ind];
	ind = 0;
	while (env && env->value && env->value[ind])
	{
		n_w[ind + index] = env->value[ind];
		if (n_w[ind + index] == '\'' || n_w[ind + index] == '\"')
			n_w[ind + index] = (unsigned char)(n_w[ind + index] + 100);
		ind++;
	}
	ind += index - 1;
	while (n_w[++ind])
		n_w[ind] = token->word[index++ + skip_l + 1];
	(free(token->word), token->word = n_w);
}

void	m_expand_status(t_mini *mini, t_token *token, int index)
{
	char	*new_word;
	int		ind;
	char	*exit_st;

	exit_st = ft_itoa(mini->exit_status);
	if (!exit_st)
		clean_exit(mini, NULL, errno);
	new_word = alloc(mini, ft_strlen(token->word) - 2, exit_st, true);
	ind = -1;
	while (++ind < index)
		new_word[ind] = token->word[ind];
	ind = 0;
	while (exit_st[ind])
	{
		new_word[ind + index] = exit_st[ind];
		ind++;
	}
	ind += index - 1;
	while (new_word[++ind])
		new_word[ind] = token->word[index++ + 2];
	free(token->word);
	free(exit_st);
	token->word = new_word;
}
