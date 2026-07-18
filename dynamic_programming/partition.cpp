#include<bits/stdc++.h>
using namespace std;

//Partition DP
//Toughest Pattern Till Now
//Partition DP comes into picture whenever there are more than one ways to solve the problem, see below question for more understanding

//Matrix Chain Multiplication (MCM)
//Consider matrix A (m*n) and a matrix B (p*q), The multiplication between them is possible only if p==n and the total number of operations done will be equal to m*(n or p)*q
//Suppose we are given three matrices, A, B and C
//Now we have two choices to multiply them : (AB)C or A(BC), both of these will have different number of operations
//For example, let's consider A of order (3x4) B of order (4x5) and C of order (5x6)
//Multiplying as (AB)C we first get AB of order 3x5 (operations done will be 3x4x5 => 60) then we multiply it by C
//The order will be 3x6 and the operations done will be 3x5x6 => 90, therefore total operations will be 90+60 = 150
//Doing the same in second operation A(BC) we get total operations as 192
//Clearly going by the approach of (AB)C will result in fewer operations, therefore that one is preferable
//This is what we have to return

//We will be given an array as say [10,20,30,40,50], this has dimensions of n-1 matrices
//The dimensions are 10x20, 20x30, 30x40, 40x50 (4 Matrices)
//Therefore the dimensions of ith matrix is A[i-1]xA[i]
int minOperationsInMCMHelper_brute(int i,int j,vector<int> &arr){
    if(i==j) return 0;
    int mini=1e9;
    for(int k=i;k<j;k++){
        int steps=(arr[i-1]*arr[k]*arr[j])+minOperationsInMCMHelper_brute(i,k,arr)+minOperationsInMCMHelper_brute(k+1,j,arr);
        mini=min(steps,mini);
    }
    return mini;
}
int minOperationsInMCM_brute(vector<int> &arr){
    int n=arr.size();
    return minOperationsInMCMHelper_brute(1,n-1,arr);
}
//Time Complexity will be exponential O(2^n)
//Space Complexity will be O(n)

//Memoization
int minOperationsInMCMHelper_memoization(int i,int j,vector<vector<int>> &dp,vector<int> &arr){
    if(dp[i][j]!=-1) return dp[i][j];
    if(i==j) return dp[i][j]=0;
    int mini=1e9;
    for(int k=i;k<j;k++){
        int steps=arr[i-1]*arr[k]*arr[j]+minOperationsInMCMHelper_memoization(i,k,dp,arr)+minOperationsInMCMHelper_memoization(k+1,j,dp,arr);
        mini=min(mini,steps);
    }
    return dp[i][j]=mini;
}
int minOperationsInMCM_memoization(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (n,-1));
    return minOperationsInMCMHelper_memoization(1,n-1,dp,arr);
}
//Time taken will be due to the loop which can go upto O(n) and due to counting of states which are n2 in total, so total time will be O(n)*O(n2)
//Time Complexity will be O(n3)
//Space Complexity will be O(n2)+O(n)

//Tabulation
//The tabulation in this case is the most optimised version, and we can't optimise it any further
int minOperationsInMCM(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (n,0));
    for(int i=n-1;i>=1;i--){
        for(int j=i+1;j<n;j++){
            int mini=1e9;
            for(int k=i;k<j;k++){
                int steps=arr[i-1]*arr[k]*arr[j]+dp[i][k]+dp[k+1][j];
                mini=min(mini,steps);
            }
            dp[i][j]=mini;
        }
    }
    return dp[1][n-1];
}
//Time Complexity will be O(n3)
//Space Complexity will be O(n2)


//Minimum Cost to cut the stick
//Cost to cut the stick will be equal to the length of the stick
int minCostToCutStickHelper_brute(int i,int j,vector<int> &arr){
    if(i>j) return 0;
    int mini=1e9;
    for(int idx=i;idx<=j;idx++){
        int cost=arr[j+1]-arr[i-1]+minCostToCutStickHelper_brute(i,idx-1,arr)+minCostToCutStickHelper_brute(idx+1,j,arr);
        mini=min(mini,cost);
    }
    return mini;
}

