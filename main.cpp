//#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
#define code(i, j) ((i - 1) * m + j)
#define all(x) (x).begin(),(x).end()
#define all1(x) (x).begin()+1,(x).end()
#define fi first
#define se second
#define ctz __builtin_ctzll
#define ppc __builtin_popcountll
typedef long long LL;
typedef unsigned long long ull;
typedef double db;
const int maxn=3e6+10;
const int maxm=2e7+10;
const int mod=1e9 + 7;
const int inf= 0x3f3f3f3f;
const int dx[] = {-2, -2, -1, 1, 2, 2, -1, 1}, dy[] = {-1, 1, 2, 2, 1, -1, -2, -2};
const db pi=acosl(-1);
const db eps = 1e-6;
const int di[]={-1, 0, 1, 0, -1};
const int dir[6][3] ={{0, -1, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, -1}, {1, 0, 0}, {-1, 0, 0}};
//----------------------------------------------------//

void slove() {
    int n, m, h, w;
    cin >> n >> m >> h >> w;

    if(n % h == 0 && m % w == 0) {
        cout << "N" << '\n';
        return ;
    }

    vector<vector<int>> a(n,vector<int>(m,0));
    cout << "Y\n";
    if(m % w != 0) {
        int ws = - (1e5 * (w - 1) + 1);
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if((j+1)%w==0) {
                    a[i][j] = ws;
                }else {
                    a[i][j] = 1e5;
                }
            }
        }
    } else {
        int ws = - (1e5 * (h - 1) + 1);
        for(int j=0;j<m;j++) {
            for(int i=0;i<n;i++) {
                if((i+1)%h == 0) {
                    a[i][j] = ws;
                } else {
                    a[i][j] = 1e5;
                }
            }
        }
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cout << a[i][j] << " \n"[j==m-1];
        }
    }
}
int main() {
    ios::sync_with_stdio(0),cin.tie(0);
    cout << fixed << setprecision(3);

    int t = 1;
    //cin >> t;
    while(t -- ) {
        slove();
    }

    return 0;
}
