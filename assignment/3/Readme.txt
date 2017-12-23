1)Run ./thread
2)n threads are created for n readers and one thread for writer
3)two semaphores arrays are used
4) first semaphore for writer access.. only one writer can access at a time
5)writes the buffer with rand() function
6)read count of that block is initialized to 0 after writer writes..
7)a count of write position is noted.. where the writer writes
8)in reader read count at that block is incremented.
9)if read count==1 write access is locked..
10)when read count==n write access is unlocked..
11)read lock semaphore is used here for shared variable read count here..
12)writes waits till all readers read at that location ...
