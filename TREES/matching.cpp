#include<bits/stdc++.h>
using namespace std;

// Changed from fixed size to dynamic allocation based on input size (n <= 2e5)
vector<vector<long long>> dp;
vector<vector<int>> adj;

/*APPROACH/INTUITION*/
/**************************************/
/*1. the logic is simple each node we can have two choices either take that node and match it with one of the 
  children or we do not match the node with any of the children 


2. In the dp[u][0]----> Means we do not match with any of the child of u , 
   Imagine this as the case we do not take the node but move forward; in this case, the child will be processed

   dp[u][1]----> Means we match with one of the child of u,
   Imagine this as the case we take the node and match it with one of the child of u,
   In this case, we will not process the child of u as we have already matched it
   Tricky: then we skip that child 

/*
     1----u( dp[u][0] and dp[u][1] )
    / \
   2   3---all children v run dfs for every one 
      / \
     4   5
*/

void dfs(int u , int parent)
{
    for(auto &child: adj[u])
    {
        // think of this as the case we are processing the child of u
        // if child is parent then we skip it
        // here we do not match the parent u with any of its children
        if(child == parent) 
            continue;
        dfs(child, u);
        dp[u][0] += max(dp[child][0], dp[child][1]);
    }

    // now we will see if we combine u with any one of the children and rest possible 
    for(auto &child: adj[u])
    {
        if(child == parent) 
            continue;

        // here we are matching u with child
        // suppose we match u with this present child
        // means we need to remove the contribution 
        long long ans = 1; // for u-v match 

        // now if we took u-v , then for v we need to take only the case of dp[child][0] all sub tree with no v
        ans += dp[child][0];

        // now we will add all the other child contributions except the present child
        /*
             1----u( dp[u][0] and dp[u][1] )
            / \
           2   3---all children v run dfs for every one 
              / \
             4   5   suppose we took 1-2 then we need to add the dp[3][0];
        */

        // TRICK TO DO THAT 
        ans += dp[u][0] - max(dp[child][0], dp[child][1]);
        dp[u][1] = max(dp[u][1], ans);
    }
}

int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

   
    dp.assign(n + 1, vector<long long>(2, 0));
    adj.assign(n + 1, vector<int>());

    for(int i = 1; i < n; i++) 
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected tree
    }

    // assume node 1 as root (safe for trees)
    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]) << endl;

    return 0;
}
