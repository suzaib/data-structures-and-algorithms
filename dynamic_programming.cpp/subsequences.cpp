#include<bits/stdc++.h>
using namespace std;

//DP On Subsequences


//Subset Sum equal to target
//Return true or false if there exists a single subset with sum K
bool fxEOSS_brute(int idx,int target,vector<int> arr){
    if(target==0) return true;
    if(idx==0) return arr[idx]==target;

    bool pick=false;
    if(target>=arr[idx]) pick=fxEOSS_brute(idx-1,target-arr[idx],arr);
    bool notPick=fxEOSS_brute(idx-1,target,arr);
    return (pick || notPick);
}
bool existenceOfSubsetSum_brute(vector<int> arr,int k){
    int n=arr.size();
    return fxEOSS_brute(n-1,k,arr);
}
//Recursion time will be pow(2,n) since every step we have two options, take or not take
//Therefore time complexity will be O(2*n)
//Space Complexity will be O(n)

//Memoization
bool fxEOSS_mem(int idx,int target,vector<int> &arr,vector<vector<int>> &dp){
    if(dp[idx][target]!=-1) return dp[idx][target];
    if(target==0) return dp[idx][target]=1;
    if(idx==0) return dp[idx][target]=(arr[idx]==target);
    bool pick=false;
    if(target>=arr[idx]) pick=fxEOSS_mem(idx-1,target-arr[idx],arr,dp);
    bool notPick=fxEOSS_mem(idx-1,target,arr,dp);
    return dp[idx][target]=(pick || notPick);
}
bool existenceOfSubsetSum_mem(vector<int> arr,int k){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (k+1,-1));
    return fxEOSS_mem(n-1,k,arr,dp);
}
//Time Complexity will be O(n*target)
//Space Complexity will be O(n*target + n)(n is due to recursion stack space)

//Tabulation
bool existenceOfSubsetSum_tabulation(vector<int> arr,int target){
    int n=arr.size();
    vector<vector<bool>> dp(n,vector<bool>(target+1,0));
    for(int i=0;i<n;i++) dp[i][0]=true;
    dp[0][arr[0]]=true;
    for(int i=1;i<n;i++){
        for(int j=1;j<=target;j++){
            bool notTake=dp[i-1][j];
            bool take=false;
            if(arr[i]<=j) take=dp[i-1][j-arr[i]];
            dp[i][j]=(take || notTake);
        }
    }
    return dp[n-1][target];
}
//Time Complexity will be O(MN)
//Space Complexity will be O(MN)

//Space Optimization
bool existenceOfSubsetSum_spaceOptimized(vector<int> arr,int k){
    int n=arr.size();
    vector<bool> prev(k+1,0);
    vector<bool> curr(k+1,0);
    prev[0]=curr[0]=true;
    if(arr[0]<=k) prev[arr[0]]=true;
    for(int ind=1;ind<n;ind++){
        for(int target=1;target<=k;target++){
            bool notTake=prev[target];
            bool take=false;
            if(arr[ind]<=target) take=prev[target-arr[ind]];
            curr[target]=(take || notTake);
        }
        prev=curr;
    }
    return prev[k];
}
//Time Complexity will be O(MN)
//Space Complexity will be O(2M)

//Further Optimization
//Using only one array
bool existenceOfSubsetSum(vector<int> &arr,int k){
    int n=arr.size();
    vector<int> dp(k+1,0);
    dp[0]=true;
    if(arr[0]<=k) dp[arr[0]]=true;
    for(int idx=1;idx<n;idx++){
        for(int target=k;target>=0;target--){
            if(arr[idx]<=target) dp[target]=(dp[target] || dp[target-arr[idx]]);
        }
    }
    return dp[k];
}
//Time Complexity will be O(MN)
//Space Complexity will be O(M)




//Partition Equal Subset Sum
//Check whether or not you can form two subsequences(exhaustive) which will have the same sum
bool partitionEqualSubsetSum(vector<int> &arr){
    int n=arr.size();
    
    //If the sum of all the elements is odd, then the answer will be false
    int totalSum=accumulate(arr.begin(),arr.end(),0);
    if(totalSum%2!=0) return false;

    //We just now need to find whether a subset exists with half of the total sum
    return existenceOfSubsetSum(arr,totalSum/2);
}
//Time Complexity will be O(MN + N)
//Space Complexity will be O(2M)


