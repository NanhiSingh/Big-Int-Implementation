#include<bits/stdc++.h>
//#include<sstream>
using namespace std;

struct bigIntNode	// Doubly linked list
{
	int data;
	struct bigIntNode *left,*right;
}*head1,*head2, *head3, *tail1,*tail2;	

//head1 - head node of 1st linked list
//head2 - head node of 2nd linked list
//head3 - head node of resultant linked list

void addition();	// Function to add numbers
void subtraction(int n1, int n2);	// Function to subtract numbers
void deallocate();	// Function to deallocate memory

int main()
{
    string str1, str2;
    cout<<"Enter a: ";
    cin>>str1;			// Input number a 
    cout<<"Enter b: ";
    cin>>str2;			// Input number b
    
    int l1 = str1.length(); 		//No. of digits in Number a
    cout<<"length of a = "<<l1<<"\n";
    int l2 = str2.length();			//No. of digits in Number b
    cout<<"length of b = "<<l2<<"\n";
    
    int n1,n2;
	// calculation of no. of nodes required
	// Each node will contain atmost 9 digits
    if(l1%9 == 0)
    	n1 = l1/9;
	else
		n1 = l1/9 + 1;
	
	if(l2%9 == 0)
		n2 = l2/9;
	else
    	n2 = l2/9 +1;
		
    //Extraction of digits from string-1 & forming linked list-1
    struct bigIntNode*temp1,*temp2,*temp;
    int low = l1-9, high = l1;
    int i=0,d;
    do
    {
    	if(low < 0)
    		low = 0;
    	string s = str1.substr(low, (high - low));
    	stringstream ss;
    	ss<<s;
    	ss>>d;
    	
    	temp = (struct bigIntNode*)malloc(sizeof(struct bigIntNode));
    	temp->data = d;
    	temp->left = NULL;
    	temp->right = NULL;
    	if(head1 == NULL)
    	{
    		head1 = temp;
    		tail1 = temp;
    		temp1 = head1;
		}
		else
		{
			temp1->left = temp;
			temp->right = temp1;
			temp1 = temp1->left;
			tail1 = temp1;
		}
		low = low - 9;
		high = high - 9;
		i++;
	}while(i<n1);
	
	//Extraction of digits from string-2 and forming linked list-2
	low = l2-9; high = l2;
	i = 0;
	do
    {
    	if(low < 0)
    		low = 0;
    	string s = str2.substr(low, (high - low));
    	stringstream ss;
    	ss<<s;
    	ss>>d;
    	
    	temp = (struct bigIntNode*)malloc(sizeof(struct bigIntNode));
    	temp->data = d;
    	temp->left = NULL;
    	temp->right = NULL;
    	if(head2 == NULL)
    	{
    		head2 = temp;
    		tail2 = temp;
    		temp2 = head2;
		}
		else
		{
			temp2->left = temp;
			temp->right = temp2;
			temp2 = temp2->left;
			tail2 = temp2;
		}
		low = low - 9;
		high = high - 9;
		i++;
	}while(i<n2);
	
	//Menu
    int choice;
    while(choice != 0)
    {
    	cout<<"\n\n press 1 for a+b\n press 2 for a-b\n press 0 to exit\n Enter your choice: ";
    	cin>>choice;
    
    	switch(choice)
    	{
    		case 1:
    			{
					cout<<"\n a + b = ";
    				addition();
    				break;
				}
			case 2:
				{
					cout<<"\n a - b = ";
					subtraction(n1,n2);
					break;
				}
		}	
	}
    
    return 0;
}

