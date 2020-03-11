#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>


#define MAX 100


void printArray(int size,int array1[][size]){
   for(int row=0; row<size; row++){
       for(int col=0;col<size;col++){
           printf("%d ",array1[row][col]);
       }
       printf("\n");
   }
    
    
}


//Used this code for reference https://www.geeksforgeeks.org/matrix-multiplication-recursive/
static void recur3(int size,int array1[][size], int array2[][size], int array5[][size], int reset) //for some reason the second dimension has to be given
{ 
/*Really important to use static variables because they can keep their value from call to call*/
    static int i = 0, j = 0, k = 0; 
    if(reset==1){//reset the static variables to zero when the function is first called
        i=0;
        j=0;
        k=0;
        reset=0;
    }
    if (i >= size){//This means we went through every row
        return; 
    }
    if (j < size){ //this means we are still going through the columns
     
      if (k < size){ //this is where we do the multiplying and adding calculations
       
         array5[i][j] += array1[i][k] * array2[k][j]; 
         k++; 
         recur3(size, array1, array2, array5,reset); //so here we're going through every k
      } 
      k = 0; //this is when we finished goin through all the k's we reset it for the net run
      j++; 
      recur3(size, array1, array2, array5,reset); //here is when we finished with the caclualtionf ro one value in C and are moving to the next one
    }
    j = 0; 
    i++; 
    recur3(size, array1, array2, array5,reset); 
}

void sum(int size,int array1[][size], int array2[][size], int sumArray[][size]){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            sumArray[i][j]=array1[i][j]+array2[i][j];
        }
    }
}

//MinusArray= Array1-Array2
void minus(int size,int array1[][size], int array2[][size], int minusArray[][size]){

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            minusArray[i][j]=array1[i][j]-array2[i][j];
        }
    }

}
//This round to the next power of two function is from https://stackoverflow.com/questions/466204/rounding-up-to-next-power-of-2
int next_two(int v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;

    v++;
    return v;
}

