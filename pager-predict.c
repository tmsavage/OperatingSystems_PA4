/*
 * File: pager-predict.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains a predictive pageit
 *      implmentation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) {

	/* This file contains the stub for a predictive pager */
	/* You may need to add/remove/modify any part of this file */

	/* Static vars */
	static int initialized = 0;
	static int tick = 1; // artificial time
	static int timestamps[MAXPROCESSES][MAXPROCPAGES];

	/* Local vars */
	int proctmp;
	int pagetmp;
	int oldpage;
	int pageOut;
	int pc;
	//int pcArr[MAXPROCESSES][MAXPROCPAGES];
	static int Arr[6][MAXPROCPAGES];
	static int counters[MAXPROCESSES];
	static int countFlags[MAXPROCESSES];
	static int programCounterArr[MAXPROCESSES][MAXPROCPAGES];


/*
	if (!initialized) {
		// Initialized pageArr here
		for (proctmp = 0; proctmp < 6; proctmp++) {
			for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++) {
				Arr[proctmp][pagetmp] = -1;
			}
		}

		// Program 1 Path 1 (1.1)
		Arr[0][0] = 0;
		Arr[0][1] = 1;
		Arr[0][2] = 2;
		Arr[0][3] = 3;
		Arr[0][4] = 10;
		Arr[0][5] = 11;
		Arr[0][6] = 4;
		Arr[0][7] = 5;
		Arr[0][8] = 6;
		Arr[0][9] = 7;
		Arr[0][10] = 8;
		Arr[0][11] = 9;

		// Program 2
		Arr[1][0] = 0;
		Arr[1][1] = 1;
		Arr[1][2] = 2;
		Arr[1][3] = 3;
		Arr[1][4] = 4;
		Arr[1][5] = 5;
		Arr[1][6] = 6;
		Arr[1][7] = 7;
		Arr[1][8] = 8;

		// Program 3
		Arr[2][0] = 0;
		Arr[2][1] = 1;
		Arr[2][2] = 2;
		Arr[2][3] = 3;
		Arr[2][4] = 4;
		Arr[2][5] = 5;
		Arr[2][6] = 6;
		Arr[2][7] = 7;
		Arr[2][8] = 8;
		Arr[2][9] = 9;
		Arr[2][10] = 10;
		Arr[2][11] = 11;
		Arr[2][12] = 12;
		Arr[2][13] = 13;

		// Program 4
		Arr[3][0] = 0;
		Arr[3][1] = 1;
		Arr[3][2] = 2;
		Arr[3][3] = 3;
		Arr[3][4] = 4;
		Arr[3][5] = 5;
		Arr[3][6] = 6;
		Arr[3][7] = 7;
		Arr[3][8] = 8;
		Arr[3][9] = 9;
		Arr[3][10] = 10;
		Arr[3][11] = 11;
		Arr[3][12] = 12;
		Arr[3][13] = 13;
		Arr[3][14] = 14;

		// Program 5
		Arr[4][0] = 0;
		Arr[4][1] = 1;
		Arr[4][2] = 2;
		Arr[4][3] = 3;

		// Program 1 Path 2 (1.2)
		Arr[5][0] = 0;
		Arr[5][1] = 1;
		Arr[5][2] = 2;
		Arr[5][3] = 3;
		Arr[5][4] = 4;
		Arr[5][5] = 5;
		Arr[5][6] = 6;
		Arr[5][7] = 7;
		Arr[5][8] = 8;
		Arr[5][9] = 9;
		Arr[5][10] = 10;
		Arr[5][11] = 11;




		*/
