#include<bits/stdc++.h>
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
#define pb emplace_back
using namespace std;
using ll = long long;
constexpr int N = 5e3 + 5;

int n, v1[N], v2[N], p[N], b[N], t[N], ans;
/*
v1[i] = p[0] ^ b[i]
v2[i] = p[i] ^ b[0]

p[i] ^ b[j] = v2[i] ^ v1[0] ^ v1[j] 

*/


int ask(int i, int j) {
	cout << "? " << i << ' ' << j << endl;
	int ret; cin >> ret;
	return ret;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for(int i = 0; i < n; ++ i) {
		v1[i] = ask(0, i);
		v2[i] = ask(i, 0);
	}
	for(int i = 0; i < n; ++ i) {
		/*
		钦定p[0] = 0
		*/
		p[0] = i;
		for(int j = 0; j < n; ++ j) {
			b[j] = v1[j] ^ p[0];
			p[j] = v2[j] ^ b[0];
		}
		int ok = 1;
		for(int j = 0; j < n; ++ j) {
			if(b[j] >= n || p[b[j]] != j) {
				ok = 0;
				break;
			}
		}
		if(ok) {
			++ ans;
			for(int j = 0; j < n; ++ j) t[j] = p[j];
		}
	}
	cout << '!' << endl;
	cout << ans << endl;
	for(int i = 0; i < n; ++ i) cout << t[i] << ' ';
	return 0;
}
