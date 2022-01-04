#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;


int main() {
//-------------- Code to read input ---------------------
    static int N;
    static int K;


    string first_line;
    getline(cin, first_line);
    istringstream iss(first_line);
    iss >> N;
    iss >> K;
    int *population = (int*)malloc(N*sizeof(int));


    string sec_line;
    int num;
    getline(cin, sec_line);
    istringstream isb(sec_line);
    for (int i=0; i < N; i++) {
        isb >> num;
        population[i] = num;
    }
//-------------------------------------------------------
//  Create a hash table
//  Here we have the minimum subarray for every value of K
    unordered_map <int, int> h_table;
    for (int i=0; i < K; i++) {
        h_table.insert({i, 0});
    }

//  Loop starts here
    int p_sum, l_sum;
    int min = N + 1;                   // first value of min subarrays
    for (int i=0; i < N; i++) {
        p_sum = population[i];
        if (p_sum > K)
                continue;
        else if (p_sum == K) {
            if (1 < min)
                min = 1;
        }
        else {
            if ((1 + h_table[K-p_sum] < min) and h_table[K-p_sum] != 0)
                min = 1 + h_table[K-p_sum];
        }
        for (int j=i+1; j < N; j++) {
            p_sum += population[j];         //  sum of every RIGHT subarray
            if (p_sum > K)
                break;
            else if (p_sum == K) {
                if (j-i < min)
                    min = (j-i)+1;
            }
            else {
                if (((j-i) + h_table[K-p_sum] < min) and h_table[K-p_sum] != 0)
                    min = (j-i) + h_table[K-p_sum] + 1;
            }
        }
        l_sum = population[i];
        if (l_sum > K)                 // if the sum is > K, so the sum w/ next elem will be
            break;
        else {                         //   we care only for sums < K
            if (1 < h_table[l_sum] || h_table[l_sum] == 0)      // update only if subarray len < existed value
                h_table[l_sum] = 1;                             // or if existed value == 0, (1st time found sum)
            }
        if (i == 0)
            h_table[l_sum] = 1;
        for (int k=i-1; k >= 0; k--) {
            l_sum += population[k];        //   sum of every LEFT subarray
            if (l_sum > K)                 // if the sum is > K, so the sum w/ next elem will be
                break;
            else {                         //   we care only for sums < K
                if ((i-k) < h_table[l_sum] || h_table[l_sum] == 0)          // update only if subarray len < existed value
                    h_table[l_sum] = (i-k) + 1;                             // or if existed value == 0, (1st time found sum)
            }
        }
    }
    if (min == N + 1) {
        min = -1;
    }

    cout << min << endl;

    return 0;
}