//DP 16
//Partition a set into two subsets with minimum absolute difference
//Brute Force
//Start from half of the sum and see if you can find a subset with the closest sum to half
int minDiffSubsets_brute(vector<int> &arr){
    int n=arr.size();
    int totalSum=accumulate(arr.begin(),arr.end(),0);
    for(int sum=totalSum/2;sum>=0;sum--){
        if(existenceOfSubsetSum(arr,sum)){
            int x=sum;
            int y=totalSum-sum;
            return abs(x-y);
        }
    }
    return 0;
}
//The loop will run for (k/2)*(mn) times, here k is the total sum of array
//Time Complexity will be O(MN)*O(K/2)
//Space Complexity will be O(2M)

//Better Approach 
//The dp we form in tabulation stores every index and sum combination that can be formed
//Therefore we should simply generate that dp
int minDiffSubsets_better(vector<int> &arr){
    int n=arr.size();
    int totalSum=accumulate(arr.begin(),arr.end(),0);
    vector<vector<int>> dp(n,vector<int> (totalSum+1,0));
    for(int i=0;i<n;i++) dp[i][0]=true;
    dp[0][arr[0]]=true;
    for(int i=1;i<n;i++){
        for(int j=1;j<=totalSum;j++){
            bool pick=false;
            if(arr[i]<=j) pick=dp[i-1][j-arr[i]];
            bool notPick=dp[i-1][j];
            dp[i][j]=(notPick || pick);
        }
    }
    
    int minSum=INT_MAX;
    for(int i=0;i<=totalSum/2;i++){
        if(dp[n-1][i]){
            int x=i;
            int y=totalSum-i;
            minSum=min(minSum,abs(x-y));
        }
    }
    return minSum;
}
//Time Complexity will be O(MN + M/2)
//Space Complexity will be O(MN)

//Optimal Method
//Using the Space Optimization Approach
int minDiffSubsets_spaceOptimized(vector<int> &arr){
    int n=arr.size();
    int totalSum=accumulate(arr.begin(),arr.end(),0);
    vector<int> prev(totalSum+1,0);
    vector<int> curr(totalSum+1,0);
    prev[0]=curr[0]=1;
    prev[arr[0]]=1;
    for(int i=1;i<n;i++){
        for(int j=1;j<=totalSum;j++){
            bool pick=false;
            if(arr[i]<=j) pick=prev[j-arr[i]];
            bool notPick=prev[j];
            curr[j]=(pick || notPick);
        }
        prev=curr;
    }

    for(int i=totalSum/2;i>=0;i--){
        if(curr[i]) return abs(i-(totalSum-i));
    }
    return 0;
}
//The loop runs for n*totalSum(k)
//Time Complexity will be O(NK)
//Space Complexity will be O(2K)

//Further Optimization
int minDiffSubsets(vector<int> &arr){
    int n=arr.size();
    int totalSum=accumulate(arr.begin(),arr.end(),0);
    vector<int> dp(totalSum+1,0);
    dp[0]=true;
    dp[arr[0]]=true;
    for(int idx=1;idx<n;idx++){
        for(int target=totalSum;target>=arr[idx];target--) dp[target]=(dp[target] || dp[target-arr[idx]]);
    }

    for(int i=totalSum/2;i>=0;i--){
        if(dp[i]) return abs(i-(totalSum-i));
    }
    return 0;
}
//Time Complexity will be O(KN)
//Space Compexity will be O(K)



//Number of subsets with the given sum
//Brute Force 
//Same as in recursion where we count number of subsequences
int noOfSubsetsWithSumKHelper_brute(int idx,int target,vector<int> &arr){
    if(idx==0){
        if(arr[idx]==0 && target==0) return 2;
        if(target==0 || arr[idx]==target) return 1;
        return 0;
    }
    int pick=0;
    if(target>=arr[idx]) pick=noOfSubsetsWithSumKHelper_brute(idx-1,target-arr[idx],arr);
    int notPick=noOfSubsetsWithSumKHelper_brute(idx-1,target,arr);
    return pick+notPick;
}
int noOfSubsetsWithSumK_brute(vector<int> &arr,int k){
    int n=arr.size();
    return noOfSubsetsWithSumKHelper_brute(n-1,k,arr);
}
//For each element we have a choice if we want to pick or not Pick, therefore 2^n ways
//A stack space of n is used, since there are total of n levels in recursion stack
//Time Complexity will be O(2^n)
//Space Complexity will be O(n)

