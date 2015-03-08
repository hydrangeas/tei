#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "MT.h"

//低確率
static const uint32_t LOW_MAX = ((uint64_t)UINT32_MAX + 1) * 165 / 65536;
//高確率
static const uint32_t HIGH_MAX = ((uint64_t)UINT32_MAX + 1) * 507 / 65536;
//特定図柄突入確率
static const uint32_t ZGR_MAX = ((uint64_t)UINT32_MAX + 1) * 54 / 100;

//状態
#define MODE_NORMAL	0	//低確率・非時短
#define MODE_ST			1	//高確率・時短
#define MODE_JITAN	2	//低確率・時短
#define MODE_LAST		3	//低確率・非時短(時短後4回転)

static int status1 = MODE_NORMAL;
static int status2 = 0;

static uint32_t game_total = 0;
static uint32_t game_hit = 0;
static uint32_t game_continue = 0;

//ゲーム数
#define GAME_MAX		10000000

//大当り判定
bool rand1(void) {
	uint32_t rnd = genrand_int32();
	uint32_t brd = LOW_MAX;

	if (status1 == MODE_ST) {
		brd = HIGH_MAX;
	}

#ifdef DEBUG
	fprintf(stdout, "rnd:%010u brd:%010u\r\n", rnd, brd);
#endif
	if (rnd <= brd && rnd != 0) {
		return true;
	}
	return false;
}
//図柄判定
bool rand2(void) {
	uint32_t rnd = genrand_int32();
	uint32_t brd = ZGR_MAX;

	if (rnd <= brd && rnd != 0) {
		return true;
	}
	return false;
}

void output(int zgr) {
#ifndef CONTINUE
	fprintf(stdout, "%010u %010u %02d %d %d\r\n",
			game_total, game_hit, game_continue, status1, zgr
			);
#endif
	game_hit = 0;
}

int main(int argc, char *argv[]) {

	//メルセンヌツイスタ初期化
  init_genrand((unsigned)time(NULL));

	int jitan = 0;
	int last = 0;

	for (int i = 0; i < GAME_MAX; i++) {

		game_total++;
		game_hit++;

		switch (status1) {
			case MODE_NORMAL:
				if (rand1()) {
					game_continue++;
					if (rand2()) {
						output(1);
						jitan = 190;
						status1 = MODE_ST;
					} else {
						output(0);
						jitan = 100;
						status1 = MODE_JITAN;
					}
				}
				break;
			case MODE_ST:
			case MODE_JITAN:
				if (rand1()) {
					game_continue++;
					output(1);
					jitan = 190;
					status1 = MODE_ST;
				} else {
					jitan--;
					if (jitan <= 0) {
						last = 4;
						status1 = MODE_LAST;
#ifdef CONTINUE
						fprintf(stdout, "%02d\r\n", game_continue);
#endif
					}
				}
				break;
			case MODE_LAST:
				game_continue = 0;
				if (rand1()) {
					game_continue++;
					output(1);
					jitan = 190;
					status1 = MODE_ST;
				} else {
					last--;
					if (last <= 0) {
						status1 = MODE_NORMAL;
					}
				}
		}
	}

	return 0;
}

