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

  #ifdef DEBUG
  printHashmap(hashmap);
  printf("\n");
  #endif

  // Don't buffer stdout, so we can "tee" our results.
  setbuf(stdout, NULL);
  
  for (int s=39; s<50; s++) {
    double startTime = getTime();
    for (int i=0; i<5000; i++)
      for (char c=64; c != 0; c++)
	for (int j=0; j<s; j++) {
	  char str[] = {j, '\0'};
	  char val[] = {j, 'v', '\0'};
	  hashmapInsert(hashmap, str, strdup(val), 1);
	}
    double endTime = getTime();
    printf("Stress test (%d) took %.0f seconds\n", s, endTime - startTime);
  }
  
  printf("All tests passed!\n");
}