//Memoization
int noOfSubsetsWithSumKHelper_memoization(int idx,int target,vector<vector<int>> &dp,vector<int> &arr){
    if(dp[idx][target]!=-1) return dp[idx][target];
    if(idx==0){
        if(arr[idx]==0 && target==0) return dp[idx][target]=2;
        if(target==0 || arr[idx]==target) return dp[idx][target]=1;
        return dp[idx][target]=0;
    }

    int pick=0;
    if(arr[idx]<=target) pick=noOfSubsetsWithSumKHelper_memoization(idx-1,target-arr[idx],dp,arr);
    int notPick=noOfSubsetsWithSumKHelper_memoization(idx-1,target,dp,arr);
    return dp[idx][target]=(pick+notPick);
}
int noOfSubsetsWithSumK_memoization(vector<int> &arr,int k){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (k+1,-1));
    return noOfSubsetsWithSumKHelper_memoization(n-1,k,dp,arr);
}
//The code runs for N*K times in total
//Space occupied will be the dp (N*K) along with N recursion stack space
//Time Complexity will be O(NK)
//Space Complexity will be O(NK+N)

//Tabulation
int noOfSubsetsWithSumK_tabulation(vector<int> &arr,int k){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (k+1,0));
    for(int i=0;i<=k;i++){
        if(i==0 && arr[0]==0) dp[0][i]=2;
        else if(i==0 || arr[0]==i) dp[0][i]=1;
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<=k;j++){
            int pick=0;
            if(arr[i]<=j) pick=dp[i-1][j-arr[i]];
            int notPick=dp[i-1][j];
            dp[i][j]=(pick+notPick);
        }
    }
    return dp[n-1][k];
}
//Time Complexity will be O(NK)
//Space Complexity will be O(NK)

//Space Optimization
//This is the most optimal method in this case
//The One array approach won't work since we have 0s in this case
int noOfSubsetsWithSumK(vector<int> &arr,int k){
    int n=arr.size();
    vector<int> prev(k+1,0);
    if(arr[0]==0) prev[0]=2;
    else{
        prev[0]=1;
        if(arr[0]<=k) prev[arr[0]]=1;

    }
    for(int i=1;i<n;i++){
        vector<int> curr(k+1,0);
        for(int j=0;j<=k;j++){
            int pick=0;
            if(arr[i]<=j) pick=prev[j-arr[i]];
            int notPick=prev[j];
            curr[j]=pick+notPick;
        }
        prev=curr;
    }
    return prev[k];
}
//Time Complexity will be O(NK)
//Space Complexity will be O(2K)


//Partitions With Given Difference
//Divide into two sets s1 and s2 such that s1-s2=d (s1>s2)
//Method
//Since we know s1+s2=t(total sum)
//Solving the two equations, we get s1=(t+d)/2 and s2=(t-d)/2
//Now we just need to find the number of subsets whose sum is (t+d)/2
//Also the constraint is that all elements >=0 so s1 will definitely be greater(as none of t or d is negative) 
//Edge Cases:
    //What if s2=t-d<0, we must ensure that t>=d atleast
    //Also since we are diving by 2, we must ensure t-d or t+d must be even
//For obvious reason we will work on t-d (s2) since we can study both edge cases with s2
//We will just apply the previous question's solution
//Also since the answer can be too large, we have to return it modulo 10^9+7
int partitionsWithGivenDiff(vector<int> &arr,int d){
    int mod=(1e9+7);
    int n=arr.size();
    int t=accumulate(arr.begin(),arr.end(),0);
    if(t<d || (t-d)%2!=0) return 0;
    return (noOfSubsetsWithSumK(arr,((t-d)/2)))%mod;
}
//Time Complexity will be O(NK + N)
//Space Complexity will be O(K)


