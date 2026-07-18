#include<bits/stdc++.h>
using namespace std;

//DP on Strings
//Longest Common Subsequence
//Two Strings given and you have to find the longest common subsequence between them
//Return the length of such a subsequence

//Naive Method
//Generate all the subsequences of string s1 and string s2 and then compare which are common subsequences then find which one of them is the longest

//Generating all subsequences, by using take and not take approach
void allSubsequencesHelper(int idx,int n,vector<vector<char>> &ans,vector<char> &temp,string &str){
    if(idx==n){
        ans.push_back(temp);
        return;
    }
    
    //Pick
    temp.push_back(str[idx]);
    allSubsequencesHelper(idx+1,n,ans,temp,str);

    //Not Pick
    temp.pop_back();
    allSubsequencesHelper(idx+1,n,ans,temp,str);
}
vector<vector<char>> allSubsequences(string &str){
    int n=str.size();
    vector<vector<char>> ans;
    vector<char> temp;
    allSubsequencesHelper(0,n,ans,temp,str);
    return ans;
}
//Each element has two choices, can be picked or not picked, therefore code will run 2^n times
//Also the thing to be noted is that at the base case when we say ans.push_back(temp), it takes n time as well, where n is the length of temp
//Therefore it can be n in the worst case, therefore the total time code will run will be O(n*2^n)
//Recursion stack space of n is used along with n more due to temp array. The space used to return the ans is not counted
//Time Complexity will be O(n*2^n)
//Space Complexity will be O(2n)

//Now we will write our function
int longestCommonSubsequences_naive(string &s1,string &s2){
    vector<vector<char>> sub1=allSubsequences(s1);
    vector<vector<char>> sub2=allSubsequences(s2);
    int maxLen=0;
    for(auto it:sub1){
        for(auto pq:sub2){

            //We can just use the comparison operator, it takes O(n) time, where n is the length of subsequence
            if(it==pq) maxLen=max(maxLen,(int)pq.size());
        }
    }
    return maxLen;
}
int lcsHelper_brute(int i,int j,string &s1,string &s2){
    if(i<0 || j<0) return 0;
    if(s1[i]==s2[j]) return (1+lcsHelper_brute(i-1,j-1,s1,s2));
    int ls=lcsHelper_brute(i-1,j,s1,s2);
    int rs=lcsHelper_brute(i,j-1,s1,s2);
    return max(ls,rs);
}
int longestCommonSubseq_brute(string str1,string str2){
    int n=str1.size();
    int m=str2.size();
    return lcsHelper_brute(n-1,m-1,str1,str2);
}
//Since there are a total pow(2,n) subsequences for first string and pow(2,m) subsequences for the second string, time complexity will be pow(2,n)*pow(2,m)
//A recursion stack space of N+M is also used
//Time Complexity will be O(2^n)*O(2^m)
//Space Complexity will be O(N+M)

//Memoization
int lcsHelper_mem(int i,int j,string &s1,string &s2,vector<vector<int>> &dp){
    if(i<0 || j<0) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    if(s1[i]==s2[j]) return dp[i][j]=(1+lcsHelper_mem(i-1,j-1,s1,s2,dp));
    int ls=lcsHelper_mem(i-1,j,s1,s2,dp);
    int rs=lcsHelper_mem(i,j-1,s1,s2,dp);
    return dp[i][j]=max(ls,rs);
}

int longestCommonSubseq_mem(string str1,string str2){
    int n=str1.size();
    int m=str2.size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    return lcsHelper_mem(n-1,m-1,str1,str2,dp);
}
//Time Complexity will be O(NM)
//Space Complexity will be O(NM) + O(N+M)(auxiliary stack space) (recursion, since we move in two directions)

//Tabulation
//The tabulation in such cases is usually written using shifting index method
//It tries to copy the base case used in memoization, since there it is when any index < 0 , return 0
//But since array don't have negative index, therefore we do a shifting of indices in the above problem
//So every i becomes i-1 and every j is j-1
//This method uses a dp of (n+1)*(m+1) but it is important as this method will be used in several other problems
int longestCommonSubseq_tabulation(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<int>> dp(n+1,vector<int> (m+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]) dp[i][j]=1+dp[i-1][j-1];
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[n][m];
}
//Time Complexity will be O(nm)
//Space Complexity will be O((n+1)*(m+1))

