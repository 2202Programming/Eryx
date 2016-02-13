#include "Profile/DProfile.h"
#define FILE "/home/docs/profile.txt"

using namespace std;
DProfile::DProfile()
{
	findIndex();
}


DProfile::~DProfile()
{
	generateIndex();
	profileNode *temp = master;
	profileNode *test;
	while (temp != NULL) {
		test = temp;
		temp = temp->parent;
		delete test;
	}
	delete temp;
}

std::string DProfile::getValue(std::string label)
{
	profileNode *temp = master;
	while (temp != NULL) {
		if (temp->label.compare(label) == 0) {
			return temp->value;
		}
		temp = temp->parent;
	}
	return "";
}

bool DProfile::setValue(std::string label, std::string value)
{
	/* Iterate throughout the program and check to make sure the value does not exist */
	master = new profileNode(label, value, master);
	return false;
}

void DProfile::findIndex()
{
	string line;
	ifstream myfile("test.txt");
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			string first = line.substr(0, line.find(","));
			string sec = line.substr(line.find(",") + 1, line.size());
			//master = new profileNode(first, sec, master);
			setValue(first, sec);
		}
		myfile.close();
	}
}

void DProfile::generateIndex()
{
	/* Was Designed to Make the Index if someone adds to it in the Program but I dont think it is needed */
}
