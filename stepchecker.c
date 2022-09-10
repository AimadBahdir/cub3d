/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stepchecker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:31:29 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/15 18:31:59 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resetimg(void)
{
	mlx_destroy_image(t_win.mlx_ptr, t_win.img.img);
	mlx_clear_window(t_win.mlx_ptr, t_win.win_ptr);
	t_win.img.img = mlx_new_image(t_win.mlx_ptr,
						t_win.resl.width, t_win.resl.height);
}

int		checkforwall(t_pos p, int h)
{
	int x;
	int y;

	p.y -= (h && t_ray.faceup) ? 1 : 0;
	p.x -= (!h && t_ray.faceleft) ? 1 : 0;
	x = p.x / TILE_SIZE;
	y = p.y / TILE_SIZE;
	if (t_map.map[y][x] == '1'
	|| t_map.map[y][x] == '4')
		return (1);
	return (0);
}

int		checkbeforstep(void)
{
	t_pos	p;
	char	c;
	int		an;

	p.x = t_player.pos.x;
	p.y = t_player.pos.y;
	if (t_key.down)
	{
		p.x -= cos(t_player.ang * RAD) * (STEP * 5);
		p.y -= sin(t_player.ang * RAD) * (STEP * 5);
	}
	if (t_key.up || t_key.right || t_key.left)
	{
		an = (t_key.right) ? 90 : 0;
		an = (t_key.left) ? -90 : an;
		p.x += cos((t_player.ang + an) * RAD) * (STEP * 5);
		p.y += sin((t_player.ang + an) * RAD) * (STEP * 5);
	}
	if (t_key.opendoor)
		return (opendoor());
	if ((t_key.facedown && g_updown > -800)
		|| (t_key.faceup && g_updown < 800))
		g_updown += (t_key.faceup) ? STEP * 5 : -STEP * 5;
	c = t_map.map[(int)(p.y / TILE_SIZE)][(int)(p.x / TILE_SIZE)];
	return ((c != '1' && c != '2' && c != '3' && c != '4' && c != ' ') ? 1 : 0);
}

float	getcol(float stp, t_texdata img, float wallheight)
{
	int deref;

	deref = (int)(t_tex.offset + ((int)(stp) * img.xpm.width));
	if (deref >= 0 && deref < img.xpm.width * img.xpm.height)
		t_tex.color = img.addr[deref];
	return (img.xpm.height / wallheight);
}
