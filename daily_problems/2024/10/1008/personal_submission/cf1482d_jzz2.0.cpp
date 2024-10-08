#include <bits/stdc++.h>
 
using namespace std;
using LL = long long;
 
#define int LL
#define endl "\n"
#define all(x) (x).begin(), (x).end()
 
struct DSU {
	std::vector<int> f, siz;
	DSU(int n) : f(n + 1), siz(n + 1, 1) {
		std::iota(f.begin(), f.end(), 0);
	}
	int find(int x) {
		while (x != f[x]) x = f[x] = f[f[x]];
		return x;
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	bool merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) return false;
		siz[x] += siz[y];
		f[y] = x;
		return true;
	}
	int size(int x) {
		return siz[find(x)];
	}
};
 
void solve() {
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	
	queue<array<int, 2>> q;
	for (int i = 2; i <= n; i++) {
		if (gcd(a[i - 1], a[i]) == 1) {
			q.push({i - 1, i});
		}
	}
	if (gcd(a[n], a[1]) == 1) {
		q.push({n, 1});
	}
	
	DSU L(n), R(n);
	vector<int> ans;
	while (q.size()) {
		auto [x, y] = q.front();
		q.pop();
		if (R.f[x] != x) {
			continue;
		}
		L.f[y] = y == 1 ? n : y - 1;
		R.f[y] = y == n ? 1 : y + 1;
		ans.push_back(y);
		int z = R.find(y);
		if (x != y && gcd(a[x], a[z]) == 1) {
			q.push({x, z});
		}
	}
	
	cout << ans.size() << " ";
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " \n"[i + 1 == ans.size()];
	}
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0 ^ 0;
}
