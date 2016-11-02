// Project by Kristoffer Louie Balinang
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "windows.h"
using namespace std;

class contact
{
	char name[30];
	int homeNumber;
	int mobileNumber;
public:
	contact();
	void setContact(char n[], int hn, int mn);
	void display();
	friend class contactlist;
};

contact::contact()
{
	strcpy_s(name, "");
	homeNumber = 1;
	mobileNumber = 1;
}

void contact::setContact(char n[], int hn, int mn)
{
	strcpy_s(name, n);
	homeNumber = hn;
	mobileNumber = mn;
}
void contact::display()
{
	printf("Name: %s  Home Number: %d Mobile Number: %d \n", name, homeNumber, mobileNumber);
}

class contactlist
{
	char filename[50];
	contact **mylist;
public:
	int contactCount;
	contactlist();
	~contactlist();
	void setFilename(char f[]);
	int getCount();
	void addToList(contact *c);
	void checkList();
	void showList();
	int saveList();
	void readList();
};

contactlist::contactlist()
{
	mylist = new contact*[100];
	contactCount = 0;
}

contactlist::~contactlist()
{
	delete mylist;
}

void contactlist::setFilename(char f[])
{
	strcpy_s(filename, f);
}

void contactlist::addToList(contact *c)
{
	mylist[contactCount] = c;
	contactCount++;
}

int contactlist::getCount()
{
	return contactCount;
}

void contactlist::showList()
{
	//the variable ThisLine is incremented along with the contact count; however  when ThisLine 
	//reaches 5 the loop will clear the screen and pause it the program only display 5 entries
	//this loop continues when all the entries are displayed. 
	int ThisLine = 0;
	int pageNumber = 1;
	for (int i = 0; i < contactCount; i++)
	{
		if (ThisLine == 5)
		{
			system("pause");
			system("cls");
			printf("Page %d\n", pageNumber);
			cout << "---------------------" << endl;
			mylist[i]->display();
			ThisLine = 1;
			pageNumber++;
		}
		else
		{
			mylist[i]->display();
			ThisLine++;
		}
	}
		
}

int contactlist::saveList()
{
	ofstream output(filename);
	if (!output)
	{
		cout << "<Alert> Failure" << endl;
		return -1;
	}

	for (int i = 0; i < contactCount; i++)
	{
		output << mylist[i]->name << ",";
		output << mylist[i]->homeNumber << ",";
		output << mylist[i]->mobileNumber << "," << endl;
	}
	output.close();
	return 0;
}

void contactlist::readList()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		contact *ptr;
		char name[30];
		char homeNumber[30];
		char mobileNumber[30];

		infile.getline(name , 30, ',');
		if (strlen(name))
		{
			infile.getline(homeNumber, 30, ',');
			infile.getline(mobileNumber, 30);
			ptr = new contact();
			ptr->setContact(name, atoi(homeNumber), atoi(mobileNumber));
			addToList(ptr);
		}
	}
	infile.close();
}
 // this function created checks the inputted object with the objects written into the file, 
// if the objects contain the same name than one of those in the file, the information slot is not inputted and the contactcounter is sent back.

void contactlist::checkList()
{
	int  i;
	ifstream infile(filename);

	for (i = 1; i <= contactCount; i++)
	{
		if (strcmp(mylist[contactCount-1]->name, mylist[(contactCount-1) - i]->name) == 0)
		{
			system("pause");
			system("cls");
			cout << "<ALERT> This contact already exists." << endl;
			cout << "------------------------------------" << endl;
			cout << " " << endl;
			cout << "Contact was not added!" << endl;
			cout << " " << endl;
			i++;
			contactCount--;
			return ;
		}
		else
		{
			return ;
		}
	}
}

int main()
{
	char answer = 'y';
	char name[30];
	int homeNumber;
	int mobileNumber;
	char filename[50];

	contactlist *cList = new contactlist();

	cout << "Your Phonebook" << endl;
	cout << "--------------" << endl;
	cout << "Enter a file name: " << endl;
	gets_s(filename);
	cList->setFilename(filename);

	cList->readList();
	system("pause");
	system("cls");
	if (cList->getCount() == 0)
	{
		system("pause");
		system("cls");
		cout << "New file!" << endl;
		cout << "<ALERT> No contacts available!" << endl;
	}
	else
	{
		cout << "You have " << cList->getCount() << " contacts." << endl;
		cout << 100 - cList->getCount() << " contacts remaining!" << endl;
	}

	cout << "Would you like to enter a new contact? Enter Y to add; Any other key to display" << endl;
	cin >> answer;

	while (answer == 'Y' || answer == 'y')
	{
		//count check, if there are more than 100 contacts the user
		//is alerted and the program will close
		//ensures that the phonebook will not overfill
		if (cList->getCount() >= 100)
		{
			system("pause");
			system("cls");
			cout << "<ALERT> Phonebook is full!" << endl;
			cout << "--------------------------" << endl;
			cout << " " << endl;
			cout << "Closing program...." << endl;
			cout << " " << endl;
			return 0;
		}

		cin.ignore();
		cin.clear();
		system("pause");
		system("cls");
		cout << "New contact creation" << endl;
		cout << "--------------------" << endl;
		cout << "Enter contact name: " << endl;
		gets_s(name);
		cout << "Enter home number: " << endl;
		cin >> homeNumber;
		cin.ignore();
		cin.clear();
		cout << "Enter mobile number: " << endl;
		cin >> mobileNumber;
		cin.ignore();
		cin.clear();

		contact *mycontact = new contact();
		mycontact->setContact(name, homeNumber, mobileNumber);
		cList->addToList(mycontact);

		

		cout << "Would you like to enter another contact? Enter Y to add; any other key to display" << endl;
		cin >> answer;
	}

	
	cList->checkList();
	system("pause");
	system("cls");
	cout << "Contact List" << endl;
	cout << "-------------------------------------------" << endl;

	cList->showList();
	cList->saveList();

	return 0;
}
