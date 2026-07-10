#include<bits/stdc++.h>
using namespace std;

//Some Functions to be used down
//Max in Array : O(n)
int maxInArr(vector<int> arr){
    int n=arr.size();
    int maxi=INT_MIN;
    for(int i=0;i<n;i++) maxi=max(maxi,arr[i]);
    return maxi;
}




//Assign Cookies
int assignCookies(vector<int> cookies,vector<int> children){
    int n=cookies.size();
    int m=children.size();
    sort(cookies.begin(),cookies.end());
    sort(children.begin(),children.end());
    int i=0;
    int j=0;
    int count=0;
    while(i<n && j<m){
        if(cookies[i]>=children[j]){
            count++;
            j++;
        }
        i++;
    }
    return count;
}
//TC is NLogN + MLogM + min(n,m);




//Lemonade Change 
bool lemonadeChange(vector<int> customers){
    int n=customers.size();
    int count5=0;
    int count10=0;
    for(int i=0;i<n;i++){
        if(customers[i]==5){
            count5++;
        }
        else if(customers[i]==10){
            count5--;
            count10++;
        }
        else {
            if(count10>0){
                count10--;
                count5--;
            }
            else{
                count5=count5-3;
            }
        }
        if(count5<0 || count10<0) return false;
    }
    return true;
}



//Shortest Job First
int ShortestJobFirst(vector<int> arr){
    int n=arr.size();
    int waitTime=0;
    int startTime=0;
    sort(arr.begin(),arr.end());
    for(int i=0;i<n;i++){
        waitTime+=startTime;
        startTime+=arr[i];
    }
    return waitTime/n;
}
//Time Complexity will be O(n*logn + n)




//Jump Game
bool jumpGame(vector<int> arr){
    int n=arr.size();
    int maxReach=0;
    for(int i=0;i<n;i++){
        if(i>maxReach) return false;
        maxReach=max(maxReach,arr[i]+i);
        if(maxReach>=n-1) return true; //This optimises the code a bit
    }
    return true;
}
//Time Complexity will be O(n)



//Jump Game II
//Minimum Jumps needed to reach the last Idx or cross it
//Return -1, in case the last index is unreachable
//This is a question involving dynamic programming as we have to try all ways
//Recursion
int jumpGameHelper_brute(int idx,int jumps,int endIdx,vector<int> &arr){
    if(idx>=endIdx) return jumps;
    if(arr[idx]==0) return 1e9;
    int minJumps=1e9;
    for(int i=1;i<=arr[idx];i++){
        int result=jumpGameHelper_brute(i+idx,jumps+1,endIdx,arr);
        if(result!=1e9) minJumps=min(minJumps,result);
    }
    return minJumps;
}
int jumpGameII_brute(vector<int> &arr){
    int n=arr.size();
    int ans=jumpGameHelper_brute(0,0,n-1,arr);
    return (ans==1e9? -1:ans);
}
//The worst case we assume that at each index we can jump n times, we have n choices to jump at n elements each
//Therefore the code will run for about N^N times
//A recursion stack space of n will be used as well
//Time Complexity will be O(n^n)
//Space Complexity will be O(n)

//Memoization
int jumpGameIIHelper_memoization(int idx,int endIdx,vector<int> &dp,vector<int> &arr){
    if(idx>=endIdx) return 0;
    if(arr[idx]==0) return 1e9;
    if(dp[idx]!=-1) return dp[idx];
    int minJumps=1e9;
    for(int i=1;i<=arr[idx];i++){
        int result=jumpGameIIHelper_memoization(idx+i,endIdx,dp,arr);
        if(result!=1e9) minJumps=min(minJumps,1+result);
    }
    return dp[idx]=minJumps;
}
int jumpGameII_memoization(vector<int> &arr){
    int n=arr.size();
    vector<int> dp(n,-1);
    int ans=jumpGameIIHelper_memoization(0,n-1,dp,arr);
    return (ans==1e9? -1:ans);
}
//The loop can run for a max of arr[idx] value which can be say m, also the code runs to count all states of dp which is n
//A dp of n size is used along with a recursion stack space of n
//Time Complexity will be O(mn)
//Space Complexity will be O(2n)

