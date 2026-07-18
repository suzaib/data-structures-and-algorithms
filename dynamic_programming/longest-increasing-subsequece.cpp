#include<bits/stdc++.h>
using namespace std;

//DP on LIS
//Longest Increasing Subsequence
//Length of Longest Increasing Subsequence
//Naive Solution
//Form all the subsequences and then see if they are increasing(strictly increasing), if they are, count their length
bool checkIfIncreasing(vector<int> &arr){
    int n=arr.size();
    for(int i=0;i<n-1;i++){
        if(arr[i+1]<=arr[i]) return false;
    }
    return true;
}
void lengthOfLISHelper_naive(int idx,vector<int> &arr,vector<int> &temp,vector<vector<int>> &allSub){
    if(idx==0){
        if(checkIfIncreasing(temp)) allSub.push_back(temp);
        return;
    }

    //Pick
    temp.push_back(arr[idx]);
    lengthOfLISHelper_naive(idx-1,arr,temp,allSub);

    //Not Pick
    temp.pop_back();
    lengthOfLISHelper_naive(idx-1,arr,temp,allSub);
}
int lengthOfLIS_naive(vector<int> &arr){
    int n=arr.size();
    vector<int> temp;
    vector<vector<int>> allSub;
    lengthOfLISHelper_naive(n-1,arr,temp,allSub);
    int maxCnt=1;
    for(auto it:allSub){
        maxCnt=max(maxCnt,(int)it.size());
    }
    return maxCnt;
}
//Time Complexity will be ~ O(2^n)
//Space Complexity will be O(n) recursion stack space

//Brute Force
//Using the same pick / not pick technique
int lengthOfLISHelper_brute(int idx,int prevIdx,int n,vector<int> &arr){
    if(idx==n) return 0;
    int len=0+lengthOfLISHelper_brute(idx+1,prevIdx,n,arr);
    if(prevIdx==-1 || arr[idx]>arr[prevIdx]) len=max(len,1+lengthOfLISHelper_brute(idx+1,idx,n,arr));
    return len;
}
int lengthOfLIS_brute(vector<int> &arr){
    int n=arr.size();
    return lengthOfLISHelper_brute(0,-1,n,arr);
}
//Each element has a choice to be picked or not, therefore the code will run for 2^n times
//n levels in total, therefore stack space of n will be used
//Time Complexity will be O(2^n)
//Space Complexity will be O(n)

//Memoization
//We use the index shifting here since -1 can't be used as dp[prevIdx]
int lengthOfLISHelper_memoization(int idx,int prevIdx,int n,vector<vector<int>> &dp,vector<int> &arr){
    if(idx==n) return 0;
    if(dp[idx][prevIdx+1]!=-1) return dp[idx][prevIdx+1];

    //Not Picking the element
    int len=0+lengthOfLISHelper_memoization(idx+1,prevIdx,n,dp,arr);

    //Picking the element
    if(prevIdx==-1 || arr[idx]>arr[prevIdx]) len=max(len,1+lengthOfLISHelper_memoization(idx+1,idx,n,dp,arr));
    return dp[idx][prevIdx+1]=len;
}

int lengthOfLIS_memoization(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n,vector<int> (n+1,0));
    return lengthOfLISHelper_memoization(0,-1,n,dp,arr);
}
//The loop runs only for at max n2 times (since that is the total size of dp array)
//Recursion stack space of n and dp matrix of n2
//Time Complexity will be O(n2)
//Space Complexity will be O(n+n2)

//Tabulation
int lengthOfLIS_tabulation(vector<int> &arr){
    int n=arr.size();
    vector<vector<int>> dp(n+1,vector<int> (n+1,0));
    for(int idx=n-1;idx>=0;idx--){
        for(int prevIdx=idx-1;prevIdx>=-1;prevIdx--){
            int len=0+dp[idx+1][prevIdx+1];
            if(prevIdx==-1 || arr[idx]>arr[prevIdx]) len=max(len,1+dp[idx+1][idx+1]);
            dp[idx][prevIdx+1]=len;
        }
    }
    return dp[0][-1+1];
}
//Time Complexity will be O((n+1)^2)
//Space Complexity will be O((n+1)^2)

