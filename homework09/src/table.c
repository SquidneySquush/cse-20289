/* table.c: Separate Chaining Hash Table */

#include "table.h"
#include "hash.h"
#include "macros.h"

/**
 * Create Table data structure.
 * @param   capacity        Number of buckets in the hash table.
 * @return  Allocated Table structure.
 */
Table *	    table_create(size_t capacity) {
    if (capacity == 0){
      capacity = DEFAULT_CAPACITY;
    }
    Table* t = (Table*)malloc(sizeof(Table));
    if(!t){
      free(t);
      return NULL;
    }
    t->capacity  = capacity;
    t->size = 0;

    t->buckets = calloc(capacity, sizeof(Pair) );
    if(!t->buckets){
      free(t->buckets);
      free(t);
      return NULL;
    }

    return t;
}

/**
 * Delete Table data structure.
 * @param   t               Table data structure.
 * @return  NULL.
 */
Table *	    table_delete(Table *t) {
      for (int i = 0; i < t->capacity; i++){
        if (t->buckets[i].next){
          pair_delete(t->buckets[i].next, true);
        }
      }

    free(t->buckets);
    free(t);

    return NULL;
}

/**
 * Insert or update Pair into Table data structure.
 * @param   m               Table data structure.
 * @param   key             Pair's key.
 * @param   value           Pair's value.
 * @param   type            Pair's value's type.
 */
void        table_insert(Table *t, const char *key, const Value value, Type type) {
  uint64_t hash = hash_from_data(key, strlen(key)) % t->capacity;

    Pair* pair = t->buckets[hash].next;
    if (pair == NULL){
      t->size += 1;
      t->buckets[hash].next = pair_create(key, value, NULL, type);
      return;
    }

    while(pair != NULL){
      if (streq(pair->key, key)) {
          pair_update(pair, value, type);
          return;
        }
      pair = pair->next;
    }

    t->size += 1;
    t->buckets[hash].next = pair_create(key, value, t->buckets[hash].next, type);
    return;
}


/**
 * Search Table data structure by key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to search for.
 * @return  Pointer to the Value associated with specified key (or NULL if not found).
 */
Value *     table_search(Table *t, const char *key) {
  int hash = hash_from_data(key, strlen(key)) % t->capacity;
  Pair* pair = t->buckets[hash].next;
  if(!pair){
    return NULL;
  }

  while(pair != NULL){
    if(pair->key == NULL && pair->next != NULL){
      pair = pair->next;
    }
    if(streq(pair->key, key)){
      return (&pair->value);
    }
    pair = pair->next;
  }
    return NULL;
}

/**
 * Remove Pair from Table data structure with specified key.
 * @param   t               Table data structure.
 * @param   key             Key of the Pair to remove.
 * return   Whether or not the removal was successful.
 */
bool        table_remove(Table *t, const char *key) {
    int hash = hash_from_data(key, strlen(key)) % t->capacity;

    Pair* pair = t->buckets[hash].next;
    if(!pair){
      return false;
    }
    Pair* prev = &t->buckets[hash];

    while(pair != NULL){
      if(streq(pair->key, key) ){
        prev->next = pair->next;
        pair_delete(pair, false);
        t->size = t->size - 1;
        return true;
      }

      prev = pair;
      pair = pair->next;
    }
    return false;
}

/**
 * Format all the entries in the Table data structure.
 * @param   m               Table data structure.
 * @param   stream          File stream to write to.
 */
void	    table_format(Table *t, FILE *stream) {
  for (int i = 0; i < t->capacity; i++){
    if (t->buckets[i].next){
      pair_format(t->buckets[i].next, stream);
    }
  }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
