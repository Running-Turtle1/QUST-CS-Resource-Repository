// eg : ![](C:\Users\95432\Desktop\��ҵ\�����߼���·\md_inserts\19.png)
#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int l, r;
	cin >> l >> r;
	for(int i = l; i <= r; i ++){
		cout << "![](C:\\Users\\95432\\Desktop\\��ҵ\\�����߼���·\\����ѡ����\\" + to_string(i) + ".png)\n";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
