#include "CountyArr.h"
#include"DividedCounty.h"
#include"UnifiedCounty.h"
CountyArr::CountyArr()
{
}


CountyArr::~CountyArr()
{
	for (auto county : counties)
		delete county;
}

void CountyArr::addCounty( County& add,const int& curNumOfParties)// add new county to counties array of election.
{
    try {
	   if (typeid(add) == typeid(DividedCounty))
	   {
		  County* divCounty = new DividedCounty(add);
		  counties.push_back(divCounty);
	   }
	   else
	   {
		  County* uniCounty = new UnifiedCounty(add);
		  counties.push_back(uniCounty);
	   }	  
    }
    catch (bad_alloc& msg)
    {
	   cout << msg.what() << endl;
	   exit(1);
    }

    counties.back()->InitVoteArray(curNumOfParties);
}

CountyArr::CountyArr(const CountyArr& other)
{
	County* newCounty;
	try {
	    for (auto county : other.counties)
	    {
		   if (county->getCountyType().compare("Divided County") == 0)
			  newCounty = new DividedCounty(*county);
		   else
			  newCounty = new UnifiedCounty(*county);
		   counties.push_back(newCounty);
	    }
	}	
	catch (bad_alloc& msg)
	 {
	   cout << msg.what() << endl;
	   exit(1);
	 }
	
}
void CountyArr::printCounties()
{
    if (counties.size() == 0)
	   throw NoCountiesException();
    cout << "The County List is : " << endl;
    for (int i = 0; i < counties.size() ; i++)
    {
      cout << *counties[i] << endl;
    }
}

bool CountyArr::updateCountyVoteArray()
{
    for (int i = 0; i < counties.size(); i++)
    {
	   counties[i]->ResizeVoteArray();
    }
    return true;
}
int CountyArr::getTotalNumOfVotes()
{
    int count = 0;
    for (auto C: counties)
    {
	   count += C->getNumOfVotes();
    }
    return count;
}
const CountyArr& CountyArr::operator=(const CountyArr& other)
{	
	County* newCounty;

	if (this != &other) {
		for (auto county : counties)
			delete county;
		try {
		    for (auto county : counties)
		    {
			   if (county->getCountyType().compare("Divided County") == 0)
				  newCounty = new DividedCounty(*county);
			   else
				  newCounty = new UnifiedCounty(*county);
			   counties.push_back(newCounty);
		    }
		}
		catch (bad_alloc& msg)
		{
		    cout << msg.what() << endl;
		    exit(1);
		}
	}

	return *this;
}

void CountyArr::save(ofstream& outFile) const
{  
    for (int i = 0; i < counties.size(); i++)
    {
	   counties[i]->save(outFile); //write all the counties.
    }
}
