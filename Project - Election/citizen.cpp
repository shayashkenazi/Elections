
#include "citizen.h"
#include"County.h"
#include <iostream>
#pragma warning(disable : 4996)

using namespace std;
Citizen::Citizen (const string _name, long  _id, unsigned int _yearOfBirth) : yearOfBirth(_yearOfBirth), id(_id),county(nullptr) {
    if (_id < 100000000 || id>999999999)
        throw WrongIdException();
    this->name = _name;
}

Citizen::Citizen(const Citizen& other)
{
    name = other.name;
    id = other.id;
    county = other.county;
    yearOfBirth = other.yearOfBirth;
    isVoted = other.isVoted;
}

Citizen::Citizen(ifstream& inFile)
{
    int nameLen;
    inFile.read(rcastc(&nameLen), sizeof(int));
    name.resize(nameLen);
    inFile.read(rcastc(&name[0]), nameLen);
    inFile.read(rcastc(&id), sizeof(long));
    inFile.read(rcastc(&yearOfBirth), sizeof(unsigned int));
    inFile.read(rcastc(&isVoted), sizeof(bool));
}


Citizen::~Citizen() { }

Citizen& Citizen::operator=(const Citizen& add) {
    name.clear();
    name = add.name;
	id = add.id;
	county = add.county;
	yearOfBirth = add.yearOfBirth;
	isVoted = add.isVoted; 
    return *this;
}
void Citizen::save(ofstream& outFile) const
{
    int lenOfName = name.size();
    outFile.write(rcastcc(&lenOfName), sizeof(int));
    outFile.write(rcastcc(&name[0]), lenOfName);
    outFile.write(rcastcc(&id), sizeof(long));
    outFile.write(rcastcc(&yearOfBirth), sizeof(unsigned int));
    outFile.write(rcastcc(&isVoted), sizeof(bool));
}
bool Citizen::setVote()
{
    if (isVoted == false)
    {
	   isVoted = true;
	   return true;
    }
    return false;
}
ostream& operator<<(ostream& os,const Citizen& citizen) {

    os <<
	   "Citizen Name: " << citizen.getName() << endl <<
	   "ID: " << citizen.getId() << endl <<
	   "year of birth : " << citizen.getyearOfBirth() << endl <<
	   "Citizen County Number is : " << citizen.getCounty().getCountyId() << endl;
    
    return os;
}