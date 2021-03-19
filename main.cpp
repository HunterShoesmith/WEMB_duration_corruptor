#include <iostream>
#include <sys/stat.h>
#include <fstream>



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

  


  //get inp and output stream


}