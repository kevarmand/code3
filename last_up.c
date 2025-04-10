/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:49:45 by marvin            #+#    #+#             */
/*   Updated: 2025/04/10 18:53:08 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:27:19 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/05 22:47:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#undef _GLIBCXX_DEBUG
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
	unsigned int	depth[8][71];
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
void	actualise_depth(t_state *next, int i_transform);


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

void	*ft_malloc(int nb_dice);
void	ft_test_malloc(void);
void	init_malloc(void);

/***
 * Fonction de gestion de la symetrie
 */
int	gen_hash_min(int map, int *tab);



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gestion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:42:40 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/05 22:33:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/***un map va etre stocker sous sa forme octale
 * * 0 1 2 3 4 5 6 7 
 */

int				adj_lst[9][4];
unsigned int	**g_cur_depth;
unsigned int	g_max_depth;
unsigned int	g_hash;
int				g_cur_nb_dice;
t_state			**lst_map;
int				g_compteur = 0;
t_state			*g_map_table[10];
int				g_map_count[10];
int				g_max_width_dept = 0;

int g_transform[64] =
{
    0, 1, 2, 3, 4, 5, 6, 7,
    1, 0, 3, 2, 6, 7, 4, 5,
    2, 3, 0, 1, 5, 4, 7, 6,
    3, 2, 1, 0, 7, 6, 5, 4,
    4, 5, 6, 7, 0, 1, 2, 3,
    5, 4, 7, 6, 2, 3, 0, 1,
    6, 7, 4, 5, 1, 0, 3, 2,
    7, 6, 5, 4, 3, 2, 1, 0
};

#define LUT(i_transform, j) (g_transform[((j) << 3) + (i_transform)])


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

int main()
{
    int depth;
    int map0 = 0;
    int value = 0;
    scanf("%u", &depth);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            value = 0;
            scanf("%d", &value);
            map0 = (map0 << 3);
            map0 += value;
        }
    }
	init_malloc();
	lst_map = (t_state **)calloc(269000000, sizeof(t_state *));
	if (lst_map == 0)
		printf("domage");
	
	g_hash = 0;
    g_max_depth = depth;
	//printf("map0 : %o\n", map0);
	//printf("g_max_depth : %d\n", g_max_depth);
	//bsf(map0);
	gen_adj_list();
	bfs(map0);
	printf("%d\n", g_hash & MASKP30);
	printf("%d\n", g_max_width_dept);
	//afficher la map_map_count
	/*
	for (int i = 0; i < 10; i++)
	{
		if (g_map_max_cout[i] > 0)
			printf("g_map_max_cout[%d] : %d\n", i, g_map_max_cout[i]);
	}
	*/
	//printf("compteur : %d\n", g_compteur);	
	
}

/***
 * en entree on a un map en octal
 * en sortie on a un map en decimal
 */
int	decode_map(int map)
{
	int i = 0;
	int res = 0;
	int pow = 1;
	
	while (i < 9)
	{
		res += ((map >> (i * 3)) & 7) * pow;
		pow *= 10;
		i++;
	}
	return (res);
}

int	encode_map(int map)
{
	int i = 0;
	int res = 0;
	
	while (i < 9)
	{
		res += ((map % 10) & 7) << (i * 3);
		map /= 10;
		i++;
	}
	return (res);
}


//rechercher les 0

//recreer une map

//utilise un filtre

//initialise l usine a filtre :

/***
 * 
 *     0  1  2
 *     3  4  5
 *     6  7  8
 * 
 * 
 * on va creer un tableau des list disponible adjacente possible
 *  * on va formater un peu le resultat differement
 *  
 *       case 0
 * 	case 1 x case 2
 * 	     case 3
 * 
 * si n = 0 les case 1 et 3  +> -1 -1 1 3
 * si n = 1	les case 0 2 4   +> -1 0 2  4 
 * si n = 2	les case 1 5     +> -1 1 -1 5
 * si n = 3	les case 0 4 6   +> 0  -1 4 6
 * si n = 4	les case 1 3 5 7 +>  1 3 5 7
 * si n = 5	les case 2 4 8   +> 2 4 -1 8
 * si n = 6	les case 3 7     +> 3 -1 7 -1
 * si n = 7	les case 4 6 8   +> 4 6 8 -1
 * si n = 8	les case 5 7     +> 5 7 -1 -1
 * 

 */
