#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <stdio.h>
#include <string.h>

//this is overkill by around 2 times to be safe.
#define searchSize 768

int findBinaryString(char *inp,char *findMe, int inpSize, int findSize);

int main(int argc, char* argv[]) {

  //checking args
  if (argc <= 2){
    std::cout << "please enter a file inp and out in format ./main inp out" << std::endl;
    return -1;
  }else{
    std::cout << "input file path is: " << argv[1] << " output is: " << argv[2] << std::endl;
  }


  std::ifstream  inpFile(argv[1], std::ios::binary);
  std::ifstream  inpFile2(argv[1], std::ios::binary);
  std::ofstream  outFile(argv[2], std::ios::binary);

  //get size of file
  inpFile.seekg (0,inpFile.end);
  long int size = inpFile.tellg();
  inpFile.seekg (0);

  //allocate memory to hold video
  char* buffer = new char[size];

  //read input
  inpFile.read (buffer,size);

  //allocate and fill space to hold begining of file to search
  char * searchMe = new char [searchSize];
  inpFile2.read(searchMe, searchSize * sizeof(char));


  //need to find 0x 2A D7 B1
  char * findThis1 = new char [3];
  findThis1[0] = 0x2A;
  findThis1[1] = 0xD7;
  findThis1[2] = 0xB1;


  //find location of 0x 2A D7 B1
  int location1 = findBinaryString(searchMe,findThis1,searchSize,3);

  if  (location1== -1){
    std::cout << "location 1 not found, terminating" << std::endl;
    return -1;
  }
  //then move 10 bytes down and delete some data
  location1 = location1 + 10;

  //delete some data where time is located
  buffer[location1] = 0x00;
  buffer[location1 + 1] = 0x00;

  //save file then delete data
  outFile.write (buffer,size);
  delete[] buffer;

  outFile.close();
  inpFile.close();


}

int findBinaryString(char *inp, char *findMe, int inpSize, int findSize){
  
  //return this if binary string found

  //loops searchSize - inpSize times and returns location found
  for (int currPos=0; currPos < inpSize - findSize ;currPos++){

    bool foundFlag = true;

    for (int x = 0; x < findSize; x++){
      //check if currPos is start of binary string needed
      if ( (inp[currPos + x] & 0xff ) != ( findMe[x] & 0xff ) ){
        foundFlag = false;
        break;
      }

    }
    //if found return pos
    if (foundFlag){
      return currPos;
    }
  }


  //no location found, return -1
  return -1;
}
 