//Space Optimization
int longestCommonSubseq(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<int> curr(m+1,0);
    vector<int> prev(m+1,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]) curr[j]=1+prev[j-1];
            else curr[j]=max(curr[j-1],prev[j]);
        }
        prev=curr;
    }
    return prev[m];
}
//Time Complexity will be O(NM)
//Space Complexity will be O(N+M+2)


//Printing The LCS
//First part is to only print one lcs
string printingLCS(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<int>> dp(n+1,vector<int> (m+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]) dp[i][j]=(1+dp[i-1][j-1]);
            else dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
        }
    }

    int len=dp[n][m];
    string s(len,' ');

    int i=n;
    int j=m;
    while(i>0 && j>0){
        if(s1[i-1]==s2[j-1]){
            s[len-1]=s1[i-1];
            i--;
            j--;
            len--;
        }
        else if(dp[i][j-1]>dp[i-1][j]) j--;
        else i--;
    }
    return s;
}
//Time Complexity will be O(MN + M+N)
//Space Complexity will be O(MN)


//Printing lcs table
vector<vector<int>> lcsTable(string &s1,string &s2){
    int n1=s1.size();
    int n2=s2.size();
    vector<vector<int>> dp(n1+1,vector<int> (n2+1));
    for(int i=1;i<=n1;i++){
        for(int j=1;j<=n2;j++){
            if(s1[i-1]==s2[j-1]) dp[i][j]=(1+dp[i-1][j-1]);
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp;
}
//Time Complexity will be O(mn)
//Space Complexity will be o(mn)



//Longest Common Substring 
//Substrings are continuous, unlike subsequences
int lcssHelper_brute(int i,int j,string &s1,string &s2){
    if(i<0 || j<0) return 0;
    if(s1[i]==s2[j]) return 1+lcssHelper_brute(i-1,j-1,s1,s2);
    return 0;
}
int longestCommonSubstr_brute(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) ans=max(ans,lcssHelper_brute(i,j,s1,s2));
    }
    return ans;
}
//Outer loop runs mn times, the helper function can run in worst case for (since the code stops whenever anyone of i or j <0, whichever is minimum, does that first) min(n,m) therefore the code runs for (mn*min(m,n)), if we consider m==n, then code runs for n3
//Time Complexity will be O(n3)
//Space Complexity will be O(n)

//Memoization
int lcssHelper_memoization(int i,int j,string &s1,string &s2,vector<vector<int>> &dp){
    if(i<0 || j<0) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    if(s1[i]==s2[j]) dp[i][j]=1+lcssHelper_memoization(i-1,j-1,s1,s2,dp);
    else dp[i][j]=0;
    return dp[i][j];
}
int longestCommonSubstr_memoization(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ans=max(ans,lcssHelper_memoization(i,j,s1,s2,dp));
        }
    }
    return ans;
}
//Time Complexity will be O(mn+min(m,n))
//Space Complexity will be O(mn+min(m,n))

//Tabulation
//Index shifting takes place here
int longestCommonSubstr_tabulation(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<int>> dp(n+1,vector<int> (m+1,0));
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]){
                dp[i][j]=1+dp[i-1][j-1];
                ans=max(ans,dp[i][j]);
            }
            else dp[i][j]=0;
        }
    }
    return ans;
}
//Time Complexity will be O(mn)
//Space Complexity will be O(mn)

//Space Optimization
int longestCommonSubstr_spaceOptimization(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<int> curr(m+1,0);
    vector<int> prev(m+1,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]){
                curr[j]=1+prev[j-1];
                ans=max(ans,curr[j]);
            }
            else curr[j]=0;
        }
        prev=curr;
    }
    return ans;
}
//Time Complexity will be O(mn)
//Space Complexity will be O(2m)

