void removeOdd(vector<int>& v)
{
    for (vector<int>::iterator i = v.begin(); i != v.end();) {
        if ((*i) % 2 == 1){
            i = v.erase(i);
        }
        else{
            i++;
        }
    }
}
