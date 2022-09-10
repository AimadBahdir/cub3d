/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:03:36 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/15 18:29:55 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		on_keypress(int key)
{
	if (key == 126)
		t_key.faceup = 1;
	if (key == 125)
		t_key.facedown = 1;
	if (key == 13)
		t_key.up = 1;
	if (key == 1)
		t_key.down = 1;
	if (key == 0)
		t_key.left = 1;
	if (key == 123)
		t_key.faceleft = 1;
	if (key == 2)
		t_key.right = 1;
	if (key == 124)
		t_key.faceright = 1;
	if (key == 53)
		t_key.esc = 1;
	return (0);
}

int		on_keyup(int key)
{
	if (key == 126 || key == 259)
		t_key.faceup = 0;
	if (key == 125 || key == 259)
		t_key.facedown = 0;
	if (key == 13 || key == 259)
		t_key.up = 0;
	if (key == 1 || key == 259)
		t_key.down = 0;
	if (key == 0 || key == 259)
		t_key.left = 0;
	if (key == 123 || key == 259)
		t_key.faceleft = 0;
	if (key == 2 || key == 259)
		t_key.right = 0;
	if (key == 124 || key == 259)
		t_key.faceright = 0;
	if (key == 53)
		t_key.esc = 0;
	if (key == 49)
		t_key.opendoor = 1;
	return (0);
}

int		on_exit(void)
{
	exit(retfreetwo(t_map.map, 1));
	return (-1);
}

int		opendoor(void)
{
	t_pos p;

	p.x = t_player.pos.x + (cos((t_player.ang) * RAD) * (STEP * 5));
	p.y = t_player.pos.y + (sin((t_player.ang) * RAD) * (STEP * 5));
	if (t_map.map[(int)(p.y / TILE_SIZE)][(int)(p.x / TILE_SIZE)] == '4')
	{
		t_map.map[(int)(p.y / TILE_SIZE)][(int)(p.x / TILE_SIZE)] = '0';
		return (1);
	}
	t_key.opendoor = 0;
	return (0);
}

int		on_update(void)
{
	int an;

	resetimg();
	if (checkbeforstep())
	{
		if (t_key.down)
		{
			t_player.pos.x -= cos(t_player.ang * RAD) * STEP;
			t_player.pos.y -= sin(t_player.ang * RAD) * STEP;
		}
		if (t_key.up || t_key.right || t_key.left)
		{
			an = (t_key.right) ? 90 : 0;
			an = (t_key.left) ? -90 : an;
			t_player.pos.x += cos((t_player.ang + an) * RAD) * STEP;
			t_player.pos.y += sin((t_player.ang + an) * RAD) * STEP;
		}
	}
	if (t_key.faceleft || t_key.faceright)
		t_player.ang = normang(t_player.ang
						- ((t_key.faceright) ? -(STEP / 2) : STEP / 2));
	if (t_key.esc)
		on_exit();
	return (printmap());
}
