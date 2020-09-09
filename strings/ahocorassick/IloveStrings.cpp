/*
http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1620
*/


#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define REP(i,a,b) for(ll i=a; i<b; i++)
using namespace std;


struct Vertex {
	int next[52];
	bool leaf = false;
	int p = -1;
	char pch;
	int link = -1;
	int go[52];
	vector<int>ending;

	Vertex(int p = -1, char ch = '$') : p(p), pch(ch) {
		fill(begin(next), end(next), -1);
		fill(begin(go), end(go), -1);
	}
};

vector<Vertex> t(1);

void add_string(string const& s, int index) {
	int v = 0;
	for (char ch : s) {
		int c;
		if (ch >= 'A' && ch <= 'Z') {
			c = ch - 'A' + 26;
		}
		else {
			c = ch - 'a';
		}
		if (t[v].next[c] == -1) {
			t[v].next[c] = t.size();
			t.emplace_back(v, ch);
		}
		v = t[v].next[c];
	}
	t[v].leaf = true;
	t[v].ending.pb(index);
}

int go(int v, char ch);

int get_link(int v) {
	if (t[v].link == -1) {
		if (v == 0 || t[v].p == 0)
			t[v].link = 0;
		else
			t[v].link = go(get_link(t[v].p), t[v].pch);
	}
	return t[v].link;
}
int go(int v, char ch) {
	int c;
	if (ch >= 'A' && ch <= 'Z') {
		c = ch - 'A' + 26;
	}
	else {
		c = ch - 'a';
	}
	if (t[v].go[c] == -1) {
		if (t[v].next[c] != -1)
			t[v].go[c] = t[v].next[c];
		else
			t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
	}
	return t[v].go[c];
}

void solve() {

	string s;
	cin >> s;
	ll n;
	cin >> n;
	vector<string>pat(n);
	REP(i, 0, n) {
		cin >> pat[i];
	}
	REP(i, 0, n) {
		add_string(pat[i], i);
	}
	vector<bool>ans(n, false);
	ll a = s.size();
	int curr = 0;
	for (auto ch : s) {
		int c;
		if (ch >= 'A' && ch <= 'Z') {
			c = ch - 'A' + 26;
		}
		else {
			c = ch - 'a';
		}
		curr = go(curr, ch);
		for (auto y : t[curr].ending) {
			ans[y] = true;
		}
	}
	REP(i, 0, n) {
		if (ans[i]) {
			cout << "y\n";
		}
		else {
			cout << "n\n";
		}
	}

	t.clear();
	t.emplace_back();

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
// #ifndef ONLINE_JUDGE
	// freopen ("input.txt" , "r" , stdin);
	// freopen ("output.txt" , "w" , stdout);
// #endif
	ll ntc;
	cin >> ntc;
	// ntc = 1;
	REP(tc, 1, ntc + 1)
	{
		// cout << "Case #" << tc << ": ";
		solve();
	}
}