//O/1 Knapsack Problem
//See the problem description first
//Brute Force
int knapsackHelper_brute(int idx,int bagWt,vector<int> &weights,vector<int> &val){
    if(idx==0){
        if(weights[0]<=bagWt) return val[0];
        else return 0;
    }
    int pick=0;
    if(bagWt>=weights[idx]) pick=val[idx]+knapsackHelper_brute(idx-1,bagWt-weights[idx],weights,val);
    int notPick=knapsackHelper_brute(idx-1,bagWt,weights,val);
    return max(pick,notPick);
}
int knapsack_brute(vector<int> &weight,vector<int> &val,int maxWt){
    int n=val.size();
    return knapsackHelper_brute(n-1,maxWt,weight,val);
}
//Each element can either be picked or not picked, therefore the code will run about 2^n times
//A recursion stack space of n will be used as well
//Time Complexity will be O(2^n)
//Space Complexity will be O(n)

//Memoization
int knapsackHelper_memoization(int idx,int bagWt,vector<int> &weights,vector<int> &val,vector<vector<int>> &dp){
    if(dp[idx][bagWt]!=-1) return dp[idx][bagWt];
    if(idx==0){
        if(bagWt>=weights[idx]) return dp[idx][bagWt]=val[0];
        else return dp[idx][bagWt]=0;
    }
    int pick=0;
    if(bagWt>=weights[idx]) pick=val[idx]+knapsackHelper_memoization(idx-1,bagWt-weights[idx],weights,val,dp);
    int notPick=knapsackHelper_memoization(idx-1,bagWt,weights,val,dp);
    return dp[idx][bagWt]=max(pick,notPick);
}
int knapsack_memoization(vector<int> &weights,vector<int> &val,int maxWt){
    int n=val.size();
    vector<vector<int>> dp(n,vector<int> (maxWt+1,-1));
    return knapsackHelper_memoization(n-1,maxWt,weights,val,dp);
}
//The code will eventually run for n*(bagWt+1) at most, since these many states are to be calculated
//The space occupied will be due to recursion stack space (n) and dp grid(n*maxWt)
//Let's take maxWt as m
//Time Complexity will be O(nm)
//Space Complexity will be O(nm+n)

//Tabulation
int knapsack_tabulation(vector<int> &weights,vector<int> &val,int maxWt){
    int n=val.size();
    vector<vector<int>> dp(n,vector<int> (maxWt+1,0));
    for(int i=0;i<=maxWt;i++){
        if(i>=weights[0]) dp[0][i]=val[0];
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=maxWt;j++){
            int pick=0;
            if(j>=weights[i]) pick=val[i]+dp[i-1][j-weights[i]];
            int notPick=dp[i-1][j];
            dp[i][j]=max(pick,notPick);
        }
    }
    return dp[n-1][maxWt];
}
//Time Complexity will be O(mn)
//Space Complexity will be O(mn)

//Space Optimization
int knapsack_spaceOptimization(vector<int> &weights,vector<int> &val,int maxWt){
    int n=val.size();
    vector<int> prev(maxWt+1,0);
    vector<int> curr(maxWt+1,0);
    for(int i=0;i<=maxWt;i++){
        if(i>=weights[0]) prev[i]=val[0];
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=maxWt;j++){
            int pick=0;
            if(j>=weights[i]) pick=val[i]+prev[j-weights[i]];
            int notPick=prev[j];
            curr[j]=max(pick,notPick);
        }
        prev=curr;
    }
    return prev[maxWt];
}
//Time Complexity will be O(mn)
//Space Complexity will be O(2m)

//Further Optimization
int knapsack(vector<int> &weights,vector<int> &val,int maxWt){
    int n=val.size();
    vector<int> dp(maxWt+1,0);
    for(int i=0;i<=maxWt;i++){
        if(i>=weights[0]) dp[i]=val[0];
    }
    for(int i=1;i<n;i++){
        for(int j=maxWt;j>=1;j--){
            int pick=0;
            if(j>=weights[i]) pick=val[i]+dp[j-weights[i]];
            int notPick=dp[j];
            dp[j]=max(pick,notPick);
        }
    }
    return dp[maxWt];
}
//Time Complexity will be O(mn)
//Space Complexity will be O(m)


//Minimum Coins
//In this problem, we are allowed to use a coin multiple times(unbounded knapsack), therefore in the pick case, we do not reduce index, instead we remain at the same index to see if that index can be picked again or not
//In case the target can't be achieved by the given denominations, return -1
int minCoinsHelper_brute(int idx,int target,vector<int> &coins){
    if(idx==0){
        if(target%coins[idx]==0) return (target/(coins[idx]));
        else return 1e9;
    }
    if(target==0) return 0;
    int pick=INT_MAX;
    if(target>=coins[idx]) pick=1+minCoinsHelper_brute(idx,target-coins[idx],coins);
    int notPick=minCoinsHelper_brute(idx-1,target,coins);
    return min(pick,notPick);
}

