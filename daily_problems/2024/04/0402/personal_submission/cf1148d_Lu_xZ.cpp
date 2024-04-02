#include<bits/stdc++.h>
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
#define pb emplace_back
using namespace std;
using ll = long long;
constexpr int N = 1e6;

struct Fenwick_Tree {
	int t[N], a[N], n;
	void init(int v) {
		n = 2 * v;
		for(int i = 1; i <= n; ++ i) {
			t[i] = 0;
		}
	}
	void pre_add(int p, int v, int x) {
		while(p <= n) {
			if(t[p] < v) {
				t[p] = v;
				a[p] = x;
			}
			p += p & -p;
		}
	}
	void suf_add(int p, int v, int x) {
		while(p) {
			if(t[p] < v) {
				t[p] = v;
				a[p] = x;
			}
			p -= p & -p;
		}
	}
	auto pre_qry(int p) {
		int ret = 0;
		int idx = 0;
		while(p > 0) {
			if(ret < t[p]) {
				ret = t[p];
				idx = a[p];
			}
			p -= p & -p;
		}
		return make_pair(ret, idx);
	}
	auto suf_qry(int p) {
		int ret = 0;
		int idx = 0;
		while(p <= n) {
			if(ret < t[p]) {
				ret = t[p];
				idx = a[p];
			}
			p += p & -p;
		}
		return make_pair(ret, idx);
	}
} F, G;


map<pair<int, int>, int> mp;
int n, pf[N], pg[N];
pair<int, int> vec[N];

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	F.init(n);
	G.init(n);
	for(int i = 1; i <= n; ++ i) {
		cin >> vec[i].first >> vec[i].second;
		mp[vec[i]] = i;
	}
	sort(vec + 1, vec + n + 1, [&](auto x, auto y) {
		return x.second > y.second;
	});
	for(int i = 1; i <= n; ++ i) {
		auto [a, b] = vec[i];
		if(a < b) {
			auto [v, id] = F.suf_qry(a + 1);
			pf[mp[vec[i]]] = id;
			F.suf_add(b, v + 1, mp[vec[i]]);
		}
	}
	
	sort(vec + 1, vec + n + 1, [&](auto x, auto y) {
		return x.second < y.second;
	});
	for(int i = 1; i <= n; ++ i) {
		auto [a, b] = vec[i];
		if(a > b) {
			auto [v, id] = G.pre_qry(a - 1);
			pg[mp[vec[i]]] = id;
			G.pre_add(b, v + 1, mp[vec[i]]);
		}
	}
	auto [vf, idf] = F.suf_qry(1);
	auto [vg, idg] = G.pre_qry(n * 2);
	
	if(vg < vf) {
		cout << vf << '\n';
		vector<int> ans = {idf};
		while(pf[idf]) {
			ans.pb(pf[idf]);
			idf = pf[idf];
		}
		reverse(ans.begin(), ans.end());
		for(int x : ans) cout << x << ' ';
	}
	else {
		cout << vg << '\n';
		vector<int> ans = {idg};
		while(pg[idg]) {
			ans.pb(pg[idg]);
			idg = pg[idg];
		}
		reverse(ans.begin(), ans.end());
		for(int x : ans) cout << x << ' ';
	}	
	return 0;
}
