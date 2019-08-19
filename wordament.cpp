/*	Template by
	Ayush Kumar
	IIT Kanpur */

#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")

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

class Trie_Node {
public:
	//number of words ending here or further down the tree
	uint word_count;
	bool word_end;
	Trie_Node* letters[26];
	Trie_Node() : word_end(false), word_count(0) {
		memset(letters, NULL, sizeof(letters));
	}
};

class Trie {
private:
	Trie_Node* head;
	bool add_word(string s, Trie_Node* n) {
		//adds the given word at n
		if (s.empty()) {
			if (n->word_end) {
				//word was already present
				return false;
			}
			n->word_end = true; n->word_count++; return true;
		}
		assert('a' <= s[0] && s[0] <= 'z');
		if (n->letters[s[0]-'a'] == NULL) {
			n->letters[s[0]-'a'] = new Trie_Node;
		}
		if (add_word(s.substr(1), n->letters[s[0]-'a'])) {
			n->word_count++; return true;
		}
		return false;
	}
	bool remove_word(string s, Trie_Node* n) {
		//removes word if found, if removed returns true
		if (s.empty()) {
			if (n->word_end) {
				//word to be removed found;
				n->word_end = false;
				n->word_count--;
				return true;
			}
			//word not found
			return false;
		}
		if (n->letters[s[0]-'a'] == NULL) {
			//word doesn't exist in the trie
			return false;
		}
		if (remove_word(s.substr(1), n->letters[s[0]-'a'])) {
			if (n->letters[s[0]-'a']->word_count == 0) {n->letters[s[0]-'a'] = NULL;}
			n->word_count--;
			return true;
		}
		return false;
	}
	bool find_word(string s, Trie_Node* n) {
		if (s.empty()) {
			return n->word_end;
		}
		if (n->letters[s[0]-'a']) {
			return find_word(s.substr(1), n->letters[s[0]-'a']);
		}
		return false;
	}
	void print_words(string pre, Trie_Node* n) {
		//will print words in lexicographical order
		if (n->word_end) {cout << pre << endl;}
		for(uint i = 0; i < 26; i++) {
			if (n->letters[i]) {
				print_words(string(pre + string(1, 'a'+i)), n->letters[i]);
			}
		}
	}	
	uint prefix_count(string pre, Trie_Node* n) {
		//returns the number of strings starting this prefix
		if (pre.empty()) {
			return n->word_count;
		}
		if (n->letters[pre[0]-'a']) {
			return prefix_count(pre.substr(1), n->letters[pre[0]-'a']);
		}
		return 0;
	}
public:
	//edges of the tree are letters
	Trie() {
		head = new Trie_Node;
	}
	Trie(const Trie& a) {
		//copy constructor
		head = a.top();
	}
	bool addWord(string s) {
		//handle redundant query
		assert(!s.empty());
		return add_word(s, head);
	}
	bool removeWord(string s) {return remove_word(s, head);}
	bool findWord(string s) {
		//handle redundant query
		assert(!s.empty());
		return find_word(s, head);
	}
	void printWords() {print_words("", head);}
	uint wordCount() {return head->word_count;}
	uint prefixCount(string s) {return prefix_count(s, head);}
	Trie_Node* top() const {return head;}
};

clock_t time_p=clock();
void ayush194() {
    time_p = clock() - time_p;
    cerr << "Time Taken : " << float(time_p) / CLOCKS_PER_SEC << "\n";
}

class WordamentSolver {
private:
	//Dictionary
	Trie dict;
	//wordament puzzle
	char wm[4][4];
	bool visited[4][4];
public:
	WordamentSolver(Trie& a, char b[4][4]) : dict(a) {
		memset(visited, false, sizeof(visited));
		for(uint i = 0; i < 4; i++) {
			for (uint j = 0; j < 4; j++) {
				wm[i][j] = b[i][j];
			}
		}
	}
	inline void cmd(int a, int b, ll c) {
		system(("adb shell sendevent /dev/input/event0 " + to_string(a) + " " + to_string(b) + " " + to_string(c)).c_str());
	}
	void swipe(vector<uint>& a) {
		//send system calls to swipe on the screen
		const uint x = 120, y = 120;
		const uint cell_width = 20;
		//send a swipe action to cover the cells in the
		//given array. Given array is in row-major form.

		//x : 500 1500 2500 3500
		//y : 1000 1500 2000 2500

		cmd(3, 57, 30090);
		cmd(1, 330, 1);
		cmd(1, 325, 1);
		cmd(3, 48, 10);
		cmd(3, 49, 10);
		for (uint i = 0; i < a.size(); i++) {
			int x = 500 + (a[i] % 4) * 1000, y = 1000 + (a[i] / 4) * 500;
			cmd(3, 53, x);
			cmd(3, 54, y);
			cmd(0, 0, 0);
		}
		cmd(3, 57, 4294967295);
		cmd(0, 0, 0);
	}
	bool bounded(int i, int j) {
		return ((0 <= i) && (i < 4) && (0 <= j) && (j < 4));
	}
	void explore(vector<uint>& curr, int i, int j, Trie_Node* n) {
		//(i, j) is the current cell of the exploration
		visited[i][j] = true;
		curr.push_back(4*i+j);
		if (n->word_end) {swipe(curr);}
		int a[8] = {0, 1, 1, 1, 0, -1, -1, -1};
		int b[8] = {1, 1, 0, -1, -1, -1, 0, 1};
		for (uint t = 0; t < 8; t++) {
			if (bounded(i+a[t], j+b[t]) && !visited[i+a[t]][j+b[t]] && n->letters[wm[i+a[t]][j+b[t]]-'a']) {
				explore(curr, i+a[t], j+b[t], n->letters[wm[i+a[t]][j+b[t]]-'a']);
			}			
		}						
		//backtrack
		visited[i][j] = false;
		curr.pop_back();
	}
	void solve() {
		for (uint i = 0; i < 4; i++) {
			for (uint j = 0; j < 4; j++) {
				//words starting with wm[i][j]
				if (!dict.top()->letters[wm[i][j]-'a']) {
					//no words starting with this letter
					continue;
				}
				memset(visited, false, sizeof(visited));
				vector<uint> tmp;
				tmp.reserve(16);
				explore(tmp, i, j, dict.top()->letters[wm[i][j]-'a']);
			}
		}
	}
};

