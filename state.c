/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:34:21 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/08 17:12:15 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc.h"
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
	//ici on casse la meta est tu pret ?
	// convertir *state->id en base 7  => map7
	//verifier si lst_map[map7] existe 
	//					=>sinon la creer
	//					=>dans tout les cas mettre a jour la dept... 
	//					=> Pour le moment on garde la liste chaine pour avance plus vite dans la boucle
	int		map7 = convert_map7(id);
	if (lst_map[map7] == 0)
	{
		//creation d'un etat
		tmp = init_state(id, nb_dice);
		lst_map[map7] = tmp;

	}
	else
		tmp = lst_map[map7];
	actualise_depth(tmp);
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