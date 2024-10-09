#include "../../includes/minishell.h"

// void	free_tree_env(t_tree **ast, t_env **env_var) free_data should be called instead
// {
// 	free_tree(ast);
// 	free_env(env_var);
// }

int is_file(const char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0)
        return (false);
    return (S_ISREG(path_stat.st_mode));
}