//Space Optimization
int lengthOfLIS_spaceOptimization(vector<int> &arr){
    int n=arr.size();
    vector<int> prev(n+1,0);
    for(int idx=n-1;idx>=0;idx--){
        vector<int> curr(n+1,0);
        for(int prevIdx=idx-1;prevIdx>=-1;prevIdx--){
            int len=0+prev[prevIdx+1];
            if(prevIdx==-1 || arr[idx]>arr[prevIdx]) len=max(len,1+prev[idx+1]);
            curr[prevIdx+1]=len;
        }
        prev=curr;
    }
    return prev[0];
}
//Time Complexity will be O(n^2)
//Space Complexity will be O(2n)

//Further Optimization
//The most optimized approach is quite different this time
//It uses tabulation in a more neat way, try to see video for explanation
int lengthOfLIS(vector<int> &arr){
    int n=arr.size();
    vector<int> dp(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(arr[j]>arr[i]) continue;
            dp[i]=max(1+dp[j],dp[i]);
        }
    }

    return *(max_element(dp.begin(),dp.end()));
}
//Time Complexity will be O(n2)
//Space Complexity will be O(n)

//There's another method to doing these kind of problems
//First sort the array then find LCS of the sorted array and the original array, that will be the LIS

//Printing The LIS
//Similar to the upper approach
//Watch video for clear explanation
vector<int> printLIS(vector<int> &arr){
    int n=arr.size();
    vector<int> dp(n,1);
    vector<int> hash(n);
    iota(hash.begin(),hash.end(),0); //This fills the array as arr[0]=0, arr[1]=1 ..
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(arr[j]<arr[i] && 1+dp[j]>dp[i]){
                dp[i]=1+dp[j];
                hash[i]=j;
            }
        }
    }
    auto it=max_element(dp.begin(),dp.end());
    int maxLen=*it;
    int maxIdx=it-dp.begin();
    vector<int> ans;
    while(ans.size()!=maxLen){
        ans.push_back(arr[maxIdx]);
        maxIdx=hash[maxIdx];
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
//No need to include n space of ans array as it is used to show answer
//Time Complexity will be O(n2+3n)
//Space Complexity will be O(2n)


//LIS Using Binary Search
//We just print the length of LIS
int lengthOfLISII(vector<int> &arr){
    int n=arr.size();
    vector<int> ans;
    ans.push_back(arr[0]);
    for(int i=1;i<n;i++){
        if(arr[i]>ans.back()) ans.push_back(arr[i]);
        else{
            int low=0;
            int high=ans.size()-1;
            int pos=high;
            while(low<=high){
                int mid=(low+high)>>1;
                if(ans[mid]>=arr[i]){
                    pos=mid;
                    high=mid-1;
                }
                else low=mid+1;
            }
            ans[pos]=arr[i];
        }
    }
    return ans.size();
}
//Time Complexity will be O(nlogn)
//Space Complexity will be O(n)


//Largest Divisible Subset
//Logic is same as LIS using the tabulation method, just change the if condition
vector<int> largestDivisibleSubset(vector<int> &arr){
    int n=arr.size();
    vector<int> dp(n,1);
    vector<int> hash(n);
    sort(arr.begin(),arr.end());
    iota(hash.begin(),hash.end(),0);//fills the array as 0,1,2...
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(arr[i]%arr[j]==0 && dp[i]<dp[j]+1){
                dp[i]=1+dp[j];
                hash[i]=j;
            }
        }
    }
    vector<int> ans;
    auto it=max_element(dp.begin(),dp.end());
    int maxLen=*(it);
    int maxIdx=it-dp.begin();
    while(ans.size()!=maxLen){
        ans.push_back(arr[maxIdx]);
        maxIdx=hash[maxIdx];
    }
    return ans;
}
//No need to include n space of ans array as it is used to show answer
//Time Complexity will be O(n2+3n)
//Space Complexity will be O(2n)


//Longest String Chain
//First we will write a compare function to check if two strings(of lengths x and x-1, differ by just one character)
bool compare(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    if(n!=m+1) return false;

    int skipped=0;
    //We assume that n=m+1

    int i=0;
    int j=0;
    while(i<n){
        if(s1[i]==s2[j]){
            i++;
            j++;
        }
        else{
            i++;
            skipped++;
            if(skipped>1) return false;
        }
        if(i==s1.size() && j==s2.size()) return true;
    }
    return false;
}
//The function runs for n times where n is the length of bigger string

