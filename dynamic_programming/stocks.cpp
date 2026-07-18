#include<bits/stdc++.h>
using namespace std;


//DP on Stocks


//Buy and Sell stocks (Only one transaction allowed)
//This problem was already done in arrays, still the code is being attached here
int buySellStocksI_brute(vector<int> arr){
    int n = arr.size();
    int start = 0;
    int profit;
    int maxProfit = INT_MIN;
    for (int i = 1; i < n; i++){
        for (int j = i - 1; j >= 0; j--){
            profit = arr[i] - arr[j];
            maxProfit = max(maxProfit, profit);
        }
    }
    return maxProfit;
}
// Time Complexity is almost O(N*N)
//Space Complexity will be O(1) (constant space)

//Optimal Method
//Keeping the track of min element
int buySellStocksI(vector<int> arr){
    int n = arr.size();
    int minEl = arr[0];
    int profit;
    int maxProfit = 0;
    for (int i = 1; i < n; i++){
        profit = arr[i] - minEl;
        maxProfit = max(maxProfit, profit);
        minEl = min(minEl, arr[i]);
    }
    return maxProfit;
}
//Time Complexity will be O(N)
//Space Complexity will be O(N) (constant space)


//DP on Stocks II
//No limit on transaction, but we must sell the stock we bought, before buying another one
int stocksIIHelper_brute(int idx,int canBuy,vector<int> &arr){
    if(idx==arr.size()) return 0;
    int profit;
    if(canBuy){
        int buy=-arr[idx]+stocksIIHelper_brute(idx+1,0,arr);
        int notBuy=stocksIIHelper_brute(idx+1,1,arr);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]+stocksIIHelper_brute(idx+1,1,arr);
        int notSell=stocksIIHelper_brute(idx+1,0,arr);
        profit=max(sell,notSell);
    }
    return profit;
}

int buySellStocksII_brute(vector<int> &arr){
    return stocksIIHelper_brute(0,1,arr);
}
//Time Complexity will be O(pow(2,n)) (exponential)
//Space Complexity will be O(N)

//Memoization
//We can memoize it using a dp of size n*2
//At each index, we can have the choice of whether we are allowed to buy or not
int stocksIIHelper_mem(int idx,int canBuy,vector<vector<int>> &dp,vector<int> &arr){
    if(idx==arr.size()) return dp[idx][canBuy]=0;
    if(dp[idx][canBuy]!=-1) return dp[idx][canBuy];
    int profit;
    if(canBuy){
        int buy=-arr[idx]+stocksIIHelper_mem(idx+1,0,dp,arr);
        int notBuy=stocksIIHelper_mem(idx+1,1,dp,arr);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]+stocksIIHelper_mem(idx+1,1,dp,arr);
        int notSell=stocksIIHelper_mem(idx+1,0,dp,arr);
        profit=max(sell,notSell);
    }
    return dp[idx][canBuy]=profit;
}

int buySellStocksII_memoization(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n+1,vector<int> (2,-1));
    return stocksIIHelper_mem(0,1,dp,arr);
}
//Time Complexity will be O(2N)
//Space Complexity will be O(2N + N) (N is for recursion stack space)

//Tabulation
//An Important Note : 
//Since in this case the memoization was from 0 to n, therefore the tabulation will be from n to 0
int buySellStocksII_tabulation(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n+1,vector<int> (2,-1));
    dp[n][0]=0;
    dp[n][1]=0;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<2;j++){
            int profit;
            if(j==0){
                int sell=arr[i]+dp[i+1][1];//That's why, since we need dp[i+1], therefore we iterate from the back
                int notSell=dp[i+1][0];
                profit=max(sell,notSell);
            }
            else{
                int buy=-arr[i]+dp[i+1][0];
                int notBuy=dp[i+1][1];
                profit=max(buy,notBuy);
            }
            dp[i][j]=profit;
        }
    }
    return dp[0][1];
}
//Time Complexity will be O(2N)
//Space Complexity will be O(2N)

//We just need four variables in this case
//Space Optimization
int buySellStocksII(vector<int> &arr){
    int n=arr.size();
    vector<long> ahead(2,0);
    vector<long> curr(2,0);
    ahead[0]=ahead[1]=0;
    for(int i=n-1;i>=0;i++){
        for(int j=0;j<2;j++){
            int profit;
            if(j==0){
                int sell=arr[i]+ahead[1];
                int notSell=ahead[0];
                profit=max(sell,notSell);

            }
            else{
                int buy=-arr[i]+ahead[0];
                int notBuy=ahead[1];
                profit=max(buy,notBuy);
            }
            curr[j]=profit;
        }
        ahead=curr;
    }
    return ahead[1];
}
//Time Complexity will be O(2N)
//Space Complexity will be O(4)



