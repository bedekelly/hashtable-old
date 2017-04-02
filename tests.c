#include "hashmap.h"
#include "hmdebug.h"


int main(int argc, char* argv[]) {
  struct hashmap *hashmap = makeHashmap(8);

  hashmapInsert(hashmap, "1", "value 1.old", 11);
  hashmapInsert(hashmap, "2", "value 2", 7);
  hashmapInsert(hashmap, "1", "value 1", 7);
  hashmapInsert(hashmap, "1.2", "value 1.2", 9);
  hashmapInsert(hashmap, "1.3", "value 1.3", 9);
  hashmapDelete(hashmap, "1.2");

  assert(hashmapGet(hashmap, "1.2") == NULL);
  assert(strcmp(hashmapGet(hashmap, "1")->start, "value 1") == 0);
  assert(strcmp(hashmapGet(hashmap, "1.3")->start, "value 1.3") == 0);
  
  printf("All tests passed!\n");
}