//Tabulation
//The tabulation method is all the optimisation dp techniques can provide. The most optimal approach requires the greedy algorithm
int jumpGameII_tabulation(vector<int> &arr){
    int n=arr.size();
    if(n<=1) return 0;
    if(arr[0]==0) return -1;
    vector<int> dp(n,1e9);
    dp[0]=0;
    for(int i=0;i<n;i++){
        if(dp[i]==1e9) continue; //Since this step is unreachable
        for(int j=1;j<=arr[i] && j+i<n;j++) dp[i+j]=min(dp[i+j],dp[i]+1);
    }
    return (dp[n-1]==1e9? -1:dp[n-1]);
}
//Time Complexity will be O(nm)
//Space Complexity will be O(n)

//Optimal Method
//The most optimal method is using the greedy approach
int jumpGameII(vector<int> &arr){
    int n=arr.size();
    int r=0;
    int l=0;
    int jumps=0;
    while(r<n-1 && r>=l){
        int farthest=0;
        for(int i=l;i<=r;i++) farthest=max(farthest,arr[i]+i);
        if(farthest==r) return -1;
        l=r+1;
        r=farthest;
        jumps++;
    }
    return jumps;
}
//Each element is only visited once
//No extra space is used
//Time Complexity will be O(n)
//Space Complexity will be O(1)



//Job Sequencing Problem
bool compare(pair<int,int> &a,pair<int,int> &b){
    return a.second>b.second;
}
vector<int> jobSequencing_brute(vector<int> &deadline,vector<int> &profit){
    int n=deadline.size();
    vector<pair<int,int>> Jobs;
    for(int i=0;i<n;i++) Jobs.push_back({deadline[i],profit[i]});
    sort(Jobs.begin(),Jobs.end(),compare);
    int maxDeadline=*(max_element(deadline.begin(),deadline.end()));
    vector<bool> slot(maxDeadline+1,false);

    int jobCnt=0;
    int totalProfit=0;
    for(int i=0;i<n;i++){
        for(int j=Jobs[i].first;j>0;j--){
            if(slot[j]) continue;
            slot[j]=true;
            jobCnt++;
            totalProfit+=Jobs[i].second;
            break;
        }
    }
    return {totalProfit,jobCnt};
}
//Sorting takes nlogn and then the two loops take n*D where D is the max Deadline
//Space is occupied by the slot array and storing jobs
//Space used is approximately n+D
//Time Complexity will be O(nlogn+nD)
//Space Compelexity will be O(n+D)

//Optimal Method
//We only try to eliminate the nD portion in time complexity 
//We do that by using disjoint set data structure
//When we mark slot[i] as taken, we make i-1 its parent

//We first import the dsu class from our graphs file with a few changes to it
//Parent[x] represents the biggest slot available that is <=x
class DisjointSet{
    public:
        vector<int> parent;
        DisjointSet(int n){
            parent.resize(n+1);
            iota(parent.begin(),parent.end(),0);
        }

        int findPar(int node){
            if(node==parent[node]) return node;
            return parent[node]=findPar(parent[node]);
        }

        void unionBySize(int u,int v){
            int pu=findPar(u);
            int pv=findPar(v);
            parent[pu]=pv;
        }
};

vector<int> jobSequencing(vector<int> &deadline,vector<int> &profit){
    int n=deadline.size();
    vector<pair<int,int>> Jobs;
    for(int i=0;i<n;i++) Jobs.push_back({deadline[i],profit[i]});
    sort(Jobs.begin(),Jobs.end(),compare);
    int maxDeadline=*(max_element(deadline.begin(),deadline.end()));

    int jobCnt=0;
    int totalProfit=0;
    DisjointSet ds(maxDeadline+1);
    for(int i=0;i<n;i++){
        int j=ds.findPar(Jobs[i].first);
        if(j==0) continue;
        jobCnt++;
        totalProfit+=Jobs[i].second;
        ds.unionBySize(j,j-1);
    }
    return {totalProfit,jobCnt};
}
//Time taken will be reduced to nlogn + n(time taken by dsu can be assumed constant)
//Space will be the same as the slot space is now occupied by the dsu
//Time Complexity will be O(nlogn+n)
//Space Complexity will be O(n+D)



//N Meetings in one room
class Meeting{
    public:
        int startTime;
        int endTime;
};