//DP On Stocks III
//You can do only two transactions, two buy and two sell
//Also, you need to sell the previously bought stock before you can buy again
int stocksIIIHelper_brute(vector<int> &arr,int idx, int canBuy,int sellCnt){
    if(sellCnt==2) return 0;
    if(idx==arr.size()) return 0;
    int profit;
    if(canBuy){
        int buy=-arr[idx]+stocksIIIHelper_brute(arr,idx+1,0,sellCnt);
        int notBuy=stocksIIIHelper_brute(arr,idx+1,1,sellCnt);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]+stocksIIIHelper_brute(arr,idx+1,1,sellCnt+1);
        int notSell=stocksIIIHelper_brute(arr,idx+1,0,sellCnt);
        profit=max(sell,notSell);
    }
    return profit;
}
int buySellStocksIII_brute(vector<int> &arr){
    return stocksIIIHelper_brute(arr,0,1,0);
}
//Time Complexity will be O(pow(2,n)) (exponential)
//Space Complexity will be O(n)(recursion stack space)

//Memoization
//We need to store 3 things : idx, canBuy and sellCnt => n*2*3
int stocksIIIHelper_memoization(int idx,int canBuy,int sellCnt,vector<vector<vector<int>>> &dp, vector<int> &arr){
    if(sellCnt==2) return 0;
    if(idx==arr.size()) return 0;
    if(dp[idx][canBuy][sellCnt]!=-1) return dp[idx][canBuy][sellCnt];
    int profit;
    if(canBuy){
        int buy=-arr[idx]+stocksIIIHelper_memoization(idx+1,0,sellCnt,dp,arr);
        int notBuy=stocksIIIHelper_memoization(idx+1,1,sellCnt,dp,arr);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]+stocksIIIHelper_memoization(idx+1,1,sellCnt+1,dp,arr);
        int notSell=stocksIIIHelper_memoization(idx+1,0,sellCnt,dp,arr);
        profit=max(sell,notSell);
    }
    return dp[idx][canBuy][sellCnt]=profit;
}
int buySellStocksIII_memoization(vector<int> &arr){
    int n=arr.size();
    vector<vector<vector<int>>> dp(n,vector<vector<int>> (2,vector<int> (3,-1)));
    return stocksIIIHelper_memoization(0,1,0,dp,arr);
}
//Time Complexity will be O(n*2*3)
//Space Complexity will be O(n*2*3)+O(n) recursion stack space

//Tabulation
int buySellStocksIII_tabulation(vector<int> &arr){
    int n=arr.size();
    vector<vector<vector<int>>> dp(n+1,vector<vector<int>> (2,vector<int> (3,-1)));

    //Now write down the base cases
    //This time instead of sellCnt we will use cap, when cap=0, that's the end

    //When cap=0, we return 0 for all 
    for(int i=0;i<=n;i++){
        for(int j=0;j<2;j++){
            dp[i][j][0]=0;
        }
    }

    //For idx==n, buy and cap can be anything
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            dp[n][i][j]=0;
        }
    }

    for(int ind=n-1;ind>=0;ind--){
        for(int buy=0;buy<=1;buy++){
            //We are starting from cap 1 because for cap 0, everyone's value is already set as 0, so there's no need
            for(int cap=1;cap<=2;cap++){
                if(buy){
                    dp[ind][buy][cap]=max(-arr[ind]+dp[ind+1][0][cap],dp[ind+1][1][cap]);
                }
                else{
                    dp[ind][buy][cap]=max(arr[ind]+dp[ind+1][1][cap-1],dp[ind+1][0][cap]);
                }
            }
        }
    }
    return dp[0][1][2];
}

//Space Optimizatin
int buySellStocksIII(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> after(2,vector<int> (3,0));
    vector<vector<int>> curr(2,vector<int> (3,0));

    for(int ind=n-1;ind>=0;ind--){
        for(int buy=0;buy<=1;buy++){
            for(int cap=1;cap<=2;cap++){
                if(buy){
                    curr[buy][cap]=max(-arr[ind]+after[0][cap],after[1][cap]);
                }
                else{
                    curr[buy][cap]=max(arr[ind]+after[1][cap-1],after[0][cap]);
                }
            }
        }
        after=curr;
    }
    return after[1][2];
}
//Time Complexity will be O(N*2*3)
//Space Complexity will be O(6) which is as good as constant space



//DP on Stocks IV
int stocksIVHelper_brute(int idx,int cnt,int k,vector<int> &arr){
    if(idx==arr.size() || cnt==k) return 0;
    int profit;
    if(cnt%2==0){
        int buy=-arr[idx]+stocksIVHelper_brute(idx+1,cnt+1,k,arr);
        int notBuy=stocksIVHelper_brute(idx+1,cnt,k,arr);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]+stocksIVHelper_brute(idx+1,cnt+1,k,arr);
        int notSell=stocksIVHelper_brute(idx+1,cnt,k,arr);
        profit=max(sell,notSell);
    }
    return profit;
}
int buySellStocksIV_brute(vector<int> &arr,int k){
    k=k*2;//Since k is the number of times we can buy stock, therefore total transactions would be 2k
    return stocksIVHelper_brute(0,0,k,arr);
}

