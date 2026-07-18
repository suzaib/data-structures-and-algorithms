//This file contains binary search questions on 2d arrays

//Unless stated otherwise, the space complexity of the solutions is O(1), that is constant space

//Binary search on matrices is applied when we notice that each row is sorted, that is when we call the matrix as a sorted matrix

#include<bits/stdc++.h>
using namespace std;

//Find row with maximum 1's
//Brute Force : Simple Iteration
int rowWithMax1_brute(vector<vector<int>> mat){
    int rows=mat.size();
    int cols=mat[0].size();
    int ans=0;
    int cnt=0;
    int maxCnt=0;
    for(int i=0;i<rows;i++){
        cnt=0;
        for(int j=0;j<cols;j++){
            if(mat[i][j]==1) cnt++;
        }
        if(cnt>maxCnt){
            ans=i;
            maxCnt=cnt;
        }
    }
    return ans;
}
//Time Complexity will be O(n*m)

//The optimal solution in this case would be using the binary search
//If an arras is like this : {0,0,1,1} then we need to find the first occurence of 1 using binary search, then we do n-i (where n is the length of array 
//& i is the index of first occ)
//Therefore we first create a function to find the first occ of an element
int firstOcc(vector<int> arr,int k){
    int n=arr.size();
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=((low+high)>>1);
        if(arr[mid]>=k) high=mid-1;
        else low=mid+1;
    }
    if(arr[low]!=k) return -1;
    return low;
}
//Time Complexity is O(log n)

int rowWithMax1(vector<vector<int>> mat){
    int rows=mat.size();
    int cols=mat[0].size();
    int cnt=0;
    int maxCnt=0;
    int ans=-1;
    for(int i=0;i<rows;i++){
        int j=firstOcc(mat[i],1);
        if(j==-1) continue;
        int n=mat[i].size();
        cnt=n-j;
        if(cnt>maxCnt){
            ans=i;
            maxCnt=cnt;
        }
    }
    return ans;
}
//Time complexity will be O(n*log m)


//Search in a matrix
//Brute Force : Simple traversal
vector<int> searchInAMatrix_brute(vector<vector<int>> mat,int target){
    int rows=mat.size();
    int cols=mat[0].size();
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(mat[i][j]==target) return {i,j};
        }
    }
    return {-1};
}
//Time Complexity will be O(n*m) 

//If the array is sorted, then the solution can be optimised using binary Search
//Steps : Suppose we are searching for 23 in a sorted matrix, Here we are assuming that the whole matrix is sorted, 
//We go to the first row and see its first and last element(say 3 and 13), since target doesn't lie between them, we skip that row and move to next
//When we find a row that contains the target we use binary search on that row using the firstOcc function
vector<int> searchInAMatrix_better(vector<vector<int>> mat,int target){
    int rows=mat.size();
    int cols=mat[0].size();
    for(int i=0;i<rows;i++){
        if(target>mat[i][cols-1] || target<mat[i][0]) continue;
        int ind=firstOcc(mat[i],target);
        if(ind==-1) return {-1};
        else return {i,ind};
    }
    return {-1};
}
//Time Complexity will be O(n) + O(log m) (yes, addition and not n*log m) (Reason being that the binary search condition will only be executed once)

//If however, the whole matrix is sorted(instead of just rows) then we can even optimise this code
//The first step would be to flatten the matrix, However if we flatten it would take n*m time (Flattening : {{1,2,3},{4,5,6}} ==> {1,2,3,4,5,6})
//We therefore try to think of flattening it inside our head. The main part is to how to know an element's location in 1d and 2d , for eg
// 4 lies on (1,0) in 2d and on index 3 in 1d. So we need a formula to convert coordinates into index
vector<int> idxToCoordinates(vector<vector<int>> mat,int idx){
    int m=mat[0].size();
    int x=idx/m;
    int y=idx%m;
    return {x,y};
}
//Constant Time : O(1)

//We also create another function, which may help us
int coordinatesToIdx(vector<vector<int>> mat,vector<int> arr){
    int x=arr[0];
    int y=arr[1];
    int m=mat[0].size();
    int ind=(x*(m-1))+(x*y)+1;
    return ind;
}
//Constant Time : O(1)

//We can now write our function
vector<int> searchInAMatrix(vector<vector<int>> mat,int target){
    int n=mat.size();
    int m=mat[0].size();
    if(target>mat[n-1][m-1] || target<mat[0][0]) return {-1};
    int low=0;
    int high=(n*m)-1;
    while(low<=high){
        int mid=((low+high)>>1);
        vector<int> coord=idxToCoordinates(mat,mid);
        int x=coord[0];
        int y=coord[1];
        if(mat[x][y]>=target) high=mid-1;
        else low=mid+1;
    }
    vector<int> ans=idxToCoordinates(mat,low);
    if(mat[ans[0]][ans[1]]!=target) return {-1};
    return ans;
}
//Time Complexity will be O(log n*m)


//Searching in a matrix which is not fully sorted , but sorted row and column wise, for eg consider : {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}}
//We can employ our earlier techniques(except of flattening one, since the whole array is not sorted)
//We can use the condition of eliminating a whole row at once by comparing if target lies in row[0] and row[n-1] that is between the row
//However we have an even better method : 
//Watch video !! absolutely necessary
vector<int> searchInAMatrix2(vector<vector<int>> mat,int target){
    int n=mat.size();
    int m=mat[0].size();
    int r=0;
    int c=m-1;
    while(r<n && c>=0){
        if(mat[r][c]>target) c--;
        else if(mat[r][c]<target) r++;
        else return {r,c};
    }
    return {-1};
}
//Time Complexity will be O(n+m) 


