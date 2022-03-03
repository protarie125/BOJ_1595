#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using Adj = map<int, vii>;
using sii = stack<ii>;
using vb = vector<bool>;

Adj adj{};
vi roots{};
auto mx = int{ 0 };
auto mxNode = int{ -1 };
vb isVisited{};

void solve(int v, int root) {
	isVisited = vb(v, false);

	auto st = sii{};
	st.push({ root, 0 });
	isVisited[root - 1] = true;

	while (!st.empty()) {
		auto [t, d] = st.top();
		st.pop();

		auto addedCount = int{ 0 };
		for (const auto& [node, dist] : adj[t]) {
			if (!isVisited[node - 1]) {
				isVisited[node - 1] = true;

				st.push({ node, d + dist });
				addedCount += 1;
			}
		}

		if (0 == addedCount) {
			if (mx < d) {
				mx = d;
				mxNode = t;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto v = int{ 0 };

	int a, b, d;
	cin >> a >> b >> d;
	while (cin.good()) {
		if (v < a) {
			v = a;
		}

		if (v < b) {
			v = b;
		}

		if (adj.end() == adj.find(a)) {
			adj[a] = vii{ {b, d} };
		}
		else {
			adj[a].push_back({ b, d });
		}

		if (adj.end() == adj.find(b)) {
			adj[b] = vii{ {a, d} };
		}
		else {
			adj[b].push_back({ a, d });
		}

		cin >> a >> b >> d;
	}

	auto root = int{ -1 };
	for (const auto& [node, a] : adj) {
		if (1 == a.size()) {
			root = node;
			break;
		}
	}

	if (-1 == root) {
		cout << 0;
		return 0;
	}

	solve(v, root);
	solve(v, mxNode);

	cout << mx;

	return 0;
}