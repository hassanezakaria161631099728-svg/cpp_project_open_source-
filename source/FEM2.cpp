// 2D Frame FEM Solver - STEP 4: Post Processing // Pure C++ implementation without external libraries // 3 DOF per node: ux, uy, rotz

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// ===================================================== //                 BASIC DATA STRUCTURES // =====================================================

struct Node { int id; double x; double y; };

struct Element { int id; int n1; int n2;

double E;
double A;
double I;
double q;

string load_type;

double L;
double c;
double s;

};

// ===================================================== //            PREPROCESSING // =====================================================

void computeGeometry(Element &e, const vector<Node> &nodes) {

double x1 = nodes[e.n1-1].x;
double y1 = nodes[e.n1-1].y;

double x2 = nodes[e.n2-1].x;
double y2 = nodes[e.n2-1].y;

double dx = x2 - x1;
double dy = y2 - y1;

e.L = sqrt(dx*dx + dy*dy);

e.c = dx / e.L;
e.s = dy / e.L;

}

// =====================================================
//ELEMENT ROUTINES // =====================================================

void localStiffness(const Element &e, double k[6][6]) {

double E = e.E;
double A = e.A;
double I = e.I;
double L = e.L;

double EA = E*A / L;
double EI = E*I;

double a = EA;
double b = 12*EI/(L*L*L);
double c = 6*EI/(L*L);
double d = 4*EI/L;
double f = 2*EI/L;

for(int i=0;i<6;i++)
    for(int j=0;j<6;j++)
        k[i][j]=0;

k[0][0]= a;   k[0][3]= -a;
k[3][0]= -a;  k[3][3]= a;

k[1][1]= b;   k[1][2]= c;   k[1][4]= -b;  k[1][5]= c;

k[2][1]= c;   k[2][2]= d;   k[2][4]= -c;  k[2][5]= f;

k[4][1]= -b;  k[4][2]= -c;  k[4][4]= b;   k[4][5]= -c;

k[5][1]= c;   k[5][2]= f;   k[5][4]= -c;  k[5][5]= d;

}

void transformationMatrix(const Element &e, double T[6][6]) {

double c = e.c;
double s = e.s;

for(int i=0;i<6;i++)
    for(int j=0;j<6;j++)
        T[i][j]=0;

T[0][0]= c;  T[0][1]= s;
T[1][0]= -s; T[1][1]= c;
T[2][2]= 1;

T[3][3]= c;  T[3][4]= s;
T[4][3]= -s; T[4][4]= c;
T[5][5]= 1;

}

void multiply6(double A[6][6], double B[6][6], double C[6][6]) {

for(int i=0;i<6;i++){
    for(int j=0;j<6;j++){

        C[i][j]=0;

        for(int k=0;k<6;k++)
            C[i][j]+=A[i][k]*B[k][j];
    }
}

}

void transpose6(double A[6][6], double AT[6][6]) {

for(int i=0;i<6;i++)
    for(int j=0;j<6;j++)
        AT[j][i]=A[i][j];

}

void globalStiffness(const Element &e, double kg[6][6]) {

double k[6][6];
double T[6][6];
double TT[6][6];
double temp[6][6];

localStiffness(e,k);
transformationMatrix(e,T);
transpose6(T,TT);

multiply6(TT,k,temp);
multiply6(temp,T,kg);

}

void equivalentLoad(const Element &e, double fe[6]) {

double L = e.L;
double q = e.q;

double fl[6];

fl[0]=0;
fl[1]= q*L/2;
fl[2]= q*L*L/12;

fl[3]=0;
fl[4]= q*L/2;
fl[5]= -q*L*L/12;

if(e.load_type=="local"){
    for(int i=0;i<6;i++)
        fe[i]=fl[i];
}
else{
    double T[6][6];
    transformationMatrix(e,T);

    for(int i=0;i<6;i++){
        fe[i]=0;
        for(int j=0;j<6;j++)
            fe[i]+=T[j][i]*fl[j];
    }
}

}

// =====================================================
//GLOBAL SYSTEM ROUTINES // =====================================================

void assembleGlobal(double K[12][12], double kg[6][6], int n1, int n2) {

int map[6] = {
    3*(n1-1), 3*(n1-1)+1, 3*(n1-1)+2,
    3*(n2-1), 3*(n2-1)+1, 3*(n2-1)+2
};

for(int i=0;i<6;i++)
    for(int j=0;j<6;j++)
        K[ map[i] ][ map[j] ] += kg[i][j];

}