//Memoization
int stocksIVHelper_memoization(int idx,int cnt,int k,vector<vector<int>> &dp,vector<int> &arr){
    if(idx==arr.size() || cnt==k) return 0;
    if(dp[idx][cnt]!=-1) return dp[idx][cnt];
    int profit;
    if(cnt%2==0){
        int buy=-arr[idx]+stocksIVHelper_memoization(idx+1,cnt+1,k,dp,arr);
        int notBuy=stocksIVHelper_memoization(idx+1,cnt,k,dp,arr);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]+stocksIVHelper_memoization(idx+1,cnt+1,k,dp,arr);
        int notSell=stocksIVHelper_memoization(idx+1,cnt,k,dp,arr);
        profit=max(sell,notSell);
    }
    return dp[idx][cnt]=profit;
}

int buySellStocksIV_memoization(vector<int> &arr,int k){
    k=k*2;
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (k+1,-1));
    return stocksIVHelper_memoization(0,0,k,dp,arr);
}

//Tabulation 
int buySellStocksIV_tabulation(vector<int> &arr,int k){
    k=k*2;
    int n=arr.size();
    vector<vector<int>> dp(n+1,vector<int> (k+1,0));
    for(int ind=n-1;ind>=0;ind--){
        int profit;
        for(int cnt=k-1;cnt>=0;cnt--){
            if(cnt%2==0){
                int buy=-arr[ind]+dp[ind+1][cnt+1];
                int notBuy=dp[ind+1][cnt];
                profit=max(buy,notBuy);
            }
            else{
                int sell=arr[ind]+dp[ind+1][cnt+1];
                int notSell=dp[ind+1][cnt];
                profit=max(sell,notSell);
            }
            dp[ind][cnt]=profit;
        }
    }
    return dp[0][0];
}

//Space Optimization
int buySellStocksIV(vector<int> &arr,int k){
    k=k*2;
    int n=arr.size();
    vector<int> after(k+1,0);
    vector<int> curr(k+1,0);
    for(int idx=n-1;idx>=0;idx--){
        for(int cnt=k-1;cnt>=0;cnt--){
            if(cnt%2==0) curr[cnt]=max(-arr[idx]+after[cnt+1],after[cnt]);
            else curr[cnt]=max(arr[idx]+after[cnt+1],after[cnt]);
        }
        after=curr;
    }
    return after[0];
}
//Time Complexity will be O(nk)
//Space Complexity will be O(2k)


//DP On Stocks V
//Buying and Selling with cooldown
//We can't buy immediately after selling, unlimited transactions
int stocksVHelper_brute(int idx,int canBuy,vector<int> &arr){
    if(idx>=arr.size()) return 0;
    int profit;
    if(canBuy){
        int buy=-arr[idx]+stocksVHelper_brute(idx+1,0,arr);
        int notBuy=stocksVHelper_brute(idx+1,1,arr);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]+stocksVHelper_brute(idx+2,1,arr);
        int notSell=stocksVHelper_brute(idx+1,0,arr);
        profit=max(sell,notSell);
    }
    return profit;
}
int buySellStocksV_brute(vector<int> &arr){
    return stocksVHelper_brute(0,1,arr);
}
//At each index two calls are made ; buy/skip, sell/skip, therefore total of 2^n calls
//Time Complexity will be O(pow(2,n)) (exponential)
//Space Complexity will be O(n) (just recursion stack space)

//Memoization
int stocksVHelper_memoization(int idx,int canBuy,vector<vector<int>> &dp,vector<int> &arr){
    if(idx>=arr.size()) return 0;
    if(dp[idx][canBuy]!=-1) return dp[idx][canBuy];
    int profit;
    if(canBuy){
        int buy=-arr[idx]+stocksVHelper_memoization(idx+1,0,dp,arr);
        int notBuy=stocksVHelper_memoization(idx+1,1,dp,arr);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]+stocksVHelper_memoization(idx+2,1,dp,arr);
        int notSell=stocksVHelper_memoization(idx+1,0,dp,arr);
        profit=max(sell,notSell);
    }
    return dp[idx][canBuy]=profit;
}
int buySellStocksV_memoization(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (1,-1));
    return stocksVHelper_memoization(0,1,dp,arr);
}
//There are only n*2 different indices that needs to be computed due to memoization
//A DP array of 2n is used and recursion stack space of n is also used
//Time Complexity will be O(2n)
//Space Complexity will be O(2n+n) 

