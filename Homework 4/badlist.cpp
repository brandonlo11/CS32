void removeBad(list<Movie*>& li)
{
    for (list<Movie*>::iterator i = li.begin(); i != li.end();) {
        if((*i)->rating() <= 50){
            delete *i;
            auto remove = i;
            i++;
            li.erase(remove);
        } else {
            i++;
        }
    }
}