///////////////////////////////////////////////////////MAIN//////////////////////////////////////////////////////////
//Code https://www.daniweb.com/programming/software-development/code/216411/reading-a-file-line-by-line
int main ( void )
{
   //Time Stuff
   time_t start,end;
   
   
   static const char filename[] = "input.txt";
   FILE *file = fopen ( filename, "r" );
   FILE *out1 = fopen ( "output_p1_m1.txt", "w" );
   FILE *out2 = fopen ( "output_p1_m2.txt", "w" );
      int holder = 0;
      
      char line [ 2000 ]; /* or other suitable maximum line size */
      fscanf (file, "%d", &holder); 
      int size = holder;
      //printf("Size %d \n", size);
      //printf("Size %d \n", size);
      int array1[size][size];
      int array2[size][size];
      int array3[size][size];
      fgets ( line, sizeof line, file );//used to get rid of size line
      
    ////Parse Variables///
    int number;
    int init_size = strlen(line);
	char delim[] = " ";
	char *ptr = strtok(line, delim);
    int i = 0;
    int row = 0;
    int col = 0;
   ////////////////////////
      int loop=0;//count how many lines we've gone through
      
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
    //parse
    if(loop==size){//reset row for second array and add in zeros for missing row(s)
    row=0;
    }
    int number;
    int init_size = strlen(line);
	char delim[] = " ";
	char *ptr = strtok(line, delim);
    int i = 0;
    col = 0;
	while(ptr != NULL){//put each number in line into arrays
        ptr[strcspn(ptr, "\n")] = 0;
        sscanf(ptr, "%d", &number);//https://www.geeksforgeeks.org/converting-strings-numbers-cc/
        //printf("%d ", number);
        if(loop>=size){
            array2[row][col] = number;
            //printf("Hey\n");
        }
        else{
            array1[row][col] = number;
        }
        col++;
		ptr = strtok(NULL, delim);
        number=0;
	}
    //printf("column number %d \n", col);
    
    
    //Error Checking for not enough nums in column
    if(col<size){
        int missing = size-col;
        for(int i=col;i<size;i++){
            if(loop>=size){
            array2[row][i] = 0;
            //printf("Hey\n");
            }
            else{
                array1[row][i] = 0;
            }
        }
    }
	//printf("\n");
    row++;
    loop++;
      }
      fclose ( file );
   
   
   //Now we have both matrices stored in array1 and array2
   //Lets print array1
   //printf("Array 1: \n");
   for(int row=0; row<size; row++){
       for(int col=0;col<size;col++){
           //printf("%d ",array1[row][col]);
       }
       //printf("\n");
   }
   //Lets print array2
   //printf("Array 2: \n");
   for(int row=0; row<size; row++){
       for(int col=0;col<size;col++){
           //printf("%d ",array2[row][col]);
       }
       //printf("\n");
   }
   
   //////////////////////Matrix Multiplication//////////////////////////////////////
   start = clock();//start1
   int adder=0;
   for(int i=0;i<size;i++){
       for(int j=0;j<size;j++){
           for(int k =0;k<size;k++){//row times column
               //array3[i][j] += array1[i][k]*array2[k][j];
               adder += array1[i][k]*array2[k][j];
               //printf("%d x %d\n",array1[i][k],array2[k][j]);
           }
           array3[i][j]=adder;
           adder = 0;
           //printf("\n");
       }
       
       //printf("\n");
   }
   end=clock();//end1
   //Lets print array3
   //printf("Array 3: \n");
   //Below Function used the code here for reference: https://www.programmingsimplified.com/c-program-multiply-matrices
   for(int row=0; row<size; row++){
       for(int col=0;col<size;col++){
           //printf("%d ",array3[row][col]);
           fprintf(out1, "%d ",array3[row][col]);//print to file
       }
       //printf("\n");
       if(row<size-1)//golden out doesn't have newline at end of file
           fprintf(out1, "\n");
   }
   /////////////////////End of Naive Matrix Multiplication//////////////////////////////////////

   //Clock Stuff
   
   int running_time1 = end-start;
   //printf("Time: %d\n",running_time1);
   FILE *out3 = fopen ( "output_p2.txt", "w" );
   fprintf(out3, "%d ",running_time1);
   
   //Lets do some Strassen Method///
   
    int size2 = next_two(size);

    int arrayS1[size2][size2];
    int arrayS2[size2][size2];
    int arrayS3[size2][size2];
    int sumArray[size2/2][size2/2];//used for calculations
    int sumArray2[size2/2][size2/2];
    int minusArray[size2/2][size2/2];

    ///Make the eight total sub matrices
    int A11[size2/2][size2/2];
    int A12[size2/2][size2/2];
    int A21[size2/2][size2/2];
    int A22[size2/2][size2/2];
    int B11[size2/2][size2/2];
    int B12[size2/2][size2/2];
    int B21[size2/2][size2/2];
    int B22[size2/2][size2/2];
    
    //Make the 7 Matrices/////////////////////////
    int M1[size2/2][size2/2];//works up to here
    int M2[size2/2][size2/2];//stops working here
    int M3[size2/2][size2/2];
    int M4[size2/2][size2/2];
    int M5[size2/2][size2/2];
    int M6[size2/2][size2/2];
    int M7[size2/2][size2/2];

       //Make the C Matrices
    int C11[size2/2][size2/2];
    int C12[size2/2][size2/2];
    int C21[size2/2][size2/2];
    int C22[size2/2][size2/2];
   
   int j;
   //fill arrays with zeros just in case
    for(i =0; i<size2; i++){
        for(j=0;j<size2;j++){
            arrayS1[i][j] = 0;
            arrayS2[i][j] = 0;
            arrayS3[i][j] = 0;
        }
    }
   
   //fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             M1[i][j] = 0;
             M2[i][j] = 0;
             M3[i][j] = 0;
             M4[i][j] = 0;
             M5[i][j] = 0;
             M6[i][j] = 0;
             M7[i][j] = 0;
             C11[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
   int k=0;
//Fill normal arrays
    for(i =0; i<size; i++){
        for(j=0;j<size;j++){
            arrayS1[i][j] = array1[i][j];
            arrayS2[i][j] = array2[i][j];
            arrayS3[i][j] = 0;
            k++;
        }
    }
   
       //Fill sub arrays
    //Fill each sub matrix
    for(int i =0; i<size2; i++){
        for(int j=0;j<size2;j++){
            if(i<=size2/2-1 && j<=size2/2-1){
                A11[i][j]=arrayS1[i][j];
                B11[i][j]=arrayS2[i][j];
            }
            else if(i>size2/2-1 && j<=size2/2-1){
                A21[i-size2/2][j]=arrayS1[i][j];
                B21[i-size2/2][j]=arrayS2[i][j];
            }
            else if(i<=size2/2-1 && j>size2/2-1){
                A12[i][j-size2/2]=arrayS1[i][j];
                B12[i][j-size2/2]=arrayS2[i][j];
            }
            else if(i>size2/2-1 && j>size2/2-1){
                A22[i-size2/2][j-size2/2]=arrayS1[i][j];
                B22[i-size2/2][j-size2/2]=arrayS2[i][j];
            }
            else
                printf("Something is wrong!!!");
        }
    }
   
   //fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             M1[i][j] = 0;
             M2[i][j] = 0;
             M3[i][j] = 0;
             M4[i][j] = 0;
             M5[i][j] = 0;
             M6[i][j] = 0;
             M7[i][j] = 0;
             C11[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
   
   int reset = 1;
   ///////////////////7 Matrices/////////////////////////
    //M1--Works
    sum(size2/2, A11, A22, sumArray);
    //printf("Array A11+A22: \n");
    //printArray(size2/2,sumArray);
    sum(size2/2, B11, B22, sumArray2);
    //printf("Array B11+B22: \n");
    //printArray(size2/2,sumArray2);
    reset = 1;
    
    recur3(size2/2,sumArray,sumArray2,M1,reset);
    
    start = clock();
    //printf("Array M1: \n");
    //printArray(size2/2,M1);
//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             M2[i][j] = 0;
             M3[i][j] = 0;
             M4[i][j] = 0;
             M5[i][j] = 0;
             M6[i][j] = 0;
             M7[i][j] = 0;
             C11[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    
    //M2
    sum(size2/2, A21, A22, sumArray);
    recur3(size2/2,sumArray, B11,M2,reset);
    //printf("Array M2: \n");
    //printArray(size2/2,M2);
//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             M3[i][j] = 0;
             M4[i][j] = 0;
             M5[i][j] = 0;
             M6[i][j] = 0;
             M7[i][j] = 0;
             C11[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    //M3
    recur3(size2/2,A11,B12,sumArray,reset);
    recur3(size2/2,A11,B22,sumArray2,reset);
    minus(size2/2, sumArray, sumArray2, M3);
    //printf("Array A11: \n");
    //printArray(size2/2,A11);
    //recur3(size2/2,A11,minusArray,M3,reset);
    //printf("Array M3: \n");
    //printArray(size2/2,M3);
    
//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             M4[i][j] = 0;
             M5[i][j] = 0;
             M6[i][j] = 0;
             M7[i][j] = 0;
             C11[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    //M4
    minus(size2/2, B21, B11, minusArray);
    recur3(size2/2,A22,minusArray,M4,reset);
    //printf("Array M4: \n");
    //printArray(size2/2,M4);

//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             M5[i][j] = 0;
             M6[i][j] = 0;
             M7[i][j] = 0;
             C11[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    //M5
    sum(size2/2, A11, A12, sumArray);
    //printf("Array A11+A12: \n");
    //printf("Array B22: \n");
    recur3(size2/2,sumArray,B22,M5,reset);
    //printf("Array M5: \n");
    //printf("Array M5: \n");
    //printArray(size2/2,M5);
    //exit(0);

//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             M6[i][j] = 0;
             M7[i][j] = 0;
             C11[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    //M6
    minus(size2/2, A21, A11, minusArray);
    //printf("minus Array: \n");
    //printArray(size2/2,minusArray);
    sum(size2/2, B11, B12, sumArray);
    //printf("sumArray: \n");
    //printArray(size2/2,sumArray);
    recur3(size2/2,minusArray,sumArray,M6,reset);
    //printf("Array M6: \n");
    //printArray(size2/2,M6);
    
//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             M7[i][j] = 0;
             C11[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    //M7
    minus(size2/2, A12, A22, minusArray);
    //printf("A12-A22: \n");
    //printArray(size2/2,minusArray);
    sum(size2/2, B21, B22, sumArray);
    //printf("B21+B22: \n");
    //printArray(size2/2,sumArray);
    reset = 1;
    recur3(size2/2,minusArray,sumArray,M7,reset);
    //printf("Array M7: \n");
    //printArray(size2/2,M7);
    
    
    //printf("A22\n");
    //printArray(size2/2,A22);
    ///////////////Target Matrix C////////////
//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             C11[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    //C11
    sum(size2/2, M1, M4, sumArray);
    minus(size2/2, sumArray, M5, minusArray);
    sum(size2/2, minusArray, M7, C11);
    //printf("C Matrix C11: \n");
    //printArray(size2/2,C11);
    
//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             C12[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    //C12
    sum(size2/2, M3, M5, C12);
    //printf("C Matrix C12: \n");
    //printArray(size2/2,C12);
//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             C21[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    //C21
    sum(size2/2, M2, M4, C21);
    //printf("C Matrix C21: \n");
    //printArray(size2/2,C21);
//fill arrays with zeros just in case
    for(i =0; i<size2/2; i++){
        for(j=0;j<size2/2;j++){
            sumArray[i][j] = 0;
            sumArray2[i][j] = 0;
            minusArray[i][j] = 0;
             C22[i][j] = 0;
        }
    }
    //C22
    minus(size2/2, M1, M2, minusArray);
    sum(size2/2, minusArray, M3, sumArray);
    sum(size2/2,sumArray,M6,C22);
    //printf("C Matrix C22: \n");
    //printArray(size2/2,C22);
    end=clock();
    /////////////Recursive Matrix Multiplication//////////////////////////////////////
    reset = 1;
    recur3(size2,arrayS1,arrayS2,arrayS3,reset);
    //printf("Array3\n");
    //printArray(size2,arrayS3);
    
    //Fill each sub matrix
    for(int i =0; i<size; i++){
        for(int j=0;j<size;j++){
            if(i<=size2/2-1 && j<=size2/2-1){
                fprintf(out2, "%d ",C11[i][j]);//print to file
            }
            else if(i>size2/2-1 && j<=size2/2-1){
                fprintf(out2, "%d ",C21[i-size2/2][j]);//print to file

            }
            else if(i<=size2/2-1 && j>size2/2-1){
                fprintf(out2, "%d ",C12[i][j-size2/2]);//print to file

            }
            else if(i>size2/2-1 && j>size2/2-1){
                fprintf(out2, "%d ",C22[i-size2/2][j-size2/2]);//print to file

            }
            else
                printf("Something is wrong!!!");
        }
         if(i<size-1){//golden out doesn't have newline at end of file
           fprintf(out2, "\n");
         }
    }
   int running_time2 = end-start;
   //printf("Time: %d\n",running_time2);
   fprintf(out3, "%d ",running_time2);
   
    
    
   return 0;
}