//Tabulation
int buySellStocksV_tabulation(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n+2,vector<int> (2,0));
    for(int i=n-1;i>=0;i--){
        int profit;
        for(int buy=0;buy<=1;buy++){
            if(buy){
                int b=-arr[i]+dp[i+1][0];
                int nb=dp[i+1][1];
                profit=max(b,nb);
            }
            else{
                int s=arr[i]+dp[i+2][1];
                int ns=dp[i+1][0];
                profit=max(s,ns);
            }
            dp[i][buy]=profit;
        }
    }
    return dp[0][1];
}
//Time Complexity will be O(2n)
//Space Complexity will be O(2n+4)

//Space Optimization
int buySellStocksV(vector<int> &arr){
    int n=arr.size();
    vector<int> front2(2,0);
    vector<int> front1(2,0);
    vector<int> curr(2,0);
    for(int i=n-1;i>=0;i--){
        //Instead of running a second loop, we can just write those conditions
        curr[1]=max(-arr[i]+front1[0],front1[1]);
        curr[0]=max(arr[i]+front2[1],front1[0]);
        front2=front1;
        front1=curr;
    }
    return curr[1];
}
//Time Complexity will be O(N)
//Space Complexity will be O(6)



//DP on Stocks VI
//A transaction fee is applied for each transaction
int stocksVIHelper_brute(int idx,int canBuy,vector<int> &arr,int fee){
    if(idx==arr.size()) return 0;
    int profit;
    if(canBuy){
        int buy=-arr[idx]+stocksVIHelper_brute(idx+1,0,arr,fee);
        int notBuy=stocksVIHelper_brute(idx+1,1,arr,fee);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]-fee+stocksVIHelper_brute(idx+1,1,arr,fee);
        int notSell=stocksVIHelper_brute(idx+1,0,arr,fee);
        profit=max(sell,notSell);
    }
    return profit;
}
int buySellStocksVI_brute(vector<int> &arr,int fee){
    return stocksVIHelper_brute(0,1,arr,fee);
}
//At each step we have two options, can buy or can't buy, and there are a total of n such steps
//Recursion stack space is used which is equal to n
//Time Complexity will be O(2^n)
//Space Complexity will be O(n) 

//Memoization
int stocksVIHelper_memoization(int idx,int canBuy,vector<vector<int>> &dp,int fee, vector<int> &arr){
    if(idx==arr.size()) return 0;
    if(dp[idx][canBuy]!=-1) return dp[idx][canBuy];
    int profit;
    if(canBuy){
        int buy=-arr[idx]+stocksVIHelper_memoization(idx+1,0,dp,fee,arr);
        int notBuy=stocksVIHelper_memoization(idx+1,1,dp,fee,arr);
        profit=max(buy,notBuy);
    }
    else{
        int sell=arr[idx]-fee+stocksVIHelper_memoization(idx+1,1,dp,fee,arr);
        int notSell=stocksVIHelper_memoization(idx+1,0,dp,fee,arr);
        profit=max(sell,notSell);
    }
    return dp[idx][canBuy]=profit;
}
int buySellStocksVI_memoization(vector<int> &arr,int fee){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (2,-1));
    return stocksVIHelper_memoization(0,1,dp,fee,arr);
}
//Time Complexity will be O(2N)
//Space Complexity will be O(N+2N)

//Tabulation
int buySellStocksVI_tabulation(vector<int> &arr,int fee){
    int n=arr.size();
    vector<vector<int>> dp(n+1,vector<int> (2,0));
    for(int idx=n-1;idx>=0;idx--){
        for(int buy=0;buy<=1;buy++){
            int profit;
            if(buy){
                int b=-arr[idx]+dp[idx+1][0];
                int nb=dp[idx+1][1];
                profit=max(b,nb);
            }
            else{
                int s=arr[idx]-fee+dp[idx+1][1];
                int ns=dp[idx+1][0];
                profit=max(s,ns);
            }
            dp[idx][buy]=profit;
        }
    }
    return dp[0][1];
}
//Time Complexity will be O(2n)
//Space Complexity will be O(2n)

//Space Optimization
int buySellStocksVI_spaceOptimized(vector<int> &arr,int fee){
    int n=arr.size();
    vector<int> curr(2,0);
    vector<int> above(2,0);
    for(int idx=n-1;idx>=0;idx--){

        //We can also use the earlier approaches, by running a loop from buy=0 to buy=1, but this code is more cleaner(both codes work in same time)
        curr[0]=max(arr[idx]-fee+above[1],above[0]);
        curr[1]=max(-arr[idx]+above[0],above[1]);
        above=curr;
    }
    return curr[1];
}
//Time Complexity will be O(2n)
//Space Complexity will be O(4)


int main(){
    return 0;
}
