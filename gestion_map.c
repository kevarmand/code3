/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:42:40 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/08 17:11:57 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/***un map va etre stocker sous sa forme octale
 * * 0 1 2 3 4 5 6 7 
 */
#include "inc.h"

 int				adj_lst[9][4];
 unsigned int	*g_cur_depth;
 unsigned int	g_max_depth;
 unsigned int	g_hash;
 int				g_cur_nb_dice;
 t_state			**lst_map;
 int				g_compteur = 0;
 t_state			*g_map_table[10];
 int				g_map_count[10];
 int				g_max_width_dept = 0;
 
 

 
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