int minCostToCutStick_brute(vector<int> &arr,int len){
    int n=arr.size();

    //It is necessary to sort the array first
    sort(arr.begin(),arr.end());

    //We also need to insert 0 at back and len at front
    arr.push_back(len);
    arr.insert(arr.begin(),0);

    return minCostToCutStickHelper_brute(1,n,arr);
}
//This code takes exponential time, finding exact time is quite tough
//Time Complexity will be exponential

//Memoization
int minCostToCutStickHelper_memoization(int i,int j,vector<int> &arr,vector<vector<int>> &dp){
    if(dp[i][j]!=-1) return dp[i][j];
    if(i>j) return dp[i][j]=0;
    int mini=1e9;
    for(int idx=i;idx<=j;idx++){
        int cost=arr[j+1]-arr[i-1]+minCostToCutStickHelper_memoization(i,idx-1,arr,dp)+minCostToCutStickHelper_memoization(idx+1,j,arr,dp);
        mini=min(mini,cost);
    }
    return dp[i][j]=mini;
}
int minCostToCutStick_memoization(vector<int> &arr,int len){
    int n=arr.size();
    
    //It is necessary to sort the array first
    sort(arr.begin(),arr.end());

    //We also need to insert 0 at the front and n at the back
    arr.insert(arr.begin(),0);
    arr.push_back(len);
    vector<vector<int>> dp(n+2,vector<int> (n+2,-1));
    return minCostToCutStickHelper_memoization(1,n,arr,dp);
}
//Time is taken to fill all the (n+1)*(n+1) and n for the loop 
//Space is occupied by the dp array of size n2, and an extra recursion stack
//Time Complexity will be O(n3)
//Space Complexity will be O(n2+recursion stack space)

//Tabulation
//This is the most optimal code for this problem
int minCostToCutStick(vector<int> &arr,int len){
    int n=arr.size();
    sort(arr.begin(),arr.end());

    arr.push_back(len);
    arr.insert(arr.begin(),0);

    vector<vector<int>> dp(n+2,vector<int> (n+2,0));
    for(int i=n;i>=1;i--){
        //The second loop will start from j=i since if i>j, we already return 0
        for(int j=i;j<=n;j++){
            int mini=1e9;
            for(int idx=i;idx<=j;idx++){
                int cost=arr[j+1]-arr[i-1]+dp[i][idx-1]+dp[idx+1][j];
                mini=min(mini,cost);
            }
            dp[i][j]=mini;
        }
    }
    return dp[1][n];
}
//Time taken will be three loops, n3
//Space will be due to dp array
//Time  Complexity will be O(n3)
//Space Complexity will be O(n2)


//Burst Balloons
//Given an array of balloons [3,1,5,8] and every balloon has a number written on it. Now suppose we burst 5, we will get the number of coins to its left*coins to it right*coin on it
//That is we will get a total of 1*5*8 coins on bursting 5. We need to maximise the number of coins. After bursting 5, the array will look like [3,1,8]
//We can burst the balloon in any order, suppose we burst 3 at first, then coins=1*3*1(since no one on left, therefore assume 1),then 1 then 5 then 8
//We can also follow the order of bursting 1 first, 3, 5, 8. This will give us the maximum coins
//We will solve the problem for the minimum coins 
//Recursion
int burstBalloonsHelper_brute(int i, int j,vector<int> &arr){

    //Remember, even if i==j, we still solve it, since the neighbours may contribute
    //Therefore the base condition will be when i crosses j
    if(i>j) return 0;
    int maxi=-1;
    //Which will be the last balloon to be bursted
    for(int k=i;k<=j;k++){
        int coins=arr[i-1]*arr[k]*arr[j+1]+burstBalloonsHelper_brute(i,k-1,arr)+burstBalloonsHelper_brute(k+1,j,arr);
        maxi=max(maxi,coins);
    }
    return maxi;
}
int burstBalloons_brute(vector<int> &arr){
    int n=arr.size();
    arr.push_back(1);
    arr.insert(arr.begin(),1);
    return burstBalloonsHelper_brute(1,n,arr);
}
//Time taken will be exponential perhaps n!*n
//A recursion stack space of n will also be occupied
//Time Complexity will be O(n!*n)
//Space Complexity will be O(n)

