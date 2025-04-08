/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:47:16 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/08 17:11:36 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

/****
 * ja i un tableua de filtre et une map
 */
int	try_take2(int map, int *tab, int cur_case)
{
	//je test toutes les pair de deux dans le tableau (double boucle)
	int i;
	int j;
	int sum;
	int new_map;

	int err = 0;
	for (i = 0; i < 3; i++)
	{
		if (tab[i] == 0)
			continue;
		for (j = i + 1; j < 4; j++)
		{
			if (tab[j] == 0)
				continue;
			sum = sum_map(tab[i] + tab [j]);
			if (sum <= 6)
			{
				//faire la prise ici
				//on va generer la map
				new_map = map;
				new_map -= (tab[i] + tab[j]);
				new_map += (sum << (3 * cur_case));
				// et on limprime plutot que de la stoker
				//printf("map : %o\n", new_map);
				add_state_list(g_cur_nb_dice - 1, new_map);
				err++;
			}
		}
	}	
	return (err);
}

// faire la meme chose mais avec 3 cases
int	try_take3(int map, int *tab, int cur_case)
{
	int sum;
	int new_map;
	int err = 0;
	
	if (tab[0] && tab[1] && tab[2])
	{
		sum = sum_map(tab[0] + tab[1] + tab[2]);
		if (sum <= 6)
		{
			//faire la prise ici
			//on va generer la map
			new_map = map;
			new_map -= (tab[0] + tab[1] + tab[2]);
			new_map += (sum << (3 * cur_case));
			// et on limprime plutot que de la stoker
			//printf("map : %o\n", new_map);
			add_state_list(g_cur_nb_dice - 2, new_map); 
			err++;
		}
	}
	if (tab[0] && tab[1] && tab[3])
	{
		sum = sum_map(tab[0] + tab[1] + tab[3]);
		if (sum <= 6)
		{
			//faire la prise ici
			//on va generer la map
			new_map = map;
			new_map -= (tab[0] + tab[1] + tab[3]);
			new_map += (sum << (3 * cur_case));
			// et on limprime plutot que de la stoker
			//printf("map : %o\n", new_map);
			add_state_list(g_cur_nb_dice - 2, new_map);
			err++;
		}
	}
	if (tab[0] && tab[2] && tab[3])
	{
		sum = sum_map(tab[0] + tab[2] + tab[3]);
		if (sum <= 6)
		{
			//faire la prise ici
			//on va generer la map
			new_map = map;
			new_map -= (tab[0] + tab[2] + tab[3]);
			new_map += (sum << (3 * cur_case));
			// et on limprime plutot que de la stoker
			//printf("map : %o\n", new_map);
			add_state_list(g_cur_nb_dice - 2, new_map);
			err++;
		}
	}
	if (tab[1] && tab[2] && tab[3])
	{
		sum = sum_map(tab[1] + tab[2] + tab[3]);
		if (sum <= 6)
		{
			//faire la prise ici
			//on va generer la map
			new_map = map;
			new_map -= (tab[1] + tab[2] + tab[3]);
			new_map += (sum << (3 * cur_case));
			// et on limprime plutot que de la stoker
			//printf("map : %o\n", new_map);
			add_state_list(g_cur_nb_dice - 2, new_map);
			err++;
		}
	}
	return (err);
}

int	try_take4(int map, int *tab, int cur_case)
{
	int sum;
	int new_map;

	if (tab[0] && tab[1] && tab[2] && tab[3])
	{
		sum = sum_map(tab[0] + tab[1] + tab[2] + tab[3]);
		if (sum <= 6)
		{
			//faire la prise ici
			//on va generer la map
			new_map = map;
			new_map -= (tab[0] + tab[1] + tab[2] + tab[3]);
			new_map += (sum << (3 * cur_case));
			// et on limprime plutot que de la stoker
			//printf("map : %o\n", new_map);
			add_state_list(g_cur_nb_dice - 3, new_map);
			return (1);
		}
	}
	return (0);
}

