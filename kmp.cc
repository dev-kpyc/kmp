/*
      KMP Pattern matching algorithm
*/

#include <iostream>
#include <fstream>
using namespace std;

void computeFailureArray(int* F, string P) {
   F[0] = 0;
   int i = 1;
   int j = 0;
   int m = P.length();
   
   while (i < m) {
      if (P[i] == P[j]) {
         F[i] = j + 1;
         i++;
         j++;
      } else if (j > 0) {
         j = F[j-1];
      } else {
         F[i] = 0;
         i++;
      }
   }
}

int main(int argc, char* argv[]) {

   if (argc != 3) { 
      cerr << "Invalid arguments" << endl;
      cerr << "Usage ./kmp pattern file" << endl;
      return 3;
   }
   string P = argv[1];
   int m = P.length();
   
   ifstream fin;
   fin.open(argv[2]);
   
   if (!fin.is_open()) {
      cerr << "Unable to open file " << argv[2] << endl;
      cerr << "Exiting" << endl;
   }

   int* F = new int[m];
   computeFailureArray(F, P);

   int j = 0;
   
   int line_num = 0;
   streampos line_pos = 0;
   
   char c = fin.get();
   
   while (fin.good()) {     
      if (c == '\n') { 
         line_pos = fin.tellg();
         line_num ++;
      }
      if (c == P[j]) {
         if (j == m - 1) {
            char buf[256];
            fin.seekg(line_pos);
            fin.getline(buf,256);
            cout << line_num << ": " << buf << endl;
            delete F;
            return 0;           
         } else {
            c = fin.get();
            j++;
         }
      } else {
         if (j > 0) {
            j = F[j-1];
         } else {
            c = fin.get();
         }
      }
   }
   delete F;
   return 1;
}
