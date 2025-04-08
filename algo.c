
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:12:37 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/05 22:45:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

void bfs(int map)
{
	int depth = 0;
	t_state *tmp;

	// creation d un premier etat
	t_state *current_state = 0;
	//inititialise le count
	memset(g_map_count, 0, sizeof(g_map_count));
	if (map == 0)
	{
		//si c est la map nul
		current_state = init_state(0, 0);
		current_state->depth[0] = 1;
		g_cur_depth = current_state->depth;
		g_cur_nb_dice = 0;
		gen_next_map (current_state->id);
	}
	else
		current_state = init_state(map, 9 - count_zero(map));
	current_state->depth[0] = 1;
	

	while (depth <= g_max_depth + 2)  //securite pas de reel perte de temp
	{
		for (int i = 9; i >= 0; i--)
		{
			//printf("depth : %d      nb_de : %d\n", depth, i);
			//affich_tab_map();
			for (int w = 0; w < g_map_count[i]; w++)
			{
				/*
				printf("depth : %d      nb_de : %d [", depth, i);
				for (int j = 0; j < 10; j++)
					printf("%d ", g_map_count[j]);
				printf("]\n");
				*/
				current_state = &(g_map_table[i][w]);
			
				add_hash(current_state); //On enleve jsute ceux qui ateignent la depth. hash += curent_state->depth[depth] 
				//on met a jours les variable globales
				g_cur_depth = current_state->depth;
				g_cur_nb_dice = i;
				if (test_depth (current_state))
					gen_next_map (current_state->id);
				//free current_state au fur et a mesure
			}
			g_map_count[i] = 0; 		//reset le compteur
		}
		depth++;
	}
}