#include<bits/stdc++.h>
using namespace std;
/*

/*APPROACH/INTUITION*/
/**************************************/
/*
1.The question is crafted out of the tree diameter problem.
2. The logic is simple, the largest distence of any node is from 
    the farthest node from it, which is the diameter of the tree.
3. So we can find the farthest node from any node, and then find the farthest node from that node.
4. The distance of the farthest node from the first node is the diameter of the tree.
5. We can use BFS to find the farthest node from any node.
6. We can use BFS to find the distance of each node from the farthest node.
7. We can use BFS to find the distance of each node from the second farthest node
remember that the tree is undirected and connected, so we can use BFS to find the farthest node from any node.
8. Finally, we can print the maximum distance of each node from the two farthest nodes


[node1]--[node2]--[node3]--[node4]--[node5]
    |         |         |         |
imagine this as the case
for any node the diamete is node 1 and node 5
so the max of any node is either from 1 or from 5

so our target is to have two sidtance vestor sotring the distace fo each node frfom the end points 
by 3 step bfs calls


*/


int GetMeNode(vector<vector<int>>&adj, int start, vector<int>&dist)
{
    vector<int> visited(adj.size(), 0);
 //   vector<int>dist(adj.size(), 0);
    queue<pair<int, int>> q;
    q.push({start,0});
    visited[start] = 1;
    int node = start;
    while(!q.empty())
    {
       auto  curr=q.front();
        q.pop();
        node=curr.first;
        int curr_dist=curr.second;
        dist[node]=curr_dist;
        for(int i=0; i<adj[curr.first].size(); i++)
        {
            int child=adj[curr.first][i];
            if(!visited[child])
            {
                visited[child]=1;
                q.push({child, curr_dist+1});
            }

        }
    }
    int mxdist=0;
    int mxnode=0;
    for(int i=1; i<dist.size(); i++)
    {
        if(dist[i]>mxdist)
        {
            mxdist=dist[i];
            mxnode=i;
        }
    }
    return mxnode;
}




int main()
{

int n ;
cin>>n;
if(n==1)
{
    cout<<0;
    return 0;
}
vector<vector<int>>adj(n+1);
for(int i =0; i<n; i++)
{
    int u, v;
    cin>>u>>v;
    adj[u].push_back(v);
    adj[v].push_back(u);
}
 vector<int>dist(adj.size(), 0);
int nodeB=GetMeNode(adj, 1, dist);// this is the farthest node from 1
vector<int>dist2(adj.size(), 0);
int nodeC=GetMeNode(adj, nodeB, dist2);// this is the farthest node from nodeB
dist.assign(adj.size(), 0);
int nodeA=GetMeNode(adj, nodeC, dist);// this is the farthest node from nodeC, which is nodeB

for(int i=1; i<dist2.size(); i++)
{
    cout<<max(dist[i],dist2[i])<<" ";

}
}