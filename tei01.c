#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "MT.h"

#define rand_gen 1
#define rand_static false

static const uint32_t LOW_MAX = ((uint64_t)UINT32_MAX + 1) * 165 / 65536;
static const uint32_t HIGH_MAX = ((uint64_t)UINT32_MAX + 1) * 507 / 65536;
static uint32_t x = 123456789;
static uint32_t y = 362436069;
static uint32_t z = 521288629;
static uint32_t w = 88675123; 

uint32_t xor128(void) { 
  uint32_t t;

  t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)); 
}

int main(int argc, char *argv[]) {
  uint32_t i;
  uint32_t n = 100000000;

  uint32_t num_rnd = 0;
  uint32_t num_hit1 = 0;
  uint32_t num_hit2 = 0;
  uint32_t num_try = 0;

  //乱数閾値出力
  //printf("%010u\r\n", LOW_MAX);
  //printf("%010u\r\n", (uint32_t)((uint64_t)UINT32_MAX / 395.81387));

#if rand_static == true
  //メルセンヌツイスタ用乱数生成回路初期化2:固定seed
  init_genrand(123456789);
#else
  //メルセンヌツイスタ用乱数生成回路初期化1:不定seed
  init_genrand((unsigned)time(NULL));
  x = genrand_int32();
  y = genrand_int32();
  z = genrand_int32();
  w = genrand_int32();
#endif

  for(i=0;i<n;i++){

    //乱数取得
    switch (rand_gen) {
      case 0:
        num_rnd = xor128();
        break;
      case 1:
        num_rnd = genrand_int32();
        break;
    }

    //試行回数
    num_try++;

    //低確時の大当り回数
    if (num_rnd <= LOW_MAX && num_rnd != 0) {
      num_hit1++;
    }
    //高確時の大当り回数
    if (num_rnd <= HIGH_MAX && num_rnd != 0) {
      num_hit2++;
    }

    if (num_try % 1000000 == 0) {
      printf("%010u %010u 1/%.5f %.10f 1/%.5f %.10f\r\n",
          num_try, num_rnd,
          (double)num_try/num_hit1, (double)num_hit1/num_try,
          (double)num_try/num_hit2, (double)num_hit2/num_try);
    }
  }
  return 0;
}
