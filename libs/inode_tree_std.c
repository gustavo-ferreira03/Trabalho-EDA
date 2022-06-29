/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inode_tree_std.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoutinh <felipe_coutinho@id.uff.br>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:49:10 by fcoutinh          #+#    #+#             */
/*   Updated: 2022/06/29 17:38:25 by fcoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inode_tree.h" 

t_itree	*ibt_new(int t)
{
	int		i;
	t_itree	*new_node;

	new_node = (t_itree *) malloc(sizeof(t_itree));
	if (!new_node)
		return (NULL);
	new_node->leaf = 1;
	new_node->n_db = 0;
	new_node->blocks = (t_db **) malloc(sizeof(t_db *) * ((t * 2) - 1));
	new_node->c = (t_itree **) malloc(sizeof(t_itree *) * t * 2);
	i = 0;
	while (i < (t * 2))
	{
		new_node->c[i] = NULL;
		i++;
	}
	return (new_node);
}

t_itree	*ibt_clear(t_itree *target)
{
	int	i;

	if (target)
	{
		if (!target->leaf)
		{
			i = 0;
			while (i < target->n_db)
			{
				ibt_clear(target->c[i]);
				i++;
			}
		}
		free(target->blocks); // mem leak: implement function to free each block
		free(target->c);
		free(target);
	}
	return (NULL);
}

t_itree	*ibt_search(t_itree *T, int db_id)
{
	int	i;

	i = 0;
	if (!T)
		return (NULL);
	while (i < T->n_db && db_id > (T->blocks[i])->id)
		i++;
	if (i < T->n_db && db_id == (T->blocks[i])->id)
		return (T);
	if (T->leaf)
		return (NULL);
	return (ibt_search(T->c[i], db_id));
}

static void	print_aux(t_itree *a, int level)
{
	int	i;
	int	j;

	if (a)
	{
		i = 0;
		while (i <= (a->n_db - 1))
		{
			print_aux(a->c[i], level + 1);
			j = 0;
			while (j <= level)
			{
				printf("\t");
				j++;
			}
			printf("%d | %s\n", (a->blocks[i])->id, *(a->blocks[i])->content);
			i++;
		}
		print_aux(a->c[i], level + 1);
	}
}

void	ibt_print(t_itree *T)
{
	print_aux(T, 0);
}

// t_itree	*ibt_remove(t_itree *T, t_db datablock, int t);
