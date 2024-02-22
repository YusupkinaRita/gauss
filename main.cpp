#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>


void manual_fill(double** matrix, int size){
    for (int i=0;i<size;i++){
        for(int j=0;j<size; j++){
            std::cout<<"cell "<<i<<"_"<<j<<std::endl;
            std::cin>>matrix[i][j];
        }
    }
}
void vector_fill(double** matrix, int size){
    for (int i=0;i<size;i++){
            std::cout<<"vector cell "<<i<<std::endl;
            std::cin>>matrix[i][size];
        
    }
}

void matrix_fill(double ** matrix, int size){
    for(int i=0; i<size; i++){
        for (int j=0; j< size+1; j++){
            matrix[i][j]=static_cast<double>(10000000+rand()%100000000);
        }
    }
}

void print_matrix(double** matrix, int size){
     for(int i=0; i<size; i++){
        for (int j=0; j< size; j++){
            std::cout<<matrix[i][j]<<' ';
            
        }
        std::cout<<'=';
        std::cout<<matrix[i][size]; 
        std::cout<< std::endl;
    }
}

void col_swap(double** matrix, int size, int s){
    int temp=0;
    for(int j=s+1;j<size;j++){
        if(matrix[s][j]!=0){
            for(int i=0;i<size;i++){
                temp=matrix[i][s];
                matrix[i][s]=matrix[i][j];
                matrix[i][j]=temp;
            }
        break;
        }
    }
}

void matrix_multiply(double** matrix, double* solution, double* check, int size){
    for(int i=0; i<size;i++){
        for( int j=0; j<size;j++){
            check[i]+=matrix[i][j]*solution[j];

        }

    }
}


void gauss(double** matrix, int size){
    double r=0;
    for( int i=0; i<size; i++){
        r=matrix[i][i];
        if(r==0)
            col_swap(matrix, size,i);
        
        r=matrix[i][i];
        for (int j=0; j<size+1;j++){
            matrix[i][j]/=r;
        }
        for (int k=i+1;k<size; k++){
            r=matrix[k][i];
            for(int j=0; j<size+1;j++){
                matrix[k][j]=matrix[k][j]-matrix[i][j]*r;
            }
        }
        print_matrix(matrix, size);
        std::cout<<"   |"<< std::endl;
        std::cout<<"   v"<< std::endl;
    }
}

void approx_find(double** matrix, double* check, double* approx, int size){
    for (int i=0; i<size; i++){
        approx[i]=matrix[i][size]-check[i];

    }
}


int main(){
srand ( time(NULL) );
int size=0;
std::cout << "Enter matrix size ";
std::cin >> size;

double* solution= new double[size];
double* check= new double[size];
double* approx= new double[size];

double** matrix = new double*[size];
for (int i = 0; i < size; i++){
    matrix[i] = new double[size+1];
}

int id=0;
std::cout<<"0 if random, 1 if manual ";
std::cin>>id;
if(id==0)
matrix_fill(matrix, size);
else{
manual_fill(matrix, size);
vector_fill(matrix, size);
}

print_matrix(matrix, size);
std::cout<<' '<<std::endl;
gauss(matrix, size);
std::cout<<"the solution = "<<std::endl;
for (int i=size-1;i>=0;i--){
    solution[i]=matrix[i][size];
    for(int j=i+1;j<size;j++){
        solution[i]=solution[i]-solution[j]*matrix[i][j];
    }
}

for (int i=0; i<size;i++){
    std::cout<<solution[i]<<std::endl;
}

matrix_multiply(matrix, solution, check, size);
std::cout<<" "<<std::endl;
approx_find(matrix, check, approx,size);
std::cout<<"checking: "<<std::endl;
for (int i=0; i<size;i++){
    std::cout<<approx[i]<<std::endl;
}

for(int i=0;i<size;i++){
    delete(matrix[i]);
}
delete(matrix);
delete(check);
delete(approx);


return 0;

// \'o'/
}