bool anyFalse(const double a[], int n)
{
    if (n <= 0){
        return false;
    }
    if (!somePredicate(a[n-1])){
        return true;
    }
    return anyFalse(a, n-1);
}

int countFalse(const double a[], int n)
{
    if (n <= 0){
        return 0;
    }
    int counter = 0;
    if (!somePredicate(a[n-1])){
        counter++;
    }
    return counter + countFalse(a, n-1);
}

int firstTrue(const double a[], int n)
{
    if (n == 0) {
        return -1;
    }
    if (somePredicate(a[0]) == true){
        return 0;
    }
    int x = firstTrue(a+1, n-1);
    x = (x == -1) ? -1 : 1 + x;
    return x;
    
}

int locateMax(const double a[], int n)
{
    if (n <= 0){
        return -1;
    }
    if (n == 1){
        return 0;
    }
    int mid = n/2;
    int max1 = locateMax(a, mid);
    int max2 = locateMax(a+mid, n-mid) + mid;
    if (a[max1] >= a[max2]){
        return max1;
    }
    else{
        return max2;
    }
}

bool contains(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0){
        return true;
    }
    if (n1 < n2){
        return false;
    }
    if (a1[0] == a2[0]){
        return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    else{
        return contains(a1 + 1, n1 - 1, a2, n2);
    }
}
