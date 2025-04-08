
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:12:02 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/05 22:37:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"


/***
 * notre map est stockée sous forme octale
 * pour faire le hash on a besoin de le faire avec la base decimale donc
 */
void	add_hash(t_state *state)
{
	int i = 0;
	int n_final = state->depth[g_max_depth];
	unsigned int id_hash = decode_map(state->id);
	

	g_hash += n_final * id_hash;
}

/*
#include <xmmintrin.h>  // Pour les intrinsics SSE
void actualise_depth(t_state *next)
{
	int i = 0;

	// On suppose que g_max_depth est un multiple de 4
	for (; i < g_max_depth; i += 4)
	{
		// Charger 4 éléments de next->depth et g_cur_depth dans des registres SSE
		__m128i depth_data = _mm_loadu_si128((__m128i*)&next->depth[i]);
		__m128i cur_depth_data = _mm_loadu_si128((__m128i*)&g_cur_depth[i]);

		// Ajouter g_cur_depth[i] à next->depth[i + 1]
		__m128i updated_depth = _mm_add_epi32(depth_data, cur_depth_data);

		// Appliquer le masque MASKP30 sur chaque élément de next->depth
		__m128i mask = _mm_set1_epi32(MASKP30);  // Charger MASKP30 dans un registre
		__m128i masked_depth = _mm_and_si128(depth_data, mask);

		// Sauvegarder les résultats dans next->depth
		_mm_storeu_si128((__m128i*)&next->depth[i], masked_depth);
		_mm_storeu_si128((__m128i*)&next->depth[i + 1], updated_depth);
	}
}*/


void actualise_depth(t_state *next)
{
	int i = 0;

	while (i < g_max_depth)
	{
		next->depth[i + 1] += g_cur_depth[i];
		//next->depth[i + 1] &= MASKP30;
		i++;
	}
}

/***
 * Dans le cas ou une map est une deadend
 */
void	add_all_hash(int map)
{
	int				i = 0;
	unsigned int	n_final = 0;
	int				id_hash = decode_map(map);

	while (i < g_max_depth)
	{
		n_final += g_cur_depth[i];
		i++;
	}
	g_hash += (n_final * id_hash);
}
/***
 * Checjk si la map est encore dans la range
 */
int test_depth(t_state *current)
{
	unsigned int i = 0;
	while (i < g_max_depth)
	{
		if (current->depth[i] != 0)
			return (1);
		i++;
	}
	return (0);
}