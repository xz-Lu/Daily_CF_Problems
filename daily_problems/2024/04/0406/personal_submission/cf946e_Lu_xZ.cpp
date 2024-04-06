#include<bits/stdc++.h>
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
#define pb emplace_back
using namespace std;
using ll = long long;

void solve() {
	string s; cin >> s;
	if(s.length() & 1) {
		for(int i = 2; i < s.length(); i += 2) {
			cout << "99";
		}
		cout << '\n';
		return;
	}
	vector<int> pre(s.length(), 0);
	for(int i = 0; i < s.length(); ++ i) {
		pre[i] = 1 << (s[i] - '0');
		if(i) pre[i] ^= pre[i - 1];
	}
	for(int i = s.length() - 1; i >= 0; -- i) {	//第一个不一样的位置
		while(s[i] > '0') {
			if(s[i] == '1' && i == 0) break;
			pre[i] ^= 1 << (s[i] - '0');
			pre[i] ^= 1 << (s[i] - '1');
			s[i] -= 1;
			int cnt = __builtin_popcount(pre[i]);
			int len = s.length() - i - 1;
			if(len < cnt) continue;
			set<int> se;
			for(int j = 0; j < 10; ++ j) {
				if(pre[i] >> j & 1) {
					se.insert(j);
				}
			}
			int j = s.length() - 1;
			if(j - i - se.size() & 1) continue;
			while(se.size()) {
				s[j --] = *se.begin() + '0';
				se.erase(se.begin());
			}
			while(j > i) s[j --] = '9';
			cout << s << '\n';
			return;
		}
	}
	for(int i = 2; i <= s.length() - 2; i += 2)  cout << "99";
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
	cin >> T;
	while(T --) solve();
	return 0;
}
