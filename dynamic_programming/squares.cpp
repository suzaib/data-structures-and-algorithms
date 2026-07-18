
#include<bits/stdc++.h>
using namespace std;


//DP on Rectangles
//Maximum Rectangle Area with all 1s
//For this problem it is needed that we understand the question "Largest rectangle in histogram" which is in the stacks and queue playlist
//We are attaching the optimal solution for that problem 
int largestRectInHist(vector<int> &arr){
    int n=arr.size();
    stack<pair<int,int>> st;
    int maxArea=0;
    for(int i=0;i<n;i++){
        while(!st.empty() && st.top().first>=arr[i]){
            int x=st.top().first;
            st.pop();
            int pse=(st.empty() ? -1:st.top().second);
            int area=x*(i-pse-1);
            maxArea=max(area,maxArea);
        }
        st.push({arr[i],i});
    }
    int nse=n;
    while(!st.empty()){
        int x=st.top().first;
        st.pop();
        int pse=(st.empty()? -1:st.top().second);
        int area=x*(nse-pse-1);
        maxArea=max(maxArea,area);
    }
    return maxArea; 
}
//Time Complexity will be O(2n)
//Space Complexity will be O(2n)

//Now we use this formula to solve maximalRectangles problem
//The question and hence the solution is also there, with the same name
int maxRectangle(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    if(n==0 || m==0) return 0;
    vector<int> hist(m,0);
    int maxArea=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mat[i][j]==1) hist[j]++;
            else hist[j]=0;
        }
        int area=largestRectInHist(hist);
        maxArea=max(area,maxArea);
    }
    return maxArea;
}
//The first loop runs n times and inside it two loop of n time
//Space is used by the hist array and by the largestRect function 
//Time Complexity will be O(3n2)
//Space Complexity will be O(3n)


//Count Square Submatrices with all Ones
//DP[i][j] represents the number of square submatrices ending in i,j(rightmost corner is i,j)
int countSquareSubmatrices_tabulation(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<int>> dp(n,vector<int> (m,0));

    int totalSubMatrices=0;

    //Let us fill the first row and first column
    //The first row and first column will have the same value as the matrix
    for(int j=0;j<m;j++){
        dp[0][j]=mat[0][j];
        totalSubMatrices+=dp[0][j];
    }

    for(int i=1;i<n;i++){
        dp[i][0]=mat[i][0];
        totalSubMatrices+=dp[i][0];
    }

    //Now we start our loop
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){

            //We only fill when mat[i][j] has 1
            if(mat[i][j]==1){
                int minValue=min(dp[i-1][j-1],min(dp[i][j-1],dp[i-1][j]));
                dp[i][j]=1+minValue;
            }
            totalSubMatrices+=dp[i][j];

        }
    }
    return totalSubMatrices;
}
//The code runs for mn time
//Space is occupied by the dp table of mn size
//Time Complexity will be O(mn)
//Space Complexity will be O(mn)

//Space Optimisation
int countSquareSubmatrices_spaceOptimisation(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    
    int ans=0;
    vector<int> prev(m,0);
    vector<int> curr(m,0);
    for(int j=0;j<m;j++){
        prev[j]=mat[0][j];
        ans+=prev[j];
    }

    for(int i=1;i<n;i++){
        curr[0]=mat[i][0];
        ans+=curr[0];
        for(int j=1;j<m;j++){
            if(mat[i][j]==1){
                int minValue=min(prev[j-1],min(prev[j],curr[j-1]));
                curr[j]=1+minValue;
            }
            else curr[j]=0;
            ans+=curr[j];
        }
        prev=curr;
    }

    return ans;
}
//The total combined time for loops is mn
//Space is occupied by curr and prev array
//Time Complexity will be O(mn)
//Space Complexity will be O(2m)

//Further Optimisation
int countSquareSubmatrices(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();

    vector<int> dp(m,0);
    int ans=0;
    for(int j=0;j<m;j++){
        dp[j]=mat[0][j];
        ans+=dp[j];
    }

    for(int i=1;i<n;i++){
        int diag=dp[0];
        dp[0]=mat[i][0];
        ans+=dp[0];
        for(int j=1;j<m;j++){
            int temp=dp[j];
            if(mat[i][j]==1){
                int minValue=min(diag,min(dp[j-1],dp[j]));
                dp[j]=1+minValue;
            }
            else dp[j]=0;
            ans+=dp[j];
            diag=temp;
        }
    }

    return ans;
}
//The total time taken by loops is mn
//Space is occupied by the single 1D dp array
//Time Complexity will be O(mn)
//Space Complexity will be O(m)



int main(){
    return 0;
}
