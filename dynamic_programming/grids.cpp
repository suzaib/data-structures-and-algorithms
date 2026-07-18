#include<bits/stdc++.h>
using namespace std;

//2D Dynamic Programming
//Ninja Training
//Brute Force
int fxNT_brute(int idx,int prevTask,vector<vector<int>> &schedule){
    if(idx==0){
        int maxi=0;
        for(int i=0;i<3;i++){
            if(i!=prevTask) maxi=max(maxi,schedule[0][i]);
        }
        return maxi;
    }
    int maxi=0;
    for(int i=0;i<3;i++){
        if(i!=prevTask) maxi=max(maxi,schedule[idx][i]+fxNT_brute(idx-1,i,schedule));
    }
    return maxi;
}
int ninjaTraining_brute(vector<vector<int>> schedule){
    int n=schedule.size();
    return fxNT_brute(n-1,3,schedule);
}

//Memoization
int fxNT_memoization(int idx,int prevTask,vector<vector<int>> &dp,vector<vector<int>> &schedule){
    if(dp[idx][prevTask]!=-1) return dp[idx][prevTask];
    if(idx==0){
        int maxi=0;
        for(int i=0;i<3;i++){
            if(i!=prevTask) maxi=max(maxi,schedule[0][i]);
        }
        return dp[idx][prevTask]=maxi;
    }
    int maxi=0;
    for(int i=0;i<3;i++){
        if(i!=prevTask) maxi=max(maxi,schedule[idx][i]+fxNT_memoization(idx-1,i,dp,schedule));
    }
    return dp[idx][prevTask]=maxi;
}

int ninjaTraining_memoization(vector<vector<int>> schedule){
    int n=schedule.size();
    vector<vector<int>> dp(n,vector<int> (4,-1));
    return fxNT_memoization(n-1,3,dp,schedule);
}

//Tabulation
int ninjaTraining_tabulation(vector<vector<int>> schedule){
    int n=schedule.size();
    vector<vector<int>> dp(n,vector<int>(4,-1));
    dp[0][0]=max(schedule[0][1],schedule[0][2]);
    dp[0][1]=max(schedule[0][0],schedule[0][2]);
    dp[0][2]=max(schedule[0][0],schedule[0][1]);
    dp[0][3]=max(schedule[0][0],max(schedule[0][1],schedule[0][2]));

    for(int day=1;day<n;day++){
        for(int last=0;last<4;last++){
            dp[day][last]=0;
            for(int task=0;task<3;task++){
                if(task!=last){
                    int point=schedule[day][task]+dp[day-1][task];
                    dp[day][last]=max(dp[day][last],point);
                }
            }
        }
    }
    return dp[n-1][3];
}
//Time Complexity will be (3*4*n)
//Space Complexity will be (4n)

//Space Optimization
int ninjaTraining(vector<vector<int>> schedule){
    int n=schedule.size();
    vector<int> dp(4,-1);
    dp[0]=max(schedule[0][1],schedule[0][2]);
    dp[1]=max(schedule[0][0],schedule[0][2]);
    dp[2]=max(schedule[0][0],schedule[0][1]);
    dp[3]=max(schedule[0][0],max(schedule[0][1],schedule[0][2]));

    for(int day=1;day<n;day++){
        vector<int> temp(4,0);
        for(int last=0;last<4;last++){
            temp[last]=0;
            for(int task=0;task<3;task++){
                if(task!=last) temp[last]=max(temp[last],schedule[day][task]+dp[task]);
            }
        }
        dp=temp;
    }
    return dp[3];
}
//Time Complexity will be O(12n)


//Unique Paths in a Grid
//Total ways to clear a grid || Total paths in a grid
//Also we can only move in either right or down direction
//The way we are solving(opposite , from n-1,m-1 to 0,0 we can only move up or left)
//In this question since the grid is useless, we will be only given dimensions of the grid
int fxUP_brute(int x,int y){
    if(x==0 && y==0) return 1;
    if(x<0 || y<0) return 0; //since only moving up or left is allowed therefore the condition x>=n and y>=m is not needed
    int up=fxUP_brute(x-1,y);
    int down=fxUP_brute(x,y-1);
    return (up+down);
}
int uniquePaths_brute(int n,int m){
    return fxUP_brute(n-1,m-1);
}
//Since at every cell(total m*n cells), we have two options, to either move up or left, therefore Time Complexity will be pow(2,m*n)
//Space Complexity will be due to recursion stack space, which will be equal to the path length, which will be in any case equal to (n-1)+(m-1)