/* Init complex static vars here *//*

		for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
			counters[proctmp] = 0;
			countFlags[proctmp] = 0;
			for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++) {
				timestamps[proctmp][pagetmp] = 0;
				programCounterArr[proctmp][pagetmp] = -1;
			}
		}
		initialized = 1;
	}
*/

	/* TODO: Implement Predictive Paging */
	for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) { // every element in 'q' array
		/* Is process active? */
		pc = q[proctmp].pc;  // program counter for process

		// calculate what page it wants
		pagetmp = pc / PAGESIZE;  // page the program counter needs [generated single value from reference string

		int mightPageIn[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		mightPageIn[pagetmp] = 1;
		switch (pagetmp) {
			case 0:
				// direct
				mightPageIn[1] = 1;
				// neighbor of neighbor
				mightPageIn[2] = 1;
				break;
			case 1:
				// direct
				mightPageIn[2] = 1;
				// neighbor of neighbor
				mightPageIn[3] = 1;
				break;
			case 2:
				// direct
				mightPageIn[3] = 1;
				break;
			case 3:
				// direct
				mightPageIn[0] = 1;
				mightPageIn[4] = 1;
				mightPageIn[10] = 1;

				break;
			case 4:
				// direct
				mightPageIn[5] = 1;
				// neighbor of neighbor
				mightPageIn[6] = 1;
				break;
			case 5:
				// direct
				mightPageIn[6] = 1;
				// neighbor of neighbor
				mightPageIn[7] = 1;
				break;
			case 6:
				// direct
				mightPageIn[7] = 1;
				// neighbor of neighbor
				mightPageIn[8] = 1;
				break;
			case 7:
				// direct
				mightPageIn[8] = 1;
				// neighbor of neighbor
				mightPageIn[0] = 1;
				mightPageIn[9] = 1;
				break;
			case 8:
				// direct
				mightPageIn[0] = 1;

				mightPageIn[9] = 1;
				// neighbor of neighbor
				mightPageIn[10] = 1;
				break;
			case 9:
				// direct
				mightPageIn[10] = 1;
				// neighbor of neighbor
				mightPageIn[11] = 1;
				break;
			case 10:
				// direct
				mightPageIn[11] = 1;

				// neighbor of neighbor
				mightPageIn[0] = 1;
				mightPageIn[12] = 1;
				break;
			case 11:
				// direct
				mightPageIn[0] = 1;

				// neighbor of neighbor
				mightPageIn[12] = 1;
				break;
			case 12:
				// direct
				mightPageIn[13] = 1;

				// neighbor of neighbor
				mightPageIn[0] = 1;
				mightPageIn[9] = 1;
				mightPageIn[14] = 1;
				break;
			case 13:
				// direct
				mightPageIn[0] = 1;
				mightPageIn[14] = 1;
				mightPageIn[9] = 1;

				// neighbor of neighbor
				mightPageIn[10] = 1;

				// would page in 0 but we arleady did that
				break;
			case 14:
				// direct
				mightPageIn[0] = 1;

				// neighbor of neighbor
				mightPageIn[1] = 1;
				break;
		}

		for (int x = 0; x < 15; x++)
			if (mightPageIn[x] == 0)
				pageout(proctmp, x);

		for (int x = 0; x < 15; x++)
			if (mightPageIn[x] == 1)
				pagein(proctmp, x);

/*		if (q[proctmp].active) {
			*//* Dedicate all work to first active process*//*


			*//* Is page swaped-out? *//* // is it not paged in
			if (!q[proctmp].pages[pagetmp]) {
				// if at 0, page in [0, 3]
*//*
				if (pagetmp == 0) {
					for (int x = 0; x < 4; x++) {
						if (!q[proctmp].pages[x])
							!pagein(proctmp, x);
//								fprintf(stderr, "ass.\n");
					}
				}
*//*

				// reset if we're at the beginning again. Resets when pagetmp goes back to 0, "we've seen 4 unique pages minimum"
				if (countFlags[proctmp] == 0 && counters[proctmp] == 20) {
					countFlags[proctmp] = 1;
					printf("Process %d flagged, counter %d, tick %d\n", proctmp, counters[proctmp], tick);
*//*
					for (int x = 0; x < MAXPROCPAGES; x++)
						programCounterArr[proctmp][x] = -1;
					counters[proctmp] = 0; // array tells us when we restart
*//*
				}


				*//* if extraCounter - 1 PC is different than current pc at extraCounter*//*
				//check first page value, then check to make sure the next page value is different than the previous page value
				if (countFlags[proctmp] == 0 && (counters[proctmp] == 0 || programCounterArr[proctmp][counters[proctmp] - 1] != pagetmp)) {

					programCounterArr[proctmp][counters[proctmp]] = pagetmp;    // keeps track of program counter (page temp)

					//increment extraCounter when you see something new, WHEN YOU GET A NEW PROGRAM COUNTER
					counters[proctmp]++;
//					printf("ADDING NEW ELEMENT to programCounterArr: %d %d %d \n", pagetmp, proctmp, pc);
				}



				// CATEGORIZATION (figure out what programs are being used)


				//Program 1.1
*//*
				if (counters[proctmp] == 5 && pagetmp == 10) {
					//pageout pages 0 - 3?
//					printf("Process %d is program type 0.1\n", proctmp);
				}

				// Program 2
				if (counters[proctmp] == 9 && pagetmp == 8) {


//					printf("Process %d is program type 1 with tick %d \n", proctmp, tick);
//					printf("Process %d is program type 1 with tick %d \n", proctmp, tick);


				}


				// Program 3
				if (counters[proctmp] == 14 && pagetmp == 13) {
					//printf("Process %d is program type 2 \n", proctmp);

				}


				// Program 4
				if (counters[proctmp] == 15 && pagetmp == 14) {
					//printf("Process %d is program type 3 \n", proctmp);

				}


				// Program 5
				if (counters[proctmp] == 4 && pagetmp == 3) {
					//printf("Process %d is program type 4 \n", proctmp);

				}

				// Program 1.2
				if (counters[proctmp] == 12 && pagetmp == 9) {
					//printf("Process %d is program type 0.2 \n", proctmp);

				}
*//*




				*//* Try to swap in *//*
*//*
				if (!pagein(proctmp, pagetmp)) {

					int oldTime = tick;
					pageOut = 0;

					*//*
*//* If swapping fails, swap out another page *//**//*

					for (oldpage = 0; oldpage < q[proctmp].npages; oldpage++) {

						if (timestamps[proctmp][oldpage] < oldTime && pagetmp != oldpage && q[proctmp].pages[oldpage]) {

							oldTime = timestamps[proctmp][oldpage];
							pageOut = oldpage;
							//pcArr[proctmp][oldpage] = pc;

						}
					}

					pageout(proctmp, pageOut);
					pagein(pagetmp, pageOut);
					timestamps[proctmp][pagetmp] = tick;

					tick++;
				}
*//*
			}
		}*/
	}
}
