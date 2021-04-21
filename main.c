/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 01:25:08 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/07 01:25:13 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_executor.h"

// void	place_var_to_matr(char **matrix, size_t *start_i, size_t end_i,
// 			char *var)
// {
// 	free(matrix[*start_i]);
// 	matrix[*start_i] = var;
// 	*start_i += 1;
// 	while (*start_i <= end_i)
// 	{
// 		matrix[*start_i][0] = 0;
// 		*start_i += 1;
// 	}
// }

// int keycmp(const char *s1, const char *s2)
// {
//     size_t  i;
//     i = 0;
//     while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=' && s1[i] == s2[i])
//         i++;
//     if (s1[i] == '=' && s2[i] == '=')
//         return (0);
//     if (s1[i] == '=')
//         return (- (unsigned char)s2[i]);
//     if (s2[i] == '=')
//         return ((unsigned char)s1[i]);
//     return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

// int	get_fd(char **matrix, size_t *red_i, size_t cmd_end,
// 			t_cmds_pipeline	*pipeline)
// {
// 	int	fd;
// 	char *file_name;

// 	matrix[*red_i][0] = -1;
// 	while (matrix[*red_i][0] == -1)
// 		*red_i += 1;
// 	file_name = get_filename(matrix, red_i, cmd_end, pipeline);
// 	fd = open(pipeline->infile, O_RDONLY);
// 	if (fdin == -1)
// 	{
// 		write(2, "Cannot open file.\n", 18);
// 		exit(1);
//     }
// }

void	free_cmd(void *cmd)
{
	ft_split_clear(((t_command *)cmd)->argv);
	free(cmd);
	cmd = NULL;
}

int		process_shline(char **symbol_matrix, t_cmds_pipeline *pipeline)
{
	size_t	pipeline_i;

	pipeline_i = 0;
	if (!split_to_lexemes(symbol_matrix))
		exit(1); //syntax error
	while (symbol_matrix[pipeline_i])
	{
		parse_pipeline(symbol_matrix, &pipeline_i, pipeline);
		ft_executor(pipeline);
		ft_lstclear(&pipeline->cmds, &free_cmd);
	}
	return (1);
}

int		main(int argc, char *argv[], char *envp[])
{
	int				res;
	char			*line;
	char			**symbol_matrix;
	t_cmds_pipeline	pipeline;

	(void)argc;
	(void)argv;
	pipeline.cmds = NULL;
	pipeline.infile = NULL;
	pipeline.outfile = NULL;
	envp_to_list(&pipeline, envp);
	// size_t i = 0;
	// while (envp[i])
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	// printf("----------------------------------------------\n");
	// while (pipeline.envp)
	// {
	// 	printf("%s%s\n", ((t_env_var *)pipeline.envp->data)->key, ((t_env_var *)pipeline.envp->data)->value);
	// 	pipeline.envp = pipeline.envp->next;
	// }
	// return(0);
	while (1)
	{
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd("$ ", 1);
		res = get_next_line(0, &line);
		if (!res)
		{
			ft_putstr_fd("exit\n", 1);
			return(0);
		}
		else if(res < 0)
			exit(1);//gnl error
		symbol_matrix = split_line_to_matrix(line);
		if (!symbol_matrix)
			exit(1);
		process_shline(symbol_matrix, &pipeline);
		free(line);
	}
	return (0);
}


// typedef enum e_func {
//     func1,
//     func2
// }               t_func;

// void f1(void)
// {
//     printf("func1\n");
// }

// void f2(void)
// {
//     printf("func2\n");
// }

// int main()
// {
//     void (*f[2])(void);
    
//     f[0] = f1;
//     f[1] = f2;
//     (*f[func1])();
//     return 0;
// }