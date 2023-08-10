#include<iostream>
#include<ctime>
#include"myconsole.h"
#include"windows.h"
using namespace std;

class point
{
public:
	point() { x = 0; y = 0; MaxPointx = 0; MaxPointy = 0; }
	point(int a, int b) { x = a; y = b; }
	int getX() { return x; }
	int getY() { return y; }
	void set(int a, int b) { x = a; y = b; }
	void setX(int a) { x = a; }
	void setY(int b) { y = b; }
	void setMax(int a,int b) { MaxPointx = a; MaxPointy = b;}
	//increment x-coordinate.  If max limit is reached then increment y and set x to zero
	//return false if max limit for x and y is reached
	bool incrementX();
	//increment y-coordinate.  If max limit is reached return false
	bool incrementY();
	//decrement x-coordinate.  If x is already at 0 then go to line above at last x (decrement y)
	//return false if both x and y are at 0
	bool decrementX();
	//decrement y-coordinate.  If y is already at 0 then return false
	bool decrementY();
	bool operator != (point rhs)
	{
		return (!((x == rhs.x) && (y == rhs.y)));
	}
	bool operator == (point rhs)
	{
		return (((x == rhs.x) && (y == rhs.y)));
	}

	friend ostream& operator<< (ostream& print, point toPrint);

private:
	int MaxPointx;
	int MaxPointy;
	int x;
	int y;
};
ostream& operator<< (ostream& print, point toPrint)
{
	print << toPrint.x << "," << toPrint.y;
	return print;
}
bool point::incrementX()
{
	bool returnValue = true;
	if (x < MaxPointx - 1)
		x++;
	else
		returnValue = false;

	return returnValue;
}
bool point::incrementY()
{
	bool returnValue = true;
	if (y < MaxPointy - 1)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x > 0)
		x--;
	else
		returnValue = false;

	return returnValue;
}
bool point::decrementY()
{
	bool returnValue = true;
	if (y > 0)
		y--;
	else
		returnValue = false;

	return returnValue;

}
template <typename T>
class list
{

private:
	class node 
	{
		T  data;
		node * next;
		node * prev;
		node(T d, node *p)
		{ 
			data = d; 
			next = prev= p; 
		}
		friend class list<T>;
	};
	node* head;
	node* tail;
public:
	class listiterator
	{
		protected:
			node * current;
			friend class list<T>;
		public:
			//Default Constructor
			listiterator() 
			{ 
				current = nullptr; 
			}
			//Parameterized Constructor used in begin and end functions
			listiterator(node *p)
			{ 
				current = p; 
			}
			//Dereference operation to provide access of data to user
			T & operator* () const 
			{ 
				return current->data; 
			} 
			//Move forward Pre-increment
			listiterator & operator++ ()
			{
				if (current != nullptr)
					this->current = this->current->next;
				return *this;
			}
			//Move forward Post-increment
			listiterator operator++ (int)
			{
				listiterator old = *this;
				++(*this);
				return old;
			}
			listiterator & operator-- ()
			{
				if (current != nullptr)
					this->current = this->current->prev;
				return *this;
			}
			//Move forward Post-decrement
			listiterator operator-- (int)
			{
				listiterator old = *this;
				--(*this);
				return old;
			}
			//If two iterators point to same node
			bool operator== (const listiterator & rhs) const { return current == rhs.current; }
			//If two iterators point to different nodes
			bool operator!= (const listiterator & rhs) const { return !(*this == rhs); }
	};
	//Iterator returned that points to First Node 
	listiterator begin()
	{ 
		return head; 
	}
	//Iterator returned that points to Last Node  
	listiterator end()
	{ 
		return nullptr; 
	}
	listiterator returntail()
	{
		return tail;
	}

	//Other Functions of Link list
	void  printListForward()
	{
		node* current;
		current = head;
		while (current != nullptr)
		{
			cout << current->data << " -> ";
			current = current->next;
		}
		cout << "NULL" << endl;
	}
	//Inserts at tail
	void  InsertatEnd(T value)
	{
		node* nnode = new node(value, nullptr);
		if (head == nullptr)
		{
			head = nnode;
			tail = nnode;
		}
		else
		{
			tail->next = nnode;
			nnode->prev = tail;
			tail = nnode;
		}
	}
	//Deletes last element
	void deleteEnd()
	{
		node* curr = tail;
		if (curr != nullptr)
		{
			if (curr != head)
			{
				tail = curr->prev;
				tail->next = nullptr;
				delete curr;

			}
			else
			{
				delete curr;
				head = tail = NULL;
			}
		}

	}
	
	//Constructor
	list(){ head = nullptr; tail = nullptr; }

	//Destructor
	~list()
	{
		node* temp;
		while (head != NULL)
		{
			temp = head;
			head = head->next;
			delete temp;
		}

	}
};

