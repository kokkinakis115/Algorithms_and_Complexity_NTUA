#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

int P[1500][2][9];
unsigned int dp_array[1500][5000][9];
unsigned int item_array[5000][9];
int flags1[1500][5000][9];
int flags2[5000][9];
int cntr[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

#define infinity UINT_MAX/3-1

unsigned int dp(int i, int n, int mt) { //the minimum cost of buying n items using the first i offers
                                        // for a specific item type and merchant (defined by mt)
  //cout << "Debugging dp " << i << " " << n << " " << mt << endl;

  if (n <= 0)
    return 0;
  else if (i == 0 && n <= P[i][0][mt])
    return P[i][1][mt];
  else if (i == 0)
    return infinity;
  if (flags1[i][n][mt] == 0) {
    dp_array[i][n][mt] = min(dp(i-1,n,mt), dp(i-1,n-P[i][0][mt],mt)+P[i][1][mt]);
    flags1[i][n][mt]++;
  }
  //cout << dp_array[i][n][mt] << endl;
  return dp_array[i][n][mt];
}

unsigned int item_cost(int mt, int n, int i, int N) { //minimum cost of buying n items from a specific merchant when he has a total
                                                      //of i offers and the max number of items we need is N
  //cout << "Debugging total " << n << " " << offers <<endl;
  if (n >= N)
    return dp(i, N, mt);
  else if (n <= 0)
    return 0;
  if (flags2[n][mt] == 0) {
    item_array[n][mt] = min(item_cost(mt, n+1, i, N), dp(i, n, mt));
    flags2[n][mt]++;
  }
  return item_array[n][mt];
};

unsigned int set_min_cost(int m,int n, int N) { //minimum cost to buy n sets of equipment (all 3 items) from merchant m (0-2)
    return item_cost(m*3+0, n, cntr[m*3+0], N) + item_cost(m*3+1, n, cntr[m*3+1], N) + item_cost(m*3+2, n, cntr[m*3+2], N);
}

int main() {
  int N, M, merchant , nr, price;
  char type;
  cin >> N >> M;

  for (int i = 0; i < M; i++) { //creation of 9 arrays that contain all offers about one product from one merchant
                                //cntr keeps kount of how many offers were given per item and merchant
    scanf("%d", &merchant);
    type = getchar();
    scanf("%d %d\n", &nr, &price);
    //cin >> merchant >> type >> nr >> price;
    if (merchant == 1) {
      if (type == 'A') {
        P[cntr[0]][0][0] = nr;
        P[cntr[0]++][1][0] = price;
      }
      else if (type == 'B') {
        P[cntr[1]][0][1] = nr;
        P[cntr[1]++][1][1] = price;
      }
      else if (type == 'C') {
        P[cntr[2]][0][2] = nr;
        P[cntr[2]++][1][2] = price;
      }
    }
    else if (merchant == 2) {
      if (type == 'A') {
        P[cntr[3]][0][3] = nr;
        P[cntr[3]++][1][3] = price;
      }
      else if (type == 'B') {
        P[cntr[4]][0][4] = nr;
        P[cntr[4]++][1][4] = price;
      }
      else if (type == 'C') {
        P[cntr[5]][0][5] = nr;
        P[cntr[5]++][1][5] = price;
      }
    }
    else if (merchant == 3) {
      if (type == 'A') {
        P[cntr[6]][0][6] = nr;
        P[cntr[6]++][1][6] = price;
      }
      else if (type == 'B') {
        P[cntr[7]][0][7] = nr;
        P[cntr[7]++][1][7] = price;
      }
      else if (type == 'C') {
        P[cntr[8]][0][8] = nr;
        P[cntr[8]++][1][8] = price;
      }
    }
  }

  //cout << "Debugging 1" << endl;

  for (int i = 0; i<M; i++) {
    for (int j = 0; j<N; j++) {
      if (j >= 5000)
        break;
      //flags2[j][k] = 0;
      for (int k = 0; k<9; k++) {
        flags1 [i][j][k] = 0;
        flags2 [j][k] = 0;
      }
    }
  }

  //cout << "Debugging 2" << endl;

  unsigned int min_cost = 3*infinity, cost1 ,cost2, cost3;
  for (int a = 0; a <= N; a++) {
    for (int b = 0; b <= N; b++) {
      cost1 = set_min_cost(0,a,N);
      if (cost1 >= infinity)
        continue;
      cost2 = set_min_cost(1,b,N);
      if (cost2 >= infinity)
        continue;
      cost3 = set_min_cost(2,N-a-b,N);
      if (cost3 >= infinity)
        continue;
      min_cost = min(min_cost, cost1+cost2+cost3);
    }
  }

  if (min_cost >= 3*infinity) {
    printf("-1\n");
    //cout << -1 << endl;
    return 0;
  }
  printf("%d\n", min_cost);
  //cout << min_cost << endl;
  return 0;
}