//Let us discuss the sort method in more detail
//sort(iterator_beginning,iterator_ending,comparator function)
//The third argument is optional and is a comparator function that defines how the comparison should be done
/*
Consider for eg a comparator function :
bool cmp(string &a,string &b){
    return a.size()<b.size();
}
This comparator function means put a before if it is smaller
sort function after this looks like : sort(arr.begin(),arr.end(),cmp)

Lambda Expressions
They are anonymous functions
We can use them like : 
sort(arr.begin(),arr.end(),[](string &a,string &b){
    return a.size()<b.size();
});
*/
//Now we write our code
int longestStringChain(vector<string> arr){
    int n=arr.size();
    vector<int> dp(n,1);
    sort(arr.begin(),arr.end(),[](string &a,string &b){
        return a.size()<b.size();
    });
    int maxi=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(compare(arr[i],arr[j])){
                dp[i]=max(dp[i],1+dp[j]);
                maxi=max(maxi,dp[i]);
            }
        }
    }
    return maxi;
}
//Time used is due to sorting (nlogn) and two loops (n2) multiplied by the time taken by compare function (n2*l) where l is the length of string
//Time Complexity will be O(n2*l+nlogn)
//Space Complexity will be O(n)


//Longest Bitonic Subsequence
//An increasing or decreasing or inreasing first then decreasing or decreasing first then increasing, all of it constitutes a bitonic subsequence
//Make the dp from the front and from the back then find the greatest sum in both and subtract 1 from it
int longestBitonicSubseq_brute(vector<int> &arr){
    int  n=arr.size();
    vector<int> dp1(n,1);
    vector<int> dp2(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if((arr[i]>arr[j]) && (1+dp1[j]>dp1[i])) dp1[i]=1+dp1[j];
        }
    }

    //Backward Iteration
    for(int i=n-1;i>=0;i--){
        for(int j=n-1;j>i;j--){
            if((arr[i]>arr[j]) && (1+dp2[j]>dp2[i])) dp2[i]=1+dp2[j];
        }
    }

    int maxLen=0;
    for(int i=0;i<n;i++){
        maxLen=max(maxLen,dp1[i]+dp2[i]);
    }
    return (maxLen-1);
}
//Time Complexity will be O(2n2 + n)
//Space Complexity will be O(2n)

//Optimal Method
//We can reduce time complexity to O(2n2) by calculating maxLen in the second loop itself
int longestBitonicSubseq(vector<int> &arr){
    int n=arr.size();
    vector<int> dp1(n,1);
    vector<int> dp2(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if((arr[i]>arr[j]) && (1+dp1[j]>dp1[i])) dp1[i]=1+dp1[j];
        }
    }

    int maxLen=0;

    for(int i=n-1;i>=0;i--){
        for(int j=n-1;j>i;j--){
            if((arr[i]>arr[j]) && (1+dp2[j]>dp2[i])) dp2[i]=1+dp2[j];
        }
        maxLen=max(maxLen,dp1[i]+dp2[i]);
    }
    return (maxLen-1);
}
//Time Complexity will be O(2n2)
//Space Complexity will be O(2n)


//Longest Bitonic Subsequence II
//This is another version in which you have to report only bitonic sequence and not monotonic
int longestBitonicSequenceII(int n, vector<int> &nums) {
    // code here
    int s=nums.size();
    vector<int> dp1(s,1);
    vector<int> dp2(s,1);
    
    //Forward Iteration
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(nums[i]>nums[j] && dp1[i]<1+dp1[j]) dp1[i]=1+dp1[j];
        }
    }
    int maxi=0;
    
    for(int i=n-1;i>=0;i--){
        for(int j=n-1;j>i;j--){
            if(nums[i]>nums[j] && 1+dp2[j]>dp2[i]) dp2[i]=1+dp2[j];
        }
        if(dp1[i]!=1 & dp2[i]!=1) maxi=max(maxi,dp1[i]+dp2[i]);
    }
    if(maxi==0) return maxi;
    return maxi-1;
}
//Time Complexity will be O(2n2)
//Space Complexity will be O(2n)


//Number of LIS
//In this along with a dp array, we use a count array as well
int numberOfLIS(vector<int> &arr){
    int n=arr.size();
    vector<int> dp(n,1);
    vector<int> cnt(n,1);
    int maxi=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(arr[i]>arr[j] && 1+dp[j]>=dp[i]){
                if(1+dp[j]==dp[i]) cnt[i]=cnt[i]+cnt[j];
                else{
                    cnt[i]=cnt[j];
                    dp[i]=1+dp[j];
                }
            }
        }
        maxi=max(maxi,dp[i]);
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(dp[i]==maxi) ans+=cnt[i];
    }

    return ans;
}
//Time Complexity will be O(n2+n)
//Space Complexity will be O(2n)

int main(){
    return 0;
}

