/*
	Author         : Jooyeon Mok
	Date           : 2018 - 04- 30

	Linked List
		- add
		- display
		- search by  ID
		- search by SIN
		- sort by ID (reverse)
		- sort by ID 
		- sort by SIN
		- sort by Full Name
		- write to file
		- read from file
*/





#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Date
{
	int day, month, year;
};
struct Employee
{
	int id;
	string fname;
	string lname;
	string sin;
	Date hired;
};

struct Node
{
	Employee data;
	Node *next_ptr;
};

void reverse_sort(Node *); // reverse sorting
void sort(Node *); // sorting by ID
void sort_sin(Node *); // sorting by SIN
void sort_name(Node *); // sorting by ID
void display(Node *); // displaying
void remove(Node *, int*); // deleting
Node *search_id(Node*, int*); // ID searching
Node *search_sin(Node*, string*); // SIN searching
void write_to_file(const char * , Node* ); // writing to file
void read_from_file(const char * , vector<Node> *); // reading from file

int main()
{
	// adding contacts
	Node *head_ptr = NULL;
	Node *node1 = new Node;
	Employee *s = new Employee;
	s->id = 1;
	s->fname = "Dave";
	s->lname = "Goodman";
	s->sin = "923456789";
	s->hired.day = 1;
	s->hired.month = 1;
	s->hired.year = 2011;
	node1->data = *s;
	node1->next_ptr = NULL;
	head_ptr = node1;

	Node *node2 = new Node;
	s->id = 2;
	s->fname = "Zong";
	s->lname = "Lindman";
	s->sin = "234567890";
	s->hired.day = 2;
	s->hired.month = 2;
	s->hired.year = 2012;
	node2->data = *s;
	node2->next_ptr = NULL;
	node1->next_ptr = node2;

	Node *node3 = new Node;
	s->id = 3;
	s->fname = "Adrian";
	s->lname = "Catbaby";
	s->sin = "345678901";
	s->hired.day = 3;
	s->hired.month = 3;
	s->hired.year = 2013;
	node3->data = *s;
	node3->next_ptr = NULL;
	node2->next_ptr = node3;


	// displaying contacts
	cout << "\n\nNow Displaying - \n\n";
	display(head_ptr);

	int target;
	int* target_ptr = &target;
	// Search for an employee by ID
	cout << "Enter the ID of Employee to search : ";
	cin >> target;
	if (search_id(head_ptr, target_ptr) != NULL)
	{
		cout << "\nEmployee ID                           : " << search_id(head_ptr, target_ptr)->data.id;
		cout << "\nEmployee Name                         : " << search_id(head_ptr, target_ptr)->data.fname << " " << search_id(head_ptr, target_ptr)->data.lname;
		cout << "\nSocial Security Number                : " << search_id(head_ptr, target_ptr)->data.sin;
		cout << "\nHired Date                            : " << search_id(head_ptr, target_ptr)->data.hired.day << "." << search_id(head_ptr, target_ptr)->data.hired.month << "." << search_id(head_ptr, target_ptr)->data.hired.year << endl;
	}
	else
	{
		cout << "The ID is not in the list." << "\n\n\n";
	}

	// Search for an employee by SIN
	string target_sin;
	string* target_sin_ptr = &target_sin;
	cout << "Enter the Social Insurance Number of Employee to search : ";
	cin >> target_sin;
	if (search_sin(head_ptr, target_sin_ptr) != NULL)
	{
		cout << "\nEmployee ID                           : " << search_sin(head_ptr, target_sin_ptr)->data.id;
		cout << "\nEmployee Name                         : " << search_sin(head_ptr, target_sin_ptr)->data.fname << " " << search_sin(head_ptr, target_sin_ptr)->data.lname;
		cout << "\nSocial Security Number                : " << search_sin(head_ptr, target_sin_ptr)->data.sin;
		cout << "\nHired Date                            : " << search_sin(head_ptr, target_sin_ptr)->data.hired.day << "." << search_sin(head_ptr, target_sin_ptr)->data.hired.month << "." << search_sin(head_ptr, target_sin_ptr)->data.hired.year << endl;
	}
	else
	{
		cout << "The social insurance number is not in the list." << "\n\n\n";
	}
	system("pause");

	// Sort by ID (Descending)
	cout << "\n\Descending ID Sorting -\n";
	reverse_sort(head_ptr);
	cout << "\n\Displaying (result of sorting)-\n";
	display(head_ptr);
	system("pause");

	// Sort by ID (Ascending)
	cout << "\n\Ascending ID Sorting - \n";
	sort(head_ptr);
	cout << "\n\Displaying (result of sorting)-\n";
	display(head_ptr);
	system("pause");

	// Sort by SIN
	cout << "\n\Sorting by Social Security Number - \n";
	sort_sin(head_ptr);
	cout << "\n\Displaying (result of sorting)-\n";
	display(head_ptr);
	system("pause");

	// Sort by Full Name
	cout << "\n\Sorting by Full Name - \n";
	sort_name(head_ptr);
	cout << "\n\Displaying (result of sorting)-\n";
	display(head_ptr);
	system("pause");

	// Removing an employee

	cout << "Enter the ID of Employee to delete : ";
	cin >> target;
	remove(head_ptr, target_ptr);

	// Writing to a file
	cout << "\n\nThe Nodes are being written too file : nodes.bin\n";
	char * file_name = "Personal.bin";
	write_to_file(file_name, head_ptr);
	cout << "File writing Completed. \n\n\n";

	// Reading from the file
	cout << "\n\nThe Nodes are being written too file : nodes.bin\n";
	vector<Node>* fromfile = new vector<Node>();
	read_from_file(file_name, fromfile);

	// Displaying the Data from file
	cout << "\n\n DISPLAYING from File ...........\n";
	for (vector<Node>::iterator it = fromfile->begin(); it != fromfile->end(); it++)
	{
		cout << "\nEmployee ID                           : " << it->data.id;
		cout << "\nEmployee Name                         : " << it->data.fname << " " << it->data.lname;
		cout << "\nSocial Security Number                : " << it->data.sin;
		cout << "\nHired Date                            : " << it->data.hired.day << "." << it->data.hired.month << "." << it->data.hired.year << endl;
	}

	system("pause");
}



