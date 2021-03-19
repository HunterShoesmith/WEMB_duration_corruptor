#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <stdio.h>
#include <string.h>

//
#define searchSize 6144

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

  std::ofstream  outFile(argv[2], std::ios::binary);

  outFile << inpFile.rdbuf();
  //copy file to destination with name

  //read in #TODO
  //char mask = 0x01;
  char * searchMe = new char [searchSize];
  inpFile.seekg (0, std::ios::beg);
  inpFile.read(searchMe, searchSize * sizeof(char));

  //find this
  /*
  for (int x=0; x<3;x++){

    char printThis = searchMe[x];

    

    //ust this to get unsigned int from char
    std::cout << "  " << ( printThis & 0xff) ;
    

    
  }
  */

  std::cout << std::endl;

  //need to find 2A D7 B1
  char * findThis1 = new char [3];
  findThis1[0] = 0x2A;
  findThis1[1] = 0xD7;
  findThis1[2] = 0xB1;

  char * findThis2 = new char [2];

  //find 0x4489
  findThis2[0] = 0x44;
  findThis2[1] = 0x89;


  //then from there find next occurence of 100010010001001
  //then move 3 bytes (24) spots down and delete some data
  //std::cout << findBinaryString(searchMe, ) << std::endl;

  int location1 = findBinaryString(searchMe,findThis1,searchSize,3);

  if  (location1== -1){
    std::cout << "location not found, terminating" << std::endl;
  }

  //std::cout << "location of bytes: " << findBinaryString(searchMe,findThis2,searchSize,2) << std::endl; 



  


  //get inp and output stream
}

int findBinaryString(char *inp, char *findMe, int inpSize, int findSize){
  
  //return this if binary string found
  

  //char * currChars = new char [findSize];

  //loops searchSize - inpSize times and returns location found
  for (int currPos=0; currPos < inpSize - findSize ;currPos++){

    //get chars to check
    //strncpy(currChars, inp + currPos ,findSize);

    

    

    bool foundFlag = true;

    for (int x = 0; x < findSize; x++){
      //checking currChars == findMe
      //std::cout << "made it! " << "curr val " << (inp[currPos + x] & 0xff ) << " findVal " << ( findMe[x] & 0xff ) <<  std::endl;

      if ( (inp[currPos + x] & 0xff ) != ( findMe[x] & 0xff ) ){
        foundFlag = false;
        break;
      }

    }

    //std::cout << "flag: " << foundFlag << "  at: " << currPos << std::endl;

    //if found return pos
    if (foundFlag){
      return currPos;
    }
  }


  //no location found, return -1
  return -1;


}