//Memoization
int fxUP_mem(int x,int y,vector<vector<int>> &dp){
    if(dp[x][y]!=-1) return dp[x][y];
    if(x==0 && y==0) return dp[x][y]=1;
    if(x<0 || y<0) return 0;
    int up=fxUP_mem(x-1,y,dp);
    int down=fxUP_mem(x,y-1,dp);
    return dp[x][y]=up+down;
}
int uniquePaths_memoization(int n,int m){
    vector<vector<int>> dp(n,vector<int> (m,-1));
    return fxUP_mem(n-1,m-1,dp);
}
//Time Complexity will be total number of dp's that is n*m
//Space Complexity will be n-1+m-1 + n*m(for dp grid)

//Tabulation
int uniquePaths_tabulation(int n,int m){
    vector<vector<int>> dp(n,vector<int> (m,-1));
    dp[0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int up=0;
            int left=0;
            if(i==0 && j==0) continue;
            if(i>0) int up=dp[i-1][j];
            if(j>0) int left=dp[i][j-1];
            dp[i][j]=up+left; 
        }
    }
    return dp[n-1][m-1];
}
//Time Complexity will be O(n*m)
//Space Complexity will be O(n*m)

//Space Optimization
int uniquePaths_spaceOptimized(int n,int m){
    vector<int> prev(m,0);
    for(int i=0;i<n;i++){
        vector<int> curr(m,0);
        for(int j=0;j<m;j++){
            if(i==0 && j==0) curr[j]=1;
            else{
                int up=0;
                int left=0;
                if(i>0) up=prev[j];
                if(j>0) left=curr[j-1];
                curr[j]=up+left;
            }
        }
        prev=curr;
    }
    return prev[m-1];
}

//This can be optimized as well
int uniquePaths(int n,int m){
    vector<int> dp(m,0);
    for(int i=0;i<n;i++){
        int prev=0;
        for(int j=0;j<m;j++){
            if(i==0 && j==0) dp[j]=1;
            else{
                int up=dp[j];
                dp[j]=up+prev;
            }
            prev=dp[j];
        }
    }
    return dp[m-1];
}
//Time complexity will be O(n*m)
//Space Complexity will be O(m)



//Unique Paths with Obstacles
int fxUPII_brute(int i,int j,vector<vector<int>> &mat){
    if(i<0 || j<0) return 0;
    if(mat[i][j]==-1) return 0;
    if(i==0 && j==0) return 1;
    int up=fxUPII_brute(i-1,j,mat);
    int left=fxUPII_brute(i,j-1,mat);
    return (up+left);
}
int uniquePathsII_brute(vector<vector<int>> &mat){
    if(mat[0][0]==-1) return 0;
    int n=mat.size();
    int m=mat[0].size();
    return fxUPII_brute(n-1,m-1,mat);
}

//Memoization
int fxUPII_mem(int i,int j,vector<vector<int>> &mat,vector<vector<int>> &dp){
    if(i<0 || j<0) return 0;
    if(mat[i][j]==-1) return 0;
    if(i==0 && j==0) return dp[i][j]=1;
    if(dp[i][j]!=-1) return dp[i][j];
    int up=fxUPII_mem(i-1,j,mat,dp);
    int left=fxUPII_mem(i,j-1,mat,dp);
    return dp[i][j]=up+left;
}

int uniquePathsII_memoization(vector<vector<int>> &mat){
    if(mat[0][0]==-1) return 0;
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    return fxUPII_mem(n-1,m-1,mat,dp);
}

//Tabulation
int uniquePathsII_tabulation(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    if(mat[0][0]==-1 || mat[n-1][m-1]==-1) return 0;
    vector<vector<int>> dp(n,vector<int> (m,0));
    dp[0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){

            //If this nested loops runs for i=0 and j=0, then the value we stored inside dp[0][0] will get replaced by 0, therefore we must avoid that
            if(i==0 && j==0) continue;
            if(mat[i][j]==-1) dp[i][j]=0;
            else{
                int up=0;
                int left=0;
                if(i>0) up=dp[i-1][j];
                if(j>0) left=dp[i][j-1];
                dp[i][j]=up+left;
            }
        }
    }
    return dp[n-1][m-1];
}

