
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "kv_cache.h"


// Lookup the provided key in the KV cache 
// if not found fetch from storage by calling read_key
// if number of elements in bin is > max, replace lru KV pair, call write_key.
// if found, update lru order appropriately
// Input: the KV cache hash table and key to lookup
// Return: pointer to KVPAIR


KVPAIR *lookup(KVCACHE *kv_cache, long key, unsigned int bins) {
    
    int hitset = 0;
    int count = 0;
    
    unsigned int index = get_index(key, bins);

    // print_cache(kv_cache, bins);
    // printf("\n ________ \n\n");

    KVPAIR* head = kv_cache[index].list;
    KVPAIR* pair = head; 

    // print_cache(&(kv_cache[index]), bins);

    for (int i=0; i<MAX_BIN_ELEMENTS; i++) {
        if(pair == NULL) {
            break;
        }
        else {    
            if (pair->key == key) {
                hits++;
                hitset = 1;

                if(count != 0){ /* If key is the first element we don't need to change
                except incrementing hits */

                    if(pair->next != NULL) {
                        /*If we are not looking at the first element and
                        and we find the key we are looking for then
                        we move the current pair to the front */

                        pair->prev->next = pair->next; 
                        pair->next->prev = pair->prev; 

                        pair->next = head;
                        head->prev = pair;

                        pair->prev = NULL; 
                        
                        kv_cache[index].list = pair;
                        return pair;  
                    }
                    else{
                        /*Same as previous except this is if
                        pair->next is null so we don't need to
                        adjust its values */

                        pair->prev->next = pair->next; 
                        pair->next = head;
                        head->prev = pair;
                        pair->prev = NULL; 

                        kv_cache[index].list = pair;
                        return pair;  
                    }
                }
                break;
            }
            count++; 
            //count is the amount of KVPairs we have looked at
            //printlist(pair);
            if (count != MAX_BIN_ELEMENTS) {
                pair = pair->next;
            }
        }
    }
    


    if (hitset == 0) {
        if(count == 0){
            //If cache is empty we insert the value from storage
            head = read_key(key);
            kv_cache->num_keys++;
        }
        else if(count == MAX_BIN_ELEMENTS){
            /*If cache is full we remove the last value and then place the
            correct value in front. Every other element is pushed forward */
            
            pair->prev->next = NULL;
            head->prev = read_key(key);
            head->prev->next = head; 
            head = head->prev; 
            kv_cache->num_keys++;

            //num keys decreases because we have pushed off an element

            if(pair->modified == 1){
                //if the element is modified we have to perform a writeback
                write_key(pair); 
                writebacks++; 
            }
    
            free(pair->val);
            free(pair);
            kv_cache->num_keys--;
            //we free the memory of both the KVPair that we removed and the value
        }
        else{
            head->prev = read_key(key);
            head->prev->next = head; 
            head = head->prev; 
            kv_cache->num_keys++;
            
        }
        
        kv_cache[index].list = head; //put adjusted KVPairs in kv_cache

        misses++; // increment misses
        
    }
    return head;
}


unsigned int get_index(unsigned long key, unsigned int bins) {
    return key % bins;
}
