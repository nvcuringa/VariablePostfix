
//Nick Curinga
//CS 256
#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <stack>
#include <vector>
#include <fstream>
#include <cctype>


using namespace std;


class Var {

private:
	string key;
	double token;


public:


	Var(string k, double t)
	{
		key = k;
		token = t;
	}

	void setKey(string k)
	{
		key = k;
	}

	void setToken(double t)
	{
		token = t;
	}

	string getKey()
	{
		return key;
	}

	double getToken()
	{
		return token;
	}
};


class PostFix
{
private:
	stack<double> s;
	vector<Var> v;
	vector<string> file;
	string input;
	int count;
	bool print = true;
	

public:

	vector<string> SplitString(string s)
	{
		vector<string> vs;
		string split(s);
		istringstream i(split);

		do
		{
			string token;
			i >> token;
			vs.push_back(token);
		} while (i);

		vs.resize(vs.size() - 1);
		return vs;
	}


	bool isOperator(string l)
	{
		if (l == "+" || "-" || "/" || "*")
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void create(string l) 
	{
			string input;
			ifstream infile(l);
			file.push_back(l);
			
	}

	void save(vector<string> l)
	{
		ofstream outfile;

		outfile.open(file[count]);
		count++;

		for (int i = 0; i < l.size(); i++)
		{
			outfile << l[i] << endl;
		}

		outfile.close();

	}



	void run(string l)
	{
		vector<string> vs;
		ifstream infile;
		infile.open(l);
		string line;

		for (line; getline(infile, line);)
		{
			 vs = SplitString(line);
			 check(vs);
		}
		
	

	}

	void dir()
	{
		for (int i = 0; i < file.size(); i++)
		{
			cout << file[i] << endl;
		}
	}

	void varList()
	{
		for (int i = 0; i < v.size(); i++) 
		{
			cout << v[i].getKey(); cout << ":";
			cout << v[i].getToken() << endl;
		}

	}


	void check(vector<string> l)
	{
		
		
		if (l[0] == "OUT" )
		{
			out(l[1]);
		}
		else
		{
			for (int i = 1; i < l.size(); i++)
			{
				if (isVariable(l[i]))
				{
					s.push(getVar(l[i]));
				}
				else if (l[i] == "=")
				{
					Var a(l[0], s.top());
					s.pop();
					v.push_back(a);
				}
				else
				{
					
					eval(l[i]);
				}
			}
		}

	}


	void out(string l)
	{

			for (int i = 0; i < v.size(); i++)
			{
				if (l == v[i].getKey())
				{

					cout << v[i].getToken() << endl;
				}
			}
	}

	bool isVariable(string l)
	{
		
		for (int i = 0; i < v.size(); i++)
		{
			if (l == v[i].getKey())
			{
				return true;
			}
		}
		return false;
	}


	double getVar(string l)
	{
	
		for (int i = 0; i < v.size(); i++)
		{
			if (l == v[i].getKey())
			{
		
				return v[i].getToken();
			}
		}
		return 0;
	}

	

	void eval(string l)
	{

		double pop1;
		double pop2;
		double operation;

		if (l == "+")
		{
			pop1 = s.top();
			s.pop();
			pop2 = s.top();
			s.pop();
			operation = pop2 + pop1;
			s.push(operation);
		}
		else if (l == "-")
		{
			pop1 = s.top();
			s.pop();
			pop2 = s.top();
			s.pop();
			operation = pop2 - pop1;
			s.push(operation);
		}
		else if (l == "*")
		{
			pop1 = s.top();
			s.pop();
			pop2 = s.top();
			s.pop();
			operation = pop2 * pop1;
			s.push(operation);
		}
		else if (l == "/")
		{
			pop1 = s.top();
			s.pop();
			pop2 = s.top();
			s.pop();
			operation = pop2 / pop1;
			s.push(operation);
		}
		else
		{
			s.push(stod(l));

		}

	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	PostFix p;
	string input;
	string in;
	vector<string> vs;
	vector<string> toSave;
	bool console = true;
	

	cout << "Please Enter Expression/s" << endl;
	cout << "Commands: CREATE, SAVE, RUN, DIR, VARLIST, and OUT" << endl;
	cout << "To end please type: END" << endl;
	
	
		while (input != "END")
		{
			getline(cin, input);
			vs = p.SplitString(input);
		
			if (vs[0] == "CREATE")
			{
				p.create(vs[1]);
				console = false;
			}
			else if (vs[0] == "SAVE")
			{
				p.save(toSave);
				toSave.clear();
			}
			else if (vs[0] == "RUN")
			{
				p.run(vs[1]);
				console = true;
			}
			else if (vs[0] == "DIR")
			{
				p.dir();
			}
			else if (vs[0] == "VARLIST")
			{
				p.varList();
			}
			else
			{
				toSave.push_back(input);
				if (console)
				{
					p.check(vs);
				}
		
			}
		

	}
	cin.get();
	return 0;
}

