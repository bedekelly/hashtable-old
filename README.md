# Hashtable

This is a naive implementation of hashmaps in C, following only the algorithms provided on Wikipedia and other sites, and without recourse to previous implementations in C. The intent is to add to this implementation, optimizing it for speed and time complexity, and at some suitable point to run benchmark tests against various other implementations including Python dictionaries.

The inspiration for this project came about by watching this [Raymond Hettinger talk](https://youtu.be/p33CVV29OG8) on the design and improvement of Python's dictionaries to their current state in Python 3.6.

As of *4pm Sunday 2 April*, the algorithm uses separate chaining with linked lists. The hash function is overly simplistic, and the table does not resize. Therefore for large n the worst-case insertion time grows with O(n).


### Building

No libraries are required to build this project. It has been tested on the GCC compiler using MacOS Sierra 10.12, although other systems and compilers should also work.


* `make test` will build a test application in `build/test`
* `make debug` will build the same application in `build/debug`, with a visualisation of the hashmap
* `make clean` will remove any binaries, as well as any temporary Emacs files


A sample output from the binary produced by `make debug` is shown below:


```
Map (load factor = 0.38) {
    0 => []
    1 => [('1': 'value 1'), 
          ('1.3': 'value 1.3')]
    2 => [('2': 'value 2')]
    3 => []
    4 => []
    5 => []
    6 => []
    7 => []
}

All tests passed!
```
