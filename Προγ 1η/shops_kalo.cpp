#include <iostream>
using namespace std;

int main() { //int argc, char *argv[]

  /*FILE *f;
  if ((f = fopen(argv[1], "rt")) == nullptr) {
    printf("Error opening file\n");
    return 1;
  }*/
  int N, K;
  //fscanf(f, "%d %d", &N, &K);
  cin >> N >> K;
  int *p = (int*)malloc(N*sizeof(int));
  //int p[N];
  for (int i=0; i<N; i++) {
    cin >> p[i];
    //fscanf(f, "%d", &p[i]);
  }

  int *best = (int*)malloc((K+1)*sizeof(int));
  for (int i=0; i<=K; i++) {
    best[i] = N+1;
  }

  int rsum, lsum;
  int min = N+1;
  for (int i=0; i<N; i++) {
    rsum = 0;
    for (int j=i; j<N; j++) {
      rsum += p[j];
      if (rsum > K)
        break;
      else if (rsum == K && j-i+1 < min)
        min = j-i+1;
      else if (rsum < K) {
        if ((j-i)+1+best[K-rsum] < min)
          min = (j-i)+1+best[K-rsum];
      }
    }
    lsum = 0;
    for (int j=i; j>=0; j--) {
      lsum += p[j];
      if (lsum > K)
        break;
      else if ((i-j)+1<best[lsum])
        best[lsum] = i-j+1;
    }
    /*for (int o=0; o<=K; o++) {
      cout << best[o] << " ";
    }
    cout << endl;
    cout << min << endl;*/
  }
  if (min == N+1)
    min = -1;

  cout << min << endl;
  return 0;
}
