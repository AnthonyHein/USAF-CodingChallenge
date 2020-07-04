/*******************************************************************************
*   Author: Anthony Hein        Date: 7/3/2020
*
*   Description: Finds the number of ways to sum to TARGET, which is the length
*   between two gears, using only the gears whose lengths are enumerated in the
*   the array gears. Uses a dynamic programming approach.
*
*   THIS PROGRAM SOLVES THE BONUS VERSION OF THE CHALLENGE.
*
*   With the given parameters for the coding challenge, this number is found to
*   be 1867354001 with an average compute time of 0.000004 seconds running on
*   MacBook Pro 2018 w/ 2.2 GHz Intel Core i7.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TARGET 100
#define LENGTH 6
#define TRIALS 1000


char *fmtString = "Ordered ways to sum to %d w/ available gears s.t. move in the same direction is: %d\n";

/* A combo can either render the gears to move in the same direction or opposite
 * direction. Keep track of how many combos of each for every length of gears. A
 * combo that goes the same way has an odd number of gears, but a combo that goes
 * the opposite way has an even number of gears. */
struct combo {
    int directionSame;
    int directionOpp;
};

typedef struct combo * T_combo;

/* Finds the number of combinations of gears to add to target.
 * ORDER DOES MATTER HERE
 * @param gears - the lengths of the available gears.
 * @param length - the number of available gears.
 * @param target - the number to sum to
 */
int numCombos(int * gears, int length, int target) {
    /* Array for each number from [0, TARGET] inclusive. */
    T_combo combos = (T_combo) malloc(sizeof(struct combo) * (target + 1));

    /* Loop variables. (Assuming ANSI-C 89). */
    int i = 0, j = 0;

    /* Initialize to zero bc doesn't happen automatically in C. */
    for (i = 0; i < target + 1; i++) {
        combos[i].directionOpp = 0;
        combos[i].directionSame = 0;
    }

    /* If the red and blue gear were 0m apart, they would move opp direction. */
    combos[0].directionOpp = 1;

    /* The number of ways to sum to any number N is the number of ways to sum up
     * to n < N plus the number of ways to sum up to r < N where r + n = N. */
    for (i = 0; i < target + 1; i++) {
        for (j = 0; j < length; j++) {
            /* Only can sum if i ge gears[j] since no negatives in gears */
            if (i >= gears[j])
            {
                /* Adding one gear to combo in opp direction makes it same
                 * and vice versa. */
                combos[i].directionOpp += combos[i - gears[j]].directionSame;
                combos[i].directionSame += combos[i - gears[j]].directionOpp;
            }
        }
    }

    /* We want the gears moving in the same direction. */
    return combos[target].directionSame;

}

int main () {

    /* Available gear lengths. */
    int gears[] = {1, 2, 3, 5, 7, 8};

    /* Clock stuff */
    int i = 0;
    clock_t start, end;
    double cpu_time_used, cpu_time_used_avg;

    printf(fmtString, TARGET, numCombos(gears, LENGTH, TARGET));
    /* OUTPUT: 1867354001 */

    /* Perform runtime analysis. */
    start = clock();
    for (i = 0; i < TRIALS; i++) {
        numCombos(gears, LENGTH, TARGET);
    }
    end = clock();

    cpu_time_used = ((double) end - start) / (CLOCKS_PER_SEC);
    cpu_time_used_avg = ((double) end - start) / (CLOCKS_PER_SEC * TRIALS);

    printf("CPU time used for %d function calls: %f\n", TRIALS, cpu_time_used);
    printf("Average CPU time used for %d function calls: %f\n", TRIALS, cpu_time_used_avg);

    return 0;
}