//Memoization
int burstBalloonsHelper_memoization(int i,int j,vector<int> &arr,vector<vector<int>> &dp){
    if(i>j) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    int maxi=-1;
    for(int k=i;k<=j;k++){
        int coins=arr[i-1]*arr[k]*arr[j+1]+burstBalloonsHelper_memoization(i,k-1,arr,dp)+burstBalloonsHelper_memoization(k+1,j,arr,dp);
        maxi=max(maxi,coins);
    }
    return dp[i][j]=maxi;
}

int burstBalloons_memoization(vector<int> &arr){
    int n=arr.size();
    arr.push_back(1);
    arr.insert(arr.begin(),1);
    vector<vector<int>> dp(n+1,vector<int> (n+1,-1));
    return burstBalloonsHelper_memoization(1,n,arr,dp);
}
//Time taken will be to fill all dp states which are n2 and the inner loop which takes n
//Space Will be taken by recursion stack(n) and dp array(n2)
//Time Complexity will be O(n3)
//Space Complexity will be O(n2+n)

//Tabulation
//Again, tabulation is the most optimal code for this problem
int burstBalloons(vector<int> &arr){
    int n=arr.size();
    arr.push_back(1);
    arr.insert(arr.begin(),1);

    //This time we need a dp of n+2, since in second loop we call k+1, and k can be n at max hence n+2 size is needed
    vector<vector<int>> dp(n+2,vector<int> (n+2,0));
    for(int i=n;i>=1;i--){
        for(int j=i;j<=n;j++){
            int maxi=-1;
            for(int k=i;k<=j;k++){
                int coins=arr[i-1]*arr[k]*arr[j+1]+dp[i][k-1]+dp[k+1][j];
                maxi=max(maxi,coins);
            }
            dp[i][j]=maxi;
        }
    }
    return dp[1][n];
}
//Three loops running so n3
//Space is taken by the dp array
//Time Complexity will be O(n3)
//Space Complexity will be O(n2)


//Boolean Expression Evaluation
//Number of ways the exression can be evaluated to true
//The title of this problem on gfg is boolean parenthesization, search and learn more about it if you want
//The problem approach is exactly similar to Matrix Chain Multiplication
int boolExpHelper_brute(int i,int j,bool isTrue,string &s){
    
    //Just an optional defensive case
    if(i>j) return 0;

    if(i==j){
        if(isTrue) return s[i]=='T';
        else return s[i]=='F';
    }
    int ways=0;
    for(int k=i+1;k<=j-1;k=k+2){
        int lt=boolExpHelper_brute(i,k-1,1,s);
        int lf=boolExpHelper_brute(i,k-1,0,s);
        int rt=boolExpHelper_brute(k+1,j,1,s);
        int rf=boolExpHelper_brute(k+1,j,0,s);
        char c=s[k];
        if(c=='&'){
            if(isTrue) ways+=(lt*rt);
            else ways+=(lt*rf+lf*rt+lf*rf);
        }
        else if(c=='|'){
            if(isTrue) ways+=(lt*rf+lf*rt+lt*rt);
            else ways+=(lf*rf);
        }
        else{
            if(isTrue) ways+=(lt*rf+lf*rt);
            else ways+=(lt*rt+lf*rf);
        }
    }
    return ways;
}
int boolExp_brute(string &s){
    int n=s.size();
    return boolExpHelper_brute(0,n-1,1,s);
}
//The code runs the same as the matrix multiplication one, therefore time taken will be exponential
//Recursion stack space will be used perhaps somewhere around n