void	gen_adj_list(void)
{
	for (int i = 0; i < 9; i++)
	{
		adj_lst[i][0] = -1;
		adj_lst[i][1] = -1;
		adj_lst[i][2] = -1;
		adj_lst[i][3] = -1;
	}
	adj_lst[0][2] = 1;
	adj_lst[0][3] = 3;
	adj_lst[1][1] = 0;
	adj_lst[1][2] = 2;
	adj_lst[1][3] = 4;
	adj_lst[2][1] = 1;
	adj_lst[2][3] = 5;
	adj_lst[3][0] = 0;
	adj_lst[3][2] = 4;
	adj_lst[3][3] = 6;
	adj_lst[4][0] = 1;
	adj_lst[4][1] = 3;
	adj_lst[4][2] = 5;
	adj_lst[4][3] = 7;
	adj_lst[5][0] = 2;
	adj_lst[5][1] = 4;
	adj_lst[5][3] = 8;
	adj_lst[6][0] = 3;
	adj_lst[6][2] = 7;
	adj_lst[7][0] = 4;
	adj_lst[7][1] = 6;
	adj_lst[7][3] = 8;
	adj_lst[8][0] = 5;
	adj_lst[8][1] = 7;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 4; j++)
			adj_lst[i][j] = gen_filter(adj_lst[i][j]);
	}
}

/***
 * On veux change la gestion de adj_lst
 * a la place davoir des valeur on veux des filtre en octal
 */
int	gen_filter(int indice)
{
	if (indice < 0 || indice > 8)
		return (0);
	return (7 << (indice * 3));
}

/***
 * @brief applique adj_lst sur une map
 * @param map : map a modifier
 * @param tableau : tableau de 4 case (list des case adjacente)
 * @param indice : indice de la case a modifier
 * 
 * nom de la fonction 
 */
void	apply_adj_lst(int map, int *tableau, int indice)
{
	for (int i = 0; i < 4; i++)
	{
		tableau[i] = adj_lst[indice][i] & map;
	}
}

int sum_map(int map)
{
	int i = 0;
	int res = 0;
	while (i < 9)
	{
		res += (map >> (i * 3)) & 7;
		i++;
	}
	return (res);
}

void place_1(int map, int indice)
{
	int mask = 1 << (indice * 3);
	int new_map = map + mask;

	if (g_cur_nb_dice == 8)
	{
		//on calcul le hash de la map
		// et on ajoute le la some des depth
		add_all_hash(new_map);
	}
	else
		add_state_list(g_cur_nb_dice + 1, new_map);
}

/***
 * chercher les 0 d une map
 * il sagit d un test donc on va jsut afficher les indice
 */
/***

 */
void gen_next_map(int map)
{
	int i = 0;
	int mask = 7;
	int tab[4];
	int nb;
	int err = 0;
	while (i < 9)
	{
		if ((map & mask) == 0)
		{
			apply_adj_lst(map, tab, i);
			nb = (tab[0] != 0) + (tab[1] != 0) + (tab[2] != 0) + (tab[3] != 0);
			err = 0;
			if (nb > 3)
				err += try_take4(map, tab, i);
			if (nb > 2)
				err += try_take3(map, tab, i);
			if (nb > 1)	
				err += try_take2(map, tab, i);
			if (err == 0)
				place_1(map, i);
		}
		i++;
		mask = mask << 3;
	}
}

int count_zero(int map)
{
	int i = 0;
	int mask = 7;
	int nb = 0;
	while (i < 9)
	{
		if ((map & mask) == 0)
			nb++;
		i++;
		mask = mask << 3;
	}
	return (nb);
}

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

void bfs(int map)
{
	int depth;

	// creation d un premier etat
	t_state *current_state = 0;
	
	//mettre current_state dans la table (bon inidice)

	memset(g_map_count, 0, sizeof(g_map_count));
	if (map == 0)
	{
		//faire la premiere generation
		current_state = init_state(0, 0);
		current_state->depth[0][0] = 1;
		g_cur_depth = current_state->depth;
		g_cur_nb_dice = 0;
		gen_next_map (current_state->id);
	}
	else
		current_state = init_state(map, 9 - count_zero(map));
	current_state->depth[0][0] = 1;
	t_state *tmp;
	//faire un truc pour le premier niveau;
	
	//affich_tab_map();
	
	depth = 0;
	//printf("map : %o\n", map);
	//printf("depth : %d\n", depth);
	//printf("depth max : %d\n", g_max_depth);
	while (depth <= g_max_depth+2)
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
				//printf("current_state : %o\n", current_state->id);
				//printf("current_state : %o\n", current_state->id);
				//printf("map : %o\n", current_state->id);
				//generer les maps du current_state _. les add directmeent dedans ca evite detransfere/recalculer les donnee
				//test pour la profondeur si que des 0 on genere rien 
				//si on a une fin de course c est a dire depth = data->depth on ajoute le hash
				add_hash(current_state); //On enleve jsute ceux qui ateigne la depth. hash += curent_state->depth[depth] 
				//on met a jours les variable globales
				g_cur_depth = current_state->depth;
				g_cur_nb_dice = i;
				if (test_depth (current_state))
					gen_next_map (current_state->id);
				//free current_state au fur et a mesure
			}
			g_map_count[i] = 0;
		}
		depth++;
	}
}

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


/***
 * notre map est stockée sous forme octale
 * pour faire le hash on a besoin de le faire avec la base decimale donc
 */