//Space Optimization
int uniquePathsII_spaceOptimization(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    if(mat[0][0]==-1 || mat[n-1][m-1]==-1) return 0;
    vector<int> prev(m,0);
    prev[0]=1;
    for(int j=0;j<m;j++) prev[j]=(mat[0][j]==0? prev[j-1]:0);
    for(int i=0;i<n;i++){
        vector<int> curr(m,0);
        for(int j=0;j<m;j++){
            if(i==0 && j==0)
            if(mat[i][j]==-1) curr[j]=0;
            else{
                int up=0;
                int left=0;
                if(i>0) up=prev[j];
                if(j>0) left=curr[j-1];
                curr[j]=up+left;
            }
        }
        prev=curr;
    }
    return prev[m-1];
}

//Further Optimization
int uniquePathsII(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    if(mat[0][0]==-1) return 0;
    if(mat[n-1][m-1]==-1) return 0;
    vector<int> prev(m,0);
    prev[0]=1;
    for(int i=0;i<n;i++){
        int back=0;
        for(int j=0;j<m;j++){
            if(mat[i][j]==-1) prev[j]=0;
            else{
                int up=0;
                int left=0;
                if(i>0) up=prev[j];
                if(j>0) left=back;
                if(i==0 && j==0) up=1;//This line is only for the initial row (0,0)
                prev[j]=up+left;
            }
            back=prev[j];
        }
    }
    return prev[m-1];
}
//Time Complexity will be O(n*m)
//Space Complexity will be O(m)


//Unique Paths : Minimum Sum along the Path
int upmsHelper_brute(int i,int j,vector<vector<int>> &mat){
    if(i==0 && j==0) return mat[i][j];
    if(i<0 || j<0) return 1e9;
    int up=mat[i][j]+upmsHelper_brute(i-1,j,mat);
    int left=mat[i][j]+upmsHelper_brute(i,j-1,mat);
    return min(up,left);
}
int uniquePathsMinSum_brute(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    return upmsHelper_brute(n-1,m-1,mat);
}

//Memoization
int upmsHelper_mem(int i,int j,vector<vector<int>> &dp,vector<vector<int>> &mat){
    if(i==0 && j==0) return dp[i][j]=mat[i][j];
    if(i<0 || j<0) return 1e9;
    if(dp[i][j]!=-1) return dp[i][j];
    int up=mat[i][j]+upmsHelper_mem(i-1,j,dp,mat);
    int left=mat[i][j]+upmsHelper_mem(i,j-1,dp,mat);
    return dp[i][j]=min(up,left);
}
int uniquePathsMinSum_memoization(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    return upmsHelper_mem(n-1,m-1,dp,mat);
}

//Tabulation
int uniquePathsMinSum_tabulation(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    dp[0][0]=mat[0][0];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i==0 && j==0) continue;
            int up=1e9;
            int left=1e9;
            if(i>0) up=mat[i][j]+dp[i-1][j];
            if(j>0) left=mat[i][j]+dp[i][j-1];
            dp[i][j]=min(up,left);
        }
    }
    return dp[n-1][m-1];
}

//Space Optimization
int uniquePathsMinSum_spaceOptimization(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<int> prev(m,0);
    prev[0]=mat[0][0];
    for(int i=0;i<n;i++){
        vector<int> curr(m,0);
        for(int j=0;j<m;j++){
            if(i==0 && j==0) continue;
            int up=1e9;
            int left=1e9;
            if(i>0) up=mat[i][j]+prev[j];
            if(j>0) left=mat[i][j]+curr[j-1];
            curr[j]=min(up,left);
        }
        prev=curr;
    }
    return prev[m-1];
}