int minCoins_brute(vector<int> &coins,int target){
    int n=coins.size();
    int ans=minCoinsHelper_brute(n-1,target,coins);
    if(ans>=1e9) return -1;
    return ans;
}
//At each element we have two choices, either to pick that particular coin or not, that is two choices, and hence for a total of n elements the code will run for 2^n times
//Except, however, in this case we may keep standing at the same index even after picking up the element
//Time Complexity in such cases can't be calculated that easily so just say it is exponential
//A recursion stack space of size n is occupied usually but this time the recursion can go till k times assuming the worst case where there is single coin of denomination 1
//Time Complexity will be exponential
//Space Compelexity will be O(k)

//Memoization
int minCoinsHelper_memoization(int idx,int target,vector<vector<int>> &dp,vector<int> &coins){
    if(dp[idx][target]!=-1) return dp[idx][target];
    if(idx==0){
        if(target%coins[idx]==0) return dp[idx][target]=(target/(coins[idx]));
        else return dp[idx][target]=1e9;
    }
    if(target==0) return dp[idx][target]=0;
    int pick=INT_MAX;
    if(target>=coins[idx]) pick=1+minCoinsHelper_memoization(idx,target-coins[idx],dp,coins);
    int notPick=minCoinsHelper_memoization(idx-1,target,dp,coins);
    return dp[idx][target]=min(pick,notPick);
}
int minCoins_memoization(vector<int> &coins,int target){
    int n=coins.size();
    vector<vector<int>> dp(n,vector<int> (target+1,-1));
    int ans=minCoinsHelper_memoization(n-1,target,dp,coins);
    if(ans>=1e9) return -1;
    return ans;
}
//Consider the target to be k, then the code runs in total to calculate all the elements of dp grid, which are equal to nk
//Time Complexity will be O(nk)
//Space Complexity will be O(nk+n)

//Tabulation
int minCoins_tabulation(vector<int> &coins,int target){
    int n=coins.size();
    vector<vector<int>> dp(n,vector<int>(target+1,0));
    for(int i=0;i<=target;i++){
        if(i%coins[0]==0) dp[0][i]=i/coins[0];
        else dp[0][i]=1e9;
    }

    for(int i=1;i<n;i++){
        for(int j=1;j<=target;j++){
            int pick=1e9;
            if(j>=coins[i]) pick=1+dp[i][j-coins[i]];
            int notPick=dp[i-1][j];
            dp[i][j]=min(pick,notPick);
        }
    }
    int ans=dp[n-1][target];
    if(ans>=1e9) return -1;
    return ans;
}
//Time Complexity will be O(nk)
//Space Complexity will be O(nk)

//Space Optimization
int minCoins_spaceOptimization(vector<int> &coins,int target){
    int n=coins.size();
    vector<int> prev(target+1,0);
    vector<int> curr(target+1,0);
    for(int i=0;i<=target;i++){
        if(i%coins[0]==0) prev[i]=i/coins[0];
        else prev[i]=1e9;
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<=target;j++){
            int pick=1e9;
            if(j>=coins[i]) pick=1+curr[j-coins[i]];
            int notPick=prev[j];
            curr[j]=min(pick,notPick);
        }
        prev=curr;
    }
    int ans=prev[target];
    if(ans>=1e9) return -1;
    return ans;
}
//Time Complexity will be O(nk)
//Space Complexity will be O(2k)

//Further Optimization
int minCoins(vector<int> &coins,int target){
    int n=coins.size();
    vector<int> dp(target+1,0);
    for(int i=0;i<=target;i++){
        if(i%coins[0]==0) dp[i]=i/coins[0];
        else dp[i]=1e9;
    }

    for(int i=1;i<n;i++){
        for(int j=1;j<=target;j++){
            int pick=1e9;
            if(j>=coins[i]) pick=1+dp[j-coins[i]];
            int notPick=dp[j];
            dp[j]=min(pick,notPick);
        }
    }
    return (dp[target]>=1e9? -1:dp[target]);
}
//Time Complexity will be O(nk)
//Space Complexity will be O(k)


