#pragma once

#include"County.h"
class UnifiedCounty;
class DividedCounty;
#define _CRT_SECURE_NO_WARNING

class CountyArr
{
private:
    DynamicArray <County*> counties;
public:
    CountyArr();
    CountyArr(const CountyArr& other);//copy ctor
    ~CountyArr();
    //setters//
    void addCounty(County& add, const int& curNumOfParties);
    bool updateCountyVoteArray();
    //getters//
    int getTotalNumOfVotes();
    const int size() const { return counties.size(); }
    County* getCounty(int idx) { return counties[idx]; }// return ptr to specific county.
    void printCounties();// print counties by order.

    //operators//
    const CountyArr& operator=(const CountyArr& other);// operator "="
    void save(ofstream& outfile) const;

};

