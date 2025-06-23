#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <set>

using namespace std;

int main() {
    // List of people in the social circle
    vector<string> people = {"олег", "никита", "настя", "ваня", "женя"};
    int n = people.size();

    // Mapping names to indices for easier management
    map<string, int> nameToIndex;
    for (int i = 0; i < n; ++i) {
        nameToIndex[people[i]] = i;
    }

    // Initialize adjacency list
    vector<vector<int>> adj(n);

    // Example input: list of pairs who know each other (social ties)
    // You can modify these connections based on the actual social graph
    // For example:
    // олег <-> никита
    // никита <-> настя
    // настя <-> ваня
    // ваня <-> женя

    adj[nameToIndex["олег"]].push_back(nameToIndex["никита"]);
    adj[nameToIndex["никита"]].push_back(nameToIndex["олег"]);

    adj[nameToIndex["никита"]].push_back(nameToIndex["настя"]);
    adj[nameToIndex["настя"]].push_back(nameToIndex["никита"]);

    adj[nameToIndex["настя"]].push_back(nameToIndex["ваня"]);
    adj[nameToIndex["ваня"]].push_back(nameToIndex["настя"]);

    adj[nameToIndex["ваня"]].push_back(nameToIndex["женя"]);
    adj[nameToIndex["женя"]].push_back(nameToIndex["ваня"]);

    // To store pairs connected within 3 handshake steps
    set<pair<string, string>> connections;

    // For each person, perform BFS up to depth 3
    for (int start = 0; start < n; ++start) {
        vector<int> dist(n, -1);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            if (dist[current] >= 3) continue; // Limit to 3 steps

            for (int neighbor : adj[current]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[current] + 1;
                    q.push(neighbor);
                    if (dist[neighbor] <= 3 && neighbor != start) {
                        // Save pair in lex order to avoid duplicates
                        string name1 = people[start];
                        string name2 = people[neighbor];
                        if (name1 > name2) swap(name1, name2);
                        connections.insert({name1, name2});
                    }
                }
            }
        }
    }

    // Output all pairs found
    cout << "Пары знакомств через три рукопожатия или меньше:" << endl;
    for (const auto& pair : connections) {
        cout << pair.first << " - " << pair.second << endl;
    }

    return 0;
}