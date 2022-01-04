#include <iostream>
#include <stack>
using namespace std;

int p[20000];
int best[1000001][3];
int test[10] {0};

int main(int argc, char *argv[]) {
  cout << test[5] << endl;
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
  stack<int> stoiva;
  int sum;
  for (int i=0; i<=K; i++) {
    best[i][0] = 20001;
  }

  for (int i=0; i<N; i++) {
    sum = 0;
    for (int j=i; j<N; j++) {
      sum += p[j];
      if (sum <= K) {
        if (best[sum][0] == 20001) {
          //cout << "Pushed " << sum << endl;
          stoiva.push(sum);
        }
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

  /*for (int i=0; i<=K; i++) {
    cout << best[i][0] << endl;
  }*/

  int min=best[K][0], current;
  while (!stoiva.empty()) {
    current = stoiva.top();
    if (best[K-current][0] == 20001) {
      stoiva.pop();
      continue;
    }
    if (best[current][0] + best[K-current][0] < min && (best[current][1]<best[K-current][2] || best[current][2]>best[K-current][1])) {
      min = best[current][0] + best[K-current][0];
    }
    else if (best[current][0] + best[K-current][0] >= min) {
      stoiva.pop();
      continue;
    }
    else {
      int summ = 0, prwto = 0, teleftaio = 0;
      for (int j=0; j<best[current][2]; j++) {
        summ += p[j];
        teleftaio = j;
        while (summ > K-current) {
          summ -= p[prwto++];
        }
        if (summ == K-current && ((teleftaio-prwto) + best[current][0] < min)) {
          min = (teleftaio-prwto+1)+best[current][0];
        }
      }
      summ = 0, prwto = best[current][1]+1;
      for (int j=best[current][1]+1; j<N; j++) {
        summ += p[j];
        teleftaio = j;
        while (summ > K-current) {
          summ -= p[prwto++];
        }
        if (summ == K-current && ((teleftaio-prwto) + best[current][0] < min)) {
          min = (teleftaio-prwto+1)+best[current][0];
        }
      }
    }
    stoiva.pop();
    //cout << "entered2" << endl;
  }
  if (min == N+1) {
    cout << -1 << endl;
  }
  else {
    cout << min << endl;
  }
}
