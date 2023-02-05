#include <vector>
#include <functional>
#include <queue>
#include <iostream>
#include <utility>
using namespace std;

const int MAX = 100050;
const int INF = 1e9;

void dijkstra(vector< vector< pair<int,int> > > &G, int vertexCount, int src, int dist[])
{
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  bool isvisited[MAX];

  for (int i = 0; i < vertexCount; i++) {
      dist[i] = INF;
      isvisited[i] = false;
  }

  dist[src] = 0;
  pq.push(make_pair(0, src));
  while (!pq.empty()){
      pair<int, int> tp = pq.top();
      pq.pop();
      int node = tp.second;
      int d = tp.first;
      if (!isvisited[node]) {
          isvisited[node] = true;
          for (int i = 0; i < G[node].size(); i++) {
              int v = G[node][i].first;
              int w = G[node][i].second;
              if (dist[v] > d + w) {
                  dist[v] = d + w;
                  pq.push(make_pair(dist[v], v));
              }
          }
      }
  }
}

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  int *d = new int[N];
  int *s = new int[Q];


  int min_d = 0;
  scanf("%d", &d[0]);

  min_d = d[0];

  for(int i = 1; i < N; ++i) {
    scanf("%d", &d[i]);
    if(d[i] < min_d) {
      min_d = d[i];
    }

  }
  for(int i = 0; i < Q; ++i) {
    scanf("%d", &s[i]);
  }

  vector<vector<pair<int, int>>> nodes;
  for(int i = 0; i < min_d; ++i) {
    vector<pair<int, int>> v;
    for(int j = 0; j < N; ++j) {
      if(d[j] == min_d) {
        continue;
      }
      v.push_back(make_pair((i + (d[j] % min_d)) % min_d, d[j]));
    }
    nodes.push_back(v);
  }

  int *dists = new int[min_d];
  dijkstra(nodes, min_d, 0, dists);

  for(int i = 0; i < Q; ++i) {
    if(dists[s[i] % min_d] <= s[i]) {
      printf("%s\n", "YES");
    }
    else {
      printf("%s\n", "NO");
    }
  }

  delete[] d;
  delete[] s;
  delete[] dists;
}
