#include<bits/stdc++.h>
using namespace std;
/*APPROACH/INTUITION*/
/**************************************/
/*
the problem can be solved usin two steps if u look at a node and think what are the ways i the total distance
from that node to all other nodes, things get simple
     1
    / \        observe : node one has distance sum=6 
   2   3       ASK: how to achieve is (JUST FOCUS ON NODE 1)
      / \      if u imagine the paths u get to see that the there are braodly two sub trees
     4   5     we try to get 6 using these sub tress ?

     we see for each node in subtree rooted at 3 , we count the edge 1-3 that many times 
     1-3-4
     1-3-5
     1-3
     how many times 1-3 => size of subtree rooted at 3
     okay , 
     now only consider the subtree rooted at 3

       3      
      / \      
     4   5     
     think this as the independent problem
     we know the ans of for just NODE 3 is 2;

     so logically if we need to get the ans for node1
     we can just add the ans of node 3 to the ans of node 1
     okay , but how many times we add the edge 1-3
    that is ::::: we add it size of subtree rooted at 3 

    so we need 2 things:
    VVI: 
    *dp[u]=for a node acting as root, the total distance sum of all nodes in its subtree
    *and size[u]=size of subtree rooted at u
    so for root node 1
    dp[1]=dp[3]+size[3] // size[3] is the number of nodes in subtree rooted at 3
    and we can do this for all nodes in the tree
    GENERALIZE:
    dp[u]=dp[child]+size[child] 


    2ND QUESTION:what about the other nodes like 1 was the root but the other nodes are not ?
    : HERE is the trick, we can use the same logic but we need to change the root
    so we can use the same logic but we need to change the root

    AGAIN consider the same tree
    1 -prv assume 1 is the root
    / \         
    2   3-> this time assume 3 is the root
         / \      
        4   5

// we are RE-ROOTING the tree
// now we create a realetion such that we ustilize the previous root(1) to get the new root(3)

WHAT HEPPANS in REROOTING
some values from the previous root are used to get the new root 

CRITICAL POINT:
when we make 3 as the root then :
Moving root from u to child v:
Nodes in subtree of v: all become 1 step closer → -size[v]
Nodes outside subtree of v: become 1 step farther → +(n - size[v])
dry run with pen paper 
reimagine the tree as 

3--1---2
/ \
5   4
   
now 3 is the root 

so dp[v]=dp[u]-size[v]+(n-size[v])

imagine we took root saatatus from 1(u) and gave to 3(v)

so if i had som ans for 1 then definety it had some componenet foe 3 acting assubtree
so we need to dexrese someting from dp[u]
and add something to dp[v]
so we are just trying to get ans form3 using 1 and manipulating the duplicate calculations 

so the code will need 2 bfs funtions 
1. for size storeing of subtree and solving root 1 
2. for rerooting the tree and getting the ans for all nodes

     
*/

vector<vector<long long int>>adj;
vector<long long int>dp;
vector<long long int>sizee;
void dfs(long long int u, long long int parent)
{
    dp[u]=0;
    sizee[u]=1;
    for(auto child: adj[u])
    {
        if(child == parent) continue; // avoid going back to parent
        dfs(child, u);
        dp[u] += dp[child] + sizee[child]; // add child's dp and sizee to parent's dp
        sizee[u] += sizee[child]; // add child's sizee to parent's sizee
    }
}

void dfs2(long long int u, long long int parent, long long int n) {
    for (auto child : adj[u]) {
        if (child == parent) continue;
        dp[child] = dp[u] - sizee[child] + (n - sizee[child]);  
        dfs2(child, u, n);
    }
}

 int main()
{
    int n ;
    cin>>n;
    adj.resize(n + 1);  // 1-based indexing
    for(int i =0; i<n-1; i++)
    {
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dp.resize(n + 1, 0);
    sizee.resize(n + 1, 0);
    dfs(1, 0);
    dfs2(1, 0,n);

    for (int i = 1; i <= n; i++) {
        cout << dp[i] << " ";
    }
    cout << endl;
}