//Further Optimization
int longestCommonSubstr(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<int> dp(m+1,0);
    int ans=0;
    for(int i=1;i<=n;i++){
        int prevDiag=0;
        for(int j=1;j<=m;j++){
            int temp=dp[j];
            if(s1[i-1]==s2[j-1]){
                dp[j]=1+prevDiag;
                ans=max(ans,dp[j]);
            }
            else dp[j]=0;
            prevDiag=temp;
        }
    }
    return ans;
}
//Time Complexity will be O(mn)
//Space Complexity will be O(m)


//Longest Palindromic Subsequence
//Brute Force 
//Generate All Subsequences then find out the length of the longest one

//Optimal Method
//If we take string s1 as original string and string s2 as s1 but reversed, then if we find out the LCS of s1 and s2, that will be the longest palindromic subsequence of string s
int longestPalindromicSubseq(string &s1){
    string s2=s1;
    reverse(s2.begin(),s2.end());
    return longestCommonSubseq(s1,s2);
}
//Time Complexity will be O(n2+n)
//Space Complexity will be O(2n)


//Minimum Insertions to make string palindromic
//One way is to insert the whole string at the back in reverse order(try it), then the new string becomes palindromic
//For eg consider string abc now add reverse of it at back, it becomes abccba, now that is a palindrome, therefore we know the ans would be <=n
//Remember, we have to do insertions(new characters, and not replacement)
//Insertions can be done anywhere, in the middle, end or front, anywhere
//Watch the video to get the ans which is n-length of longest palindromic sequence
int minInsertionsToMakePalindrome(string &s){
    int n=s.size();
    return (n-longestPalindromicSubseq(s));
}
//Time Complexity will be O(n2+n)
//Space Complexity will be O(2n)


//Minimum Insertions or deletions to make string s1 equal to string s2
//Consider s1=abcd and s2=apqde
//In this ad is a common subsequence, and hence we need to replace bc by pq and add e
int minOperationsToConvert(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    int lcs=longestCommonSubseq(s1,s2);
    return ((n-lcs)+(m-lcs));
}
//Time Complexity will be O(n2+n)
//Space Complexity will be O(2n)


//Shortest Common Supersequence
//First Print length of the supersequence
int lenOfShortestCommonSupersequence(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    int lcs=longestCommonSubseq(s1,s2);
    return (n+m-lcs);
}
//Time Complexity will be O(n2+n)
//Space Complexity will be O(2n)


//Shortest Common Supersequence
//Print the Supersequence
string shortestCommonSupersequence(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();

    //First we form the dp table
    vector<vector<int>> dp=lcsTable(s1,s2);
    //Time Complexity will be O(n*m)

    int i=n;
    int j=m;
    string s="";
    while(i>0 && j>0){
        if(s1[i-1]==s2[j-1]){
            s+=s1[i-1];
            i--;
            j--;
        }
        else if(dp[i-1][j]>dp[i][j-1]){ //Upward Movement
            s+=s1[i-1];
            i--;
        }
        else{ //Leftward Movement
            s+=s2[j-1];
            j--;
        }
    }

    while(i>0){
        s+=s1[i-1];
        i--;
    }

    while(j>0){
        s+=s2[j-1];
        j--;
    }

    reverse(s.begin(),s.end());
    return s;
}
//The lcs table construction takes mn time, the while loops takes n+m time and the reverse method takes n+m time
//Space is used by the dp table which is of mn size
//Time Complexity will be O(mn+2m+2n)
//Space Complexity will be O(mn)


//Number of Distinct Subsequences
int distinctSubseqHelper_brute(int i,int j,string &s1,string &s2){
    if(j<0) return 1;
    if(i<0) return 0;
    if(s1[i]==s2[j]){
        int take=distinctSubseqHelper_brute(i-1,j-1,s1,s2);
        int notTake=distinctSubseqHelper_brute(i-1,j,s1,s2);
        return (take+notTake);
    }
    return distinctSubseqHelper_brute(i-1,j,s1,s2);
}
int distinctSubseq_brute(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    return distinctSubseqHelper_brute(n-1,m-1,s1,s2);
}
//The code will run exponentially
//Recursion stack space will be used as well which will be about n+m
//Time Complexity will be exponential
//Space Complexity will be O(n+m)

