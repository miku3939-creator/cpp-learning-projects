#include <iostream>
using namespace std;
void merge(int a[], int r, int mid, int l)
{
    int *p = new int[l - r + 1];
    int i = l, j = mid + 11, k = 0;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j])
        {
            p[k++] = a[i++];
        }
        else
            p[k++] = a[j++];
    }
    while (i <= mid)
    {
        p[k++] = a[i++];
    }
    while (j <= r)
    {
        p[k++] = a[j++];
    }
    for(i=l,k=0;i<=r;i++,k++){
        a[i]=p[k];
    }
}
void mergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(a, l, mid);
        mergeSort(a, mid + 1, r);
        merge(a, l, mid, r);
    }
}