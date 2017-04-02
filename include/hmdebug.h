#pragma once
#include "hashmap.h"

////////////////////////////////////////////////////
// Print methods: to display a pretty Map format! //
////////////////////////////////////////////////////

void printValue(struct dataValue *value);

void printEntry(struct hashmapEntry *entry);

void printBucket(struct bucket bucket);

void printHashmap(struct hashmap *hashmap);
