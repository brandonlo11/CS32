void removeOdd(list<int>& li)
{
    for (list<int>::iterator q = li.begin(); q != li.end();){
        if ((*q) % 2 == 1){
            auto remove = q;
            q++;
            li.remove(*remove);
        } else{
        q++;
        }
    }
}
