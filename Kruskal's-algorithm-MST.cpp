#include<iostream>
#include<vector>;
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

//for chechking two components are belongs to same set or not
class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);

        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};

int spanningTree(int V, vector<vector<int>> matrix)
    {
        // 1 - 2 wt = 5
        /// 1 - > (2, 5)
        // 2 -> (1, 5)

        // 5, 1, 2
        // 5, 2, 1
        vector<pair<int, pair<int, int>>> edges;

        for (int i = 0; i < V; i++) {
            for (int j = 0; j<V;j++){
            	if(matrix[i][j] != 0){
            		int adjNode = j;
	                int wt = matrix[i][j];
	                int node = i;

	                edges.push_back({wt, {node, adjNode}});
				}
            }
        }
        DisjointSet ds(V);
        sort(edges.begin(), edges.end());
        int mstWt = 0;
        for (auto it : edges) {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;

            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWt += wt;
                ds.unionByRank(u, v);
                cout << u << "-->" << v << endl;
            }
        }

        return mstWt;
    }

int main(){
	ifstream text_file("asn.txt");

	if(!text_file){
		cout << "File not created";
	}
	else{
 	vector<vector<int>> matrix(8, vector<int>(8, 0));;
 	string row_data, word;
 	int i = 0;
 	while(getline(text_file, row_data)){
 			stringstream str(row_data);
			int j = 0;
            while(getline(str,word,' ')){
                stringstream s(word);
                int n;
                s>>n;
                matrix[i][j] = n;
                j++;
            }
            i++;
		}
    for(int i=0;i<matrix.size();i++){
		for(int j = 0;j<matrix[0].size();j++){
			cout << matrix[i][j] << " ";
		}
	cout << endl;
    }
    cout << "Minimum Spnning Tree : " << endl;

    int ans = spanningTree(8, matrix);

    cout << "Minimum cost : "<< ans;
   }
	return 0;
}
