#include <iostream>
using namespace std;

int p[20000];
int best[1000001][3];

int main(int argc, char *argv[]) {
  FILE *f;
  if ((f = fopen(argv[1], "rt")) == nullptr) {
    printf("Error opening file\n");
    return 1;
  }
  int N, K;
  fscanf(f, "%d %d", &N, &K);
  //int p[N];
  for (int i=0; i<N; i++) {
    fscanf(f, "%d", &p[i]);
  }

  int sum;
  for (int i=0; i<=K; i++) {
    best[i][0]=N+1;
  }

  for (int i=0; i<N; i++) {
    sum = 0;
    for (int j=i; j<N; j++) {
      sum += p[j];
      if (sum <= K) {
        if (j-i+1<best[sum][0]) {
          best[sum][0]=j-i+1;
          best[sum][1]=j;
          best[sum][2]=i;
        }
      }
      else
        break;
    }
  }
  int min=best[K][0]; //, tl1=-1, pl1=-1, tl2=-1, pl2=-1;
  for (int i=1; i<K; i++) {
    if (best[i][0] == N+1 || best[K-i][0] == N+1) {
      continue;
    }
    if (best[i][0] + best[K-i][0] < min && (best[i][1]<best[K-i][2] || best[i][2]>best[K-i][1])) {
      min = best[i][0] + best[K-i][0];
      /*tl1 = best[i][1];
      pl1 = best[i][2];
      tl2 = best[K-i][1];
      pl2 = best[K-i][2];*/
    }
    else if (best[i][0] + best[K-i][0] >= min) {
      continue;
    }
    else {
    //  tl1 = best[i][1];
    //  pl1 = best[i][2];
      int summ = 0, prwto = 0, teleftaio = 0;
      for (int j=0; j<best[i][2]; j++) {
        summ += p[j];
        teleftaio = j;
        while (summ > K-i) {
          summ -= p[prwto++];
        }
        if (summ == K-i && ((teleftaio-prwto) + best[i][0] < min)) {
          min = (teleftaio-prwto+1)+best[i][0];
      //    tl2 = teleftaio;
      //    pl2 = prwto;
        }
      }
      summ = 0, prwto = best[i][1]+1;
      for (int j=best[i][1]+1; j<N; j++) {
        summ += p[j];
        teleftaio = j;
        while (summ > K-i) {
          summ -= p[prwto++];
        }
        if (summ == K-i && ((teleftaio-prwto) + best[i][0] < min)) {
          min = (teleftaio-prwto+1)+best[i][0];
      //    tl2 = teleftaio;
      //    pl2 = prwto;
        }
      }
    }
  }
  if (min == N+1) {
    cout << -1 << endl;
  }
  else {
    cout << min << endl;
    //cout << pl1 << " " << tl1 << "  " << pl2 << " " << tl2 << endl;
  }
}