//Memoization
//We will need a 3d dp owing to the isTrue variable
int boolExpHelper_memoization(int i,int j,bool isTrue,vector<vector<vector<int>>> &dp,string &s){
    if(i>j) return 0;
    if(dp[i][j][isTrue]!=-1) return dp[i][j][isTrue];
    int ways=0;
    if(i==j){
        if(isTrue) return dp[i][j][isTrue]=(s[i]=='T');
        else return dp[i][j][isTrue]=(s[i]=='F');
    }
    for(int k=i+1;k<=j-1;k=k+2){
        int lt=boolExpHelper_memoization(i,k-1,1,dp,s);
        int lf=boolExpHelper_memoization(i,k-1,0,dp,s);
        int rt=boolExpHelper_memoization(k+1,j,1,dp,s);
        int rf=boolExpHelper_memoization(k+1,j,0,dp,s);
        char c=s[k];
        if(c=='&'){
            if(isTrue) ways+=(lt*rt);
            else ways+=(lt*rf+lf*rt+lf*rf);
        }
        else if(c=='|'){
            if(isTrue) ways+=(lt*rt+lf*rt+lt*rf);
            else ways+=(lf*rf);
        }
        else{
            if(isTrue) ways+=(lt*rf+lf*rt);
            else ways+=(lf*rf+lt*rt);
        }
    }
    return dp[i][j][isTrue]=ways;
}
int boolExp_memoization(string s){
    int n=s.size();
    vector<vector<vector<int>>> dp(n,vector<vector<int>> (n,vector<int> (2,-1)));
    return boolExpHelper_memoization(0,n-1,1,dp,s);
}
//The code will run to eventually fill out all the dp states and an inner loop of i->j will also contribute
//The space taken will be due to the dp array and recursion stack space
//Time Complexity will be O(2n3)
//Space Complexity will be O(2n2+n)

//Tabulation
//This is the most optimal solution 
int boolExp(string &s){
    int n=s.size();
    if(n==0) return 0;
    vector<vector<vector<int>>> dp(n,vector<vector<int>> (n,vector<int> (2,0)));

    //Let us write the base case when i==j
    for(int i=0;i<n;i++){
        dp[i][i][0]=s[i]=='F';
        dp[i][i][1]=s[i]=='T';
    }
    for(int i=n-1;i>=0;i++){
        for(int j=i+1;j<n;j++){
            for(int isTrue=0;isTrue<=1;isTrue++){
                int ways=0;
                for(int k=i+1;k<=j-1;k=k+2){
                    int lt=dp[i][k-1][1];
                    int lf=dp[i][k-1][0];
                    int rt=dp[k+1][j][1];
                    int rf=dp[k+1][j][0];
                    char c=s[k];
                    if(c=='&'){
                        if(isTrue) ways+=(lt*rt);
                        else ways+=(lt*rf+lf*rt+lf*rf);
                    }
                    else if(c=='|'){
                        if(isTrue) ways+=(lt*rt+lt*rf+lf*rt);
                        else ways+=(lf*rf);
                    }
                    else{
                        if(isTrue) ways+=(lt*rf+lf*rt);
                        else ways+=(lf*rf+lt*rt);
                    }
                }
                dp[i][j][isTrue]=ways;
            }
        }
    }
    return dp[0][n-1][1];
}
//There are 4 loops n*n*2*n
//The dp array occupies a space of 2n2
//Time Complexity will be O(2n3)
//Space Complexity will be O(2n2)



//Palindrome Partitioning II
//See question for more detail
//First we are going to create a function that checks whether a string is a palindrome or not
bool isPalindrome(string &s){
    int n=s.size();
    int i=0;
    int j=n-1;
    while(i<j){
        if(s[i++]!=s[j--]) return false;
    }
    return true;
}
//Time Complexity will be O(n/2)

//Now we start our solution
int partitionHelper_brute(int i,int n,string &s){
    if(i==s.size()) return 0;
    string temp="";
    int minCost=INT_MAX;

    for(int j=i;j<n;j++){
        temp+=s[j];
        if(isPalindrome(temp)){
            int cost=1+partitionHelper_brute(j+1,n,s);
            minCost=min(minCost,cost);
        }
    }
    return minCost;
}
int palindromePartitionII_brute(string &s){
    int n=s.size();
    int ans=partitionHelper_brute(0,n,s);
    return (ans-1);
}
//Time taken to run this code will be exponential
//The code will also use a recursion stack space of n size
//Time Complexity will be exponential
//Space Compleixty will be O(n)

