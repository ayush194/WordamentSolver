/*	Template by
	Ayush Kumar
	IIT Kanpur */

#include <bits/stdc++.h> 
using namespace std;

#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")

/*
#define TRACE
 
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1 <<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif
*/

/*
clock_t time_p=clock();
void ayush194()
{
    time_p=clock()-time_p;
    cerr<<"Time Taken : "<<(float)(time_p)/CLOCKS_PER_SEC<<"\n";
}
*/

#define rep(i, n)    for(int i = 0; i < (n); ++i)
#define repA(i, a, n)  for(int i = a; i <= (n); ++i)
#define repD(i, a, n)  for(int i = a; i >= (n); --i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define fill(a)  memset(a, 0, sizeof (a))
#define fst first
#define snd second
#define mp make_pair
#define pb push_back
#define MOD 1000000007

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;

bool check(string& s) {
	if (s.size() < 3) {return false;}
	for(int i = 0; i < s.size(); i++) {
		if (!('a' <= s[i] && s[i] <= 'z') && !('A' <= s[i] && s[i] <= 'Z')) {
			return false;
		}
		if ('A' <= s[i] && s[i] <= 'Z') {
			s[i] = 'a' + s[i] - 'A';
		}
	}
	return true;
}

int main() {
    //cin.sync_with_stdio(0); cin.tie(0);
	//cin.exceptions(cin.failbit);
	//FILE* dict = fopen("dict.txt", 'r');
	FILE* newfile = fopen("dict.txt", "w");
	ifstream dict;
	dict.open("dict_sample.txt");
	string tmp;
	vector<string> arr;
	while (dict >> tmp) {
		//cout << tmp.size() << ' ' << tmp << endl;
		if (check(tmp)) {
			arr.push_back(tmp);
		}
		//cout << tmp << endl;
	}
	dict.close();
	sort(arr.begin(), arr.end());
	for (int i = 0; i < arr.size(); i++) {
		//cout << arr[i] << endl;
		fprintf(newfile, "%s\n", arr[i].c_str());
	}
	fclose(newfile);
	return 0;
}