//Further Optimization
int uniquePathsMinSum(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<int> prev(m,0);
    prev[0]=mat[0][0];
    for(int i=0;i<n;i++){
        int back=0;
        for(int j=0;j<m;j++){
            if(i==0 && j==0) continue;
            int up=1e9;
            int left=1e9;
            if(i>0) up=mat[i][j]+prev[j];
            if(j>0) left=mat[i][j]+back;
            back=min(up,left);
            prev[j]=back;
        }
    }
    return prev[m-1];
}
//Time Complexity will be O(NM)
//Space Complexity will be O(M)



//Unique Paths : Variable Ending Point
//Triangle
//Start from the head of a right angled triangle, and end at the last row(any cell of the last row)
//Therefore ending point is variable(can be any cell on the last row)
//In this case instead of writing n different recursions for each cell in the last row, we should write recursion from the top
//And Then compute the min sum
//F(i,j) represents the min sum from starting point i,j to last row
//Traversing is allowed only in two direction, down, and down right diagonal
//We are writing the function when starting point is (0,0), but the function can be modified for any other starting coordinate very easily
int upTriangleHelper_brute(int row,int col,vector<vector<int>> &triangle){
    if(row==triangle.size()-1) return triangle[row][col];

    //Going Down
    int down=triangle[row][col]+upTriangleHelper_brute(row+1,col,triangle);

    //Going Diagonally
    int diagonal=triangle[row][col]+upTriangleHelper_brute(row+1,col+1,triangle);
    return min(down,diagonal);
}
int uniquePathsTriangle_brute(vector<vector<int>> &triangle){
    return upTriangleHelper_brute(0,0,triangle);
}
//At each step, there are two ways the recursion could go, and since there are (1+2+3+...+n) such steps, it would take 2^(n(n+1)/2) time
//Recursion stack space is used as n steps
//Time Complexity will be O(pow(2,n))
//Space Complexity will be O(n)

//Memoization
int upTriangleHelper_memoization(int row,int col,vector<vector<int>> &dp,vector<vector<int>> &triangle){
    if(row==triangle.size()-1) return triangle[row][col];
    if(dp[row][col]!=-1) return dp[row][col];

    //Going Down
    int down=triangle[row][col]+upTriangleHelper_memoization(row+1,col,dp,triangle);

    //Going Diagonally
    int diagonal=triangle[row][col]+upTriangleHelper_memoization(row+1,col+1,dp,triangle);

    return dp[row][col]=min(down,diagonal);
}

int uniquePathsTriangle_memoization(vector<vector<int>> &triangle){
    int n=triangle.size();
    vector<vector<int>> dp(n,vector<int> (n,-1));
    return upTriangleHelper_memoization(0,0,dp,triangle);
}
//The recursion will learn for somewhat lesser than n2 steps(n*n) , but we can say it would be n2 steps
//DP array occupies n2 space and n space is used as recursion stack space
//Time Complexity will be O(n*n) 
//Space Complexity will be O(n2+n)

//Tabulation
int uniquePathsTriangle_tabulation(vector<vector<int>> &triangle){
    int n=triangle.size();
    vector<vector<int>> dp(n,vector<int> (n,0));
    for(int i=0;i<n;i++) dp[n-1][i]=triangle[n-1][i];
    for(int i=n-2;i>=0;i--){
        for(int j=0;j<=i;j++){
            int down=dp[i+1][j];
            int diagonal=dp[i+1][j+1];
            dp[i][j]=triangle[i][j]+min(down,diagonal);
        }
    }
    return dp[0][0];
}
//Time Complexity will be O(n2)
//Space Complexity will be O(n2)

//Space Optimization
int uniquePathsTriangle_spaceOptimized(vector<vector<int>> &triangle){
    int n=triangle.size();
    vector<int> below(n,0);
    vector<int> curr(n,0);
    for(int i=0;i<n;i++) below[i]=triangle[n-1][i];
    for(int i=n-2;i>=0;i--){
        for(int j=0;j<=i;j++){
            int down=below[j];
            int diagonal=below[j+1];
            curr[j]=triangle[i][j]+min(down,diagonal);
        }
        below=curr;
    }
    return curr[0];
}
//Time Complexity will be O(n2)
//Space Complexity will be O(2n)

