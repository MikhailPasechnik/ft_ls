#include "libft.h"

void	        ft_htdel(t_htable **ht) {
    t_htentry  *tmp;
    size_t      i;

    if (ht)
    {
        i = 0;
        while (i < (*ht)->size)
        {
            while ((*ht)->bins[i]) {

                tmp = (*ht)->bins[i]->next;
                if ((*ht)->key_del)
                    (*ht)->key_del((*ht)->bins[i]->key);
                if ((*ht)->val_del)
                    (*ht)->val_del((*ht)->bins[i]->value);
                ft_memdel((void **)&(*ht)->bins[i]);
                (*ht)->bins[i++] = tmp;
            }
            ft_memdel((void **)&(*ht)->bins);
        }
        ft_memdel((void **)ht);
        *ht = NULL;
    }
}
