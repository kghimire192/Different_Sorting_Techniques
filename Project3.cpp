/**
 * @file Project.cpp
 * main program
 * @author Kanchan Ghimire
 * @date Nov 2016
 */

#include "TreeNode.h"
#include "Timer.h"
#include "BinarySearchTree.h"
#include <fstream> // include the file stream library
#include <iostream>

using namespace std;

#define SIZE 1000

//////
//Function Definitions
//////

/**
* Function that prints the contents of the array
* @param strArray the array to print
* @param size : size of the array (filled array)
*
*/
void PrintArray(string strArray[], int size);

/**
* Function that sorts the array in ascending order, using bubble sort
*@param strArray[]  the array to bubble sort
*@param size the size of the array
*/
void BubbleSort(string strArray[], int size);

/**
 * Function that reads the contents of the file
 * @param filename file to read
 * @param myArray[] array to be filled with the data from the file
 * @return int number of words in the file
 */
int ReadFile(string filename, string myArray[]);

/**
 * Function that uses quick sort to sort an array of strings
 * @param myArray array to be sorted
 * @param leftIndx left bound
 * @param rtIndx right bound
 */
void QuickSort(string myArray[], int leftIndx, int rtIndx);

/**
 * Function that finds the average of all sorting techniques
 * @param myTimer myTimer object
 */
void UsingAllSorts(Timer myTimer );

/**
 * Function that sorts the array by first adding nodes in the tree, and then doing inorder traversal
 * @param strArray array to sort
 * @param size size of the filled array
 * @param nextIndx nextIndex to search in the binary tree
 */
void BinaryTreeSort(string strArray[], int size, int nextIndx);


////////Functions///////////////////////

//Print the contents of the array
void PrintArray(string strArray[], int size)
{
    cout << "{";
    for(int i = 0; i < size; i ++)
    {
        if(i < size - 1){
            cout << strArray[i] << ", ";
        }
        else{
            cout << strArray[i];
        }
    }
    cout << "}" << endl;
}//end of PrintArray function

//sorts the array in ascending order using bubble sort
void BubbleSort(string strArray[], int size) {

    int itemsSorted = 0;    //initialize itemSorted
    string temp = "";       //initialize temp
    bool swap = false;      //initialize swap to false
    do {
        swap = false; //begin a pass
        for (int b = size-1, t = size-2; t >= itemsSorted; b--,t--){
            if(strArray[b] < strArray[t]){ //two adjacent elements are not in sorted order
                swap = true;   //there was a change on this pass
                ////swapping/////
                temp = strArray[b];
                strArray[b] = strArray[t];
                strArray[t] = temp;

            }
        }
        itemsSorted++;  //increase pass

    } while(swap == true && itemsSorted != size-1);
} //end of BubbleSort function



//opens and reads file
int ReadFile(string filename, string myArray[]) {

    int count = 0;     //initialize count to 0

    string line = "";   //initialize line to empty string
    ifstream inFile;  // create an instance of an input file stream

    int i = 0;   //initialize i to 0

// open the file that is named filename (a string)
    inFile.open(filename);
// read every line of the file, one at a time, into the variable line (a string)
    if (inFile.is_open())
    {  // file opened successfully
        while (getline(inFile, line))
        {  // process this line in some way, maybe by printing it
            count++;
            if(line[line.length()-1] == '\r'){
                string myLine = line.substr(0,line.length()-1);
                myArray[i]=myLine;
            }
            else{
                myArray[i] = line;
            }
            i++;
        }
        // close the file
        inFile.close();
    }
    else
    {  // error opening file
        cout << "Unable to open file" << endl;
    }
    return count;
} //end of ReadFile function


//sorts using quick sort
void QuickSort(string myArray[], int leftIndx, int rtIndx){

    int partitionSize = rtIndx - leftIndx + 1;
    if(partitionSize <= 1) { // base case, one item to be sorted
        return;
    }
    string pivotValue = myArray[(leftIndx + rtIndx) / 2];
    int i = leftIndx; // initialize the two partition indices
    int j = rtIndx;
    do // general solution.  First generate rate the two partitions
    {
        while (myArray[i] < pivotValue) // left partition item is in correct part.
         {
             i++;
         }
        while (myArray[j] > pivotValue) // right partition item is in correct part.
            {
                j--;
            }
        if (i <= j) // pointers have not crossed, switch items in wrong partition
            {  string temp = myArray[i];
               myArray[i] = myArray[j];
               myArray[j]= temp;
               i++;
               j--;
            }
    } while (i <= j); // the pointers have not crossed
    QuickSort(myArray, leftIndx, j); //reduced problems: sort left partition
    QuickSort(myArray, i, rtIndx); // sort right partition

}//end of QuickSort function

//function that uses binary tree sort to sort the array
void BinaryTreeSort(string strArray[], int size, int nextIndx){
    BinarySearchTree myTree;

    ////////insert nodes//////////
    for(int k = 0; k < size; k++){
        myTree.insertNode(strArray[k]);
    }

    myTree.inorderTraversal(strArray, nextIndx);    //do inorder traversal and sort the array
}//end of BinaryTreeSort function