//Further Optimization
int uniquePathsTriangle(vector<vector<int>> &triangle){
    int n=triangle.size();
    vector<int> curr(n,0);
    for(int i=0;i<n;i++) curr[i]=triangle[n-1][i];
    for(int i=n-2;i>=0;i--){
        for(int j=0;j<=i;j++) curr[j]=triangle[i][j]+min(curr[j],curr[j+1]);
    }
    return curr[0];
}
//Time Complexity will be O(n2)
//Space Complexity will be O(n)



//Unique Paths : Maximum falling sum
int upmxfsHelper_brute(int x,int y,int n,int m,vector<vector<int>> &mat){
    if(x==n-1) return mat[x][y];
    if(x<0 || x>=n || y<0 || y>=m) return 0;
    int down=mat[x][y]+upmxfsHelper_brute(x+1,y,n,m,mat);
    int leftDiag=mat[x][y]+upmxfsHelper_brute(x+1,y-1,n,m,mat);
    int rightDiag=mat[x][y]+upmxfsHelper_brute(x+1,y+1,n,m,mat);
    return max(down,max(leftDiag,rightDiag));
}
int uniquePathsMaxFallingSum_brute(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    int maxSum=0;
    for(int i=0;i<m;i++){
        maxSum=max(maxSum,upmxfsHelper_brute(0,i,n,m,mat));
    }
    return maxSum;
}
//At each level we can have three steps, and there are n such levels. Also the recursion runs for m-1 times(m-1 variable starting points)
//Only recursion stack space is being utilised
//Time Complexity will be O(m*(3^n))
//Space Complexity will be O(n)

//Memoization
int upmxfsHelper_memoization(int x,int y,int n,int m,vector<vector<int>> &dp,vector<vector<int>> &mat){
    if(x==n-1) return dp[x][y]=mat[x][y];
    if(x<0 || x>=n || y<0 || y>=m) return 0;
    if(dp[x][y]!=-1) return dp[x][y];
    int down=mat[x][y]+upmxfsHelper_memoization(x+1,y,n,m,dp,mat);
    int leftDiag=mat[x][y]+upmxfsHelper_memoization(x+1,y-1,n,m,dp,mat);
    int rightDiag=mat[x][y]+upmxfsHelper_memoization(x+1,y+1,n,m,dp,mat);
    return dp[x][y]=max(down,max(leftDiag,rightDiag));
}
int uniquePathsMaxFallingSum_memoization(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    int maxSum=0;
    for(int i=0;i<m;i++){
        maxSum=max(maxSum,upmxfsHelper_memoization(0,i,n,m,dp,mat));
    }
    return maxSum;
}
//There will be a total of n*m times the code will run
//Recursion stack space of n is being used along with the dp array of size n*m
//Time Complexity will be O(n*m)
//Space Complexity will be O(n+m*n)

//Tabulation
int uniquePathsMaxFallingSum_tabulation(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<int>> dp(n,vector<int> (m,0));
    for(int i=0;i<m;i++) dp[n-1][i]=mat[n-1][i];
    for(int i=n-2;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            int down=mat[i][j]+dp[i+1][j];
            int leftDiag=(j>0)? mat[i][j]+dp[i+1][j-1]:-1;
            int rightDiag=(j+1<m)? mat[i][j]+dp[i+1][j+1]:-1;
            dp[i][j]=max(down,max(leftDiag,rightDiag));
        }
    }
    int ans=0;
    for(int i=0;i<m;i++){
        ans=max(ans,dp[0][i]);
    }
    return ans;
}
//Time Complexity will be O(n*m)
//Space Complexity will be O(n*m)

//Space Optimization
//This is the most optimal approach, we can't trim it down to a single array since movement is in three ways.
int uniquePathsMaxFallingSum(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<int> below=mat[n-1];
    vector<int> curr(m,0);
    for(int i=n-2;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            int down=mat[i][j]+below[j];
            int leftDiag=(j>0)? mat[i][j]+below[j-1]:-1;
            int rightDiag=(j<m-1)? mat[i][j]+below[j+1]:-1;
            curr[j]=max(down,max(leftDiag,rightDiag));
        }
        below=curr;
    }
    int ans=0;
    for(int i=0;i<m;i++) ans=max(ans,below[i]);
    return ans;
}
//Time Complexity will be O(n*m)
//Space Complexity will be O(2m)