//Memoization
int partitionHelper_memoization(int i,int n,vector<int> &dp,string &s){
    if(i==n) return 0;
    if(dp[i]!=-1) return dp[i];
    string temp="";
    int minCost=INT_MAX;

    for(int j=i;j<n;j++){
        temp+=s[j];
        if(isPalindrome(temp)){
            int cost=1+partitionHelper_memoization(j+1,n,dp,s);
            minCost=min(minCost,cost);
        }
    }
    return dp[i]=minCost;
}
int palindromePartitionII_memoization(string &s){
    int n=s.size();
    vector<int> dp(n,-1);
    int ans=partitionHelper_memoization(0,n,dp,s);
    return (ans-1);
}
//The code will run to fill the dp array of size n along with the loop which runs n times in the worst case
//The dp array takes space n along with the recursion stack space occupied of n
//Time Complexity will be O(n2)
//Space Complexity will be O(2n)

//Tabulation
//Tabulation code is the most optimal code in this case
int palindromePartitionII(string &s){
    int n=s.size();
    vector<int> dp(n+1,0);
    for(int i=n-1;i>=0;i--){
        string temp="";
        int minCost=INT_MAX;
        for(int j=i;j<n;j++){
            temp+=s[j];
            if(isPalindrome(temp)){
                int cost=1+dp[j+1];
                minCost=min(minCost,cost);
            }
        }
        dp[i]=minCost;
    }
    return dp[0]-1;
}
//The code runs two nested loop therefore time taken will be n2 in worst case
//The code also occupies space due to the dp array of size n
//Time Complexity will be O(n2)
//Space Complexity will be O(n)


//Partition Array 
//See question for more details
//Brute Force Or Recursion method
int partitionArrHelper_brute(int idx,int n,int k,vector<int> &arr){
    if(idx==n) return 0;
    int maxCost=INT_MIN;
    int len=0;
    int maxi=INT_MIN;
    for(int i=idx;i<min(n,idx+k);i++){
        len++;
        maxi=max(maxi,arr[i]);
        int cost=len*maxi+partitionArrHelper_brute(i+1,n,k,arr);
        maxCost=max(maxCost,cost);
    }
    return maxCost;
}
int partitionArr_brute(vector<int> &arr,int k){
    int n=arr.size();
    return partitionArrHelper_brute(0,n,k,arr);
}
//The code will run exponentially
//A recursion stack space of n will be used as well
//Time Complexity will be exponential
//Space Complexity will be O(n)

//Memoization
int partitionArrHelper_memoization(int idx,int n,int k,vector<int> &dp,vector<int> &arr){
    if(idx==n) return 0;
    if(dp[idx]!=-1) return dp[idx];
    int maxCost=INT_MIN;
    int len=0;
    int maxi=INT_MIN;
    for(int i=idx;i<min(n,k+idx);i++){
        len++;
        maxi=max(maxi,arr[i]);
        int cost=len*maxi+partitionArrHelper_memoization(i+1,n,k,dp,arr);
        maxCost=max(maxCost,cost);
    }
    return dp[idx]=maxCost;
}
int partitionArr_memoization(vector<int> &arr,int k){
    int n=arr.size();
    vector<int> dp(n,-1);
    return partitionArrHelper_memoization(0,n,k,dp,arr);
}
//The code will run to fill the dp table along with the inner loop which runs k times
//Space will be used due to the dp array and the recursion stack space
//Time Complexity will be O(nk)
//Space Complexity will be O(2n)

//Tabulation
//Tabulation is the most optimal method in this problem
int partitionArr(vector<int> &arr,int k){
    int n=arr.size();
    vector<int> dp(n,0);
    for(int i=n-1;i>=0;i--){
        int len=0;
        int maxi=INT_MIN;
        int maxCost=INT_MIN;
        for(int j=i;j<min(n,i+k);j++){
            len++;
            maxi=max(maxi,arr[j]);
            int cost=len*maxi+dp[j+1];
            maxCost=max(maxCost,cost);
        }
        dp[i]=maxCost;
    }
    return dp[0];
}
//The code will run for two nested loops
//Space will be occupied due to the array but no recursion stack space this time
//Time Complexity will be O(nk)
//Space Complexity will be O(n)


int main(){
  return 0;
}
