#include <iostream>
#include <vector>

using namespace std;

/*-----------------------------------

动态规划
状态a(i,j)表示考虑前i个农场，当前拥有的作物总单位为j时的最低成本
这道题有个性质，比如前i个农场一共需要i个单位的作物
假设j＞i，即有多出来的部分，肯定是堆到第i个农场给之后的农场用
同理，如果j＜i，作物不够,需要从之后的农场拿
那么本质上也是之后的农场先发给第i个农场，然后第i个再发给前面不够的
可以视作前i个农场把不够的都从第i个农场“借”，然后第i个农场持有负数单位的作物，之后从后面的农场补回来
因此转移方程里，j如果不等于i，多出来的或者不够的那部分作物，都需要经过d[i-1]来运输，所以运输成本会写成d[i-1] * 差的绝对值

                {  a[i-1][j-2] + d[i-1] * abs(i-1-(j-2)) + 2 * g(i)
a[i][j] =   min {  a[i-1][j-1] + d[i-1] * abs(i-1-(j-1)) + g(i)
                {  a[i-1][j] + d[i-1] * abs(i-1-j)

优化：
如果使用二维数组存储所有 N * N 个状态，最大达到 200000 * 200000 个int的内存空间
每次递推只与前一步有关，前面的状态用过后不用再保存，节省空间
使用一维数组替代二维数组，同时注意更新的次序是逆序更新

Example：
输入：   4
        1 2 3
        1 1 100 100
每步更新：
0  1  2  0  0   0   0   0   0
0  1  2  3  5   0   0   0   0
0  3  2  5  9   205 209 0   0
0  9  5  5  12  112 212 411 418

-----------------------------------*/

void dp(vector<int>& a, int n, vector<int>& g, vector<int>& d) {
    for(int i = 2; i <= n; i++) {
        for(int j = i * 2; j >= 1; j--) {
            // 边界条件判断是否存在
            int num1 = INT_MAX;
            if(j <= 2*(i-1))
                num1 = a[j] + d[i-1] * abs(i-1-j);
            
            int num2 = INT_MAX;
            if(j <= 2*(i-1))
                num2 = a[j-1] + d[i-1] * abs(i-1-(j-1)) + g[i];

            int num3 = INT_MAX;
            if(j - 2 >= 0)
                num3 = a[j-2] + d[i-1] * abs(i-1-(j-2)) + 2 * g[i];

            a[j] = min(num1 > num2 ? num2 : num1, num3);
        }
    }
}




int main(int argc, char* argv[]) {
    int n = 0;
    cin >> n;

    vector<int> a(2 * n + 1);

    vector<int> d(n);
    d[0] = 0;
    for(int i = 1; i < n; i++) {
        cin >> d[i];
    }

    vector<int> g(n + 1);
    g[0] = 0;
    for(int i = 1; i <= n; i++) {
        cin >> g[i];
    }

    a[0] = 0, a[1] = g[1], a[2] = 2 * g[1];
    dp(a, n, g, d);

    
}