//Memoization
int distinctSubseqHelper_memoization(int i,int j,string &s1,string &s2,vector<vector<int>> &dp){
    if(j<0) return 1;
    if(i<0) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    if(s1[i]==s2[j]){
        int take=distinctSubseqHelper_memoization(i-1,j-1,s1,s2,dp);
        int notTake=distinctSubseqHelper_memoization(i-1,j,s1,s2,dp);
        return dp[i][j]=(take+notTake);
    }
    return dp[i][j]=distinctSubseqHelper_memoization(i-1,j,s1,s2,dp);
}
int distinctSubseq_memoization(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    return distinctSubseqHelper_memoization(n-1,m-1,s1,s2,dp);
}
//The code runs to completely fill the dp table of mn size
//The space is used by the dp table of mn size along with a recursion stack space of m+n
//Time Complexity will be O(mn)
//Space Complexity will be o(mn+m+n)

//Tabulation
//Shifting Index Method
int distinctSubseq_tabulation(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<int>> dp(n+1,vector<int> (m+1,0));
    for(int i=0;i<=n;i++) dp[i][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]){
                int take=dp[i-1][j-1];
                int notTake=dp[i-1][j];
                dp[i][j]=(take+notTake);
            }
            else dp[i][j]=dp[i-1][j];
        }
    }
    return dp[n][m];
}
//There is a loop at start which takes n time and a nested loop which takes mn time
//Space is occupied by the dp table which takes space of mn size
//Time Complexity will be O(mn+n)
//Space Complexity will be O(mn)

//Further Optimization
int distinctSubseq_spaceOptimised(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<int> curr(m+1,0);
    vector<int> prev(m+1,0);
    prev[0]=curr[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]){
                int take=prev[j-1];
                int notTake=prev[j];
                curr[j]=(take+notTake);
            }
            else curr[j]=prev[j];
        }
        prev=curr;
    }
    return prev[m];
}
//There is a nested loop which takes mn time in total
//Space is used by two 1d arrays of m size
//Time Complexity will be O(mn)
//Space Complexity will be O(m+n)

//Further Optimization
int distinctSubseq(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<int> dp(m+1,0);
    dp[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
            if(s1[i-1]==s2[j-1]) dp[j]+=dp[j-1];
        }
    }
    return dp[m];
}
//There is a nested loop which takes mn time
//Space is used by dp array of m size
//Time Complexity will be O(mn)
//Space Complexity will be O(m)


//Edit Distance
//Similar to previous problem
int editDistanceHelper_brute(int i,int j,string &s1,string &s2){
    if(i<0) return j+1;
    if(j<0) return i+1;
    if(s1[i]==s2[j]) return (0+editDistanceHelper_brute(i-1,j-1,s1,s2));

    //This is the case when string char don't match, We can do three things
    //First is to insert another character similar to it in front
    int ins=1+editDistanceHelper_brute(i,j-1,s1,s2);

    //Second is delete that char and see if the next one matches, so only i will move back
    int del=1+editDistanceHelper_brute(i-1,j,s1,s2);

    //Third is to replace that char so that they match, then move both the pointers
    int rep=1+editDistanceHelper_brute(i-1,j-1,s1,s2);
    return min(ins,min(del,rep));
    
}
int editDistance_brute(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    return editDistanceHelper_brute(n-1,m-1,s1,s2);
}
//The code will run exponentially
//Space is used by recursion stack which can be n+m
//Time Complexity will be exponential
//Space Complexity will be O(n+m)