//Minimum Falling Sum
int upmnfsHelper_brute(int x,int y,int n,int m,vector<vector<int>>& mat){
    if(x==0) return mat[x][y];
    if(x<0 || x>=n || y<0 || y>=m) return 1e9;
    int up=mat[x][y]+upmnfsHelper_brute(x-1,y,n,m,mat);
    int leftUp=mat[x][y]+upmnfsHelper_brute(x-1,y-1,n,m,mat);
    int rightUp=mat[x][y]+upmnfsHelper_brute(x-1,y+1,n,m,mat);
    return min(up,min(leftUp,rightUp));
}
int uniquePathsMinFallingSum_brute(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    int minSum=INT_MAX;
    for(int i=m-1;i>=0;i--) minSum=min(minSum,upmnfsHelper_brute(n-1,i,n,m,mat));
    return minSum;
}
//Time Complexity will be O(m*(3^n))
//Space Complexity will be O(n)

//Memoization
int upmnfsHelper_memoization(int x,int y,int n,int m,vector<vector<int>> &dp,vector<vector<int>> &mat){
    if(x==0) return mat[x][y];
    if(x<0 || x>=n || y<0 || y>=m) return 1e9;
    if(dp[x][y]!=-1) return dp[x][y];
    int up=mat[x][y]+upmnfsHelper_memoization(x-1,y,n,m,dp,mat);
    int leftUp=mat[x][y]+upmnfsHelper_memoization(x-1,y-1,n,m,dp,mat);
    int rightUp=mat[x][y]+upmnfsHelper_memoization(x-1,y+1,n,m,dp,mat);
    return dp[x][y]=min(up,min(leftUp,rightUp));
}
int uniquePathsMinFallingSum_memoization(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    int minSum=INT_MAX;
    vector<vector<int>> dp(n,vector<int> (m,-1));
    for(int i=m-1;i>=0;i--) minSum=min(minSum,upmnfsHelper_memoization(n-1,i,n,m,dp,mat));
    return minSum;
}
//There will be a total of n*m times the code will run
//Recursion stack space of n is being used along with the dp array of size n*m
//Time Complexity will be O(n*m)
//Space Complexity will be O(n+m*n)

//Tabulation
int uniquePathsMinFallingSum_tabulation(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<int>> dp(n,vector<int> (m,-1));
    for(int i=0;i<m;i++) dp[0][i]=mat[0][i];
    for(int i=1;i<n;i++){
        for(int j=0;j<m;j++){
            int up=mat[i][j]+dp[i-1][j];
            int leftUp=(j>0 ? mat[i][j]+dp[i-1][j-1]:1e9);
            int rightUp=(j<m-1 ? mat[i][j]+dp[i-1][j+1]:1e9);
            dp[i][j]=min(up,min(leftUp,rightUp));
        }
    }
    int ans=INT_MAX;
    for(int i=0;i<m;i++) ans=min(ans,dp[n-1][i]);
    return ans;
}
//Time Complexity will be O(n*m)
//Space Complexity will be O(n*m)

//Space Optimization
int uniquePathsMinFallingSum(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<int> prev=mat[0];
    for(int i=1;i<n;i++){
        vector<int> curr(m,0);
        for(int j=0;j<m;j++){
            int up=mat[i][j]+prev[j];
            int leftUp=(j>0 ? mat[i][j]+prev[j-1]:1e9);
            int rightUp=(j<m-1 ? mat[i][j]+prev[j+1]:1e9);
            curr[j]=min(up,min(leftUp,rightUp));
        }
        prev=curr;
    }
    int ans=INT_MAX;
    for(int i=0;i<m;i++) ans=min(ans,prev[i]);
    return ans;
}
//Time Complexity will be O(n*m)
//Space Complexity will be O(2m)