/*
void swipeUp() {
	if [ "$SWIPE_UP_ENABLED" = true ]; then
		adb shell input swipe ${SWIPE_UP_X} ${SWIPE_UP_Y_FROM} ${SWIPE_UP_X} ${SWIPE_UP_Y_TO}
	fi
}
*/

void startTouch() {
	system("adb shell sendevent /dev/input/event0 3 57 14");
}

void sendCoordinates(int x, int y) {
	//system("adb shell sendevent /dev/input/event0 0 0 0");
	system(("adb shell sendevent /dev/input/event0 3 53 " + to_string(x)).c_str());
	system(("adb shell sendevent /dev/input/event0 3 54 " + to_string(y)).c_str());
	system("adb shell sendevent /dev/input/event0 3 48 5");
	system("adb shell sendevent /dev/input/event0 3 58 50");
	//system("adb shell sendevent /dev/input/event0 0 2 0");
	system("adb shell sendevent /dev/input/event0 0 0 0");
	//system("adb shell sendevent /dev/input/event0 0 2 0");
	//system("adb shell sendevent /dev/input/event0 0 0 0");	
}

void finishTouch() {
	system("adb shell sendevent /dev/input/event0 3 57 -1");
	system("adb shell sendevent /dev/input/event0 0 0 0");
}

void swipePattern() {
	sendCoordinates(100, 500);
	system("adb shell sleep 1");
}

int main() {
    //cin.sync_with_stdio(0); cin.tie(0);
	//cin.exceptions(cin.failbit);
	//x : 500 1500 2500 3500
	//y : 1000 1500 2000 2500
	/*
	system("adb shell sendevent /dev/input/event0 3 57 30090");
	system("adb shell sendevent /dev/input/event0 1 330 1");
	system("adb shell sendevent /dev/input/event0 1 325 1");
	system("adb shell sendevent /dev/input/event0 3 53 500");
	system("adb shell sendevent /dev/input/event0 3 54 1000");
	system("adb shell sendevent /dev/input/event0 3 48 10");
	system("adb shell sendevent /dev/input/event0 3 49 10");
	system("adb shell sendevent /dev/input/event0 0 0 0");
	system("adb shell sendevent /dev/input/event0 3 53 1500");
	system("adb shell sendevent /dev/input/event0 3 54 1000");
	system("adb shell sendevent /dev/input/event0 0 0 0");
	system("adb shell sendevent /dev/input/event0 3 53 1500");
	system("adb shell sendevent /dev/input/event0 3 54 1500");
	system("adb shell sendevent /dev/input/event0 0 0 0");
	system("adb shell sendevent /dev/input/event0 3 53 2500");
	system("adb shell sendevent /dev/input/event0 3 54 1500");
	system("adb shell sendevent /dev/input/event0 0 0 0");
	system("adb shell sendevent /dev/input/event0 3 53 2500");
	system("adb shell sendevent /dev/input/event0 3 54 2000");
	system("adb shell sendevent /dev/input/event0 0 0 0");
	system("adb shell sendevent /dev/input/event0 3 57 4294967295");
	system("adb shell sendevent /dev/input/event0 0 0 0");
	//system("adb shell sendevent /dev/input/event0 3 57 30073");	
	*/
	//sendCoordinates(100, 500);
	//finishTouch();
	Trie mydict;
	//take input from file and add words to the trie
	ifstream dict;
	dict.open("dict.txt");
	string word;
	vector<string> arr;
	while (dict >> word) {
		mydict.addWord(word);
		//arr.push_back(tmp);
	}
	dict.close();
	////////////
	//mydict.printWords();
	char tmp[4][4];
	for (uint i = 0; i < 4; i++) {
		for (uint j = 0; j < 4; j++) {
			cin >> tmp[i][j];
		}
	}
	WordamentSolver mysolver(mydict, tmp);
	mysolver.solve();
	ayush194();
	return 0;
}


