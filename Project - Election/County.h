#pragma once
#include "CitizenArr.h"

#include <iostream>
#define _CRT_SECURE_NO_WARNING
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class PartyArr;

using namespace std;
class County
{
protected:
    string CountyName;
    int NumOfRep;//represenative
    CitizenArr eligibleCitizen;//eligible citiizen for spefific county
    static int countySerialNumber;
    int countyId;
    int   numOfVotes = 0;
    DynamicArray<int> VoteCountyArray ; //how much votes per party
    DynamicArray<int> ElectorsByIdx ;
    DynamicArray<float> restArrayVoters;
    int MaxPartyVotesIndex;
   
public:
    County(const string _CountyName, int _NumOfRep);
    County();
    County(const County& other);//copy ctor
    County(ifstream& inFile);
    virtual  ~County();

    //setters//

    bool AddCitizen(Citizen& add) { return eligibleCitizen.addCitizen(add); }// add new citizen to the county.
    bool setMaxPartyVotesIndex(int& PartyIdx) { MaxPartyVotesIndex = PartyIdx; return true; }
    bool setVoteById(int& idx) { VoteCountyArray[idx] = -1; return true; }//when we count the number of votes , insert -1
    virtual bool SetElectorsToParty(PartyArr& PartyArray) = 0 ;
    virtual void PrintRepByCounty(PartyArr& PartyArray) = 0 ;
    bool ResizeVoteArray();// update the size of array
    bool UpdateVoteArray(int& partyIdx) { VoteCountyArray[partyIdx - 1]++; numOfVotes++; return true; }//update after vote
    bool UpdateVoteArrayToRep();// calcualte how many reps each party gets [electors]
    bool UpdateRestArrayVoters();
    void MostVotedParty();// calculate num of votes for each party by the county's citizens.
    void CreateVoteArrayFromFile(ifstream& inFile);
    static void resetCounter() { countySerialNumber = 0; }
    

    //getters//
    const string getName() const { return CountyName; }
    const int getNumOfRep() const { return NumOfRep; }
    int getCountyId() const { return countyId; }
    int getNumOfVotes() const { return numOfVotes; }
    int getNumOfElectors(int& idx)const { return ElectorsByIdx[idx]; }
    const int getVoteArrayLogic() const { return VoteCountyArray.size(); }

    int getVoteByIdx(int& idx)const { return VoteCountyArray[idx]; }
    int getMaxPartyVotesIndex() { return MaxPartyVotesIndex; }
    int getSizeOfEligiblE()const { return eligibleCitizen.size(); }
    int FindMaxValueIdx();
    CitizenArr* getCitizenList() { return &eligibleCitizen; }//return eligible citizen list to election's voters list.
    bool InitVoteArray(const int& CurNumOfParties);// update new county by the num of parties.
    virtual const string getCountyType() const = 0;
    //operators//
    friend std::ostream& operator<<(std::ostream& os, const County& county); //cout op
    const County& operator=(const County& other);// oprator "="
    virtual  void save(ofstream& outfile) const = 0;
};