void	add_hash(t_state *state)
{
	int i = 0;
	unsigned int tab[8];
	
	gen_hash_min(state->id, tab);
	for (int j = 0; j < 8; j++)
	{
		tab[j] = decode_map(tab[j]);
		g_hash += (tab[j] * state->depth[j][g_max_depth]);
	}
}

void actualise_depth(t_state *next, int i_transform)
{
    int i = 0;

	int tab[8];

    while (i < g_max_depth)
    {
		for (int j = 0; j < 8; j++)
		{
			next->depth[LUT(i_transform, j)][i + 1] += g_cur_depth[j][i];
			//next->depth[i + 1] &= MASKP30;
		}
        i++;
    }
}

/***
 * Dans le cas ou une map est une deadend
 */
void	add_all_hash(int map)
{
	int				i = 0;
	unsigned int		n_final[8] = {0};
	unsigned int		tab[8];

	gen_hash_min(map, tab);
	//on decode les 8map
	for (int i = 0; i < 8; i++)
		tab[i] = decode_map(tab[i]);
	for (int i = 0; i < g_max_depth; i++)
	{
		for (int j = 0; j < 8; j++)
			n_final[j] += g_cur_depth[j][i];
	}
	for (int i = 0; i < 8; i++)
	{
		g_hash += (tab[i] * n_final[i]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 11:47:16 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/05 19:02:32 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symetrie.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:10:42 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/10 15:01:26 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline int sym_hor(int map)
{
	return ((map & 0777000000) >> 18) + ((map & 0000000777) << 18) + (map & 0000777000);
}

static inline int sym_ver(int map)
{
	return ((map & 0700700700) >> 6) + ((map & 0007007007) << 6) + (map & 0070070070);
}

static inline int sym_diag(int map)
{
	return (((map & 0070007000) >> 6)		//2,6  => 4,8
		 + ((map & 0007000000) >> 12)		//3=>7
		 + (map & 0700070007) 				//1,5,9 id
		 + ((map & 0000700070) << 6)		//4,8 => 2,6
		 + ((map & 0000000700) << 12));		//7=>3
}

int	gen_hash_min(int map, int *tab)
{
	tab[0] = map;
	tab[1] = sym_hor(map);
	tab[2] = sym_ver(map);
	tab[3] = sym_hor(tab[2]);
	tab[4] = sym_diag(map);
	tab[5] = sym_hor(tab[4]);
	tab[6] = sym_ver(tab[4]);
	tab[7] = sym_hor(tab[6]);
	
	int min = map;
	int i_min = 0;
	for (int i = 0; i < 8; i++)
	{
		if (tab[i] < min)
		{
			min = tab[i];
			i_min = i;
		}
	}	
	//retourner le min et l'indice ( sans doute un pointeur donner en parametre)
	return (i_min);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:34:21 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/05 19:36:27 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/***
 * converti la map ( en base 8 ) vert la base 7
 */
 int convert_map7(int map)
 {
	 int		i;
	 int		res;
	 int		base;
 
	 i = 0;
	 res = 0;
	 base = 1;
	 while (map > 0)
	 {
		 res += (map % 8) * base;
		 map /= 8;
		 base *= 7;
	 }
	 return (res);
 }
 
 
 /***
  * Parcours la liste :
  * si la map est trouver on incrémente le depth
  * sinon on l'ajoute à la liste (creation + init + ajout)
  * @param depth : correspond à la profondeur a laquelle est ateint pour cette map
  */
 void	add_state_list(int nb_dice, int id)
 {
	 t_state	*tmp;

	 //On cherche le hah min de la map ainsi que la transformation necessaire
	 

	 
	 //on recup les symetrique de la map
	int	tab[8];
	int i = gen_hash_min(id, tab);

	id = tab[i];
	int		map7 = convert_map7(id);  // a discuter
	if (lst_map[map7] == 0)
	{
		
		tmp = init_state(id, nb_dice);
		lst_map[map7] = tmp;
	}
	else
		tmp = lst_map[map7];
	actualise_depth(tmp, i);
 }


void print_state(t_state *state)
{
	int i = 0;
	printf("(id : %o [", state->id);
	while (i <= g_max_depth)
	{
		printf("%d ", state->depth[i]);
		i++;
	}
	printf("]");
}


/***
 * afficher la liste des map
 */
void aff_lst(t_state *state)
{
	t_state	*tmp;

	tmp = state;
	if (!tmp)
	{
		printf("NULL");
		return ;
	}
	while (tmp)
	{
		printf("  ");
		print_state(tmp);
	}
}

/***
 * affiche le contenu de la variable g_map_table
 */
void affich_tab_map(void)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("g_map_table[%d][%d] : ", i, j);
			aff_lst(g_map_table[j]);
			printf("\n");
		}
	}
}

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
	int index = g_map_count[nb_dice];
	state = &((g_map_table[nb_dice])[index]);
	g_map_count[nb_dice]++;

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