bool compare(Meeting a, Meeting b){
    return a.endTime<b.endTime;
}
int nMeetings(vector<int> start,vector<int> end){
    int n=start.size();
    vector<Meeting> meetings(n);
    for(int i=0;i<n;i++) meetings[i]={start[i],end[i]};
    
    sort(meetings.begin(),meetings.end(),compare);
    int meetCount=0;
    int timePassed=0;
    for(int i=0;i<n;i++){
        if(meetings[i].startTime>timePassed){
            timePassed=meetings[i].endTime;
            meetCount++;
        }
    }
    return meetCount;
}


//Non Overlapping Intervals
//Consider [(1,2),(2,3),(3,4),(1,3)]
//We need to remove intervals so that there is no overlap, for eg in this we can remove (1,2) and (2,3), then the remaining intervals would be (1,3) and (3,4)
//There would be no overlap between the remaining intervals. Also unlike many other interval questions, here (1,3) and (3,4) is not considered an overlap
//We can also remove (1,3) then we will be left with (1,2), (2,3) and (3,4), still there's no overlap
//Clearly the second time we only needed to remove 1 interval
//The question asks us the minimum removals
//The minimum removals means we must hold the max number of intervals we can
//Now this question is exactly similar to N meetings, where we were told to hold the max number of meetings in one room
//Do the dry run yourself and find out
//Just remember that unlike the n meetings where if start time was equal to end time of previous meeting then the meeting was not allowed
//Here however that would be allowed
//First let us make a comparator that will sort by endTime
bool cmp_minIntervals(const pair<int,int> &a,const pair<int,int> &b){
    return a.second<b.second;
}
int minIntervals(vector<pair<int,int>> &intervals){
    int n=intervals.size();
    if(n<=1) return 0;
    sort(intervals.begin(),intervals.end(),cmp_minIntervals);
    int cnt=1;
    int timePassed=intervals[0].second;
    for(int i=1;i<n;i++){
        int startTime=intervals[i].first;
        int endTime=intervals[i].second;
        if(startTime>=timePassed){
            cnt++;
            timePassed=endTime;
        }
    }
    return n-cnt;
}
//Time taken will be due to sorting which will be 2nlog(2n) and the loop which will run for 2n times(2n elements)
//Space taken will be due to changing the intervals array, but let us just ignore that
//Time Complexity will be O(2nlog2n + 2n)



//Minimum Platforms Required
int minPlatforms(vector<int> &arr,vector<int> &dep){
    int n=arr.size();
    sort(arr.begin(),arr.end());
    sort(dep.begin(),dep.end());
    //The above steps take 2nlogn time

    int i=0;
    int j=0;
    int maxCnt=0;
    int cnt=0;
    while(i<n){
        if(arr[i]<dep[j]){
            cnt++;
            maxCnt=max(maxCnt,cnt);
            i++;
        }
        else{
            cnt--;
            j++;
        }
    }
    return maxCnt;
}
//Sorting the two arrays take 2nlogn time and the loop takes n time
//Time Complexity will be O(2nlogn+n)



//Valid Parenthesis
//To do this question, first let us solve a simpler question
//Given an expression, containing only ( and ) , tell if it is a valid parenthesis
//Intuition : Use a counter variable, increase it by one when you encounter ( and decrease it by one when you encounter )
//If at last value reaches 0, the parenthesis is valid
//Edge Case : Consider  ())( , in this also the counter gets to 0 at end, however, in such cases, the counter gets negative at one moment
//Therefore if counter<0 at any moment, return false
bool validParenthesisI(string &str){
    int n=str.size();

    //If size of string is odd, parenthesis can never be valid
    if(n%2!=0) return false;

    int cnt=0;
    for(int i=0;i<n;i++){
        if(str[i]=='(') cnt++;
        else cnt--;
        if(cnt<0) return false;
    }
    if(cnt==0) return true;
    return false;
}
//Time Complexity will be O(n)