//Target Sum
//Read the question by video, the intuition is a bit difficult to get but the question is very easy
//We would need to use the partitions with given diff question to solve this
//Therefore we are simply using that question's solution, that's all
int targetSum(vector<int> &arr,int target){
    return partitionsWithGivenDiff(arr,target);
}
//Time Complexity will be O(NK + N)
//Space Complexity will be O(K)


//Coin Change II
//Number of ways we can make the target, we can use a coin any number of times
//Therefore in such cases, even when we pick the element, we should not move the index
//Brute Force
int coinChangeIIHelper_brute(int idx,int target,vector<int> &arr){
    if(target==0) return 1;
    if(idx==0) return (target%arr[idx]==0);
    int pick=0;
    if(target>=arr[idx]) pick=coinChangeIIHelper_brute(idx,target-arr[idx],arr);
    int notPick=coinChangeIIHelper_brute(idx-1,target,arr);
    return (pick+notPick);
}
int coinChangeII_brute(vector<int> &arr,int k){
    int n=arr.size();
    return coinChangeIIHelper_brute(n-1,k,arr);
}
//Each element has two choices, either to get picked or not picked
//On top of that a single element can be picked multiple times
//Estimating time complexitty in such cases is quite complex
//A recursion stack space of n is used as well
//Time Complexity will be Exponential
//Space Complexity will be O(n)

//Memoization
int coinChangeIIHelper_memoization(int idx,int target,vector<vector<int>> &dp,vector<int> &arr){
    if(dp[idx][target]!=-1) return dp[idx][target];
    if(target==0) return dp[idx][target]=1;
    if(idx==0) return dp[idx][target]=(target%arr[idx]==0);
    int pick=0;
    if(target>=arr[idx]) pick=coinChangeIIHelper_memoization(idx,target-arr[idx],dp,arr);
    int notPick=coinChangeIIHelper_memoization(idx-1,target,dp,arr);
    return dp[idx][target]=(pick+notPick);
}
int coinChangeII_memoization(vector<int> &arr,int k){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (k+1,-1));
    return coinChangeIIHelper_memoization(n-1,k,dp,arr);
}
//The code runs to fill all dp states, which are n*k in total
//The dp table is used, which takes a space of n*k, also an extra recursion stack space is needed
//Time Complexity will be O(nk)
//Space Complexity will be O(nk+n)

//Tabulation 
int coinChangeII_tabulation(vector<int> &arr,int k){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (k+1,0));
    for(int i=0;i<n;i++) dp[i][0]=1;
    for(int i=0;i<=k;i++) dp[0][i]=(i%arr[0]==0);
    for(int i=1;i<n;i++){
        for(int j=1;j<=k;j++){
            int pick=0;
            if(j>=arr[i]) pick=dp[i][j-arr[i]];
            int notPick=dp[i-1][j];
            dp[i][j]=(pick+notPick);
        }
    }
    return dp[n-1][k];
}
//Two loops at the start running n and k times
//Then two nested loop running for a total of nk times
//Space is occupied due to dp table taking up nk space
//Time Complexity will be O(nk+n+k)
//Space Complexity will be O(nk)

//Space Optimisation
int coinChangeII_spaceOptimization(vector<int> &arr,int k){
    int n=arr.size();
    vector<int> curr(k+1,0);
    vector<int> prev(k+1,0);
    for(int i=0;i<=k;i++) prev[i]=(i%arr[0]==0);
    for(int i=1;i<n;i++){
        for(int j=0;j<=k;j++){
            int pick=0;
            if(j>=arr[i]) pick=curr[j-arr[i]];
            int notPick=prev[j];
            curr[j]=(pick+notPick);
        }
        prev=curr;
    }
    return prev[k];
}
//One loop at the top running for k times
//Two nested loops which run for a total of nk times
//Two array occupy space of 2k
//Time Complexity will be O(nk+k)
//Space Complexity will be O(2k)

//Further Optimization to single array
int coinChangeII(vector<int> &arr,int k){
    int n=arr.size();
    vector<int> dp(k+1,0);
    for(int i=0;i<=k;i++) dp[i]=(i%arr[0]==0);
    for(int i=1;i<n;i++){
        for(int j=0;j<=k;j++){
            int pick=0;
            if(j>=arr[i]) pick=dp[j-arr[i]];
            int notPick=dp[j];
            dp[j]=(pick+notPick);
        }
    }
    return dp[k];
}
//One loop at start which takes k time
//One nested loop which takes a total of nk time
//Space is occupied due to the dp array of k size
//Time Complexity will be O(nk+k)
//Space Complexity will be O(k)


