#include "hmdebug.h"

////////////////////////////////////////////////////
// Print methods: to display a pretty Map format! //
////////////////////////////////////////////////////

void printValue(struct dataValue *value) {
  printf("'%s'", value->start);
}


void printEntry(struct hashmapEntry *entry) {
  printf("('%s': ", entry->key);
  printValue(entry->value);
  printf(")");
}

void printBucket(struct bucket bucket) {
  printf("[");
  struct hashmapEntry *e = bucket.firstEntry;
  while (e) {
    printEntry(e);
    if (e->next) printf(", \n          ");
    e = e->next;
  }
  printf("]");
}

void printHashmap(struct hashmap *hashmap) {
  printf("\nMap (load factor = %.2f) {\n", hashmap->loadFactor);
  for (int i=0; i<hashmap->numBuckets; i++) {
    printf("    %d => ", i);
    printBucket(hashmap->buckets[i]);
    printf("\n");
  }
  printf("}\n");
}