template<typename T>
class Stack
{
private:
	list<T>*ptr;
public:
	Stack()
	{
		ptr=new list<T>;
	}
	void push(T value)
	{
		ptr->InsertatEnd(value);
	}
	bool isEmpty()
	{
		typename list<T>::listiterator i=ptr->begin();
		if(i==ptr->end())
			return true;
		else
			return false;
	}
	void pop()
	{
		 ptr->deleteEnd();
	}
	bool top(T& num)
	{
		typename list<T>::listiterator i=ptr->returntail();
		if(!isEmpty())
		{
			num=*i;
			return true;
		}
		else
			return false;
	}
	void printStack()
	{
		ptr->printListForward();
	}
	~Stack()
	{
		ptr->~list();
	}
};
class Maze
{
private:
	char** mazeRoom;//2D Char array for Maze
	int row, col;//Rows and Columns of Maze
	point currentPosition;//Point for the current position of Rat
	point destination;//Point for the destination
	Stack<point> path;//Stack to Track and Return the Path
public:
	Maze(int r,int c)//Overloaded Constructor that takes rows and columns than randomly generates the Maze
	{
		currentPosition.setMax(r, c);
		row = r+2;
		col = c+2;
		mazeRoom = new char* [row];
		for (int i = 0; i < row; i++)
			mazeRoom[i] = new char[col];
		srand(time(NULL));
		int block;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
				{
					mazeRoom[i][j] = char(219u);
					continue;
				}
				block = rand() % 4;//25% chance of no path
				switch (block)
				{
				case 0:
					mazeRoom[i][j] = ' ';
					break;
				case 1:
					mazeRoom[i][j] = char(219u);
					break;
				case 2:
					mazeRoom[i][j] = ' ';
					break;
				case 3:
					mazeRoom[i][j] = ' ';
					break;
				default:
					mazeRoom[i][j] = ' ';
				}
			}
		}
	}
	void startGame()
	{
		int temp;
		bool flag=1;
		cout << "Enter Starting Position X of Rat: ";//Starting X index of Rat
		cin >> temp;
		currentPosition.setX(temp+1);
		cout << "Enter Starting Position Y of Rat: ";//Starting Y index of Rat
		cin >> temp;
		currentPosition.setY(temp+1);
		path.push(currentPosition);
		cout << "Enter Destination Position X: ";// X index of Destination
		cin >> temp;
		destination.setX(temp+1);
		cout << "Enter Destination Position Y: ";// X index of Destination
		cin >> temp;
		destination.setY(temp+1);
		mazeRoom[currentPosition.getX()][currentPosition.getY()]='@';
		mazeRoom[destination.getX()][destination.getY()]='X';
		while (currentPosition != destination && !(path.isEmpty()))//Loop till Destination is Found or Till all possible Paths have been traversed
		{
			flag = 0;
			if (mazeRoom[currentPosition.getX()+1][currentPosition.getY()]==' '|| mazeRoom[currentPosition.getX() + 1][currentPosition.getY()] == 'X')//Move Right
			{
				mazeRoom[currentPosition.getX()][currentPosition.getY()] = char(176u);
				currentPosition.set(currentPosition.getX()+1, currentPosition.getY());
				flag = 1;

			}
			else if (mazeRoom[currentPosition.getX()-1][currentPosition.getY()] == ' ' || mazeRoom[currentPosition.getX() -1][currentPosition.getY()] == 'X')//Move Left
			{
				mazeRoom[currentPosition.getX()][currentPosition.getY()] = char(176u);
				currentPosition.set(currentPosition.getX()-1, currentPosition.getY());
				flag = 1;
			}
			else if(mazeRoom[currentPosition.getX()][currentPosition.getY()+1] == ' ' || mazeRoom[currentPosition.getX()][currentPosition.getY()+1] == 'X')//Move Down
			{
				mazeRoom[currentPosition.getX()][currentPosition.getY()] = char(176u);
				currentPosition.set(currentPosition.getX(), currentPosition.getY()+1);
				flag = 1;
			}
			else if (mazeRoom[currentPosition.getX()][currentPosition.getY()-1] == ' ' || mazeRoom[currentPosition.getX()][currentPosition.getY()-1] == 'X')//Move Up
			{
				mazeRoom[currentPosition.getX()][currentPosition.getY()] = char(176u);
				currentPosition.set(currentPosition.getX(), currentPosition.getY()-1);
				flag = 1;
			}
			if (flag)//Check if Rat moved to New block
			{
				path.push(currentPosition);
			}
			else//If path is blocked steps back
			{
				mazeRoom[currentPosition.getX()][currentPosition.getY()] = char(177u);
				path.pop();
				path.top(currentPosition);
			}
			printMaze();
			Sleep(360);
		}
		if (!flag)//Game Ends and no path is Found
			cout << "No Path Found\n";
		else//Game Ends and rat reaches Destination
			Win();

	}
	void Win()
	{
		cout << "You Won \n";
		path.printStack();
	}
	void printMaze()
	{
		system("cls");
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				(currentPosition.getX()==i&& currentPosition.getY() == j)?cout<<"@":cout << mazeRoom[i][j];
				if (mazeRoom[i][j] == char(219u))
					SetColorAtPoint(i, j, 0x06|0x06);
				if(mazeRoom[i][j]==char(176u))
					SetColorAtPoint(i, j, 0x00|0xA0);
				if(mazeRoom[i][j]==char(177u))
					SetColorAtPoint(i, j, 0x04|0x04);
			}
			cout << endl;
		}
	}
};
int main()
{
	int row, col;
	cout << "Enter row of Maze: ";
	cin >> row;
	cout << "Enter col of Maze: ";
	cin >> col;
	Maze mazeRoom(row, col);
	mazeRoom.startGame();
	system("pause");
	return 0;
}