void addition()
{
	int carry=0;	// Initially carry will be zero
	struct bigIntNode *temp1, *temp2, *temp3, *temp;
	
	temp3 = head3;	
	temp1 = head1;
	temp2 = head2;
	
	// Traverse and perform addition of data in nodes until one of the linked list gets exhausted and 
	// store the result in new node which is then added to resultant linked list
	// Also propogate carry, if it gets generated
	while(temp1!=NULL && temp2!=NULL)	
	{
		temp = (struct bigIntNode*)malloc(sizeof(struct bigIntNode));
		temp->data = (temp1->data + temp2->data + carry)%1000000000;
		temp->left = NULL;
		carry = (temp1->data + temp2->data + carry)/1000000000;

		if(temp3 == NULL)
		{
			temp->right = NULL;
			temp3 = temp;
			head3 = temp;	
		}
		else
		{
			temp->right = temp3;
			temp3->left = temp;
			temp3 = temp3->left;
		}
		
		temp1 = temp1->left;
		temp2 = temp2->left;
	}
	
	if(temp1==NULL)	// 1st linked list is exhausted
	{
		// 1-Traverse through remaining nodes of 2nd linked list
		// 2-perform addition of data in nodes with previously generated carry and propogate newly generated carry  
		// 3-Create new node, store the result and add it to resultant linked list
		while(temp2!=NULL)
		{
			temp = (struct bigIntNode*)malloc(sizeof(struct bigIntNode));
			temp->data = (temp2->data + carry)%1000000000;
			carry = (temp2->data + carry)/1000000000;

			temp->left = NULL;
			temp->right = temp3;
			temp3->left = temp;
			temp3 = temp3->left;

			temp2 = temp2->left;
		}
	}

	else	// 2nd linked list is exhausted
	{
		while(temp1!=NULL)
		{
			temp = (struct bigIntNode*)malloc(sizeof(struct bigIntNode));
			temp->data = (temp1->data + carry)%1000000000;
			carry = (temp1->data + carry)/1000000000;

			temp->left = NULL;
			temp->right = temp3;
			temp3->left = temp;
			temp3 = temp3->left;

			temp1 = temp1->left;
		}
	}
	
	if(carry!=0)	// Printing carry if it is non-zero
	{
		cout<<carry;	
	}	
	
	temp = temp3;
	while(temp!=NULL)	// Printing the remaining terms of the result
	{
		stringstream ss;
		ss<<temp->data;
		string s = ss.str();
		
		if(temp->left==NULL && carry!=0 && s.length()<9)	 
		{
			while(s.length()!=9)
				s.insert(0,"0");
			cout<<s;
		}
		else if(temp->left!=NULL && s.length()<9)
		{
			while(s.length()!=9)
				s.insert(0,"0");
			cout<<s;
		}
		else
			cout<<temp->data;
	
		temp = temp->right;
	}
	deallocate();	// Deallocating the memory occupied by resultant linked list
}

