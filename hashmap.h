#pragma once

#include "assert.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"


/**
 * Simple wrapper for indirect reference to any amount of data.
 */
struct dataValue {
  void *start;
  long size;
};

void deleteValue(struct dataValue **dv);


/**
 * A hashmap entry doubles as a linked list. It contains the exact
 * key and value stored in the map.
 */
struct hashmapEntry {
  struct hashmapEntry *next;

  long hash;
  char *key;
  struct dataValue *value;
};

void deleteEntry(struct hashmapEntry **entry);


/**
 * A bucket is just a wrapper for the linked list of hashmap entries.
 */
struct bucket {
  struct hashmapEntry *firstEntry;
};


/**
 * A hashmap is a list of buckets, and also contains information about
 * its load (i.e. the ratio of items stored to buckets).
 */
struct hashmap {
  int numBuckets;
  struct bucket *buckets;
  float loadFactor;
};


/**
 * A naive hash of a key just returns its address in memory.
 */
long hash(char *key);



/**
 * Create a hashmap, given a starting number of buckets.
 */
struct hashmap *makeHashmap(int startSize);


/**
 * Create a "data value" from a pointer to the data and its size.
 */
struct dataValue *makeValue(void *data, long size);


/**
 * Create a hashmap entry, given its key and value (data and size).
 */
struct hashmapEntry *makeEntry(char *key, void *data, long size);


/**
 * Insert into a bucket at a given key the provided data.
 * Returns true if we've created a new entry, false otherwise.
 */
bool bucketInsert(struct bucket *bucket, char *key, void *data, long size);


/**
 * Retrieve from a bucket using a given key.
 */
struct dataValue *bucketGet(struct bucket *bucket, char *key);


/**
 * Delete from a bucket using a given key.
 */
void bucketDelete(struct bucket *bucket, char *key);


/**
 * Insert a key-value pair into a hashmap. The value in this case
 * is a pointer to some data and the size in bytes of that data.
 */
void hashmapInsert(struct hashmap *map, char *key, void *data, long size);


/**
 * Retrieve a value from the hashmap.
 */
struct dataValue *hashmapGet(struct hashmap *map, char *key);


/**
 * Deletes a value with the given key from the hashmap.
 */
void hashmapDelete(struct hashmap *map, char *key);

/**
 * Utility function to free all the memory used by a hashmap entry.
 */
void deleteEntry(struct hashmapEntry **entry);


/**
 * Utility function to free all the memory used by a dataValue.
 */
void deleteValue(struct dataValue **dv);




