#pragma once

#include"citizen.h"

#define _CRT_SECURE_NO_WARNING

class CitizenArr
{
private:
    vector<Citizen*> citizens;
public:
    //ctors//
    CitizenArr();
    CitizenArr(const CitizenArr& other);
    ~CitizenArr();
    const CitizenArr& operator=(const CitizenArr& other);
    //setters//
    bool addCitizen(Citizen& add);
    bool SearchById(const long& id) const;
    void printList() const;

    void save(ofstream& outfile) const;
    //getters//
    int size() const { return citizens.size(); }
    int length() const { return citizens.size(); }
    Citizen* PtrToCitizen(long& id);
    Citizen& getCitizenByInx(int idx) { return *citizens[idx]; }//return citizen by index
    const Citizen* getCitizen(long id) const;//search specific id and return referance 
    struct CitizenPtrComp {
        bool operator()(const Citizen* first, const Citizen* second)// ptr to citizen comperator inorder to insert citizens sorted.
        {
            
            return first->getId() < second->getId();
        }
    };
};





