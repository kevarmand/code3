
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:05:58 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/07 17:37:20 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"

/****
 * 
 * faire le travaille de malloc a sa place putain !!! 
 *dans quel monde vis t on
 * list des indice
 * 1,       10,      226,     2494,    20890,   119170,   483058,  1347670,  2571256,  3338650, 
 * liste des size
 * 1,       9,       216,     2268,    18396,   98280,    363888,  864612,   1224586,  769394
 
 */
 
/****
 * structure de donnee :
 * un tableau de t_state taille 3338650  => g_state_table
 * un tableau de t_state * taille 10 => g_map_table
 * on init le tableau :
 * g_map_table[0] : &g_state_table[0]
 * g_map_table[1] : &g_state_table[1]
 * g_map_table[2] : &g_state_table[10]
 * g_map_table[3] : &g_state_table[226]
 * g_map_table[4] : &g_state_table[2494]
 * g_map_table[5] : &g_state_table[20890]
 * g_map_table[6] : &g_state_table[119170]
 * g_map_table[7] : &g_state_table[483058]
 * g_map_table[8] : &g_state_table[1347670]
 * g_map_table[9] : &g_state_table[2571256]
 * 
 * il nous faut egalement une tableau dint pour savoir le nombre d element actif dans le tableau
 * g_map_count[10]  : memset(0) ->incremente sur un appel a ft_malloc
 * 
 * ATTENTION : Penser a reset g_map_count[i] apres la gestion de l etat i
 * 
 */



/***
 * Du coup on a besoin de l idee mais egalement savoir dans quel zone memoire on se trouve
 */
void	*init_state(int id, int nb_dice)
{
	//on demande de la memoire pour un state
	t_state *state = ft_malloc(nb_dice);
	state->id = id;
	memset(state->depth, 0, sizeof(state->depth));
	return (state);
}

/***
 * On sait dans quel zone de memoire on reserve
 */
void	*ft_malloc(int nb_dice)
{
	t_state *state;
	int i = 0;
	
	//on catch l index de la liste 

	int index = g_map_count[nb_dice];

	//on recup le pointeur sur cette element

	state = &((g_map_table[nb_dice])[index]);

	//on incremente le compteur
	g_map_count[nb_dice]++;
	//on returne l adresse de l element

	//Pour etre sur qu on depasse pas  on va faire des check TODO delete avant de push
	ft_test_malloc();
	return (state);
}

void	ft_test_malloc(void)
{
	int i = 0;
	if (g_map_count[0] > 1)
	{
		printf("erreur : g_map_count[0] > 1\n");
		exit(0);
	}
	if (g_map_count[1] > 9)
	{
		printf("erreur : g_map_count[1] > 10\n");
		exit(0);
	}
	if (g_map_count[2] > 216)
	{
		printf("erreur : g_map_count[2] > 226\n");
		exit(0);
	}
	if (g_map_count[3] > 2268)
	{
		printf("erreur : g_map_count[3] > 2268\n");
		exit(0);
	}
	if (g_map_count[4] > 18396)
	{
		printf("erreur : g_map_count[4] > 18396\n");
		exit(0);
	}
	if (g_map_count[5] > 98280)
	{
		printf("erreur : g_map_count[5] > 98280\n");
		exit(0);
	}
	if (g_map_count[6] > 363888)
	{
		printf("erreur : g_map_count[6] > 363888\n");
		exit(0);
	}
	if (g_map_count[7] > 864612)
	{
		printf("erreur : g_map_count[7] > 864612\n");
		exit(0);
	}
	if (g_map_count[8] > 1224586)
	{
		printf("erreur : g_map_count[8] > 1224586\n");
		exit(0);
	}
	if (g_map_count[9] > 769394)
	{
		printf("erreur : g_map_count[9] > 769394\n");
		exit(0);
	}
	
}

/***
* g_map_table[0] : &g_state_table[0]
* g_map_table[1] : &g_state_table[1]
* g_map_table[2] : &g_state_table[10]
* g_map_table[3] : &g_state_table[226]
* g_map_table[4] : &g_state_table[2494]
* g_map_table[5] : &g_state_table[20890]
* g_map_table[6] : &g_state_table[119170]
* g_map_table[7] : &g_state_table[483058]
* g_map_table[8] : &g_state_table[1347670]
* g_map_table[9] : &g_state_table[2571256]
*/
void	init_malloc(void)
{
	int i = 0;
	
	g_map_table[0] = malloc(sizeof(t_state) * MAP_0);
	if (g_map_table[0] == 0)
	{
		printf("malloc g_map_table[0] failed\n");
		exit(0);
	}
	g_map_table[1] = malloc(sizeof(t_state) * MAP_1);
	if (g_map_table[1] == 0)
	{
		printf("malloc g_map_table[1] failed\n");
		exit(0);
	}
	g_map_table[2] = malloc(sizeof(t_state) * MAP_2);
	if (g_map_table[2] == 0)
	{
		printf("malloc g_map_table[2] failed\n");
		exit(0);
	}
	g_map_table[3] = malloc(sizeof(t_state) * MAP_3);
	if (g_map_table[3] == 0)
	{
		printf("malloc g_map_table[3] failed\n");
		exit(0);
	}
	g_map_table[4] = malloc(sizeof(t_state) * MAP_4);
	if (g_map_table[4] == 0)
	{
		printf("malloc g_map_table[4] failed\n");
		exit(0);
	}
	g_map_table[5] = malloc(sizeof(t_state) * MAP_5);
	if (g_map_table[5] == 0)
	{
		printf("malloc g_map_table[5] failed\n");
		exit(0);
	}
	g_map_table[6] = malloc(sizeof(t_state) * MAP_6);
	if (g_map_table[6] == 0)
	{
		printf("malloc g_map_table[6] failed\n");
		exit(0);
	}
	g_map_table[7] = malloc(sizeof(t_state) * MAP_7);
	if (g_map_table[7] == 0)
	{
		printf("malloc g_map_table[7] failed\n");
		exit(0);
	}
	g_map_table[8] = malloc(sizeof(t_state) * MAP_8);
	if (g_map_table[8] == 0)
	{
		printf("malloc g_map_table[8] failed\n");
		exit(0);
	}
	g_map_table[9] = malloc(sizeof(t_state) * MAP_9);
	if (g_map_table[9] == 0)
	{
		printf("malloc g_map_table[9] failed\n");
		exit(0);
	}
	//on affiche juste epour test
	memset(g_map_table[0], 0, sizeof(t_state) * MAP_0);
	memset(g_map_table[1], 0, sizeof(t_state) * MAP_1);
	memset(g_map_table[2], 0, sizeof(t_state) * MAP_2);
	memset(g_map_table[3], 0, sizeof(t_state) * MAP_3);
	memset(g_map_table[4], 0, sizeof(t_state) * MAP_4);
	memset(g_map_table[5], 0, sizeof(t_state) * MAP_5);
	memset(g_map_table[6], 0, sizeof(t_state) * MAP_6);
	memset(g_map_table[7], 0, sizeof(t_state) * MAP_7);
	memset(g_map_table[8], 0, sizeof(t_state) * MAP_8);
	memset(g_map_table[9], 0, sizeof(t_state) * MAP_9);
}
