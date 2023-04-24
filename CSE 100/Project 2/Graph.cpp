#include "Graph.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

Graph::Graph(const char* const & edgelist_csv_fn) {
    map<string,bool> nodeFound;
    ifstream inputFile(edgelist_csv_fn);      // open the file
    string line;                     // helper var to store current line
    while(getline(inputFile, line)) {  // read one line from the file
        istringstream ss(line);      // create istringstream of current line
        string first, second, third; // helper vars
        getline(ss, first, ',');     // store first column in "first"
        getline(ss, second, ',');    // store second column in "second"
        getline(ss, third, '\n');    // store third column column in "third"
        float weight = stof(third);
        //node_list.insert(first);

        if (!nodeFound[first]) {
            node_list.push_back(first);
            nodeFound[first] = true;
        }
        if (!nodeFound[second]) {
            node_list.push_back(second);
            nodeFound[second] = true;
        }
        //node_list.insert(second);

        edges.push_back(make_tuple(first, second, weight));
        //cout << first << ", " << second << ", " << weight << endl;
    }
    //reverse(node_list.begin(),node_list.end());
}

unsigned int Graph::num_nodes() {
    return node_list.size();
}

vector<string> Graph::nodes() {
    return node_list;
}

unsigned int Graph::num_edges() {
    return edges.size();
}

unsigned int Graph::num_neighbors(string const & node_label) {
    return neighbors(node_label).size();
}

double Graph::edge_weight(string const & u_label, string const & v_label) {
    vector<tuple<string, float>> nlist;
    nlist = neighbors_weights(u_label);
    for (auto edge : nlist)
        if ((v_label.compare(get<0>(edge)) == 0))
            return get<1>(edge);
    return -1.0;
}

vector<string> Graph::neighbors(string const & node_label) {
    set<string> nset;
    vector<string> nlist;
    for (auto node : edges) {
        if (node_label.compare(get<0>(node)) == 0)
            nset.insert(get<1>(node));
        if (node_label.compare(get<1>(node)) == 0)
            nset.insert(get<0>(node));
    }
    for (auto node: nset)
        nlist.push_back(node);
    return nlist;
}

vector<tuple<string, float>> Graph::neighbors_weights(string const & node_label) {
    set<tuple<string, float>> nset;
    vector<tuple<string, float>> nlist;
    for (auto node : edges) {
        if (node_label.compare(get<0>(node)) == 0)
            nset.insert(make_tuple(get<1>(node),get<2>(node)));
        if (node_label.compare(get<1>(node)) == 0)
            nset.insert(make_tuple(get<0>(node), get<2>(node)));
    }
    for (auto node: nset)
        nlist.push_back(node);
    return nlist;
}


struct Node {
public:
    float weight;
    string name;
    float dist;
    string prev;

    bool operator <(const Node& n) {
        if (weight < n.weight)
            return true;
        else
            return false;
    }
};

vector<string> Graph::shortest_path_unweighted(string const & start_label, string const & end_label) {
    if (start_label.compare(end_label) == 0)
        return {start_label};
    map<string, tuple<string, int>> paths; // map of paths<from> <to, dist>
    tuple<string, string, int> current; // current node <from, to, dist>
    queue<tuple<string,string,int>> q; // queue of nodes for BFS <from, to, dist>
    map<string, bool> visited; // list of visited nodes
    vector<string> path;
    int dist; // current distance
    string from; // current from node
    string dest; // current destination node
    current = make_tuple("",start_label,0);
    q.push(current);
    while (!q.empty()) {
        current = q.front();
        from = get<0>(current);
        dest = get<1>(current);
        dist = get<2>(current);
        //cout << "*" << from << "," << dest << "," << dist;
        if (get<0>(paths[dest]) == "") {
            paths[dest] = make_tuple(from, dist);
        }
        if (!visited[from]) // node not yet visited
            visited[from]=true;
        q.pop();
        from = dest;
        for (auto node : neighbors(dest)) {
            if (!visited[node]) // node not yet visited
                q.push(make_tuple(from, node, dist+1));
            if (end_label.compare(node) == 0)
                break;
        }
    }
    dist = get<1>(paths[end_label]);
    dest = get<0>(paths[end_label]);
    path = {};
    if (dist != 0)
        path.push_back(end_label);
    while(dist != 0 && dest != "") {
        if (dist != 0)
            path.push_back(dest);
        dist = get<1>(paths[dest]);
        dest = get<0>(paths[dest]);
    }
    reverse(path.begin(),path.end());
    return path;
}

