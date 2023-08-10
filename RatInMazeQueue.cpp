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
	void setMax(int a, int b) { MaxPointx = a; MaxPointy = b; }
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
	int value;
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
class Queue
{

public:
	class node
	{
		T  data;
		node* next;
		node(T d, node* p)
		{
			data = d;
			next = p;
		}
		friend class Queue<T>;
	};

	class Queueiterator
	{
	protected:
		node* current;
		friend class Queue<T>;
	public:
		//Default Constructor
		Queueiterator()
		{
			current = nullptr;
		}
		//Parameterized Constructor used in begin and end functions
		Queueiterator(node* p)
		{
			current = p;
		}
		//Dereference operation to provide access of data to user
		T& operator* () const
		{
			return current->data;
		}
		//Move forward Pre-increment
		Queueiterator& operator++ ()
		{
			if (current != nullptr)
				this->current = this->current->next;
			return *this;
		}
		//Move forward Post-increment
		Queueiterator operator++ (int)
		{
			Queueiterator old = *this;
			++(*this);
			return old;
		}
		//If two iterators point to same node
		bool operator== (const Queueiterator& rhs) const { return current == rhs.current; }
		//If two iterators point to different nodes
		bool operator!= (const Queueiterator& rhs) const { return !(*this == rhs); }
	};
	//Iterator returned that points to First Node 
	Queueiterator begin()
	{
		return front;
	}
	//Iterator returned that points to Last Node  
	Queueiterator end()
	{
		return nullptr;
	}

	//Other Functions of Link Queue
	void printQueue();
	void Front(T& element);
	void Enqueue(T value);
	void Dequeue(T& element);
	void Dequeue();
	bool isFull();
	bool isEmpty();

	Queue() { front = nullptr; rear = nullptr; }
	~Queue();
private:
	node* front;
	node* rear;
};
template <typename T>
bool Queue<T>::isFull()
{
	return false;
}
template <typename T>
bool Queue<T>::isEmpty()
{
	if (front == nullptr)
		return true;
	else
		return false;
}
//Erase
template <typename T>
void Queue<T>::Dequeue()
{
	node* curr = front;
	front = front->next;
	delete curr;
}
template <typename T>
void Queue<T>::Dequeue(T &element)
{
	node* curr = front;
	front = front->next;
	element = curr->data;
	delete curr;
}
template <typename T>
void Queue<T>::Front(T& element)
{
	element = front->data;
}
//Enqueuenode at rear
template <typename T>
void Queue<T>::Enqueue(T value)
{
	node* nnode = new node(value, nullptr);
	if (front == NULL)
	{
		front = nnode;
		rear = nnode;
	}
	else
	{
		rear->next = nnode;
		rear = nnode;
	}
}
//Destructor
template <typename T>
Queue<T>::~Queue()
{
	node* temp;
	while (front != nullptr)
	{
		temp = front;
		front = front->next;
		delete temp;
	}

}