//Unbounded Knapsack
//Similar to 0/1 Knapsack but this time we have an unlimited supply of items
int unboundedKnapsackHelper_brute(int idx,int maxWt,vector<int> &wt,vector<int> &val){
    if(maxWt==0) return 0;
    if(idx==0){
        int k=maxWt/wt[idx];
        return val[idx]*k;
    }
    int take=0;
    if(maxWt>=wt[idx]) take=val[idx]+unboundedKnapsackHelper_brute(idx,maxWt-wt[idx],wt,val);
    int notTake=unboundedKnapsackHelper_brute(idx-1,maxWt,wt,val);
    return max(take,notTake);
}
int unboundedKnapsack_brute(int maxWt,vector<int> &wt,vector<int> &val){
    int n=wt.size();
    return unboundedKnapsackHelper_brute(n-1,maxWt,wt,val);
}
//The code will run for exponential time
//A recursion stack space will be used for the problem which will be equal to W(max wt)(consider an item has wt 1, in that case the depth of recursion stack will be equal to maxWt)
//Time Complexity will be exponential
//Space Complexity will be O(W)

//Memoization
int unboundedKnapsackHelper_memoization(int idx,int maxWt,vector<int> &wt,vector<int> &val,vector<vector<int>> &dp){
    if(dp[idx][maxWt]!=-1) return dp[idx][maxWt];
    if(maxWt==0) return 0;
    if(idx==0){
        int k=maxWt/wt[idx];
        return dp[idx][maxWt]=val[idx]*k;
    }
    int take=0;
    if(maxWt>=wt[idx]) take=val[idx]+unboundedKnapsackHelper_memoization(idx,maxWt-wt[idx],wt,val,dp);
    int notTake=unboundedKnapsackHelper_memoization(idx-1,maxWt,wt,val,dp);
    return dp[idx][maxWt]=max(take,notTake);
}
int unboundedKnapsack_memoization(int maxWt,vector<int> &wt,vector<int> &val){
    int n=wt.size();
    vector<vector<int>> dp(n,vector<int> (maxWt+1,-1));
    return unboundedKnapsackHelper_memoization(n-1,maxWt,wt,val,dp);
}
//The code runs to fill all the dp states which are n*w in total
//The code takes space for dp table and the recursion stack space of W is also used
//Time Complexity will be O(nw)
//Space Complexity will be O(nw+w)

//Tabulation
int unboundedKnapsack_tabulation(int maxWt,vector<int> &wt,vector<int> &val){
    int n=wt.size();
    vector<vector<int>> dp(n,vector<int> (maxWt+1,0));
    for(int i=0;i<=maxWt;i++){
        int k=i/wt[0];
        dp[0][i]=val[0]*k;
    }

    for(int i=1;i<n;i++){
        for(int j=0;j<=maxWt;j++){
            int take=0;
            if(j>=wt[i]) take=val[i]+dp[i][j-wt[i]];
            int notTake=dp[i-1][j];
            dp[i][j]=max(take,notTake);
        }
    }
    return dp[n-1][maxWt];
}
//The code runs for two nested loops which take nw in total
//There is also another loop at the top which runs for w time
//Space is occupied by the dp array of nw size
//Time Complexity will be O(nw+w)
//Space Complexity will be O(nw)
//DP On Strings

//Space Optimisation
int unboundedKnapsack_spaceOptimisation(int maxWt,vector<int> &wt,vector<int> &val){
    int n=wt.size();
    vector<int> prev(maxWt+1,0);
    for(int i=0;i<=maxWt;i++){
        int k=(i/wt[0]);
        prev[i]=val[0]*k;
    }

    for(int i=1;i<n;i++){
        vector<int> curr(maxWt+1,0);
        for(int j=0;j<=maxWt;j++){
            int take=0;
            if(j>=wt[i]) take=val[i]+curr[j-wt[i]];
            int notTake=prev[j];
            curr[j]=max(take,notTake);
        }
        prev=curr;
    }
    return prev[maxWt];
}
//The code runs for a nested loop which takes a time nw and another loop at the start which takes a time of w
//Space is occupied by two arrays of w size
//Time Complexity will be O(nw+w)
//Space Complexity will be O(2w)