class PathEntry {
public:
    string from;
    string dest;
    float cost;
    float origCost;
};

bool operator< (const PathEntry& a, const PathEntry& b) {
    bool result;
    result = a.cost > b.cost;
    return result;
}

const float MAXCOST = 99999.99;



vector<tuple<string,string,double>> Graph::shortest_path_weighted(string const & start_label, string const & end_label) {
if (start_label.compare(end_label) == 0)
        return {make_tuple(start_label,end_label,-1)};
    map<string, tuple<string, double>> paths; // map of paths<from> <to, dist>
    vector<tuple<string,string,double>> path; // path <from, to, cost> list
    map<string, bool> visited; // list of visited visited[node] = true
    float dist; // current distance
    string from; // current from node
    string dest; // current destination node
    priority_queue<PathEntry, vector<PathEntry>, less<vector<PathEntry>::value_type>> q;
    PathEntry b;
    b.cost = 0;
    b.from = start_label;
    b.dest = start_label;
    b.origCost = 0;
    q.push(b);
    while (!q.empty()) {
        b = q.top();
        from = b.from;
        dest = b.dest;
        dist = b.cost;
        //cout << "*" << from << "," << dest << "," << dist << endl;
        //cout << endl << "c: " << b.cost << ", f:" << b.from << ", to:" << b.dest << endl;
        if (get<0>(paths[dest]) == "") { // start node
            //cout << "*" << from << "," << dest << "," << dist << endl;
            paths[dest] = make_tuple(from, b.origCost);
        }
        if (get<1>(paths[dest]) == 0) {
            //cout << "*" << from << "," << dest << "," << dist << endl;
            paths[dest] = make_tuple(from, b.origCost);
        }
        if (!visited[from]) // node not yet visited
            visited[from]=true;
        q.pop();
        from = dest;
        for (auto node : neighbors_weights(dest)) {
            string toNode = get<0>(node);
            double toWeight = get<1>(node);
            if (!visited[toNode]) // node not yet visited
            {
                b.cost = dist + toWeight;
                b.from = from;
                b.dest = toNode;
                b.origCost = toWeight;
                //cout << b.cost << " f:" << b.from << " to:" << b.dest << endl;
                q.push(b);
                //visited[toNode] = true;
            }
            //if (end_label.compare(get<0>(node)) == 0)
            //    break;
        }
    }
    /*
    for (std::map<string, tuple<string,double>>::iterator it = paths.begin(); it != paths.end(); ++it)
        std::cout << it->first << " => " << get<0>(it->second) << get<1>(it->second) << '\n';
    */
    dest = get<0>(paths[end_label]);
    from = end_label;
    dist = get<1>(paths[end_label]);
    path.clear();
    //cout << "*" << from << "," << dest << "," << dist << endl;
    /*
    if (dst != start_label)
        path.push_back(make_tuple(from, dest, dist));
    */
    while(dest != from) {
        if (dist != 0)
            path.push_back(make_tuple(dest, from, dist));
        from = dest;
        dest = get<0>(paths[dest]);
        dist = get<1>(paths[from]);
        //cout << "*" << from << "," << dest << "," << dist << endl;
    }
    reverse(path.begin(),path.end());

    return path;
    return {make_tuple(start_label,end_label,-1)};
}

