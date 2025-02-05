/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 23:56:58 by alegrix           #+#    #+#             */
/*   Updated: 2025/02/05 01:59:03 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
{
	int	index;

	if (!array)
		return ;
	index = 0;
	while (array[index])
		free(array[index++]);
	free(array);
	return ;
}

void	access_path(char **envp, char **cmop, char **argv)
{
	if (cmop[0] == NULL)
	{
		perror("Invailible commaaande");
		free_array(cmop);
		exit(8);
	}
	if (ft_strncmp(argv[1], cmop[0], ft_strlen(argv[1])) != 0
		&& ft_strncmp(argv[4], cmop[0], ft_strlen(argv[3])) != 0)
	{
		if (access(cmop[0], X_OK) == 0)
		{
			if (execve(cmop[0], cmop, envp) == -1)
			{
				perror("Invailiblessss commande");
				free_array(cmop);
				exit(12);
			}
		}
	}
	return ;
}
