#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <chrono>


std::string getFilePath()
{
	std::string filePath;

	std::cout << "Enter file path: ";
	std::cin >> filePath;

	return filePath;
}


//function to read from file and add all names as pairs into the vector 
std::list<std::pair<std::string, std::string>> addToList(std::string fileName, std::list<std::pair<std::string, std::string>> l)
{
	std::string firstName;
	std::string secondName;
	std::string names;

	std::ifstream readFile(fileName);
	

	while (getline(readFile, names))
	{
		//seperate name pairs into firstName, secondName

		std::stringstream ss(names);
		getline(ss, firstName, ',');
		getline(ss, secondName);


		l .push_back(make_pair(firstName, secondName));
	}
	readFile.close();


	return l;
}


//function to arbitrarily chose a name from the list of pairs and add name to ordered list
std::list<std::string> addFirstName(std::list<std::pair<std::string, std::string>> l, std::list<std::string> oList)
{
	std::string currentName;
	std::pair<std::string, std::string> temp;
	int randomNum;
	int vSize = l.size(); 

	srand(time(NULL)); //random seed

	randomNum = rand() % vSize + 0; //generate a random number between total unordered list size and 0

	std::list<std::pair<std::string, std::string>>::iterator it = l.begin(); //iterator pointing to first element in list

	std::advance(it, randomNum);

	temp = *it;
	currentName = temp.first; //set first name of the pair to currentName
	oList.push_back(currentName); //pushback current to ordered list

	return oList;
}


//function to traverse list to find westerly neighbour and add name to list
std::list<std::string> findWesterly(std::string currentName, std::list<std::pair<std::string, std::string>>* l, std::list<std::string>* oList)
{
	std::string nextName;
	std::pair<std::string, std::string> p;
	std::list<std::pair<std::string, std::string>> uL = *l;
	std::list<std::string> oL = *oList;
	
	for (std::list<std::pair<std::string, std::string>>::iterator it = uL.begin(); it != uL.end(); ++it)
	{
		if (it->first == currentName)
		{
			nextName = it->second; //set 2nd element = nextName
			oL.push_back(nextName); //pushback nextName to ordered list

			oL = findWesterly(nextName, &uL, &oL); //use recursion until the last westerly neighbour has been found
		}
	}	


	return oL;
}


//function to traverse list to find easterly neighbour and add name to list
std::list<std::string> findEasterly(std::string currentName, std::list<std::pair<std::string, std::string>>* l, std::list<std::string>* oList)
{
	std::string nextName;
	std::list<std::pair<std::string, std::string>> uL = *l;
	std::list<std::string> oL = *oList;

	for (std::list<std::pair<std::string, std::string>>::iterator it = uL.begin(); it != uL.end(); ++it)
	{
		if (it->second == currentName)
		{
			nextName = it->first; 
			oL.push_front(nextName); //push to front of list to align names in correct order from east to west

			oL = findEasterly(nextName, &uL, &oL); 
		}
	}


	return oL;
}

int main(int argc, char* argv[])
{
	std::string filePath;

	if (argc > 1)
	{
		filePath = argv[1];
	}
	else
	{
		filePath = getFilePath();
	}


	std::list<std::string> sortedNames;

	std::list<std::pair<std::string, std::string>> unsortedNames;
	std::vector<std::pair<std::string, std::string>> namePairs; 
	

	unsortedNames = addToList(filePath, unsortedNames);

	unsortedNames.insert(unsortedNames.begin(), namePairs.begin(), namePairs.end()); //add names from vector of pairs to list of pairs

	//Used for measuring total time of algorithm
	/*auto startTotal = std::chrono::high_resolution_clock::now();*/

	//Used for measuring performance time of insertions
	/*auto startInsertion = std::chrono::high_resolution_clock::now();*/
	sortedNames = addFirstName(unsortedNames, sortedNames);
	/*auto stopInsertion = std::chrono::high_resolution_clock::now();
	auto durationInsertion = std::chrono::duration_cast<std::chrono::microseconds>(stopInsertion - startInsertion); 	*/


	std::string currentHead = sortedNames.front(); //used to access first name 


	//Used for measuring performance time of search
	/*auto startSearch = std::chrono::high_resolution_clock::now();*/
	sortedNames = findWesterly(currentHead, &unsortedNames, &sortedNames);
	/*auto stopSearch = std::chrono::high_resolution_clock::now();
	auto durationSearch = std::chrono::duration_cast<std::chrono::microseconds>(stopSearch - startSearch);*/

	sortedNames = findEasterly(currentHead, &unsortedNames, &sortedNames);

	/*auto stopTotal = std::chrono::high_resolution_clock::now();
	auto durationTotal = std::chrono::duration_cast<std::chrono::seconds>(stopTotal - startTotal);*/


	for (auto const& i : sortedNames)
	{
		std::cout << i << std::endl;
	}

	/*std::cout << "Insertion time: " << durationInsertion.count() << " microSecs\n" << std::endl;
	std::cout << "Search time: " << durationSearch.count() << " microSecs" << std::endl;
	std::cout << "Total time: " << durationTotal.count() << " Secs" << std::endl;*/
}