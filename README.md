You job is to implement the core part of a key value software cache.
You need to use a hash table with bounded chain depth (4 for this project).

kv_cache.h contains many definitions including the KVPAIR and KVCACHE (the hash table) structures
and MAX_BIN_ELEMENTS (chain depth).

You are to write the code for the lookup function in kv_cache.c  All your 
modifications are to be in that file alone.
You need to track hits, misses, and writebacks (KV pairs that are modified and
need to be written back to storage when replaced from the cache).

Lookup will call read_key if a key is not currently in the cache.
Lookup will call write_key if a key being replaced has been modified.
read_key and write_key are provided for you, see kv_cache.h for function prototypes.

You should increment hits for every key found in the cache, increment misses
for every key not found in the cache, and increment writebacks for every modified
key replaced from the cache.

There are eight different tests provided, numbered 1 through 8, and have increasing
complexity.  test number 0 will run all the tests. Run the tests individually via the command line for debugging and to
check valgrind output.

make will build the program kv_cache_test which includes your code from kv_cache.c
along with test harness code that is not visible to you.

Run the program on the command line with
```
./kv_cache_test -b <bins> -n <keypairs> -t <test>
```
Note that tests 1-5 ignore the keypair parameter

```
python3 hwtest.py ALL
```
---
#### Submission

***IMPORTANT:*** Run `make` before uploading your files to Gitlab

- Submit your project on gradescope using the gitlab submission process.

- ***Team specific instructions*** 
  - Teams should only do one submission via group submission.
  - Teams must also edit the file called reflection.txt and include a detailed description of each team members contributions to the project.

