#include "County.h"
#include"PartyArr.h"
#include <iostream>
#pragma warning(disable : 4996)

using namespace std;
int County :: countySerialNumber = 0;
County::County(const string _CountyName, int _NumOfRep) : NumOfRep(_NumOfRep), MaxPartyVotesIndex(0)
{
	if (_NumOfRep < 0)
		throw NumOfRepInvalidException();
    countySerialNumber++;
    countyId = countySerialNumber;
	CountyName = _CountyName;
}
County::County()
{ 
}
County::County(const County& other)
{
	CountyName = other.CountyName;
    NumOfRep = other.NumOfRep;
    countyId = other.countyId;
    eligibleCitizen = other.eligibleCitizen;
    numOfVotes = other.numOfVotes;
    MaxPartyVotesIndex = other.MaxPartyVotesIndex;    
	VoteCountyArray = other.VoteCountyArray;
}
County::County(ifstream& inFile)//file ctor.
{
	int lenOfName;
	inFile.read(rcastc(&lenOfName), sizeof(int));//read the len of county name
	CountyName.resize(lenOfName);
	inFile.read(rcastc(&CountyName[0]), sizeof(char) * lenOfName);//load county name.
	inFile.read(rcastc(&NumOfRep), sizeof(int));//get num of Rep
	inFile.read(rcastc(&numOfVotes), sizeof(int));//get num of Rep

	countySerialNumber++;
	countyId = countySerialNumber;//keep serial Number updated
}
County::~County()
{

}

int County::FindMaxValueIdx()
{
    float temp,max= restArrayVoters[0]-(float)ElectorsByIdx[0];
    int idx=0;
    for (int i = 1; i < VoteCountyArray.size(); i++)
    {
	   temp = restArrayVoters[i]- (float)ElectorsByIdx[i];
	   if (temp > max) {
		  max = temp;
		  idx = i;
	   }
    
    }
    restArrayVoters[idx] = 0;
    return idx;
}

const County& County::operator=(const County& other) {
	CountyName.clear();
	CountyName = other.CountyName;
    NumOfRep = other.NumOfRep;
	countyId = other.countyId;
	eligibleCitizen = other.eligibleCitizen;
	numOfVotes = other.numOfVotes;
	MaxPartyVotesIndex = other.MaxPartyVotesIndex;
	
	VoteCountyArray = other.VoteCountyArray;
	
	return *this;
}
bool County::ResizeVoteArray()
{    
	int zero = 0;
	VoteCountyArray.push_back(zero);//new party was added - we resize voteCountyArray with 0.
    return true;
}
bool County::UpdateVoteArrayToRep()
{
    float RepValue = (float)numOfVotes / NumOfRep;
    int sumRep=0,index;
    ElectorsByIdx.resize(VoteCountyArray.size());
    UpdateRestArrayVoters();
    for (int i = 0; i < VoteCountyArray.size(); i++)
    {
	   ElectorsByIdx[i] = (int)restArrayVoters[i];
	   sumRep += ElectorsByIdx[i];
    }
  while(sumRep < NumOfRep)
    {
	   index = FindMaxValueIdx();
	   ElectorsByIdx[index]++;
	   sumRep++;
    }
  return true;
}
bool County::UpdateRestArrayVoters()
{
    restArrayVoters.resize(VoteCountyArray.size());
    for (int i = 0; i < VoteCountyArray.size(); i++)
    {
	   if (numOfVotes == 0)
		  restArrayVoters[i] = 0;
	   else
		  restArrayVoters[i] = ((float)VoteCountyArray[i] / numOfVotes) * NumOfRep;
    }
    return true;
}
bool County::InitVoteArray(const int& CurNumOfParties)
{
     if (CurNumOfParties > VoteCountyArray.size())
    {	 
		 VoteCountyArray.resize(CurNumOfParties);
    }
	return true;
	
}
void County::MostVotedParty()
{
    int  indexP = 0;
    int maxVote = VoteCountyArray[0];
    int temp;
    for (int i = 1; i < VoteCountyArray.size(); i++)
    {
	   temp = VoteCountyArray[i];
	   if (temp > maxVote) {
		  maxVote = temp;
		  indexP = i;
	   }
    }
    setMaxPartyVotesIndex(indexP);//set index in county MaxPartyVotesIndex    
    UpdateVoteArrayToRep();        
}
void County::CreateVoteArrayFromFile(ifstream& inFile)
{
	int voteArraysize;
	   inFile.read(rcastc(&voteArraysize), sizeof(int));

	   for (int i = 0; i < voteArraysize; i++)
	   {
		   int zero = 0;
		   VoteCountyArray.push_back(zero);
	   }
	   inFile.read(rcastc(&VoteCountyArray[0]), sizeof(int) * voteArraysize);
}
ostream& operator<<(ostream& os, const County& county) {

    os <<
	   "County Type: " <<county.getCountyType()<< endl << //get county is virtual
	   "County Name: " << county.getName() << endl <<
	   "CountyID: " << county.getCountyId() << endl <<
	   "number of reps : " << county.getNumOfRep() << endl;
    return os;
}