#include "../includes/minishell.h"

#define COLOR_RESET   "\x1B[0m"
#define COLOR_RED     	"\x1B[31m"
#define COLOR_GREEN   	"\x1B[32m"
#define COLOR_YELLOW  	"\x1B[33m"
#define COLOR_BLUE    	"\x1B[34m"
#define COLOR_MAGENTA 	"\x1B[35m"
#define COLOR_CYAN    	"\x1B[36m"
#define COLOR_GREEN_2 	"\x1B[92m"
#define COLOR_B_YELLOW 	"\x1B[93m"
#define COLOR_B_BLUE  	"\x1B[94m"
#define COLOR_B_MAGENTA "\x1B[95m"
#define COLOR_B_CYAN  	"\x1B[96m"

const char *getTokenTypeName(t_token *token)
{
    switch (token->type) {
        case OR:         return "OR";
        case PIPE:       return "PIPE";
        case AND:        return "AND";
        case H_DOC:      return "H_DOC";
        case RED_IN:     return "RED_IN";
        case RED_AP_OUT: return "RED_AP_OUT";
        case RED_OUT:    return "RED_OUT";
        case OPEN_PAR:   return "OPEN_PAR";
        case CLOSE_PAR:  return "CLOSE_PAR";
        case WORD:       return "WORD";
        default:         return "Other";
    }
}

void printTokenTypeWithColor(t_token *token)
{
    const char *color = COLOR_RESET;

    switch (token->type) {
        case OR:         color = COLOR_RED;    break;
        case PIPE:       color = COLOR_GREEN;  break;
        case AND:        color = COLOR_YELLOW; break;
        case H_DOC:        color = COLOR_BLUE; break;
        case RED_IN:        color = COLOR_MAGENTA; break;
        case RED_AP_OUT:        color = COLOR_GREEN_2; break;
        case RED_OUT:        color = COLOR_B_YELLOW; break;
        case OPEN_PAR:        color = COLOR_B_BLUE; break;
        case CLOSE_PAR:        color = COLOR_B_MAGENTA; break;
        case WORD:        color = COLOR_B_CYAN; break;
        default: break;
    }

    printf("%s%s%s", color, getTokenTypeName(token), COLOR_RESET);
}


void	print_tokens(t_mini *mini)
{
	t_token *token = *mini->token;
	t_token	*last_node = NULL;
	while (token)
	{
		printf("[");
   	 	printTokenTypeWithColor(token);
		if (token->type == WORD)
			printf("(%s)", token->word);
		printf("]-");
		if (token && token->next == NULL)
			last_node = token;
		token = token->next;
	}
	printf("\n");
}

void	expand_tokens(t_mini *mini)
{
	t_token *token = *mini->token;
	while (token)
	{
		expand_token(mini, token);
		token = token->next;
	}
	printf("\n");
}

void	print_envs(t_mini *mini)
{
	t_env *env = *mini->env;
	while (env)
	{
		if (env->is_exported && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	print_tree(t_tree *tree, int level) // to delete
{
	if (!tree)
		return ;
	for (int i = 0; i < level; i++) {
        printf("  ");
    }
	printTokenTypeWithColor(tree->node);
	printf(": %d", level);
	if (tree->node->type == WORD)
	{
		t_token *token = tree->node;
		printf("\t: ");
		printf("[");
		while (token && token->type == WORD)
		{
			printf("%s", token->word);
			if (token->next && token->next->type == WORD)
				printf(" ");
			token = token->next;
		}
		printf("]");
	}
	printf("\n");
	print_tree(tree->left, level + 1);
	print_tree(tree->right, level + 1);
}