void assembleLoad(double F[12], double fe[6], int n1, int n2) {

int map[6] = {
    3*(n1-1), 3*(n1-1)+1, 3*(n1-1)+2,
    3*(n2-1), 3*(n2-1)+1, 3*(n2-1)+2
};

for(int i=0;i<6;i++)
    F[ map[i] ] += fe[i];

}

void applyBC(double K[12][12], double F[12], vector<int> bc) {

double big = 1e20;

for(size_t i=0;i<bc.size();i++){

    int d = bc[i]-1;

    K[d][d] += big;
    F[d] = 0;
}

}

void solveSystem(double K[12][12], double F[12], double U[12]) {

int n=12;

double A[12][13];

for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
        A[i][j]=K[i][j];

    A[i][n]=F[i];
}

for(int k=0;k<n;k++){

    double piv=A[k][k];

    for(int j=k;j<=n;j++)
        A[k][j]/=piv;

    for(int i=0;i<n;i++){
        if(i==k) continue;

        double f=A[i][k];

        for(int j=k;j<=n;j++)
            A[i][j]-=f*A[k][j];
    }
}

for(int i=0;i<n;i++)
    U[i]=A[i][n];

}

// =====================================================
//STEP 4 : POST PROCESSING // =====================================================

void elementForces(const Element &e, double U[12]) {

// 1. Extract element displacement vector in global

int map[6] = {
    3*(e.n1-1), 3*(e.n1-1)+1, 3*(e.n1-1)+2,
    3*(e.n2-1), 3*(e.n2-1)+1, 3*(e.n2-1)+2
};

double ug[6];

for(int i=0;i<6;i++)
    ug[i]=U[ map[i] ];

// 2. Transform to local

double T[6][6];
transformationMatrix(e,T);

double ul[6]={0};

for(int i=0;i<6;i++)
    for(int j=0;j<6;j++)
        ul[i]+=T[i][j]*ug[j];

// 3. Local stiffness

double k[6][6];
localStiffness(e,k);

// 4. Fixed end load

double fe[6];
equivalentLoad(e,fe);

// 5. Internal forces

double f_int[6]={0};

for(int i=0;i<6;i++){
    for(int j=0;j<6;j++)
        f_int[i]+=k[i][j]*ul[j];

    f_int[i]-=fe[i];
}

cout<<"\nELEMENT "<<e.id<<" FORCES (LOCAL AXIS)"<<endl;

cout<<"  START NODE"<<endl;
cout<<"    N = "<<f_int[0]<<endl;
cout<<"    V = "<<f_int[1]<<endl;
cout<<"    M = "<<f_int[2]<<endl;

cout<<"  END NODE"<<endl;
cout<<"    N = "<<f_int[3]<<endl;
cout<<"    V = "<<f_int[4]<<endl;
cout<<"    M = "<<f_int[5]<<endl;

}

// ===================================================== //MAIN // =====================================================

int main() {

vector<Node> nodes = {
    {1,0,0},
    {2,0,7},
    {3,18,7},
    {4,18,0}
};

double E=2.1e8;
double A=84.5e-4;
double I=23130e-8;
double q=-195;

vector<Element> elements;

elements.push_back({1,1,2,E,A,I,0,"local"});
elements.push_back({2,2,3,E,A,I,q,"global"});
elements.push_back({3,3,4,E,A,I,0,"local"});

for(size_t i=0;i<elements.size();i++)
    computeGeometry(elements[i],nodes);

double K[12][12]={0};
double F[12]={0};

for(size_t i=0;i<elements.size();i++){

    double kg[6][6];
    double fe[6];

    globalStiffness(elements[i],kg);
    equivalentLoad(elements[i],fe);

    assembleGlobal(K,kg,elements[i].n1,elements[i].n2);
    assembleLoad(F,fe,elements[i].n1,elements[i].n2);
}

// nodal loads
F[4]+= -1387;
F[7]+= -1387;

vector<int> bc = {1,2,3,10,11,12};

applyBC(K,F,bc);

double U[12];

solveSystem(K,F,U);

cout<<"DISPLACEMENTS"<<endl;

for(int i=0;i<12;i++)
    cout<<"U["<<i+1<<"] = "<<U[i]<<endl;

// -------- POST PROCESSING --------

for(size_t i=0;i<elements.size();i++)
    elementForces(elements[i],U);

return 0;

}


