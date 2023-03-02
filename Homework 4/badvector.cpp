void removeBad(vector<Movie*>& v)
{
    for (vector<Movie*>::iterator i = v.begin(); i != v.end();) {
        if ((*i)->rating() <= 50){
            delete *i;
            i = v.erase(i);
        }
        else{
            i++;
        }
    }
}
