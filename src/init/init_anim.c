/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:37:25 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 11:12:59 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*load_frame(const char *path)
{
	return (mlx_load_png(path));
}

void	init_anim(t_anim *anim)
{
	anim->frame_count = 5;
	anim->current = 0;
	anim->timer = 0;
	anim->frames[0] = load_frame("textures/sprite/s0.png");
	anim->frames[1] = load_frame("textures/sprite/s1.png");
	anim->frames[2] = load_frame("textures/sprite/s2.png");
	anim->frames[3] = load_frame("textures/sprite/s3.png");
	anim->frames[4] = load_frame("textures/sprite/s4.png");
}
