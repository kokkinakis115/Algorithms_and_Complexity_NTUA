#include <iostream>
#include <tuple>
using namespace std;

void swap(int a, int b, int arr[][3])
{
    int t[3];
    t[0]=arr[a][0];
    t[1]=arr[a][1];
    t[2]=arr[a][2];
    for (int j = 0; j<3; j++) {
      t[j] = arr[a][j];
    }
    for (int j = 0; j<3; j++) {
      arr[a][j] = arr[b][j];
    }
    for (int j = 0; j<3; j++) {
      arr[b][j] = t[j];
    }
}

int partition (int arr[][3], int low, int high)
{
    int pivot = arr[high][2];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j][2] >= pivot)
        {
            i++;
            swap(i, j, arr);
        }
    }
    swap(i + 1, high, arr);
    return (i + 1);
}

void quicksort(int arr[][3], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int root (int Arr[] ,int i) {
    while(Arr[i] != i) {
        Arr[i] = Arr[Arr[i]] ;
        i = Arr[i];
    }
    return i;
}

void weighted_union(int Arr[],int size[],int a,int b) {
    int root_A = root(Arr, a);
    int root_B = root(Arr, b);
    if (root_A == root_B)
      return;
    if(size[root_A] < size[root_B]) {
      Arr[root_A] = Arr[root_B];
      size[root_B] += size[root_A];
    }
    else  {
      Arr[root_B] = Arr[root_A];
      size[root_A] += size[root_B];
    }
}

bool find(int Arr[],int a,int b)
{
    if(root(Arr, a) == root(Arr,b))       //if A and B have same root,means they are connected.
    return true;
    else
    return false;
}

int c[1000001], E[1000001][3];
int heights[1000001], union_arr[1000001];

int main(int argc, char *argv[]) {
    FILE *f;
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

    for (int i=2; i<=M; i++) {
      if (E[i][2]>E[i-1][2]) {
          quicksort(E,1,M);
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
          weighted_union(union_arr,heights,E[i][0],E[i][1]);
        }
      }
      else {
        for (int i=1; i<=index; i++) {
          weighted_union(union_arr,heights,E[i][0],E[i][1]);
        }
      }

      flag = true;
      for (int i = 1; i<=N; i++) {
        if (!find(union_arr,i,c[i])) {
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
