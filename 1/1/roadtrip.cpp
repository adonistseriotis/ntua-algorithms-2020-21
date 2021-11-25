#include<iostream>
#include<stdio.h>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

typedef pair<long long int,long long int> tupla; // For (pi,ci)

long long int findMaxD(long long int * arr,const long long int &K, const long long int &D);
bool SortC(const tupla &a, const tupla &b);
double howFast(long long int c, long long int d, const int &Cf, const int &Cs);
long long int findCars(tupla * cars, long long int * stations, int left, int right, const long long int &T, const int &Cf, const int &Cs, const int &Tf, const int &Ts, const long long int &K, const long long int &D);
long long int timer(long long int * stations, long long int c, const int &Cf, const int &Cs, const int &Tf, const int &Ts, const long long int &K, const long long int &D);

int main()
{

/* Define variables */
    long long int N,K,D,T;
    int Ts,Cs,Tf,Cf;

/* Get 4 first variables */
    std::ios_base::sync_with_stdio (false);
    cin >> N >> K >> D >> T;
    tupla cars[N];      //Define array in the sizeof cars
    long long int stations[K];    //Define array in the sizeof stations

/* Get car info */
    for(int i=0; i<N; i++)
    {
        cin >> cars[i].first >> cars[i].second;
    }


/* Get stations info */
    for(int i=0; i<K; i++)
    {
        cin >> stations[i];
    }

    cin >> Ts >> Cs >> Tf >> Cf;

/* Sort stations */
    sort(stations,stations+K);

/* Sort cars with custom comperator */
    sort(cars,cars+N,SortC);
   
/* Check if possible */
    if(timer(stations,cars[N-1].second,Cf,Cs,Tf,Ts,K,D) > T or timer(stations,cars[N-1].second,Cf,Cs,Tf,Ts,K,D) == -1)
    {
        long long int res = -1;
        printf("%lld\n",res);
        return 0;
    }

/* Find first car that can be there on time */
    int pos = findCars(cars,stations,0,N-1,T,Cf,Cs,Tf,Ts,K,D);

/* Find min price from the cars that can reach */
    long long int result=cars[pos].first;
    for(int i=pos; i<N; i++)
    {
        if(cars[i].first<result)
        {
            result=cars[i].first;
        }
    }
    printf("%lld\n", result);

    return 0;
}

/* Comparator for tupla typedef */
bool SortC(const tupla &x, const tupla &y)
{
    return (x.second < y.second);
}

/* Find max element in array */
long long int findMaxD(long long int * arr,const long long int &K, const long long int &D)
{
    long long int max=0;
    for(int i=-1; i<K-1; i++)
    {
        int d;
        if(i==-1)
        {
            d = arr[0];
        }
        else
        {
            d = arr[i+1]-arr[i];
        }
        
        if(d>max)
        {
            max = d;
        }
    }

    int d = D-arr[K-1];
    if(d>max)
    {
        max = d;
    }
    return max;
}

/* Find Cf coefficient */
double howFast(long long int c, long long int d, const int &Cf, const int &Cs)
{
    double res;
    if(Cs*d > c)
    {
        res = -1;
    }
    else
    {
        double C = (double) c;
        double D = (double) d;
        double x = C/D;
        res = (Cs-x)/(Cs-Cf);

        if(res > 1)             //Car reaches in full speed and has leftovers
        {
            res = 1;
        }
        else if(res == -0)      //Bug fix
        {
            res = 0;
        }
    }
    
    return res;
}

/* Binary Searches the first car that can reach in T */
long long int findCars(tupla * cars, long long int * stations, int left, int right, const long long int &T, const int &Cf, const int &Cs, const int &Tf, const int &Ts, const long long int &K, const long long int &D)
{
    long long int maxd = findMaxD(stations,K,D);
    while(left<right)
    {
        int mid =left + (right-left)/2;
        double a = howFast(cars[mid].second,maxd,Cf,Cs);
         if(a < 0)   //Can't manage longest distance
        {
            left = mid+1;
        }
        else        //Can manage longest distance
        { 
            int timeit = timer(stations, cars[mid].second, Cf, Cs, Tf, Ts, K, D);
            if(timeit <= T)          //Can reach on time
            {
                right=mid-1;
               // return findCars(cars,stations,left,mid-1,T,Cf,Cs,Tf,Ts,K);
            }
            else                    //Can't reach on time
            {
                left = mid+1;
                //return findCars(cars,stations,mid+1,right,T,Cf,Cs,Tf,Ts,K);
            }
        }
    }
    return left;
}

/* Time the route */
long long int timer(long long int * stations, long long int c, const int &Cf, const int &Cs, const int &Tf, const int &Ts, const long long int &K, const long long int &D)
{
    long long int time = 0;
    long long int d;
    for(int i=-1; i<K-1; i++)
    {
        if(i==-1)
        {
            d = stations[0];
        }
        else
        {
            d = stations[i+1]-stations[i];
        }

        int a = howFast(c,d,Cf,Cs);     //Find Cf coeff
        if(a < 0)
        {
            return -1;
        }
        time += (a*Tf+(1-a)*Ts)*d;      //Find time for every station
    }
    d = D-stations[K-1];
    int a = howFast(c,d,Cf,Cs);
    if(a < 0)
        {
            return -1;
        }
    time += (a*Tf+(1-a)*Ts)*d;
    return time;
}