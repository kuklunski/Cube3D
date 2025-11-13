/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylemkere <ylemkere@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:23:48 by ylemkere          #+#    #+#             */
/*   Updated: 2025/11/05 20:23:48 by ylemkere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    *ft_memset(void *b, int c, size_t len)
{
    unsigned char    *tmp_ptr;

    tmp_ptr = (unsigned char *) b;
    while (len > 0)
    {
        *(tmp_ptr++) = (unsigned char) c;
        len--;
    }
    return (b);
}