//Part II
//In this, the string also contains a * which has to be converted to either (, or ) or empty character
//After that the expression will contain only (), then tell if it is valid parenthesis or not
//Since we have three options to convert * , and we need to try all three ways, the question can be solved by recursion
bool parenthesisHelper(int idx,int cnt,string &str){
    if(cnt<0) return false;
    if(idx==str.size()) return cnt==0;
    if(str[idx]=='(') return parenthesisHelper(idx+1,cnt+1,str);
    if(str[idx]==')') return parenthesisHelper(idx+1,cnt-1,str);
    else{
        bool open=parenthesisHelper(idx+1,cnt+1,str);
        bool closed=parenthesisHelper(idx+1,cnt-1,str);
        bool blank=parenthesisHelper(idx+1,cnt,str);
        return (open || closed || blank);
    }
    return true;

}
bool validParenthesisII_brute(string &str){
    return parenthesisHelper(0,0,str);
}
//At each point we have 3 choices to go, in the worst case, the string can be all asterisk, therefore the code will run atmost 3^n times in worst case
//A recursion stack space of n will be used as well
//Time Complexity will be O(3^n)
//Space Complexity will be O(n)

//Memoization
//DP table, say dp[idx][cnt], here idx is the index and cnt is the number of net opening brackets present till there
bool parenthesisHelper_memoization(int idx,int cnt,vector<vector<int>> &dp,string &str){
    if(cnt<0) return false;
    if(idx==str.size()) return cnt==0;
    if(dp[idx][cnt]!=-1) return dp[idx][cnt];
    if(str[idx]=='(') return dp[idx][cnt]=parenthesisHelper_memoization(idx+1,cnt+1,dp,str);
    if(str[idx]==')') return dp[idx][cnt]=parenthesisHelper_memoization(idx+1,cnt-1,dp,str);
    else{
        bool open=parenthesisHelper_memoization(idx+1,cnt+1,dp,str);
        bool closed=parenthesisHelper_memoization(idx+1,cnt-1,dp,str);
        bool blank=parenthesisHelper_memoization(idx+1,cnt,dp,str);
        return dp[idx][cnt]=(open || closed || blank);
    }
    return dp[idx][cnt];
}
bool validParenthesisII_memoization(string &str){
    int n=str.size();
    vector<vector<int>> dp(n,vector<int> (n+1,-1));
    return parenthesisHelper_memoization(0,0,dp,str);
}
//Time Complexity will be O(n2)
//Space Complexity will be O(n2+n)

//Tabulation
bool validParenthesisII_tabulation(string &str){
    int n=str.size();
    vector<vector<int>> dp(n+1,vector<int> (n+1,false));
    dp[n][0]=true;
    for(int idx=n-1;idx>=0;idx--){
        for(int cnt=0;cnt<=n;cnt++){
            if(str[idx]=='(') dp[idx][cnt]=(cnt<n? dp[idx+1][cnt+1]:false);
            else if(str[idx]==')') dp[idx][cnt]=(cnt>0? dp[idx+1][cnt-1]:false);
            else{
                bool open=false;
                bool closed=false;
                if(cnt<n) open=dp[idx+1][cnt+1];
                if(cnt>0) closed=dp[idx+1][cnt-1];
                bool blank=dp[idx+1][cnt];
                dp[idx][cnt]=(open || closed || blank);
            }
        }
    }
    return dp[0][0];
}
//Time Complexity will be O(n2)
//Space Complexity will be O(n2)

//Space Optimisation
bool validParenthesisII_spaceOptimised(string &str){
    int n=str.size();
    vector<bool> next(n+1,false);
    vector<bool> curr(n+1,false);
    next[0]=true;
    for(int idx=n-1;idx>=0;idx--){
        for(int cnt=0;cnt<=n;cnt++){
            if(str[idx]=='(') curr[cnt]=(cnt<n? next[cnt+1]:false);
            else if(str[idx]==')') curr[cnt]=(cnt>0? next[cnt-1]:false);
            else{
                bool open=false;
                bool closed=false;
                if(cnt<n) open=next[cnt+1];
                if(cnt>0) closed=next[cnt-1];
                bool blank=next[cnt];
                curr[cnt]=(open || closed || blank);
            }
        }
        next=curr;
    }
    return curr[0];
}
//Time Complexity will be O(n2)
//Space Complexity will be O(2n)

//Optimal Solution
//The most optimal way to solve this question is by using greedy approach
bool validParenthesisII(string &s){
    int mini=0;
    int maxi=0;
    for(char c:s){
        if(c=='('){
            maxi++;
            mini++;
        }
        else if(c==')'){
            maxi--;
            mini=max(0,mini-1);
        }
        else{
            mini=max(0,mini-1);
            maxi++;
        }
        if(maxi<0) return false;
    }
    return mini==0;
}
//Time Complexity will be O(n)
//Space Complexity will be O(1)



