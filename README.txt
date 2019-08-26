Programming 8 (Lights Out)

Files you won't modify:
   lib/contracts.h     - Contracts for C
   lib/xalloc.{c,h}    - NULL-checking allocation
   lib/boardutil.{c,h} - Useful Lights-Out relevant functions
   lib/ht.{c,h}        - Hash tables
   lib/stacks.{c,h}    - Stacks
   lib/queues.{c,h}    - Queues
   lib/bitarray.h      - Interface to bit arrays
   Makefile            - Utility for building this project

Files that don't exist yet:
   bitarray.c          - Bit array implementation
   bitarray-test.c     - Your unit tests for bit arrays (Optional)
   lightsout.c         - Lights out implementation (needs a main() function)

==========================================================

Compiling your bitarray unit tests
   % make bitarray-test
   % ./bitarray-test

Compiling and running your lights out solver (with -DDEBUG)
   % make
   % ./lightsout-d board/board0.txt

Compiling and running your lights out solver (without -DDEBUG)
   % make
   % ./lightsout board/board0.txt 

==========================================================

Submitting with Andrew handin script:
   % handin hw8 lightsout.c bitarray.c

Creating a tarball to submit with Autolab web interface:
   % tar -czvf hw8sol.tgz lightsout.c bitarray.c

On autolab: https://autolab.cs.cmu.edu/15122-f13/lightsout
