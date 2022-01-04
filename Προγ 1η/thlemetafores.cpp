#include <iostream>
using namespace std;

int c[1000001], E[1000001][3];
int heights[1000001], union_arr[1000001];

void swap(int a, int b)
{
    int t[3];
    t[0]=E[a][0];
    t[1]=E[a][1];
    t[2]=E[a][2];
    for (int j = 0; j<3; j++) {
      t[j] = E[a][j];
    }
    for (int j = 0; j<3; j++) {
      E[a][j] = E[b][j];
    }
    for (int j = 0; j<3; j++) {
      E[b][j] = t[j];
    }
}

int partition (int low, int high)
{
    int pivot = E[high][2];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (E[j][2] >= pivot)
        {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return (i + 1);
}

void quicksort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        quicksort(low, pi - 1);
        quicksort(pi + 1, high);
    }
}

int root (int i) {
    while(union_arr[i] != i) {
        union_arr[i] = union_arr[union_arr[i]] ;
        i = union_arr[i];
    }
    return i;
}

void weighted_union(int a,int b) {
    int root_A = root(a);
    int root_B = root(b);
    if (root_A == root_B)
      return;
    if(heights[root_A] < heights[root_B]) {
      union_arr[root_A] = union_arr[root_B];
      heights[root_B] += heights[root_A];
    }
    else  {
      union_arr[root_B] = union_arr[root_A];
      heights[root_A] += heights[root_B];
    }
}

bool find(int a,int b)
{
    if(root(a) == root(b))       //if A and B have same root,means they are connected.
    return true;
    else
    return false;
}
//int argc, char *argv[]
int main() {
    /*FILE *f;
    if ((f = fopen(argv[1], "rt")) == nullptr) {
      printf("Error opening file\n");
      return 1;
    }
    int N,M;
    fscanf(f, "%d %d", &N, &M);
    //int c[N+1], E[M+1][3];
    for (int i = 1; i<=N; i++) {
      fscanf(f, "%d", &c[i]);
    }
    for (int i = M; i>=1; i--) {
       fscanf(f, "%d %d %d", &E[i][0], &E[i][1], &E[i][2]);
    }
    */
    int N,M;
    cin >> N >> M;
    for (int i = 1; i<=N; i++) {
      cin >> c[i];
    }
    for (int i = M; i>=1; i--) {
      cin >> E[i][0] >> E[i][1] >> E[i][2];
    }

    for (int i=2; i<=M; i++) {
      if (E[i][2]>E[i-1][2]) {
          quicksort(1,M);
          break;
      }
    }

    //int heights[N+1], union_arr[N+1];
    int start = 1, end = M;
    int index = (end+start)/2;
    bool flag=true;
    //printf("Entered here #0\n");
    while (start<end) {
      index = (end+start)/2;

      if (flag) {
        for(int i = 1; i<=N; i++) {
          heights[i] = 1;
          union_arr[i] = i;
        }
        for (int i=1; i<=index; i++) {
          weighted_union(E[i][0],E[i][1]);
        }
      }
      else {
        for (int i=1; i<=index; i++) {
          weighted_union(E[i][0],E[i][1]);
        }
      }

      flag = true;
      for (int i = 1; i<=N; i++) {
        if (!find(i,c[i])) {
          flag = false;
          break;
        }
      }
      if (flag) {
        end = index;
      }
      else {
        start = index+1;
      }
    }

    cout << E[start][2] << endl;
    return 0;
}