//Peak element II 
//An element in a matrix which is greater than its top, bottom, right, and left is called peak element in a matrix
//For first element(0,0) left doesn't exist, in such cases, take it to be -1
//We have to return coordinates of any peak element
//Brute Force : Traversing every element in the matrix and comparing it with its neighbours
vector<int> peakElement_brute(vector<vector<int>> mat){
    int n=mat.size();
    int m=mat[0].size();
    int top;
    int left;
    int bottom;
    int right;
    int el;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            el=mat[i][j];
            j>0? left=mat[i][j-1]:left=-1;
            i>0? top=mat[i-1][j]:top=-1;
            j<m-1? right=mat[i][j+1]:right=-1;
            i<n-1? bottom=mat[i+1][j]:bottom=-1;
            if(el>top && el>right && el>bottom && el>left) return {i,j};
        }
    }
    return {-1};
}
//Time Complexity is n*m*4 (multiplication by 4 since we check four times)
//This can be optimised a bit further, since we have to return coordinates of any peak element, therefore if we return the coordinates of the max element
//It should work, as this would have time complexity of n*m

//Better Approach : Find the max element
vector<int> peakElement_better(vector<vector<int>> mat){
    int n=mat.size();
    int m=mat[0].size();
    int maxEl=INT_MIN;
    int maxX=-1;
    int maxY=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int curr=mat[i][j];
            if(curr>maxEl){
                maxX=i;
                maxY=j;
                maxEl=curr;
            }
        }
    }
    return {maxX,maxY};
}
//Time Complexity will be O(n*m)
//This code can fail for some test cases for eg, if the max element is repeated and lie adjacently to its duplicates

//Optimal approach : Watch video for explanation
//We will need a function that caculates the max element in a column
int maxInCol(vector<vector<int>> mat,int col){
    int n=mat.size();
    int m=mat[0].size();
    int maxEl=INT_MIN;
    int maxIdx;
    for(int i=0;i<n;i++){
        if(mat[i][col]>maxEl){
            maxEl=mat[i][col];
            maxIdx=i;
        }
    }
    return maxIdx;
}
//Time Complexity will be O(n)

vector<int> peakElement(vector<vector<int>> mat){
    int n=mat.size();
    int m=mat[0].size();
    int low=0;
    int high=m-1;
    while(low<=high){
        int mid=((low+high)>>1);
        int maxIdx=maxInCol(mat,mid);
        int maxEl=mat[maxIdx][mid];
        int right;
        int left;
        mid>0? left=mat[maxIdx][mid-1]:left=-1;
        mid<m-1? right=mat[maxIdx][mid+1]:right=-1;
        if(maxEl>left && maxEl>right) return {maxIdx,mid};
        if(maxEl<left) high=mid-1;
        else low=mid+1;
    }
    return {-1,-1};
}
//Time complexity will be O(n) (for maxInCol) * O(mlogm)


//Median in a row wise sorted matrix
//Median here means, the middle value when all the values are arranged in a sorted order
//Matrix is of order n*m where both n and m are odd
//In Brute force we store all the elements in an array, then sort the array, then return the median element
int medianInARowWiseSortedMatrix_brute(vector<vector<int>> mat){
    int n=mat.size();
    int m=mat[0].size();
    vector<int> arr;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            arr.push_back(mat[i][j]);
        }
    }
    sort(arr.begin(),arr.end());
    //Since the size of array will always be odd, the median would be at index (n*m)/2 (n*m is the total size of array)
    return arr[(n*m)/2];
}
//Time complexity will be : O(m*n) (two loops) + O((n*m)log(n*m)) (for sorting array of size n*m)
//Space Complexity will be O(n*m)


//Optimal code involves binary search, Watch video for intuition
//Code for upperbound will be needed for blackbox
int upperBound(vector<int> arr,int x){
    int n=arr.size();
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=((low+high)>>1);
        if(arr[mid]>x) high=mid-1;
        else low=mid+1;
    }
    return low;
}
//Time Complexity will be O(nlogn) 

//Code for blackbox
int blackBox(vector<vector<int>> mat, int idx){
    int n=mat.size();
    int m=mat[0].size();
    int cnt=0;
    for(int i=0;i<n;i++){
        cnt+=upperBound(mat[i],idx);
    }
    return cnt;
}
//Time Complexity will be O(n*nlogn)

int medianInARowWiseSortedMatrix(vector<vector<int>> mat){
    int n=mat.size();
    int m=mat[0].size();

    int low=INT_MAX;
    int high=INT_MIN;
    for(int i=0;i<n;i++){
        low=min(low,mat[i][0]);
        high=max(high,mat[i][m-1]);
    }

    int k=((n*m)>>1);
    while(low<=high){
        int mid=((low+high)>>1);
        int lesserThan=blackBox(mat,mid);
        if(lesserThan>k) high=mid-1;
        else low=mid+1;
    }
    return low;
}
//Time Complexity will be O(n) + O(klogk + n*logn)
//k is the range of numbers in the matrix

int main(){
    //function here
    return 0;
}