vector<vector<string>> Graph::connected_components(double const & threshold) {
    vector<string> currList;
    vector<vector<string>> retList;
    queue<string> q;
    queue<string> q2;
    map<string, bool> visited; // list of visited nodes
    for (auto node : node_list) // add nodes into queue
    {
        q.push(node);
        visited[node] = false;
        //cout << node << endl;
    }
    while (!q.empty()) {
        string cnode = q.front();
        q.pop();
        currList.clear();
        //cout << "cnode: " << cnode << endl;
        if (!visited[cnode]) {
            q2.push(cnode);
            while(!q2.empty()) {
                string q2node = q2.front();
                q2.pop();
                //cout << "q2n: " << cnode << endl;
                if(!visited[q2node]) {
                    //cout << "q2node: " << q2node << endl;
                    visited[q2node]=true;
                    currList.push_back(q2node);
                    for (auto neighbor : neighbors_weights(q2node)) {
                        double weight = get<1>(neighbor);
                        if (weight < 0)
                            weight = 0;
                        string node = get<0>(neighbor);
                        //cout << "node: " << node << ":" << weight << endl;
                        //cout << "node: " << node << ":" << weight << "=" << fabs(weight - threshold) << endl;
                        if (!visited[node]) {
                            if (weight <= threshold) {
                                q2.push(node);
                                //currList.push_back(node);
                                //cout << "node: " << node << ":" << weight << "=" << fabs(weight - threshold) << endl;
                            }
                        }
                        //visited[node]=true;
                    }
                }
                //cout << "q2:" << q2node << endl;
            }
        }
        /*
        for (auto a : currList)
            cout << "a: " << a << " ";
        cout << "cnode: " << cnode << endl;


        currList.clear();
        if (nodeSet.size() > 0)
            for (auto a: nodeSet)
                currList.push_back(a);
        nodeSet.clear();
         */
        if (currList.size() > 0)
            retList.push_back(currList);
    }
    return retList;
}
class Disjoint {
private:
    map<string, string> upTree;
public:
    Disjoint(vector <tuple<string, string, double>> edges, vector<string> nodes) {
    for (auto a : nodes) {
        upTree[a] = "*"; // sentinel
    }
    /*
    for (auto a : edges) {
        string x = get<0>(a);
        string y = get<1>(a);
        upTree[x] = y;
        //upTree[y] = x;
    }
     */
    /*
    for (std::map<string, string>::iterator it = upTree.begin(); it != upTree.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
    */
    }

    void setUnion(string x, string y) {
        string a = find(x);
        string b = find(y);
        if (a != b)
            upTree[b] = a;
    }

    string find(string x) {
        // perform path compression
        queue<string> compress;
        string lastn = x;
        string next = upTree[x];
        while(next != "*") {
            lastn = next;
            compress.push(next);
            next = upTree[next];
        }
        /*
        while(!compress.empty()) {
            upTree[compress.front()] = lastn;
            compress.pop();
        }
         */
        return lastn;
    }

};

double Graph::smallest_connecting_threshold(string const & start_label, string const & end_label) {
        // setup disjoint set - using all edges in the graph
    // u = start_label, v = end_label
    // for each edge beween x and y in increasing weight:
    //   perform union(x,y)
    //   if find(u) = find(v) (same set), return w - which is smallest treshold
    // if we end here (none found), 2 vertex are not connected, return -1
    if (start_label == end_label)
        return 0;
    priority_queue<PathEntry, vector<PathEntry>, less<vector<PathEntry>::value_type>> pq;
    for (auto a : edges) {
        PathEntry b;
        b.cost = get<2>(a);
        b.from = get<0>(a);
        b.dest = get<1>(a);
        pq.push(b);
    }
/*
    while (!pq.empty()) {
        PathEntry b = pq.top();
        cout << "cost: " << b.cost << endl;
        cout << "from: " << b.from << endl;
        cout << "dest: " << b.dest << endl;
        pq.pop();
    }

    for (auto a : edges) {
        PathEntry b;
        b.cost = get<2>(a);
        b.from = get<0>(a);
        b.dest = get<1>(a);
        pq.push(b);
    }
*/
    Disjoint dslist(edges, node_list);
    //cout << endl << "Find: " << dslist.find("C") << endl;
    float weight = -1;
    while(!pq.empty()) {
        PathEntry a;
        a = pq.top();
        dslist.setUnion(a.from, a.dest);
        if (dslist.find(start_label) == dslist.find(end_label)) {
            weight = a.cost;
            break;
        }
        pq.pop();
    }
    return weight;
}
