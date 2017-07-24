#include <iostream>
#include <queue>
using namespace std;

priority_queue<pair<int, pair<int, int> >,vector< pair<int, pair<int, int> > >, greater< pair<int, pair<int, int> > > > q;

int main() {
    q.push(make_pair(1, make_pair(2,3)));
    q.push(make_pair(13, make_pair(21,31)));
    q.push(make_pair(81, make_pair(82,83)));
    pair<int, pair<int, int> > a = q.top();
    cout<<a.first<<endl;
    pair <int,int> q = a.second;
    cout<<q.first<<" "<<q.second<<endl;
    return 0;
}