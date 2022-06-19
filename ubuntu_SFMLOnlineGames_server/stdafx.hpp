// header.h
#ifndef HEADER_H
#define HEADER_H

//Core
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>

#include <sys/epoll.h>

//SFML
#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

template<typename T>
class myvec{
public:
    int size=0;
    std::map<T,int> mp;
    std::vector<T> vec;
    bool isIn(T t);
    void push_back(T t);
    void erase(T t);
    void clear();
};
template<typename T>
bool myvec<T>::isIn(T t){
    if(this->mp.count(t))
        return true;
    return false;
}
template<typename T>
void myvec<T>::push_back(T t){
    this->mp[t]=this->size;
    this->size++;
    this->vec.push_back(t);
}
template<typename T>
void myvec<T>::erase(T t){
    if(isIn(t)){
        this->mp[vec[this->size-1]]=this->mp[t];
        std::swap(this->vec[this->mp[t]],this->vec[this->size-1]);
        this->mp.erase(t);
        this->vec.pop_back();
        this->size--;
    }
}
template<typename T>
void myvec<T>::clear(){
    this->size=0;
    this->mp.clear();
    this->vec.clear();
    //this->vec.swap(std::vector<T>());
}


#endif

