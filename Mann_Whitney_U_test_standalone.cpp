#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <time.h>

/* 

This is a test script that performs a Mann-Whitney U test whithout external libraries.
It's just a feasibility test, it's not optimized whatsoever

*/

using namespace std;

bool sortcol(const vector<double>& v1, const vector<double>& v2){
    return v1[1] < v2[1];
}


int main(){
    int start = clock();
    vector<vector<double> > data   {
    //{gender, reaction_time, rank}
        {0, 34, 0},
        {0, 36, 0},
        {0, 41, 0},
        {0, 43, 0},
        {0, 44, 0},
        {0, 37, 0},

        {1, 45, 0},
        {1, 33, 0},
        {1, 35, 0},
        {1, 39, 0},
        {1, 42, 0}
    };

    // Number of rows;
    int m = data.size();
 
    // Number of columns;
    int n = data[0].size();

    std::cout<< "before sorting:\n\n";

    for (int i=0; i< std::size(data); i++){
        std::cout << "\n";
        for(int j = 0; j< std::size(data[0]); j++){
            std::cout << data[i][j] << ", ";
        }
    }

    // Use of "sort()" for sorting on basis
    // of 2nd column
    sort(data.begin(), data.end(), sortcol);

    //filling 3rd column and rank sum calculation:

    int T0 = 0, T1 = 0; //ranked sums
    int n0 = 0, n1 = 0; //n. of females, n. of males

    for(int i = 0; i<size(data); i++){
        data[i][2] = i+1;
        if(data[i][0] == 0){
            T0 += data[i][2];
            n0++;
        }else{
            T1 += data[i][2];
            n1++;
        }
    }

    std::cout<< "\n\nafter sorting:\n\n";

    for (int i=0; i< std::size(data); i++){
        std::cout << "\n";
        for(int j = 0; j< std::size(data[0]); j++){
            std::cout << data[i][j] << ", ";
        }
    }
    std::cout<<"n0: "<<n0;
    std::cout<<"n1: "<<n1;
    std::cout<<"T0: "<<T0;
    std::cout<<"T1: "<<T1<<"\n\n";
    //Calculating U values:

    double U0, U1;

    U0 = n0*n1 + (n0*(n0+1)/(2))-T0;
    U1 = n0*n1 + (n1*(n1+1)/(2))-T1;
    std::cout<<"U0: "<<U0;
    std::cout<<"U1: "<<U1<<"\n\n";

    double U; // U= min(U0, U1)

    U0<U1 ? U = U0 : U = U1;
    std::cout<<"U: "<<U<<"\n\n";

    double muU; //Expected value of U

    muU = (double(n0)*double(n1))/2;
    std::cout<<"muU: "<<muU;

    double sigmaU; //standard error of U

    sigmaU = sqrt((n0*n1*(n0+n1+1))/(12));
    std::cout<<"sigmaU: "<<sigmaU;

    double z;   //Z value

    z = (U-muU)/sigmaU;
    std::cout<<"Z value: "<<z<<"\n";

    double p_bothTails;   //p value
    double p_rightTail;
    double p_leftTail;

    std::cout<<"\n\n############################################################\n\n";
    p_bothTails = (1+erf(z/sqrt(2)));   //took me forever to find this formula
    std::cout<<"p both tails: "<<p_bothTails<<"\n";

    p_leftTail = (1+erf(z/sqrt(2)))/2;
    std::cout<<"p left tail: "<<p_leftTail<<"\n";

    p_rightTail = 1-p_leftTail;
    std::cout<<"p right tail: "<<p_rightTail<<"\n";
    std::cout<<"\n\n############################################################\n\n";

    int end = clock();
    std::cout << "it took " << end - start << "ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "seconds." << std::endl;

    //system("pause");

    return 0;
}


