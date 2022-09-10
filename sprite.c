/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 12:31:29 by abahdir           #+#    #+#             */
/*   Updated: 2020/11/15 17:51:50 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sp_render(int x, int y, int sp_size, t_obj *obj)
{
	int color_sp;
	int i;
	int j;

	i = -1;
	while (++i < sp_size)
	{
		if ((x + i) < 0 || (x + i) > t_win.resl.width)
			continue;
		if (obj->dest > t_sprt.wall_dst[x + i])
			continue;
		j = -1;
		while (++j < sp_size)
		{
			if ((y + j + g_updown) < 0
			|| (y + j + g_updown) >= t_win.resl.height)
				continue;
			color_sp = obj->sp_img->addr[(int)((obj->sp_img->xpm.width
					* (j * obj->sp_img->xpm.height / sp_size))
					+ (i * obj->sp_img->xpm.width / sp_size))];
			if (color_sp != obj->sp_img->addr[0])
				pixput((x + i), (y + j + g_updown),
						shadow(color_sp, obj->dest));
		}
	}
}

short	set_sprtex(t_obj *obj)
{
	if (!(obj->sp_img->img = mlx_xpm_file_to_image(t_win.mlx_ptr,
					obj->sp_img->path, &obj->sp_img->xpm.width,
					&obj->sp_img->xpm.height)))
		return (0);
	if (!(obj->sp_img->addr = (int *)mlx_get_data_addr(obj->sp_img->img,
					&t_win.img.bits_per_pixel, &t_win.img.line_length,
					&t_win.img.endian)))
		return (0);
	return (1);
}

void	ft_sprite(t_obj *obj)
{
	float sp_size;
	float x_inter;
	float y_inter;
	float sp_ang;

	sp_ang = atan2(obj->p.y - t_player.pos.y, obj->p.x - t_player.pos.x);
	while ((sp_ang - (t_player.ang * RAD)) > M_PI)
		sp_ang -= 2 * M_PI;
	while ((sp_ang - (t_player.ang * RAD)) < -M_PI)
		sp_ang += 2 * M_PI;
	sp_size = (t_win.resl.width / obj->dest) * TILE_SIZE;
	y_inter = (t_win.resl.height / 2) - (sp_size / 2);
	x_inter = (sp_ang - t_player.ang * RAD) * t_win.resl.width /
	(FOV * RAD) + (t_win.resl.width / 2 - sp_size / 2);
	if (set_sprtex(obj) == 1)
		sp_render(x_inter, y_inter, sp_size, obj);
	else
		throwerror("Sprite textur not found!");
}

void	print_sprite(void)
{
	t_obj *ob;

	setdests();
	sortlst(&t_sprt.lstobj);
	ob = t_sprt.lstobj;
	while (ob)
	{
		ft_sprite(ob);
		ob = ob->next;
	}
}

void	set_sprite(int x, int y)
{
	char	*tex;

	tex = NULL;
	if (t_map.map[y][x] == '2' && t_sprt.sp_file)
		tex = t_sprt.sp_file;
	else if (t_map.map[y][x] == '3' && t_sprt.sp_file1)
		tex = t_sprt.sp_file1;
	else
		throwerror("Please Set Sprites");
	x = (x * TILE_SIZE) + (TILE_SIZE / 2);
	y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	ft_lstaddobj(&t_sprt.lstobj, ft_lstnewobj(x, y, 0, tex));
}