//function that uses binary sort, binary sort and quick sort multiple times to find the average time taken to sort
void UsingAllSorts(Timer myTimer, string myArray[] ){

    int timeTaken = 0;   //initialize timeTaken to 0
    int avgTime = 0;     //initialize avgTime to 0
    int filledArrSize = 0;   //initialize filledArrSize to 0

    string avgTimeTakenArr[6] ={};    //array to store average times

   // string myArray[SIZE] = {};
    string arrFilenames[6] = {"fivewords.txt","tenwords.txt","twentywords.txt","fiftywords.txt","hundredwords.txt",
                          "fourhundredwords.txt"};

///////////Bubble sort's average time////////////////////////////

    for(int i = 0; i < 6; i++){
        timeTaken = 0;
        int j = 0;
        while(j < 10){
            filledArrSize = ReadFile(arrFilenames[i], myArray);    //read file
            myTimer.startTimer();                                  //start timer
            BubbleSort(myArray, filledArrSize-1);                  //call bubble sort function
            myTimer.stopTimer();                                   //stop timer
            timeTaken += myTimer.elapsedTime();                    //report time needed to do the sorting
            j++;
        }
        avgTime = timeTaken/10;                                   //find the average of sorting a file 10 times
        avgTimeTakenArr[i] = to_string(avgTime);                  //add to the array of average time taken to sort each file
    }
    cout << "average time for bubble sort: ";
    PrintArray(avgTimeTakenArr, 6);   //call PrintArray function to print the average times

/////////////////Quick sort's average time////////////////////////////////////////////////////
    for(int i = 0; i < 6; i++){
        timeTaken = 0;
        int j = 0;
        while(j < 10){
            filledArrSize = ReadFile(arrFilenames[i], myArray);
            myTimer.startTimer();
            QuickSort(myArray, 0,filledArrSize);
            myTimer.stopTimer();
            timeTaken += myTimer.elapsedTime();
            j++;
        }
        avgTime = timeTaken/10;
        avgTimeTakenArr[i] = to_string(avgTime);
    }
    cout << "average time for quick sort: ";
    PrintArray(avgTimeTakenArr, 6);   //call PrintArray function to print the average times


////////////////Binary Tree Sort's average time/////////////////////////////////////////////
    int nextIndx = 0;
    for(int i = 0; i < 6; i++){

        timeTaken = 0;
        int j = 0;
        while(j < 10){
            filledArrSize = ReadFile(arrFilenames[i], myArray);

            myTimer.startTimer();
            BinaryTreeSort(myArray,filledArrSize,nextIndx);
            myTimer.stopTimer();

            timeTaken += myTimer.elapsedTime();
            j++;
        }
        avgTime = timeTaken/10;
        avgTimeTakenArr[i] = to_string(avgTime);
    }
    cout << "average time for binary tree sort: ";
    PrintArray(avgTimeTakenArr, 6);   //call PrintArray function to print the average times

    cout << endl;
}//end of usingAllSorts function



//main function
int main(){

    Timer myTimer;   //instantiate a timer object
    double timeTaken = 0.0;     //initialize timeTaken variable to store the time taken for sorting

    string myArray[SIZE] = {};

    cout << "Hello Users! Please enter the filename to sort  " << endl;
    string userInput ="";
    getline(cin, userInput);

    int filledArrSize = ReadFile(userInput, myArray);   //read the file
    ///////////Bubble sort/////////////////////////
    cout << "Before sorting: ";
    PrintArray(myArray, filledArrSize);
    cout << "Bubble Sorting now ........ " << endl;

    myTimer.startTimer();
    BubbleSort(myArray, filledArrSize);   //call bubble sort method to sort
    myTimer.stopTimer();           //stop the timer
    timeTaken = myTimer.elapsedTime();    //time taken to sort

    cout << "After sorting: ";
    PrintArray(myArray, filledArrSize);   //print array after sorting
    cout << "time taken for bubble sort is: " << timeTaken << " ms" << endl;


    ReadFile(userInput, myArray); //reading file again so that the array is not already sorted by bubblesort from above
    /////////////Binary Search Tree Sort//////////////////////
    //BinarySearchTree mytree;        // an instance of the binary search tree

    int nextIndx = 0;

    cout << "Binary tree sort"<<endl;
    cout << "Before sorting: ";
    PrintArray(myArray, filledArrSize);  //print array before sorting
    cout << "Binary Search Tree sorting now.............." << endl;

    myTimer.startTimer();  //start the timer
    BinaryTreeSort(myArray,filledArrSize,nextIndx);
    myTimer.stopTimer(); //stop the timer
    timeTaken = myTimer.elapsedTime();

    cout << "After sorting: ";
    PrintArray(myArray, filledArrSize);   //calling printArray function to print the array after sorting
    cout << "time taken to sort through binary search tree is: " << timeTaken << " ms" <<endl;


    ReadFile(userInput, myArray); //reading file again so that the array is not already sorted by binary search tree from above
    ////////////////Quick Sort//////////////////////
    cout << "Before sorting: ";
    PrintArray(myArray, filledArrSize);  //calling the function to print array
    cout << "Quick Sorting now ........." << endl;
    myTimer.startTimer();               //start timer
    QuickSort(myArray,0,filledArrSize-1);   //calling quicksort function
    myTimer.stopTimer();                //stop timer
    timeTaken = myTimer.elapsedTime();  //time taken
    cout << "After sorting: ";
    PrintArray(myArray, filledArrSize);   //calling the function to print array
    cout << "time taken to sort using quick sort is: " << timeTaken << " ms" << endl;

    ////////////Using all sorts to find the average time/////////////////////
    UsingAllSorts(myTimer,myArray);    //call UsingAllSorts function

    return 0;
}//end of main function