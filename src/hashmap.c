#include "assert.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

#include "hashmap.h"


/**
 * A naive hash of a key just returns its address in memory.
 */
long hash(char *key) {
  return (long) key[0];
}


/**
 * Create a hashmap, given a starting number of buckets.
 */
struct hashmap *makeHashmap(int startSize) {
  struct hashmap *hashmap = malloc(sizeof(struct hashmap));
  hashmap->numBuckets = startSize;
  hashmap->buckets = calloc(startSize, sizeof(struct bucket));
  hashmap->loadFactor = 0.0f;
  return hashmap;
}


/**
 * Create a "data value" from a pointer to the data and its size.
 */
struct dataValue *makeValue(void *data, long size) {
  struct dataValue *value = malloc(sizeof(struct dataValue));
  value->start = data;
  value->size = size;
  return value;
}


/**
 * Create a hashmap entry, given its key and value (data and size).
 */
struct hashmapEntry *makeEntry(char *key, void *data, long size) {
  struct hashmapEntry *entry = malloc(sizeof(struct hashmapEntry));
  entry->key = strdup(key);
  entry->value = makeValue(data, size);
  entry->hash = hash(entry->key);
  entry->next = NULL;
  return entry;
}


/**
 * Insert into a bucket at a given key the provided data.
 * Returns true if we've created a new entry, false otherwise.
 */
bool bucketInsert(struct bucket *bucket, char *key, void *data, long size) {
  struct hashmapEntry *thisEntry = makeEntry(key, data, size);

  if (!bucket->firstEntry) {
    bucket->firstEntry = thisEntry;
    return true;
  }

  struct hashmapEntry *entry;
  struct hashmapEntry *lastEntry;
  
  for (entry = bucket->firstEntry; entry; entry = entry->next) {
    if (!strcmp(entry->key, key)) {
      deleteValue(&entry->value);
      entry->value = makeValue(data, size);
      return false;
    }
    lastEntry = entry ? entry : lastEntry;
  }
  lastEntry->next = thisEntry;
  return true;
}


/**
 * Retrieve from a bucket using a given key.
 */
struct dataValue *bucketGet(struct bucket *bucket, char *key) {
  struct hashmapEntry *entry = bucket->firstEntry;
  while (entry) {
    if (!strcmp(key, entry->key))
      return entry->value;
    entry = entry->next;
  }
  return NULL;
}


/**
 * Delete from a bucket using a given key.
 */
void bucketDelete(struct bucket *bucket, char *key) {
  struct hashmapEntry *entry, *prev;

  if (!bucket->firstEntry) return;
  if (!bucket->firstEntry->next || !strcmp(bucket->firstEntry->key, key)) {
    entry = bucket->firstEntry;
    bucket->firstEntry = bucket->firstEntry->next;
    deleteEntry(&entry);
    return;
  }

  prev = bucket->firstEntry;
  for (entry = bucket->firstEntry->next; entry; entry = entry->next) {
    if (!strcmp(entry->key, key)) {
      prev->next = entry->next;
      deleteEntry(&entry);
      return;
    }
    prev = entry;
  }
}


void resizeUp(struct hashmap *map) {
  // Todo: implement resizeUp!
}


void resizeDown(struct hashmap *map) {
  // Todo: implement resizeDown!
}


/**
 * Insert a key-value pair into a hashmap. The value in this case
 * is a pointer to some data and the size in bytes of that data.
 */
void hashmapInsert(struct hashmap *map, char *key, void *data, long size) {
  long index = hash(key) % map->numBuckets;
  struct bucket *bucket = &(map->buckets[index]);
  if(bucketInsert(bucket, key, data, size))
    map->loadFactor += 1.0f / map->numBuckets;

  if (map->loadFactor >= 0.75f)
    resizeUp(map);
}


/**
 * Retrieve a value from the hashmap.
 */
struct dataValue *hashmapGet(struct hashmap *map, char *key) {
  int index = hash(key) % map->numBuckets;
  return bucketGet(&map->buckets[index], key);
}


/**
 * Deletes a value with the given key from the hashmap.
 */
void hashmapDelete(struct hashmap *map, char *key) {
  int index = hash(key) % map->numBuckets;
  bucketDelete(&map->buckets[index], key);
  map->loadFactor -= 1.0f/map->numBuckets;

  if (map->loadFactor <= 0.25f)
    resizeDown(map);
}


/**
 * Utility function to free all the memory used by a hashmap entry.
 */
void deleteEntry(struct hashmapEntry **entry) {
  free((*entry)->key);
  deleteValue(&(*entry)->value);
  free(*entry);
  *entry = 0;
}


void deleteValue(struct dataValue **dv) {
  free(*dv);
  *dv = 0;
}
