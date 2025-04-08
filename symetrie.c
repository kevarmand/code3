/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symetrie.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kearmand <kearmand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:10:42 by kearmand          #+#    #+#             */
/*   Updated: 2025/04/08 17:08:11 by kearmand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc2.h"

//connent transformer une map en une autre
// 123456789 +> 321654987
//seltioner une colone 100100100 et echange avec colone 001001001
// ((map & 0700700700)>>6) + ((map & 0070070070) << 6) + (map & 0070070070)

//123456789 +> 789456123
//On selection les ligne
//((map & 0777000000) >> 18) + ((map & 0000000777) << 18) + (map & 0000777000)

// 123456789 +> 987654321 idee passer de  2 a 4 pas essayer de 1 a 4
//						  autre idee faire un un reverse bit

// 123456789 +> 147258369 si tu as une idee de genie je tecoute

// une fois quon a notre table de symetrie 
//2) selectionner le min (ce sera lidentifiant)
//3) faire la recherche avec cet identifiant 
//ensuite il va falloir savoir comment on est arriver la Cad => la correspondance dans le tableaude symetrie

//passer de 0   => 1
//passer de 2   => 3       +> symetrie verticale
//passer de 4   => 5
//passer de 6   => 7

//passer de 0	=> 2
//passer de 1	=> 3      +> symetrie horizontale
//passer de 4	=> 6
//passer de 5	=> 7


//passer de 0	=> 4
//passer de 1	=> 5      +> symetrie diagonale
//passer de 2	=> 6
//passer de 3	=> 7

// si on note D V H les 3symetrie nimporte quel symetrie peut etre decompose en une combinaison de symetrie
//