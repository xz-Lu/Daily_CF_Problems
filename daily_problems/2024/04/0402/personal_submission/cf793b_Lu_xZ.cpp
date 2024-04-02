#include<bits/stdc++.h>
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
#define pb emplace_back
#define All(X) X.begin(), X.end()
using namespace std;
using ll = long long;
constexpr int N = 2e5 + 5;

int n, a[N], ans[N], fa[N][20];
vector<pair<int, int>> G[N];

void dfs(int x) {
	for(auto [y, z] : G[x]) {
		if(y != fa[x][0]) {
			fa[y][0] = x;
			rep(i, 1, 19) fa[y][i] = fa[fa[y][i - 1]][i - 1];
			dfs(y);
		}
	}
}

int get(int x, int k) {
	rep(i, 0, 19) if(k >> i & 1) x = fa[x][i];
	return x;
}

vector<ll> se;

void dfs(int x, ll dep) {
	auto it = lower_bound(se.begin(), se.end(), dep - a[x]);
	ans[fa[x][0]] += 1;
	ans[get(x, se.end() - it + 1)] -= 1;
	se.push_back(dep);
	for(auto[y, z] : G[x]) {
		if(y != fa[x][0]) {
			dfs(y, dep + z);
			ans[x] += ans[y];
		}
	}
	se.pop_back();	
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; ++ i) cin >> a[i];
	for(int i = 2; i <= n; ++ i) {
		int p, w; cin >> p >> w;
		G[p].pb(i, w);
		G[i].pb(p, w);
	}
	dfs(1);
	dfs(1, 0);
	for(int i = 1; i <= n; ++ i) cout << ans[i] << ' ';
	return 0;
}
