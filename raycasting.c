/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:18:56 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/12 18:56:18 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pos	lastinter_h(void)
{
	t_pos	h;

	h.y = floor(t_player.pos.y / TILE_SIZE) * TILE_SIZE;
	h.y += (!t_ray.faceup) ? TILE_SIZE : 0;
	h.x = t_player.pos.x + ((h.y - t_player.pos.y) / tan(t_ray.ang * RAD));
	t_ray.ystep = TILE_SIZE;
	t_ray.ystep *= (t_ray.faceup) ? -1 : 1;
	t_ray.xstep = TILE_SIZE / tan(t_ray.ang * RAD);
	t_ray.xstep *= (t_ray.faceleft && t_ray.xstep > 0) ? -1 : 1;
	t_ray.xstep *= (!t_ray.faceleft && t_ray.xstep < 0) ? -1 : 1;
	while (t_map.len.width > (int)(h.x / TILE_SIZE)
		&& (int)(h.x / TILE_SIZE) > 0
		&& t_map.len.height > (int)(h.y / TILE_SIZE)
		&& (int)(h.y / TILE_SIZE) > 0
		&& !checkforwall(h, 1))
	{
		h.x += t_ray.xstep;
		h.y += t_ray.ystep;
	}
	return (h);
}

t_pos	lastinter_v(void)
{
	t_pos	v;

	v.x = floor(t_player.pos.x / TILE_SIZE) * TILE_SIZE;
	v.x += (!t_ray.faceleft) ? TILE_SIZE : 0;
	v.y = t_player.pos.y + ((v.x - t_player.pos.x) * tan(t_ray.ang * RAD));
	t_ray.xstep = TILE_SIZE;
	t_ray.xstep *= (t_ray.faceleft) ? -1 : 1;
	t_ray.ystep = TILE_SIZE * tan(t_ray.ang * RAD);
	t_ray.ystep *= (t_ray.faceup && t_ray.ystep > 0) ? -1 : 1;
	t_ray.ystep *= (!t_ray.faceup && t_ray.ystep < 0) ? -1 : 1;
	while (t_map.len.width > (int)(v.x / TILE_SIZE)
		&& (int)(v.x / TILE_SIZE) > 0
		&& t_map.len.height > (int)(v.y / TILE_SIZE)
		&& (int)(v.y / TILE_SIZE) > 0
		&& !checkforwall(v, 0))
	{
		v.x += t_ray.xstep;
		v.y += t_ray.ystep;
	}
	return (v);
}

float	get_dest(t_pos *p)
{
	t_pos	h;
	t_pos	v;
	float	dsth;
	float	dstv;

	h = lastinter_h();
	v = lastinter_v();
	dsth = sqrt(pow((t_player.pos.x - h.x), 2)
			+ pow((t_player.pos.y - h.y), 2));
	dstv = sqrt(pow((t_player.pos.x - v.x), 2)
			+ pow((t_player.pos.y - v.y), 2));
	*p = (dsth < dstv) ? h : v;
	t_ray.horay = (dsth < dstv) ? 1 : 0;
	t_tex.offset = (dsth < dstv) ? fmod(h.x, TILE_SIZE) : fmod(v.y, TILE_SIZE);
	return ((dsth < dstv) ? dsth : dstv);
}
