# C Hashmap

This is a naive implementation of hashmaps in C, following only the algorithms provided on Wikipedia and other sites, and without recourse to previous implementations in C. The intent is to add to this implementation, optimizing it for speed and time complexity, and at some suitable point to run benchmark tests against various other implementations including Python dictionaries.

The inspiration for this project came about by watching this [Raymond Hettinger talk](https://youtu.be/p33CVV29OG8) on the design and improvement of Python's dictionaries to their current state in Python 3.6.

As of *4pm Sunday 2 April*, the algorithm uses separate chaining with linked lists. The hash function is overly simplistic, and the table does not resize. Therefore for large n the worst-case insertion time grows with O(n).