//Cherry Pickup OR Chocolate Pickup
int cherryPickupHelper_brute(int x,int y1,int y2,int n,int m,vector<vector<int>> &mat){
    if(y1<0 || y1>=m || y2<0 || y2>=m) return -1e9;
    if(x==n-1){//We need to check if they have reached the same cell or not
        if(y1==y2) return mat[x][y1];//If they reach same cell, we return the value of that cell only once
        return (mat[x][y1]+mat[x][y2]);//If they reach different cells, then we return the sum of those two cells
    }


    int maxi=INT_MIN;
    int point=(y1==y2 ? mat[x][y1] : mat[x][y1]+mat[x][y2]);
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++) maxi=max(maxi,point+cherryPickupHelper_brute(x+1,y1+i,y2+j,n,m,mat));
    }
    return maxi;
}
int cherryPickup_brute(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    return cherryPickupHelper_brute(0,0,m-1,n,m,mat);
}
//The code will obviously run for n rows along with which at each row, it can move into 9 different ways, therefore the code will run for about 9^n times
//A recursion stack space of about n will be used
//Time Complexity will be O(9^n)
//Space Complexity will be O(n)

//Memoization
int cherryPickupHelper_memoization(int x,int y1,int y2,int n,int m,vector<vector<vector<int>>> &dp,vector<vector<int>> &mat){
    if(y1<0 || y1>=m || y2<0 || y2>=m) return -1e9;
    if(dp[x][y1][y2]!=-1) return dp[x][y1][y2];
    if(x==n-1){
        int temp;
        if(y1==y2) temp=mat[x][y1];
        else temp=mat[x][y1]+mat[x][y2];
        return dp[x][y1][y2]=temp; 
    }

    int point=(y1==y2 ? mat[x][y1] : mat[x][y1]+mat[x][y2]);
    int maxi=INT_MIN;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            maxi=max(maxi,point+cherryPickupHelper_memoization(x+1,y1+i,y2+j,n,m,dp,mat));
        }
    }
    return dp[x][y1][y2]=maxi;
}

int cherryPickup_memoization(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<vector<int>>> dp(n,vector<vector<int>> (m,vector<int> (m,-1)));
    return cherryPickupHelper_memoization(0,0,m-1,n,m,dp,mat);
}
//Total times the loop can run will be n*m*m times and inside also it runs 9 times
//Total space is n for recursion stack space and n*m*m for 3d dp array
//Time Complexity will be O(9*n*m*m)
//Space Complexity will be O(n+n*m*m)

//Tabulation
int cherryPickup_tabulation(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<vector<int>>> dp(n,vector<vector<int>> (m,vector<int> (m,0)));
    for(int j=0;j<m;j++){
        for(int k=0;k<m;k++) dp[n-1][j][k]=(j==k ? mat[n-1][j] : mat[n-1][j]+mat[n-1][k]);
    }

    for(int i=n-2;i>=0;i--){
        for(int j=0;j<m;j++){
            for(int k=0;k<m;k++){
                int point=(j==k ? mat[i][j] : mat[i][j]+mat[i][k]);
                int maxi=-1e9;
                for(int x=-1;x<=1;x++){
                    for(int y=-1;y<=1;y++){
                        int nj=j+x;
                        int nk=k+y;
                        if(nj>=0 && nj<m && nk>=0 && nk<m) maxi=max(maxi,point+dp[i+1][nj][nk]);
                    }
                }
                dp[i][j][k]=maxi;
            }
        }
    }
    return dp[0][0][m-1];
}
//Time Complexity will be O(9*n*m*m)
//Space Complexity will be O(n*m*m)

//Space Optimization
int cherryPickup(vector<vector<int>> &mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<vector<int>> after(m,vector<int> (m,0));
    vector<vector<int>> curr(m,vector<int> (m,0));
    for(int j=0;j<m;j++){
        for(int k=0;k<m;k++){
            after[j][k]=(j==k ? mat[n-1][j] : mat[n-1][j]+mat[n-1][k]);
        }
    }

    for(int i=n-2;i>=0;i--){
        for(int j=0;j<m;j++){
            for(int k=0;k<m;k++){
                int point=(j==k ? mat[i][j] : mat[i][j]+mat[i][k]);
                int maxi=-1e9;
                for(int x=-1;x<=1;x++){
                    for(int y=-1;y<=1;y++){
                        int nj=j+x;
                        int nk=k+y;
                        if(nj>=0 && nj<m && nk>=0 && nk<m) maxi=max(maxi,point+after[nj][nk]);
                    }
                }
                curr[j][k]=maxi;
            }
        }
        after=curr;
    }
    return after[0][m-1];
}
//Time Complexity will be O(9*n*m)
//Space Complexity will be O(2*m*m)

