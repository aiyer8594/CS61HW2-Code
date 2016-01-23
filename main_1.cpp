#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

ostream & operator <<(ostream & os, const vector<int> & vec)
{
    for (auto e: vec)
    {
        os << e << " ";
    }
    return os;
}

int comp;
vector<int> vec;
vector< vector<int> > ans;

template <class T, class SizeType>
void merge(T A[], SizeType lo, SizeType mid, SizeType hi)
{
    SizeType n(hi-lo+1);
    T *temp = new T[n];
    SizeType i(lo), j(mid+1);

    for (SizeType k = 0; k < n; ++k)
    {
        if (i > mid)
            temp[k] = A[j++];
        else if (j > hi)
            temp[k] = A[i++];
        else if (A[j] < A[i])
        {
            temp[k] = A[j++];
            comp++;
}
        else
        {
            temp[k] = A[i++];
            comp++;
}
    }
    std::copy(temp, temp+n, A+lo);
}

template <class T, class SizeType>
void mergesort(T A[], SizeType lo, SizeType hi)
{
    if (lo < hi)
    {
        SizeType mid = (lo+hi)/2;
        mergesort(A,lo,mid);
        mergesort(A,mid+1,hi);
        merge(A,lo,mid,hi);
    }
}

void generateperms(size_t n)
{
    if (n == 1)
    {

        ans.push_back(vec);
        return;
    }

    for (size_t i = 0; i < n; ++i)
    {
        swap(vec[i], vec[n-1]);
        generateperms(n-1);
        swap(vec[i], vec[n-1]);
    }
}

int main()
{

    int worstcomp=0;
    int totalcomp=0;
    size_t n;
    cout << "Enter size: ";
    cin >> n;
    for (size_t i = 1; i <= n; ++i)
        vec.push_back(i);

    generateperms(n);

    for(int i=0;i<ans.size();++i)
    {
        comp = 0;

        int*temp = new int[n];
        std::copy(ans[i].begin(),ans[i].end(),temp);
        mergesort(temp,0u,n-1);
        totalcomp += comp;
                pair<vector<int>, int> alpha (ans[i], comp);
        if(worstcomp < alpha.second)
                worstcomp = alpha.second;
        if(alpha.second > worstcomp)
                worstcomp = alpha.second;
    }
    cout << endl;
    cout << "Permutations with the worst comparisons:" << worstcomp << endl;
    cout << "Permutations with the average comparisons:" << (double)totalcomp/ans.size() << endl;
    return 0;
}
