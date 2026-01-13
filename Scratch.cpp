#include<iostream>
#include<string>
#include<fstream>
#include<iomanip> // Setprecision
using namespace std;
int lcs_length(string x,string y,int m,int n);
void print_lcs(char* b, string x,int m,int n,int col);
int main()
{
    string x,line;
    ifstream file1 ("DNA1.txt");
    if (!file1)
    {
    cout << "Error: could not open sample.txt\n";
    return 1;
     }
         // Read entire file into x
     x = "";
    while(getline(file1,line))
    x = x + line;
    file1.close();
    
    string y;
    ifstream file2 ("DNA2.txt");
    if(!file2)
    {
        cout << "Error: could not open sample2.txt\n";
        return 1;
    }
        // Read entire file into y
    y = "";
    while(getline(file2,line))
    y = y+line;
    file2.close();
    
    int m = x.length();
    int n = y.length();
    int len = lcs_length(x,y,m,n);
    cout << "\nLength of LCS is " << len << endl;

    double similarity = (2.0*len)/(m+n) * 100;
    cout << "similarity: " << fixed << setprecision(2)<<similarity << "%" << endl;

    cout << "Length of string1: " << m << endl;
    cout << "Length of string2: " << n << endl;

    return 0;
}

int lcs_length(string x, string y, int m, int n)
{
    int c[m+1][n+1];
    char b[m+1][n+1];
    for(int i=0;i<=m;i++)
    {
        c[i][0] = 0;
    }
    for(int j=0;j<=n;j++)
    {
        c[0][j] = 0;
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(tolower(x[i-1])==tolower(y[j-1])) // Case Sensitivity
            {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 'D'; // Diagonal
            }
            else if(c[i-1][j]>=c[i][j-1])
            {
                c[i][j] = c[i-1][j];
                b[i][j] = 'U'; //Upper
            }
            else
            {
                c[i][j] = c[i][j-1];
                b[i][j] = 'L'; // Left
            }
        }
    }
    cout << "LCS is: ";
    print_lcs(&b[0][0],x,m,n,n+1);
    return c[m][n];
}

void print_lcs(char* b, string x, int m, int n,int col)
{
    int i = m;
    int j = n;
    if(i==0 || j==0)
    {
        return;
    }
    char val = *(b+i*col+j);
    if(val=='D')
    {
        print_lcs(b,x,i-1,j-1,col);
        cout << x[i-1];
    }
    else if(val == 'U')
    {
        print_lcs(b,x,i-1,j,col);
    }
    else
    {
        print_lcs(b,x,i,j-1,col);
    }
}