//Min Candy Problem
//The question is extremely simple, just do two iterations, one by only focussing on left neighbours, and one only focussing on right neighbours
int minCandy_naive(vector<int> &arr){
    int n=arr.size();
    vector<int> left(n,1);
    vector<int> right(n,1);
    for(int i=1;i<n;i++) if(arr[i]>arr[i-1]) left[i]=left[i-1]+1;
    for(int i=n-2;i>=0;i--) if(arr[i]>arr[i+1]) right[i]=right[i+1]+1;
    
    vector<int> ans(n,0);
    for(int i=0;i<n;i++) ans[i]=max(left[i],right[i]);
    int totCandies=accumulate(ans.begin(),ans.end(),0);    
    return totCandies;
}
//Time Complexity will be O(4n)
//Space Complexity will be O(3n)

//Brute Method
//We can do the things in the second loop itself
int minCandy_brute(vector<int> &arr){
    int n=arr.size();
    vector<int> left(n,1);
    vector<int> right(n,1);
    for(int i=1;i<n;i++) if(arr[i]>arr[i-1]) left[i]=left[i-1]+1;
    int totCandies=max(1,left[n-1]);
    for(int i=n-2;i>=0;i--){
        if(arr[i]>arr[i+1]) right[i]=right[i+1]+1;
        totCandies+=max(left[i],right[i]);
    }

    return totCandies;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(2n)

//Better Method
int minCandy_better(vector<int> &arr){
    int n=arr.size();
    vector<int> left(n,1);
    for(int i=1;i<n;i++) if(arr[i]>arr[i-1]) left[i]=left[i-1]+1;
    int totCandies=max(1,left[n-1]);
    int right=1;
    for(int i=n-2;i>=0;i--){
        if(arr[i]>arr[i+1]) right++;
        else right=1;
        totCandies+=max(left[i],right);
    }
    return totCandies;
}
//Time Complexity will be O(2n)
//Space Complexity will be O(n)

//Optimal Method
//We use the slope method
int minCandy(vector<int> &arr){
    int n=arr.size();
    int totCandies=1;
    int i=1;
    while(i<n){

        //Flat Surface
        if(arr[i]==arr[i-1]){
            totCandies++;
            i++;
            continue;
        } 

        int peak=1;
        //Increasing Slope
        while(i<n && arr[i]>arr[i-1]){
            peak++;
            totCandies+=peak;
            i++;
        }

        int down=1;
        //Decreasing Slope
        while(i<n && arr[i]<arr[i-1]){
            totCandies+=down;
            down++;
            i++;
        }

        if(down>peak) totCandies+=(down-peak);
    }
    return totCandies;
}
//Only one iteration so n time
//No space taken
//Time Complexity will be O(n)



//Fractional Knapsack Problem
//Try to take the bag which has the most value per one unit weight
//For this we need to sort the array, using a custom comparator
bool cmp_fk(const pair<int,int> &p,const pair<int,int> &q){
    double n=(double)(p.first)/(p.second);
    double m=(double)(q.first)/(q.second);
    return n>m;
}

double fractionalKnapsack(vector<pair<int,int>> &arr,int maxWt){
    int n=arr.size();
    if(n==0 || maxWt<=0) return 0.0;
    sort(arr.begin(),arr.end(),cmp_fk);
    int currWt=0;
    double totVal=0.0;
    for(int i=0;i<n;i++){
        int val=arr[i].first;
        int wt=arr[i].second;

        //If the weight is zero, we take the entire item without changing currWt
        if(wt==0){
            totVal+=val;
            continue;
        }

        //Can't Pick
        if(currWt>=maxWt) break;

        //Picking entirely
        else if(currWt+wt<=maxWt){
            totVal+=val;
            currWt+=wt;
        }

        //Picking up fraction
        else{
            double frac=(double)(val)/(wt);
            totVal+=frac*(maxWt-currWt);
            break;
        }
    }
    return totVal;
}
//Time is taken due to sorting and the one loop
//We also distort the array, so that much space is used
//Time Complexity will be O(n+nlogn)
//Space Complexity will be O(n)





int main(){
    //Your function here
    return 0;
}