//Memoization
int editDistanceHelper_memoization(int i,int j,string &s1,string &s2,vector<vector<int>> &dp){
    if(i<0) return j+1;
    if(j<0) return i+1;

    if(dp[i][j]!=-1) return dp[i][j];
    if(s1[i]==s2[j]) return dp[i][j]=editDistanceHelper_memoization(i-1,j-1,s1,s2,dp);

    int ins=1+editDistanceHelper_memoization(i,j-1,s1,s2,dp);
    int del=1+editDistanceHelper_memoization(i-1,j,s1,s2,dp);
    int rep=1+editDistanceHelper_memoization(i-1,j-1,s1,s2,dp);
    return dp[i][j]=min(ins,min(del,rep));
}
int editDistance_memoization(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    return editDistanceHelper_memoization(n-1,m-1,s1,s2,dp);
}
//The code runs to fill the complete dp table
//Space is used by the dp array and recursion stack of n+m
//Time Complexity will be O(nm)
//Space Complexity will be O(nm+n+m)

//Tabulation
int editDistance_tabulation(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<int>> dp(n+1,vector<int> (m+1,0));
    for(int j=0;j<=m;j++) dp[0][j]=j;
    for(int i=1;i<=n;i++) dp[i][0]=i;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1];
            else{
                int ins=1+dp[i][j-1];
                int del=1+dp[i-1][j];
                int rep=1+dp[i-1][j-1];
                dp[i][j]=min(ins,min(del,rep));
            }
        }
    }

    return dp[n][m];
}
//There are two loop at the start taking a time of n+m
//Then there is a nested loop which runs for mn time
//Space is used by the dp table of mn size
//Time Complexity will be O(mn+m+n)
//Space Complexity will be O(mn)

//Space Optimisation
int editDistance_spaceOptimised(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<int> prev(m+1,0);
    vector<int> curr(m+1,0);
    iota(prev.begin(),prev.end(),0);
    for(int i=1;i<=n;i++){
        curr[0]=i;
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1]) curr[j]=prev[j-1];
            else{
                int ins=1+curr[j-1];
                int del=1+prev[j];
                int rep=1+prev[j-1];
                curr[j]=min(ins,min(del,rep));
            }
        }
        prev=curr;
    }

    return prev[m];
}
//There is a for loop at the start taking m time 
//There is a nested loop as well which takes mn time
//Space is used by the two 1d arrays of m size
//Time Complexity will be O(mn+m)
//Space Complexity will be O(2m)

//Further Optimisation
int editDistance(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<int> dp(m+1,0);
    iota(dp.begin(),dp.end(),0);
    for(int i=1;i<=n;i++){
        int diag=dp[0];
        dp[0]=i;
        for(int j=1;j<=m;j++){
            int temp=dp[j];
            if(s1[i-1]==s2[j-1]) dp[j]=diag;
            else dp[j]=1+min(dp[j-1],min(dp[j],diag));
            diag=temp;
        }
    }
    return dp[m];
}
//The iota function takes n m time to run
//The nested loop takes mn time
//Space is occupied only by the dp array
//Time Complexity will be O(mn+m)
//Space Complexity will be O(m)


//Wildcard Matching
//? matches with any character : ==> abc?d matches with abced
//* matches with any sequence  : ==> abc*de matches with abcdefde
//? and * will only be in string 2
//We only need to tell whether or not the strings are matching or not
//Hence we only need to return true or false
bool wildcardHelper_brute(int i,int j,string &s1,string &s2){

    //If both the strings got exhausted then the comparsion was successful
    if(i<0 && j<0) return true;

    //If only s1 got exhausted then the comparsion was not successful
    if(i<0) return false;
    
    //If s2 got exhausted and there's still s1 left, the match can still be made if there is only * left in s1
    if(j<0){
        for(int k=0;k<=i;k++) if(s1[k]!='*') return false;
        return true;
    }
    if(s1[i]==s2[j] || s1[i]=='?') return wildcardHelper_brute(i-1,j-1,s1,s2);
    if(s1[i]=='*'){
        bool empty=wildcardHelper_brute(i-1,j,s1,s2);
        bool oneChar=wildcardHelper_brute(i,j-1,s1,s2);
        return (empty || oneChar);
    }
    return false;
}
bool wildcardMatching_brute(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    return wildcardHelper_brute(n-1,m-1,s1,s2);
}
//The code will run exponential times
//Space will be occupied by the recursion stack of n+m size
//Time Complexity will be exponential
//Space Complexity will be O(n+m)

