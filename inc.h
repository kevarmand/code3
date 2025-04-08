/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:27:19 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/08 17:13:45 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC optimize "Ofast,unroll-loops,omit-frame-pointer,inline"
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")
//ifndef POPCNT
#pragma GCC target("movbe,aes,pclmul,avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2,rdrnd,popcnt,bmi,bmi2,lzcnt")
//#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <immintrin.h>  // Pour les intrinsics AVX2


typedef struct s_state
{
	int 			id;
	unsigned int	depth[71];
}	t_state;


void bfs(int map);


void	aff_lst(t_state *state);
void	affich_tab_map(void);

/***
 * Functions to manage the state
 */
void 	*init_state(int id, int nb_dice);
void	add_state_list(int nb_dice, int id);

/***
 * Functions de hash
 */
void	add_hash(t_state *state);
void	add_all_hash(int map);
void	actualise_depth(t_state *next);
int test_depth(t_state *current);


/***
 * try_take
 */
int try_take2(int map, int *tab, int cur_case);
int try_take3(int map, int *tab, int cur_case);
int try_take4(int map, int *tab, int cur_case);

/****
 * fonction de gestion de la map
 */
void	print_map(int map);
int		decode_map(int map);
int		encode_map(int map);
int		gen_filter(int indice);
void	gen_adj_list(void);
void	apply_adj_lst(int map, int *tableau, int indice);
int		sum_map(int map);
void	gen_next_map(int map);
int		count_zero(int map);


/***
 * fonction de gestion de la memoire
 * memory pool
 * 
 */
void	*ft_malloc(int nb_dice);
void	ft_test_malloc(void);
void	init_malloc(void);


//define les variables globales
extern int 	adj_lst[9][4];
extern int		*g_cur_depth;
extern int		g_max_depth;
extern int		g_hash;
extern int		g_cur_nb_dice;

extern t_state	*g_map_table[9];
extern t_state	*g_map_count[9];

extern t_state	**lst_map;

#define MASKP30 1073741823
 
#define MAP_0 1
#define MAP_1 9
#define MAP_2 216
#define MAP_3 2208
#define MAP_4 16332
#define MAP_5 71216
#define MAP_6 158096
#define MAP_7 151092
#define MAP_8 55054
#define MAP_9 1