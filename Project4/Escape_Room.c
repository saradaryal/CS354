#include <stdlib.h>
#include <stdio.h>

int fun0(){
    return  136182;
}
int fun1(){
    int a = 1234;
    int b = 159934;
    int c = 131022;
    int d = 43234;

    int e = b +c;
    if (e <= a ){
        if (b > d) return 0;
    }else if (b != d){
    return 0;
    }else
    return a;
}

int fun2(int x){
    int i =0;
    int k = 0;
    for (i =0; i <= 21; i++){
        int l = i * i;
        int y = x + l;
        k  = k + y;
        i = i + 1;
       }
    return k;
}

void fun3(int l, int k){
    int j = l / k ;
}
int fun4(int i, int j, int k){
    int ip = func4_helper(i);
    int iq = func4_helper(j);
    int ir = func4_helper(k);
    int is = ip + iq + ir;
    return is;
}

void fun5(int l){
    int a[5] = {0x2484, 0xf75, 0xb21, 0x800, 0x1d1c};
    for(int k = 0; k <=4; k++){
        int j, i = 0;
        j = j + a[i];
        k = k+1;
        }
}
int fun4_helper(int ct){
    int kt = ct *2;
    return kt;
}
int is_number_correct(int lt, int pit){
    int i = 0;
        int it;
        int pkit;
        if(it =! pkit){
             printf("Incorrect");  
            i = i +1;
        }else

            printf("Correct! Good Job");
    return i;
}
int main (){ 
    int array[6]; 
    int i; 
    printf("Emter six numbers: " ); 
    for (i = 0; i < 5; i++){
        scanf("%d", &array[i]);    
        }
        printf("\n");
        printf("You have entered: " ); 
     for(int j = 0; j < 6; j++){
        printf( "%d ", array[j]);
        }
    printf("\n");
    int a = fun0();
   int real[6] = {136182, 32755, 3443, 109698, 5208, 25654};
   fun1();
   int sti =  fun2(real[1]);
   fun3(real[5], real[2]);
   int ptr = fun4(983, 838, 783);
   for (int j = 0; j <5; j++){  
    int i = is_number_correct(array[i],real[i]);
    }
    if (i < 6) printf("You didn't get any correct numbers. Please try again.");
    else printf("Good Job! You got it all right");
    
}  