//Further Optimisation
//In such cases we can also optimise the loop itself
int unboundedKnapsack(int maxWt,vector<int> &wt,vector<int> &val){
    int n=wt.size();
    vector<int> dp(maxWt+1,0);
    for(int i=0;i<=maxWt;i++){
        int k=(i/wt[0]);
        dp[i]=val[0]*k;
    }

    for(int i=1;i<n;i++){
        for(int j=wt[i];j<=maxWt;j++){
            dp[j]=max(dp[j],val[i]+dp[j-wt[i]]);
        }
    }
    return dp[maxWt];
}
//The code runs two loop, one takes w time and the other is a nested loop taking a time of nw
//A dp array is used which takes w size
//Time Complexity will be O(nw+w)
//Space Complexity will be O(w)


//Rod Cutting Problem
int rodCuttingHelper_brute(int pieceLength,int reqLength,vector<int> &cost){
    if(pieceLength==0) return 0;
    if(pieceLength==1) return reqLength*cost[0];
    int notTake=0+rodCuttingHelper_brute(pieceLength-1,reqLength,cost);
    int take=INT_MIN;
    if(pieceLength<=reqLength) take=cost[pieceLength-1]+rodCuttingHelper_brute(pieceLength,reqLength-pieceLength,cost);
    return max(take,notTake);
}
int rodCutting_brute(int n,vector<int> &cost){
    return rodCuttingHelper_brute(n,n,cost);
}
//The code will run exponentially
//Space will be used by recursion stack which will be of size n
//Time Complexity will be exponential
//Space Complexity will be O(n)

//Memoization
int rodCuttingHelper_memoization(int pieceLength,int reqLength,vector<int> &cost,vector<vector<int>> &dp){
    if(dp[pieceLength][reqLength]!=-1) return dp[pieceLength][reqLength];
    if(pieceLength==0) return dp[pieceLength][reqLength]=0;
    if(pieceLength==1) return dp[pieceLength][reqLength]=reqLength*cost[0];
    int notTake=0+rodCuttingHelper_memoization(pieceLength-1,reqLength,cost,dp);
    int take=INT_MIN;
    if(pieceLength<=reqLength) take=cost[pieceLength-1]+rodCuttingHelper_memoization(pieceLength,reqLength-pieceLength,cost,dp);
    return dp[pieceLength][reqLength]=max(take,notTake);
}
int rodCutting_memoization(int n,vector<int> &cost){
    vector<vector<int>> dp(n+1,vector<int> (n+1,-1));
    return rodCuttingHelper_memoization(n,n,cost,dp);
}
//The code runs to fill all dp states which are n*n
//Space is occupied due to the dp array and the recursion stack
//Time Complexity will be O(n2)
//Space Complexity will be O(n2+n)

//Tabulation
int rodCutting_tabulation(int n,vector<int> &cost){
    vector<vector<int>> dp(n+1,vector<int> (n+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int notTake=dp[i-1][j];
            int take=(j>=i? cost[i-1]+dp[i][j-i]:0);
            dp[i][j]=max(take,notTake);
        }
    }
    return dp[n][n];
}
//The code runs for two nested loops
//Space is used by the dp table
//Time Complexity will be O(n2)
//Space Complexity will be O(n2)

//Space Optimisation
int rodCutting_spaceOptimised(int n,vector<int> &cost){
    vector<int> curr(n+1,0);
    vector<int> prev(n+1,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int notTake=prev[j];
            int take=0;
            if(j>=i) take=cost[i-1]+curr[j-i];
            curr[j]=max(take,notTake);
        }
        prev=curr;
    }
    return prev[n];
}
//The code runs for the nested loop
//Space is used by two arrays of n size
//Time Complexity will be O(n2)
//Space Complexity will be O(2n)

//Further Optimization
int rodCutting(int n,vector<int> &cost){
    vector<int> dp(n+1,0);
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++) dp[j]=max(dp[j],cost[i-1]+dp[j-i]);
    }
    return dp[n];
}
//The code runs for the nested loop
//Space is used by a single dp array of size n
//Time Complexity will be O(n2)
//Space Complexity will be O(n)
