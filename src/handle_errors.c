/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:28:23 by ylemkere          #+#    #+#             */
/*   Updated: 2026/01/16 23:28:23 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_exit_failure(t_data *data, char *msg)
{
	printf("%s\n", msg);
	fret_edata(data);
	exit(1);
}