//print Queue
template <typename T>
void Queue<T>::printQueue()
{
	node* current;
	current = front;
	while (current != nullptr)
	{
		cout << current->data << " -> ";
		current = current->next;
	}
	cout << "NULL" << endl;
}
class Maze
{
private:
	char** mazeRoom;//2D Char array for Maze
	int row, col;//Rows and Columns of Maze
	point currentPosition;//Point for the current position of Rat
	point destination;//Point for the destination
	Queue<point> path;//Queue to Track and Return the Path
public:
	Maze(int r, int c)//Overloaded Constructor that takes rows and columns than randomly generates the Maze
	{
		currentPosition.setMax(r, c);
		row = r + 2;
		col = c + 2;
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
		bool flag = 0;
		cout << "Enter Starting Position X of Rat: ";//Starting X index of Rat
		cin >> temp;
		currentPosition.setX(temp + 1);
		cout << "Enter Starting Position Y of Rat: ";//Starting Y index of Rat
		cin >> temp;
		currentPosition.setY(temp + 1);
		path.Enqueue(currentPosition);//Enqueing start position
		cout << "Enter Destination Position X: ";// X index of Destination
		cin >> temp;
		destination.setX(temp + 1);
		cout << "Enter Destination Position Y: ";// X index of Destination
		cin >> temp;
		destination.setY(temp + 1);
		mazeRoom[currentPosition.getX()][currentPosition.getY()] = '0';
		mazeRoom[destination.getX()][destination.getY()] = 'X';
		char tmp = '0';
		while (!(path.isEmpty())&&!flag)//Loop till Destination is Found or Till all possible Paths have been traversed
		{
			path.Front(currentPosition);
			if (currentPosition==destination)
				flag=1;
			
			tmp = mazeRoom[currentPosition.getX()][currentPosition.getY()];
			currentPosition.set(currentPosition.getX() + 1, currentPosition.getY());
			if (mazeRoom[currentPosition.getX()][currentPosition.getY()] == ' '|| mazeRoom[currentPosition.getX()][currentPosition.getY()] == 'X')//Move Down
			{
				mazeRoom[currentPosition.getX()][currentPosition.getY()] = char(tmp + 1);
				path.Enqueue(currentPosition);
			}
			path.Front(currentPosition);
			currentPosition.set(currentPosition.getX() - 1, currentPosition.getY());
			if (mazeRoom[currentPosition.getX()][currentPosition.getY()] == ' ' || mazeRoom[currentPosition.getX()][currentPosition.getY()] == 'X')//Move Up
			{
				mazeRoom[currentPosition.getX()][currentPosition.getY()] = char(tmp + 1);
				path.Enqueue(currentPosition);
			}
			path.Front(currentPosition);
			currentPosition.set(currentPosition.getX(), currentPosition.getY() + 1);
			if (mazeRoom[currentPosition.getX()][currentPosition.getY()] == ' ' || mazeRoom[currentPosition.getX()][currentPosition.getY()] == 'X')//Move Right
			{
				mazeRoom[currentPosition.getX()][currentPosition.getY()] = char(tmp + 1);
				path.Enqueue(currentPosition);
			}
			path.Front(currentPosition);
			currentPosition.set(currentPosition.getX(), currentPosition.getY() - 1);
			if (mazeRoom[currentPosition.getX()][currentPosition.getY()] == ' ' || mazeRoom[currentPosition.getX()][currentPosition.getY()] == 'X')//Move Left
			{
				mazeRoom[currentPosition.getX()][currentPosition.getY()] = char(tmp + 1);
				path.Enqueue(currentPosition);
			}
			path.Dequeue();
			
		}
		printMaze();
		if (!flag)//Game Ends and no path is Found
			cout << "No Path Found\n";
		else//Game Ends and rat reaches Destination
			Win();

	}
	void backpoint()//Function to Go Back to Previous closest point towards start 
	{
		if (mazeRoom[currentPosition.getX()+1][currentPosition.getY()]== mazeRoom[currentPosition.getX()][ currentPosition.getY()]-1)
		{
			currentPosition.setX(currentPosition.getX() + 1);
			return;
		}
		if (mazeRoom[currentPosition.getX()-1][ currentPosition.getY()] == mazeRoom[currentPosition.getX()][currentPosition.getY()] - 1)
		{
			currentPosition.setX(currentPosition.getX() - 1);
			return;
		}
		if (mazeRoom[currentPosition.getX()][ currentPosition.getY()+1] == mazeRoom[currentPosition.getX()][currentPosition.getY()] - 1)
		{
			currentPosition.setY(currentPosition.getY() + 1);
			return;
		}
		if (mazeRoom[currentPosition.getX()][ currentPosition.getY()-1] == mazeRoom[currentPosition.getX()][currentPosition.getY()] - 1)
		{
			currentPosition.setY(currentPosition.getY() - 1);
			return;
		}
	}
	void Win()
	{
		currentPosition = destination;
		char temp = mazeRoom[currentPosition.getX()][currentPosition.getY()];
		Queue<point> shortpath;
		while (temp != '0')
		{
			backpoint();
			shortpath.Enqueue(currentPosition);
			temp = mazeRoom[currentPosition.getX()][currentPosition.getY()];
		}
		point colorpath;
		while ((!shortpath.isEmpty()))
		{
			shortpath.Dequeue(colorpath);
			mazeRoom[colorpath.getX()][colorpath.getY()] = char(177u);
		}
		printMaze();
		cout << "You Won \n";
		
	}
	void printMaze()
	{
		system("cls");
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				
				if (mazeRoom[i][j] == char(219))
				{
					cout << mazeRoom[i][j];
					SetColorAtPoint(i, j, 0x06 | 0x06);
				}
				else if (mazeRoom[i][j] == '0')
				{
					cout << "@";
				}
				else if (destination.getX() == i && destination.getY() == j)
					cout << "X";
				else if (mazeRoom[i][j] == char(177u))
				{
					cout<<mazeRoom[i][j];
					SetColorAtPoint(i, j, 0x00 | 0x0A);
				}
				else
					cout << " ";
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