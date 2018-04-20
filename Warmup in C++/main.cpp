#include <iostream>

//proto thing (I can't remember what this is called)
void testFucntion();

int main()
{
    //Did some research on why some people dont use namesace std because it could be bad practice if C++ was ever to update and have other cout fucntions

    int userNumber =0;
    std::cout << "Enter a number and I will square it" << std::endl;
    std::cin>>userNumber;
    userNumber*= userNumber;
    std::cout<<"The answer is "<<userNumber<<std::endl;


    //String are just char arrays and C uses a library to deal with the manipulation of strings and chars
    char name[10];
    name[0] = 'K';
    name[1] = 'i';
    name[2] = 'o';
    name[3] = 'n';
    name[4] = '\0';
    //even thought there are 10 allocated 'blocks' in memory the name only prints to the null character

    testFucntion();

    std::cout<<name<<std::endl;


    //relearned that a need to have user input to make sure teh console window in code blocks dosen't show up for an instant
    std::cin.ignore();
    return 0;
}

void testFucntion()
{
    std::cout<<"This came from a function!"<<std::endl;
}
