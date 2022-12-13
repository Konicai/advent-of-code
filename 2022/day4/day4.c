//
// Created by Konicai on 13/12/2022.
//

#include <stdio.h>
#include "day4.h"

#define MAX_LINE_LENGTH

void run4(FILE *input) {

    int full_overlap_count = 0; // part 1
    int partial_overlap_count = 0; // part 2

    // starts and ends of sections 'a' and 'b'
    int ai, af, bi, bf;
    while (fscanf(input, "%i-%i,%i-%i ", &ai, &af, &bi, &bf) == 4) {

        if (ai == bi || af == bf) {
            // One of the sections always consumes the other
            full_overlap_count++;
            partial_overlap_count++;
        } else if (ai < bi) {
            if (af >= bf) {
                // a consumes b
                full_overlap_count++;
                partial_overlap_count++;
            } else if (af >= bi) {
                // partial overlap distance is af - bi
                partial_overlap_count++;
            }
        } else {
            // ai > bi

            if (bf >= af) {
                // b consumes a
                full_overlap_count++;
                partial_overlap_count++;
            } else if (bf >= ai) {
                // partial overlap distance is bf - ai
                partial_overlap_count++;
            }
        }
    }

    printf("Full range overlap count: %i\n", full_overlap_count);
    printf("Partial range overlap count: %i\n", partial_overlap_count);
}
