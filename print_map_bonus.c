/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:18:56 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/14 10:25:16 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		getxtcol(float *stp, float wallheight)
{
	if (t_ray.faceup && t_ray.horay)
		*stp += getcol(*stp, t_tex.no_img, wallheight);
	if (!t_ray.faceup && t_ray.horay)
		*stp += getcol(*stp, t_tex.so_img, wallheight);
	if (!t_ray.faceleft && !t_ray.horay)
		*stp += getcol(*stp, t_tex.ea_img, wallheight);
	if (t_ray.faceleft && !t_ray.horay)
		*stp += getcol(*stp, t_tex.we_img, wallheight);
	return (t_tex.color);
}

int		shadow(int color, float dest)
{
	int r;
	int g;
	int b;

	if ((dest / TILE_SIZE) > 1.7)
	{
		b = fmod(color, 256) / (dest / (TILE_SIZE * 1.7));
		g = fmod(color / 256, 256) / (dest / (TILE_SIZE * 1.7));
		r = fmod(color / pow(256, 2), 256) / (dest / (TILE_SIZE * 1.7));
		return (rgbtoint(r, g, b));
	}
	return (color);
}

void	printwall(float raydest, int mpx)
{
	int		rw;
	int		i;
	float	stp;
	float	wallheight;

	if (t_map.colc == -1 || t_map.colf == -1)
		throwerror("Please set (F,C) colors");
	raydest *= cos((t_player.ang - t_ray.ang) * RAD);
	wallheight = (TILE_SIZE / raydest)
				* ((t_win.resl.width / 2) / tan((FOV / 2) * RAD));
	rw = (t_win.resl.height / 2);
	i = 0;
	stp = 0;
	while (i++ < (rw - (wallheight / 2)) + g_updown)
		pixput(mpx, i, t_map.colc);
	i = (rw - (wallheight / 2)) + g_updown;
	while (i++ < (rw + (wallheight / 2) + g_updown))
		pixput(mpx, i, shadow(getxtcol(&stp, wallheight), raydest));
	i = (rw + (wallheight / 2)) + g_updown;
	while (i++ < t_win.resl.height)
		pixput(mpx, i, t_map.colf);
}

void	setwalldst(float dest, int mpx)
{
	t_sprt.wall_dst[mpx] = dest;
	if (mpx > 2)
	{
		if (t_sprt.wall_dst[mpx - 1] > t_sprt.wall_dst[mpx]
		&& t_sprt.wall_dst[mpx - 1] > t_sprt.wall_dst[mpx - 2])
			printwall(dest, --mpx);
	}
}

int		printmap(void)
{
	float	dest;
	int		mpx;
	t_pos	o;
	float	ang;

	if (!t_player.dir)
		throwerror("Player not found :(");
	if (!t_sprt.sp_file)
		throwerror("Please Set Sprite File!");
	mpx = -1;
	ang = -(FOV / 2);
	while (ang < (FOV / 2))
	{
		t_ray.ang = normang(t_player.ang + ang);
		if ((dest = get_dest(&o)) == 0)
			dest = 1;
		printwall(dest, ++mpx);
		setwalldst(dest, mpx);
		ang += (FOV / t_win.resl.width);
	}
	t_sprt.wall_dst[mpx] = '\0';
	if (t_sprt.lstobj != NULL)
		print_sprite();
	return (mlx_put_image_to_window(t_win.mlx_ptr,
			t_win.win_ptr, t_win.img.img, 0, 0));
}
