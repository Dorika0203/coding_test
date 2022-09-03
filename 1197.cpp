// 최소 스패닝 트리, MST

/*
union-by-rank 알고리즘을 이용해 cycle 존재 검증
union-by-rank 알고리즘에 사용하는 tree_arr은 실제로 트리를 생성하지만, 이 트리는 MST와는 다른 모양임
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

typedef tuple<int, int, int> edge_t;

static bool compare_edge_t(edge_t i, edge_t j) {
    return get<2>(i) < get<2>(j);
}

int find_root(vector<int> tree_arr, int t) {
    if(t == tree_arr[t]) return t;
    else return find_root(tree_arr, tree_arr[t]);
}

int main()
{
    int V, E;
    cin >> V >> E;
    vector<int> tree_arr;
    vector<int> rank_arr;
    vector<edge_t> edge_arr;

    for(int i=0; i<V+1; i++)
    {
        tree_arr.push_back(i);
        rank_arr.push_back(1);
    }

    for(int i=0; i<E; i++)
    {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        edge_arr.push_back(make_tuple(v1, v2, w));
    }

    sort(edge_arr.begin(), edge_arr.end(), compare_edge_t);

    int weight = 0;
    int counter = 0;
    for(auto iter=edge_arr.begin(); iter != edge_arr.end(); iter++)
    {
        if (counter == V-1) break;
        int p1 = get<0>(*iter);
        int p2 = get<1>(*iter);
        int w = get<2>(*iter);

        int r1 = find_root(tree_arr, p1);
        int r2 = find_root(tree_arr, p2);

        if(r1 != r2)
        {
            if(rank_arr[r2] > rank_arr[r1])
                tree_arr[r1] = r2;
            else
                tree_arr[r2] = r1;
            weight += w;
            counter += 1;
            if(rank_arr[r2] == rank_arr[r1]) rank_arr[r1] += 1;
        }
    }
    
    cout << weight << endl;
}