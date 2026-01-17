/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:29:50 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/17 21:07:10 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <fcntl.h>

void	get_filt_edata(t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	data->filt_edata = malloc(sizeof(char *) * (data->line_count + 1));
	if (!data->filt_edata)
	{
		ft_exit_failure(data, "{-} Error! allocation");
	}
	fd = open(data->file_str, O_RDONLY);
	if (fd < 0)
		ft_exit_failure(data, "{-} Error opening file");
	line = get_next_line(fd);
	while (line)
	{
		data->filt_edata[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	data->filt_edata[data->line_count] = NULL;
	close(fd);
}
