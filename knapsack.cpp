/**
 * a framework for exhaustive-search discrete knapsack 
 * @author originally written by Jon Beck
 * @author modified by Lucas Alcala
 * @version March 7th, 2017
 */
#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

typedef unsigned int uint;

/**
 * raise an unsigned integer to an unsigned power
 * C++ has pow, but it accepts and returns floating point values
 * @param base the base to be raised to a power
 * @param exp the exponent to which to raise the base
 * @return base ^ exp
 */
uint ipow(uint base, uint exp)
{
  if( base == 0 )
    return 1;
  uint result = 1;
  while( exp > 0 )
  {
    if( (exp & 1) == 1 )
      result *= base;
    exp >>= 1;
    base *= base;
  }
  return result;
}

/*
 * standard input must be of the form
 * capacity
 * weight value
 * weight value
 * ...     ...
 * Function solves knapsack by exhaustive-search 
 */
int main()
{
  uint capacity;
  cin >> capacity;
  uint user_in = 0; //number of inputs for tabular output
  
  vector<uint> weights;
  vector<uint> values;

  while( !cin.eof() )
  {
    uint weight;
    uint value;
    cin >> weight >> value;
    if( !cin.eof() )
    {
      weights.push_back( weight );
      values.push_back( value );
      user_in++;
    }
  }

  uint v_size = weights.size();
  uint bit_w = 1;
  uint basic_op = 0;
  uint input_size = weights.size() + values.size();

  for (uint i=0; i<(bit_w<<v_size); i++)
  {
    uint sum=0;	//total sum of weights for each subset
    uint value=0;	//total value for each subset
    uint col_size = 0; //count size of j to align columns
    cout.setf(ios::left);
    cout.width(1);
    cout<<"{";
    
    for(uint j=0; j<v_size; j++)
    {
      basic_op++;
      /*if j item is to be included in i subset, add weight and value */
      if(i & (bit_w<<j))
      {
        sum += weights[j];
        value += values[j];
        cout.width(2);
        cout<<j;
        col_size++;
      }
    }
    cout.setf(ios::right);
    cout.width(2);
    cout<<"}";

    //compare number of inputs to align columns
    for(uint v=0; v<user_in-col_size; v++)
    {
      cout.setf(ios::left);
      cout.width(2);
      cout<<"";
    }
    //column align weight and value
    cout.setf(ios::right);
    cout.width(5);
    cout<<sum<<" ";
    cout.setf(ios::left);
    cout.width(5);

    if(sum>capacity)
    {
      cout<<"NF"<<endl;
    }
    else cout<<value<<endl;
  }
  cerr<< input_size  << setw(8) << basic_op <<endl; 
}



      
