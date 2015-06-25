#include <vector>
#include <iostream>
using namespace std;

class c1 {

    int _i;
    int _j;
    int _k;

    public :
    c1( int i ){ 
        _i = i;
    } 

    friend ostream &operator<< (ostream& os, const c1& temp )
    {
      std::cout << temp._i;
      return os;
    }

};



int test_vec (int argc , char *argv[])
{
  std::vector<int> temp;

  for ( int i = 0 ; i < 4 ; i ++)
  {
    temp.push_back(i);
  }

  for ( unsigned int i = 0 ; i < temp.size() ; i ++)
  {
    std::cout << temp[i];
  }

  std::vector<c1> temp_c1;

  for ( int i = 0 ; i < 4 ; i ++)
  {
    temp_c1.push_back(c1(i));
  }

  for ( unsigned int i = 0 ; i < temp_c1.size() ; i ++)
  {
    std::cout << temp_c1[i];
  }

  std::vector<c1*> temp_c2;

  for ( int i = 0 ; i < 4 ; i ++)
  {
    temp_c2.push_back(new c1(i));
  }

  for ( unsigned int i = 0 ; i < temp_c2.size() ; i ++)
  {
    std::cout << *temp_c2[i];
  }

  for ( unsigned int i = 0 ; i < temp_c2.size() ; i ++)
  {
    delete temp_c2[i];
  }
}


void create_excep ( void ) {
    throw "error";
}


void test_excep(void) {

    try {
        create_excep();
    }

    catch (...){
        std::cout << "test_excep: caugth the exception" << std::endl;
        throw "error";
    } 
}

/*
 * The below must be added with a dynamic allocated
 * member which is another class with complete copy operator 
 * and assingment operator 
 */

class c1 {
    int ar ;
    public:
    c1(){
        ar =0;
    }

    c1( c1 & other ) {
        ar = other.ar
    }

    c1 & operator= ( c1 & other ) {

        ar = other.ar;
        return *this;
    }

}

class class_test {
    int attr[10];
   c1 *lc1;

    public:
    class_test(){
        for (auto i : attr)
            attr[i] = i;
    }

    class_test ( class_test & other ){
        for (auto i:attr) {
        attr[i] = other.attr[i];
        }
    }

    class_test & operator= ( class_test & other ){
        for (auto i:attr) {
        attr[i] = other.attr[i];
        }
        return *this;
    }

};

int main (int argc , char *argv[]){

    try {
        test_excep();
    }

    catch (...){
        std::cout << "caugth the exception " << std::endl;
    }
}


