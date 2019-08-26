#include "lib/boardutil.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "lib/boardutil.h"
#include "lib/contracts.h"
#include "lib/ht.h"
#include "lib/queues.h"
#include "lib/xalloc.h"

struct position {
    bitarray B;
    int i;
};

struct position* position_new() {
    return xcalloc(1,sizeof(struct position));
    
}

bool winning_position(bitarray B) {
    return (B==bitarray_new());
    
}

ht_key elem_key(ht_elem e) {
    return (ht_key)&(((struct position *)e)->B);
}

size_t key_hash(ht_key k) {
    bitarray *bp = (bitarray*)k;
    return (size_t)* bp;
    
}

void elem_free(ht_elem e) {
    free(e);
    return;
}

bool key_equal(ht_key k1, ht_key k2) {
    return *(bitarray*)k1 == *(bitarray*)k2;
}

/*This function checks whether a struct position*
 is an element of the hashtable*/
int elemof (ht H, struct position* p) {
    ht_key k = elem_key(p);
    if(ht_lookup(H, k) == NULL)
        return 0;
    else
        return 1;
    
}

/* This function first computes the position if the ith position is
 toggled. It will flip the position called the one above, below, left
 and right if possible and will return the changed bitarray.*/
bitarray compute_pos(bitarray B, uint8_t i, int width, int height) {
    B = bitarray_flip(B, i);
    if(i%width != 0) {
        B = bitarray_flip(B, i-1);
    }
    if(i%width != (width-1)) {
        B = bitarray_flip(B, i+1);
    }
    if(i/width != 0) {
        B = bitarray_flip(B, i-width);
    }
    if(i/width != (height -1)) {
        B = bitarray_flip(B, i+width);
    }
    return B;
}
/* This function will enqueue all the possible moves into the queue
 using the enqueue_moves function above. It will add it to the
 hashtable and if its already in the hashtable it won't enqueue
 as the same move shouldn't be checked twice. */
bool enqueue_moves(queue Q, ht seen, struct position** winning,
                   int width, int height) {
    
    for(;;) {
        if(queue_empty(Q)) {
            return false;
        }
        struct position* pos = deq(Q);
        
        for(int i = 0; i < width*height; i++) {
            bitarray next = compute_pos(pos->B, (uint8_t)(i), width, height);
            struct position* newpos= position_new();
            newpos->B = next;
            newpos->i = i;
            
            if(winning_position(next)) {
                *winning = newpos;
                return true;
            }
            if(elemof(seen, newpos) == 0) {
                enq(Q, newpos);
                ht_insert(seen, newpos);
            }
            else {
                free (newpos);
            }
        }
    }
}

/* This function will print the moves that led to the winning position
 once the board has been solved. It will also print the board. */
void print_winning_moves(struct position* winning, int width,
                         int height, ht H, struct position* b) {
    if (winning == b) {
        print_board(b->B, width, height);
        return;
    }
    else {
        uint8_t i = (winning->i);
        bitarray newba = compute_pos(winning->B, i, width, height );
        ht_elem checkingelem = ht_lookup(H, &newba);
        print_winning_moves(checkingelem,  width,  height,  H,  b);
        int row = i/width;
        int col = i%width;
        printf("%d:%d\n",row, col);
        print_board(winning->B, width, height);
    }
}

/* The hashtable, queue, and starting position will be initialized
 here and then the functions will be called. The variables will
 also be freed */
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: lightsout <board name>\n");
        return 1;
    }
    bitarray B;
    uint8_t width;
    uint8_t height;
    char *board_filename = argv[1];
    
    bool succ = file_read(board_filename, &B,&width, &height);
    if (succ) {
        if (winning_position(B)) {
            print_board(B, width, height);
            return 0;
        }
        struct position* b = position_new();
        b->i = -1;
        b->B = B;
        queue Q = queue_new();
        ht H =  ht_new(1000000,elem_key,key_equal,key_hash, elem_free);
        ht_insert(H, b);
        enq(Q, b);
        struct position* winning;
        bool found = enqueue_moves(Q, H, &winning, width, height);
        if(found) {
            print_winning_moves(winning,width, height, H, b);
            free(winning);
        }
        ht_free(H);
        queue_free(Q,NULL);
        if(found)
            return 0;
        return 1;
    }
    return 1;
}

