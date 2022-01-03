#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------

    if ( s.length() == 1 ){
      return true;            
    
    }else if ( s.length() == 2 ){
      if ( s.at(0) == s.at(1) ){
          return true;
      }else{
          return false;
      }
    }else{
      if (s.at(s.length()-1) != s.at(0)) return false;
              s = s.erase(s.length()-1);
              s.erase(0,1);
              if (!palindrome_recursive(s)) return false;
          }
          return true;

}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
