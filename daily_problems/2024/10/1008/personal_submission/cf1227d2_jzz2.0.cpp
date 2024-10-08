#include <bits/stdc++.h>
 
using namespace std;
using LL = long long;
 
#define int LL
#define endl "\n"
#define all(x) (x).begin(), (x).end()
 
template <typename T>
struct fenwick {
	int n;
	std::vector<T> tr;
	fenwick(int _n = 0) {
		n = _n + 1;
		tr.assign(n, T{});
	}
	void add(int x, const T &v) {
		for (int i = x + 1; i <= n; i += i & -i) {
			tr[i - 1] = tr[i - 1] + v;
		}
	}
	T Sum(int x) {
		T ans{};
		for (int i = x + 1; i > 0; i -= i & -i) {
			ans = ans + tr[i - 1];
		}
		return ans;
	}
	T Sum(int l, int r) {
		return Sum(r) - Sum(l - 1);
	}
};
 
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> a(n + 1);
	vector<array<int, 2>> b;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b.push_back({a[i], i});
	}
	
	sort(all(b), [&](array<int, 2> x, array<int, 2> y) {
		if (x[0] == y[0]) {
			return x[1] < y[1];
		}
		return x[0] > y[0];
	});
	reverse(all(b));
	
	int m;
	cin >> m;
	vector<array<int, 3>> qry(m + 1);
	for (int i = 1; i <= m; i++) {
		auto &[j, k, pos] = qry[i];
		cin >> k >> pos;
		j = i;
	}
	sort(all1(qry), [&](array<int, 3> x, array<int, 3> y) {
		return x[1] < y[1];
	});
	
	fenwick<int> tr(n);
	vector<int> ans(m + 1);
	for (int i = 1; i <= m; i++) {
		auto [j, k, pos] = qry[i];
		while (tr.Sum(n) < k) {
			auto [x, p] = b.back();
			b.pop_back();
			tr.add(p, 1);
		}
		int l = 1, r = n, p = -1;
		while (l <= r) {
			int mid = l + r >> 1;
			if (tr.Sum(mid) >= pos) {
				r = mid - 1;
				p = mid;
			} else {
				l = mid + 1;
			}
		}
		ans[j] = a[p];
	}
	for (int i = 1; i <= m; i++) {
		cout << ans[i] << endl;
	}
	return 0 ^ 0;
}