void subtraction(int n1, int n2)
{
	int borrow = 0, flag = 0;
	struct bigIntNode *temp1, *temp2, *temp3, *temp;
	
	temp3 = head3;

	// flag = 1 (if result is positive), flag = 0 (if result is 0), & flag = -1 (if result is negative)
	if(n1 > n2)			// No. of nodes in 1st linked list > No. of nodes in 2nd linked list
		flag = 1;
	else if(n1 < n2) 	// No. of nodes in 1st linked list < No. of nodes in 2nd linked list
		flag = -1;
	else				// Both linked lists have same no. of nodes
	{
		// checking which number is greater by traversing through both the linked lists simultaneously
		temp1 = tail1;
		temp2 = tail2;
		
		while((temp1!=NULL) && (temp1->data == temp2->data))
		{
			temp1 = temp1->right;
			temp2 = temp2->right;
		}

		if(temp1==NULL)
			flag = 0;
		else if(temp1->data > temp2->data)
			flag = 1;
		else if(temp1->data < temp2->data)
			flag = -1;
	}

	temp1 = head1;
	temp2 = head2;

	if(flag == 1) // Number a > Number b
	{
		// 1-Traverse through both the linked lists until 2nd linked list gets exhausted
		// 2-Perform subtraction, propogate borrow, store the result in newly created node and add it to resultant linked list
		while(temp2!=NULL)
		{
			temp = (struct bigIntNode*)malloc(sizeof(struct bigIntNode));
			if(temp1->data >= temp2->data)
			{
				temp->data = (temp1->data - temp2->data - borrow);
				borrow = 0;
			}
			else
			{
				temp->data = (1000000000+temp1->data) - temp2->data -borrow;
				borrow = 1;
			}

			temp->left = NULL;

			if(temp3 == NULL)
			{
				temp->right = NULL;
				temp3 = temp;
				head3 = temp;
			}
			else
			{
				temp->right = temp3;
				temp3->left = temp;
				temp3 = temp3->left;
			}

			temp1 = temp1->left;
			temp2 = temp2->left;
		}

		while(temp1!=NULL)	// Traversing through remaining nodes of 1st linked list
		{
			temp = (struct bigIntNode*)malloc(sizeof(bigIntNode));
			if(borrow > temp1->data)
			{
				temp->data = (1000000000 + temp1->data) - borrow;
				borrow = 1;
			}
			else
			{
				temp->data = temp1->data - borrow;
				borrow = 0;
			}

			temp->left = NULL;
			temp->right = temp3;
			temp3->left = temp;
			temp3 = temp3->left;

			temp1 = temp1->left;
		}
	}
	else if(flag == -1)	// Number a < Number b
	{
		// 1-Traverse through both the linked lists until 1st linked list gets exhausted
		// 2-Perform subtraction, propogate borrow, store the result in newly created node and add it to resultant linked list
		while(temp1!=NULL)
		{
			temp = (struct bigIntNode*)malloc(sizeof(struct bigIntNode));
			
			if(temp2->data >= temp1->data)
			{
				temp->data = temp2->data - temp1->data - borrow;
				borrow = 0;
			}
			else
			{
				temp->data = (1000000000+temp2->data) - temp1->data - borrow;
				borrow = 1;
			}

			temp->left = NULL;

			if(temp3 == NULL)
			{
				temp->right = NULL;
				temp3 = temp;
				head3 = temp;
			}
			else
			{
				temp->right = temp3;
				temp3->left = temp;
				temp3 = temp3->left;
			}

			temp1 = temp1->left;
			temp2 = temp2->left;
		}

		while(temp2!=NULL)	//Traversing through remaining nodes of 2nd linked list
		{
			temp = (struct bigIntNode*)malloc(sizeof(bigIntNode));
			if(borrow > temp2->data)
			{
				temp->data = (1000000000+temp2->data) - borrow;
				borrow = 1;
			}
			else
			{
				temp->data = temp2->data - borrow;
				borrow = 0;
			}

			temp->left = NULL;
			temp->right = temp3;
			temp3->left = temp;
			temp3 = temp3->left;

			temp2 = temp2->left;
		}
	}
	
	if(flag == 0)	// Number a = Number b, so that output is 0
		cout<<"0";
	else
	{
		if(flag == -1)	// if result is negative
			cout<<"-";
		
		int check = 0;
		temp = temp3;
		while(temp!=NULL)	// Printing the result stored in resultant linked list
		{
			stringstream ss;
			ss<<temp->data;
			string s = ss.str();

			if(temp->data == 0 && check==0)
			{
				temp = temp->right;
				continue;
			}
			else if(temp->data!=0 && check == 0)
			{
				check = 1;
				cout<<temp->data;
			}
			else
			{
				while(s.length()!=9)
					s.insert(0,"0");
				cout<<s;
			}
			
			temp = temp->right;
		}
	}
	deallocate();	// Deallocating the memory occupied by resultant linked list
}

void deallocate()
{
	struct bigIntNode * temp3, *temp;
	temp3 = head3;
	
	while(temp3!=NULL)
	{	
		temp = temp3;
		temp3 = temp3->left;
		delete temp;
	}	
	head3 = NULL;	
}