void display(Node *head_ptr)
{
	for (Node *idx = head_ptr; idx != NULL; idx = idx->next_ptr)
	{
		cout << "\nEmployee ID                           : " << idx->data.id;
		cout << "\nEmployee Name                         : " << idx->data.fname << " " << idx->data.lname;
		cout << "\nSocial Security Number                : " << idx->data.sin;
		cout << "\nHired Date                            : " << idx->data.hired.day << "." << idx->data.hired.month << "." << idx->data.hired.year << endl;
	}
}


void remove(Node *head_ptr, int* target) // deleting
{
	bool found = false;

	for (Node *idx = head_ptr; idx != NULL; idx = idx->next_ptr)
	{
		if (idx->data.id == *target)
		{
			if (idx == head_ptr)
			{
				head_ptr = idx->next_ptr;
			}
			else
			{
				for (Node *id = head_ptr; id != NULL; id = id->next_ptr)
				{
					if (id->next_ptr == idx)
						id->next_ptr = idx->next_ptr;// set the previous member's next pointer to the the member after (of removed member)
				}
				idx->next_ptr = NULL;  //set next pointer of the first one to null
			}
			cout << "\n\n-----------ID " << *target << " IS DELETED---------" << endl;
		}
		found = true;
	}
	if (!found)
	{
		cout << "ID " << target << " is not found. -------\n";
	}
	display(head_ptr);
}

Node *search_id(Node*head_ptr, int*targetID)
{
	Node *temp = NULL;
	for (Node *idx = head_ptr; idx != NULL; idx = idx->next_ptr)
	{
		if (idx->data.id == *targetID)
		{
			temp = idx;
			break;
		}
	}
	return temp;
}

Node *search_sin(Node*head_ptr, string*targetSIN)
{
	Node *temp = NULL;
	for (Node *idx = head_ptr; idx != NULL; idx = idx->next_ptr)
	{
		if (idx->data.sin == *targetSIN)
		{
			temp = idx;
			break;
		}
	}
	return temp;
}


void sort(Node *head_ptr)
{
	Node *idx = head_ptr;
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (Node *idx = head_ptr; idx->next_ptr != NULL; idx = idx->next_ptr)
		{

			if (idx->data.id > idx->next_ptr->data.id)
			{
				swap(idx->data, idx->next_ptr->data);
				swapped = true;
			}
		}
	}
}

void reverse_sort(Node *head_ptr)
{
	Node *idx = head_ptr;
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (Node *idx = head_ptr; idx->next_ptr != NULL; idx = idx->next_ptr)
		{

			if (idx->data.id < idx->next_ptr->data.id)
			{
				swap(idx->data, idx->next_ptr->data);
				swapped = true;
			}
		}
	}
}

void sort_sin(Node *head_ptr)
{
	Node *idx = head_ptr;
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (Node *idx = head_ptr; idx->next_ptr != NULL; idx = idx->next_ptr)
		{

			if (stoi(idx->data.sin) > stoi(idx->next_ptr->data.sin))
			{
				swap(idx->data, idx->next_ptr->data);
				swapped = true;
			}
		}
	}
}

void sort_name(Node *head_ptr)
{
	Node *idx = head_ptr;
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (Node *idx = head_ptr; idx->next_ptr != NULL; idx = idx->next_ptr)
		{
			string name1 = idx->data.fname + idx->data.lname;
			string name2 = idx->next_ptr->data.fname + idx->next_ptr->data.lname;
			if (name1 > name2)
			{
				swap(idx->data, idx->next_ptr->data);
				swapped = true;
			}
		}
	}
}

void write_to_file(const char * file_name, Node* head_ptr )
{
	ofstream out_file(file_name, ios::out | ios::app); //out: writting mode
	for (Node *idx = head_ptr; idx != NULL; idx = idx->next_ptr)
	{
		out_file << idx->data.id << "\n" << idx->data.fname << "\n" << idx->data.lname << "\n" << idx->data.sin << "\n"
			<< idx->data.hired.day << "\n" << idx->data.hired.month << "\n" << idx->data.hired.year << endl;
	}
	out_file.close();
}
void read_from_file(const char * file_name, vector<Node> *v)
{
	ifstream reader(file_name, ios::in | ios::binary);
	if (reader.good())
	{
		Node *r;
		while (reader.peek() != EOF)
		{
			r = new Node();
			if (reader.read(reinterpret_cast<char*> (r), sizeof(Node)).good())
			{
				v->push_back(*r);
			}
			else exit;
		}
	}
	reader.close();
}