//Memoization
bool wildcardHelper_memoization(int i,int j,string &s1,string &s2,vector<vector<int>> &dp){
    if(i<0 && j<0) return true;
    if(i<0) return false;
    if(j<0){
        for(int k=0;k<=i;k++) if(s1[k]!='*') return false;
        return true;
    }

    if(dp[i][j]!=-1) return dp[i][j];
    if(s1[i]==s2[j] || s1[i]=='?') return dp[i][j]=wildcardHelper_memoization(i-1,j-1,s1,s2,dp);
    if(s1[i]=='*'){
        bool empty=wildcardHelper_memoization(i-1,j,s1,s2,dp);
        bool oneChar=wildcardHelper_memoization(i,j-1,s1,s2,dp);
        return dp[i][j]=(empty || oneChar);
    } 
    return dp[i][j]=false;
}
bool wildcardMatching_memoization(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    return wildcardHelper_memoization(n-1,m-1,s1,s2,dp);
}
//The code runs to fill the dp table 
//Space is occupied by the recursion stack and dp table of mn size
//Time Complexity will be O(mn)
//Space Complexity will be O(mn+n+m)

//Tabulation
bool wildcardMatching_tabulation(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<vector<bool>> dp(n+1,vector<bool> (m+1,false));
    dp[0][0]=true;
    for(int i=1;i<=n;i++){

        //Instead of writing a for loop, this time we have used a smart logic
        //We could also write a for loop (k=1 to k=i) and set a flag as false whenever the s1[k-1]!='*'
        //But this is a more cleaner method
        if(s1[i-1]!='*') dp[i][0]=false;
        else dp[i][0]=dp[i-1][0];
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1] || s1[i-1]=='?') dp[i][j]=dp[i-1][j-1];
            else if(s1[i-1]=='*') dp[i][j]=(dp[i-1][j] || dp[i][j-1]);
            else dp[i][j]=false;
        }
    }
    
    return dp[n][m];
}
//The intial for loops also runs for somewhat n times
//The code runs for mn time in the nested loop
//Space is occupied by the dp table of mn size
//Time Complexity will be O(mn+n)
//Space Complexity will be O(mn)

//Space Optimisation
bool wildcardMatching_spaceOptimisation(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<bool> prev(m+1,false);
    vector<bool> curr(m+1,false);
    prev[0]=true;

    for(int i=1;i<=n;i++){
        curr[0]=((s1[i-1]=='*') && (prev[0]));
        for(int j=1;j<=m;j++){
            if(s1[i-1]==s2[j-1] || s1[i-1]=='?') curr[j]=prev[j-1];
            else if(s1[i-1]=='*') curr[j]=(prev[j] || curr[j-1]);
            else curr[j]=false;
        }
        prev=curr;
    }
    return prev[m];
}
//The nested loop runs for nm
//Space is occupied by prev and curr arrays
//Time Complexity will be O(mn)
//Space Complexity will be O(2m)

//Further Optimisation
bool wildcardMatching(string &s1,string &s2){
    int n=s1.size();
    int m=s2.size();
    vector<bool> dp(m+1,0);
    dp[0]=true;
    for(int i=1;i<=n;i++){
        bool diag=dp[0];
        dp[0]=((s1[i-1]=='*') && (dp[0]));
        for(int j=1;j<=m;j++){
            bool temp=dp[j];
            if(s1[i-1]==s2[j-1] || s1[i-1]=='?') dp[j]=diag;
            else if(s1[i-1]=='*') dp[j]=(dp[j] || dp[j-1]);
            else dp[j]=false;
            diag=temp;
        }
    }

    return dp[m];
}
//The nested loop runs for mn times
//Space is occupied by the dp array 
//Time Complexity will be O(mn)
//Space Complexity will be O(m)

