#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>


using namespace std;

ostream & operator << (ostream & os,
                      const vector<int> & v)
{
    for (auto element: v)
        os << element << " ";
    return os;
}

vector<int> v;
vector< vector<int> > ans;

void generate_permutations(size_t n)
{
    if (n == 1)
    {
        ans.push_back(v);
        return;
    }

    for (size_t i = 0; i < n; ++i)
    {
        swap(v[i], v[n-1]);
        generate_permutations(n-1);
        swap(v[i], v[n-1]);
    }

}

template<class T>
pair<int, int> insert_sort(vector<T> A)
{
    size_t n = A.size();
    int comparisons(0);
    int swaps = 0;
    for(size_t i = 1; i < n; ++i)
    {
        for(size_t j = i; j > 0; --j)
        {
            comparisons++;
            if (A[j] < A[j-1])
            {
                swaps++;
                swap(A[j], A[j-1]);
            }
            else
                break;
        }
    }
    return pair<int, int> (comparisons, swaps); //how you push_back into pair sort of
}

int main()
    {
        size_t n;
        cout << "Please enter in a number. I will give you all the permutations of it: ";
        cin >> n;

        for (size_t i = 1; i <= n; ++i)
            v.push_back(i);

        generate_permutations(n);

        vector < pair < vector <int>, pair <int, int> > > vectorception;

        int max_comp(0), max_swaps(0);
        for(int i = 0; i < ans.size(); i ++)
        {
            pair<int, int> cost = insert_sort(ans[i]);
            pair< vector<int>, pair <int, int> > a (ans[i], cost);

            if(a.second.first > max_comp)
                max_comp = a.second.first;

            if(a.second.second > max_swaps)
                max_swaps = a.second.second;

            vectorception.push_back(a);

        }

        cout << "Perm with the greatest cost due to COMPARISONS (" << max_comp << ")" << endl;


        for(int i = 0; i < vectorception.size(); i++)
        {
            if(vectorception[i].second.first == max_comp)
                cout << vectorception[i].first << endl;
        }
        cout << endl;

        cout << "Permutations with the greatest cost due to SWAPS (" << max_swaps << ")" << endl;

        for(int i = 0; i < vectorception.size(); i++)
        {
            if(vectorception[i].second.second == max_swaps)
                cout << vectorception[i].first << endl;
        }
        cout << endl;

        return 0;
    }
