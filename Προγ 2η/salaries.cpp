#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int CeilIndexInc(vector<int>& IncTails, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (IncTails[m] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}

int CeilIndexDec(vector<int>& DecTails, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (DecTails[m] <= key)
            r = m;
        else
            l = m;
    }

    return r;
}

void LongestIncreasingSubsequenceLength(int salaries[], vector<pair<int,int>>& IncPair, vector<int>& IncTails, int size) {

    int idx;
    int Tail_max = salaries[0];
    int length = 1; // always points empty slot in tail
    IncPair.push_back(make_pair(length,salaries[0]));
    IncTails.push_back(salaries[0]);

    for (int i = 1; i < size; i++) {

      if (salaries[i] < IncTails[0]) {
        IncTails[0] = salaries[i];
        IncPair.push_back(make_pair(length, Tail_max));
      }

      else if (salaries[i] > IncTails[length - 1]) {
        length++;
        IncTails.push_back(salaries[i]);
        Tail_max = salaries[i];
        IncPair.push_back(make_pair(length,Tail_max));
      }
      else {
        idx = CeilIndexInc(IncTails, -1, length-1, salaries[i]);
        if(idx == length - 1)
          Tail_max = salaries[i];
        IncPair.push_back(make_pair(length,Tail_max));
        IncTails[idx] = salaries[i];
      }

    }

    return;
}

void LongestDecreasingSubsequenceLength(int salaries[], vector<pair<int,int>>& DecPair, vector<int>& DecTails, int size) {\

    int idx;
    int Tail_min = salaries[size-1];
    int length = 1;
    DecPair.push_back(make_pair(length, salaries[size-1]));
    DecTails.push_back(salaries[size-1]);

    for (int i = size-2; i >= 0; i--) {

      // new smallest value
      if (salaries[i] > DecTails[0]) {
        DecTails[0] = salaries[i];
        DecPair.push_back(make_pair(0, Tail_min));
      }

      else if (salaries[i] < DecTails[length - 1]) {
        length++;
        DecTails.push_back(salaries[i]);
        Tail_min = salaries[i];
        DecPair.push_back(make_pair(length,Tail_min));
      }

      else {
        idx = CeilIndexDec(DecTails, -1, length-1, salaries[i]);
        if(idx == length - 1)
          Tail_min = salaries[i];
        DecPair.push_back(make_pair(length,Tail_min));
        DecTails[idx] = salaries[i];
      }
    }

    return;
}

int tamper(vector<pair<int,int>>& IncPair, vector<pair<int,int>>& DecPair, int N, int K) {
  int maxl = 0;

  for (int i = 0; i < N-1; i++) {
    if(IncPair[i].second < DecPair[N-2-i].second + K) {
      maxl = max(maxl, IncPair[i].first + DecPair[N-2-i].first);
    }
  }
  return maxl;
}

int main()
{

    int N, K;
    scanf("%d %d", &N, &K);
    //cin >> N >> K;
    int *salaries = (int*)malloc(N*sizeof(int));
    for (int i = 0; i < N; i++) {
      //cin >> salaries[i];
      scanf("%d", &salaries[i]);
    }

    vector<int> IncTails, DecTails;
    vector< pair <int,int> > IncPair, DecPair;
    //cout << "Debugging 1\n";
    LongestDecreasingSubsequenceLength(salaries, DecPair, DecTails, N);
    LongestIncreasingSubsequenceLength(salaries, IncPair, IncTails, N);

    printf("%d\n", max(IncPair[N-1].first, tamper(IncPair, DecPair, N, K)));
    //cout << max(IncPair[N-1].first, tamper(IncPair, DecPair, N, K)) << endl;
    return 0;
}
