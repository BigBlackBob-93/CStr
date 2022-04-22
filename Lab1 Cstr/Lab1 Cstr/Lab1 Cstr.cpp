#include <iostream>
using namespace std;

class Cstr
{
    char* line;
    void MakeLine (int value)
    {
        int i;
        for (i = 0; i < value; i++) line[i] = rand() % 26 + 0x61; // от А до Z
        line[i] = '\0';
    }
public: 
    Cstr()
    {
       // cout << "!!!!!!Constructor DEFAULT!!!!!!" << endl;
        int length = 1 + rand() % 20;
        line = new char[length + 1];
        MakeLine(length);
    }
    Cstr(const char* string)
    {
       // cout << "!!!!!!Constructor with LINE parameter = " << string << "!!!!!!" << endl;
        int i, length = strlen(string);
        line = new char[length + 1];
        for (i = 0; i < length; i++) line[i] = string[i];
        line[i] = '\0';
    }
    Cstr(int length)
    {
       // cout << "!!!!!!Constructor with LENGTH parameter = " << length << "!!!!!!" << endl;
        line = new char[length + 1];
        MakeLine(length);
    }
    int GetLength()
    {
        return strlen(line);
    }
    Cstr(const Cstr& copy)
    {
       // cout << "!!!!!!Constructor COPY!!!!!!" << endl;
        line = new char[strlen(copy.line) + 1];
        strcpy(line, copy.line);
    }
    ~Cstr()
    {
        delete[] line;
       // cout << "!!!!!!Destructor!!!!!!  " << this << endl;
    }
    Cstr& operator = (Cstr& equal)
    {
       // cout << "!!!!!!OPERATOR EQUAL!!!!!!  " << this << endl;
        delete[] line;
        line = new char[strlen(equal.line) + 1];
        strcpy(line, equal.line);
        return *this;
    }
    Cstr& operator = (const char* string)
    {
      //  cout << "!!!!!!OPERATOR STRING!!!!!!  " << this << endl;
        delete[] line;
        line = new char[strlen(string) + 1];
        strcpy(line, string);
        return *this;
    }
    void Print() { cout << line << endl; }
    bool operator == (Cstr& string)
    { 
        return (strcmp(string.line, line) != 0) ? false : true;
    }
   bool operator > (Cstr& string)
    {
      return (strcmp(string.line, line) > 0) ? true : false;
    }
    bool operator < (Cstr& string)
    {
        return (strcmp(string.line, line) < 0) ? true : false;
    }
    friend ostream& operator<<(ostream& out, const Cstr& string);
};
ostream& operator<<(ostream& out, const Cstr& string)
{
    out << string.line;
    return out;
}

class CstrArray
{ 
    Cstr* Arr;
    int length;
public:
    CstrArray(int len)
    {
        length = len;
        Arr = new Cstr[len];
    }
    ~CstrArray()
    {
        delete[] Arr;
    }
    void LengthSort()
    {
        cout << endl << "//////////LENGTH SORT////////////" << endl;
        Cstr temp;
        Cstr Min;
        int t = 0, c = 0;
        for (int j = 0; j < length; j++)
        {
            Min = Arr[j];
            for (int i = j+1; i < length; i++)
                if (Min.GetLength() > Arr[i].GetLength())
                {
                    Min = Arr[i];
                    t = i;
                    c = 1;
                }
            if (c > 0)
            {
                temp = Arr[j]; Arr[j] = Min; Arr[t] = temp; c = 0;
            }
        } 
    }
    void ContentSort()
    {
        cout << endl << "//////////CONTENT SORT////////////" << endl;
        Cstr temp;
        Cstr Max;
        int t = 0, c = 0;
        for (int j = 0; j < length; j++)
        {
            Max = Arr[j];
            for (int i = j + 1; i < length; i++)
                if (Max < Arr[i])
                {
                    Max = Arr[i];
                    t = i;
                    c = 1;
                }
            if (c > 0)
            {
                temp = Arr[j]; Arr[j] = Max; Arr[t] = temp; c = 0;
            }
        }
    }
    bool CheckContentSort()
    {
        cout << endl << "//////////CHECK CONTENT SORT -> ";
        Cstr Max;
        for (int j = 0; j < length; j++)
        {
            Max = Arr[j];
            for (int i = j + 1; i < length; i++)
                if (Max < Arr[i])
                {
                    cout << " RESULT: FALSE//////////" << endl;
                    return false;
                }
        }
        cout << " RESULT: TRUE//////////" << endl;
        return true;
    }
    bool Search(Cstr& STRING)
    {
        cout << endl << "//////////SEARCH -> ";
        STRING.Print();
        cout << " -> ";
        int M = 0, R = length, L = 0;
        while (L < R)
        {
            M = (L + R) / 2;
            if (STRING < Arr[M]) R = M - 1;
            else 
                if (STRING > Arr[M]) L = M + 1;
                else
                {
                    cout << " RESULT: TRUE//////////" << endl;
                    return true;
                }
        }
            cout << " RESULT: FALSE//////////" << endl;
            return false;
    }
    Cstr& operator[](const int ind)
    {
        if (ind <= length) return Arr[ind];
        else cout << endl << "ERROR: out of area" << endl;
    }
    void PrintArr()
    {
        for (int i = 0; i < length; i++) Arr[i].Print();
    }
    friend ostream& operator << (ostream& out,  const CstrArray& Array);
};
ostream& operator << (ostream& out,  const CstrArray& Array)
{
    for (int i = 0; i < Array.length && i <= 50; i++)
        out << Array.Arr[i] << endl;
    return out;
}

int main()
{
    srand(time(NULL));

    /*Cstr KILL; KILL.Print(); 
    Cstr MY("self"); MY.Print(); 
    Cstr PLEASE(5); PLEASE.Print(); 
    Cstr KILL2(KILL); KILL2.Print(); 
    KILL = MY; 
    KILL.Print(); MY.Print();
    MY = "me"; MY.Print();
    bool result = KILL == KILL2;
    if (!result) cout << KILL << " != " << KILL2 << endl;*/

    CstrArray TRILL(25); cout << TRILL;
    TRILL.LengthSort(); cout << TRILL;
    TRILL.ContentSort(); cout << TRILL;
    TRILL.CheckContentSort();
    Cstr FAIL(5);
    TRILL.Search(FAIL);
}
