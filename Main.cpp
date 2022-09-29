#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
//preprocessor (basically all the libraries that my compiler will use)
using namespace std; // so i dont have to write std::cout each time lmao 
int maximum {}; //could maybe find a better place to put it but idc 

int randomgenerator(){
    int randomnumber {};
    
    randomnumber = rand()% maximum +1; //random number between 1 and maximum 
     
    return randomnumber; 
}

void readingtxtfile(){
    string line; //actually std::string ! 
    string usernumber;
    char useranswer; //maybe could use std::string here too to let the usertype wtv they want 
    ifstream readmaxfile("number_setup.txt"); //ifstream = input file 
    if (readmaxfile.is_open()){
        cout << "current maximum number is : ";
        while (getline(readmaxfile,line)){
            cout << line;
        };
        cout << endl;
        cout << "do you want to change it ? (y/n)";
        readmaxfile.close(); 
        cin >> useranswer; 
        while (true){
            if (useranswer == 'y' || useranswer == 'Y')
            {
                readmaxfile.close(); //pretty sure there is a better way to write and read files than closing and opening shit ever 2 lines. 
                ofstream writemaxfile;
                writemaxfile.open("number_setup.txt", ofstream::trunc); //ofstream::trunc means truncate (erasing previous txt file)
                cout << "choose your maximum number !" << endl;
                cin >> usernumber;
                writemaxfile << usernumber; 
                writemaxfile.close(); 
                break;
            }
            else if (useranswer == 'n' || useranswer == 'N'){
                break;
            }
            else  {
                cout << "do you want to change it ? (y/n)";
                cin >> useranswer;
            }
        }
        ifstream readmaxfile("number_setup.txt");
        while (getline(readmaxfile,line)){
            maximum = stoi(line); 
        }
        readmaxfile.close(); 
        
    }
    else {
        cout << "number_setup.txt is not available" << endl;
        cout << "creating new file" << endl; 
        ofstream writemaxfile;
        writemaxfile.open("number_setup.txt");
        cout << "please write maximum number" << endl; 
        cout << "note that this number can't be a negative number nor be higher than 2147483647" << endl; 
        cin >> usernumber; 
        writemaxfile << usernumber; 
        writemaxfile.close();

        ifstream readmaxfile("number_setup.txt");
        while(getline(readmaxfile,line)){
            maximum= stoi(line);
        }
        readmaxfile.close();

    }
}

void savingtxtfile(int numbertosave){
    ofstream writesavetxt;
    writesavetxt.open("save.txt", ofstream::app); //ofstream::app = append 

    //after this point lot of bullshit that i dont understand about struct tm * and asctime  
    time_t rawtime;
    struct tm * timeinfo; //pretty sure that's a pointer
    time (&rawtime); //address of rawtime
    timeinfo = localtime(&rawtime);
    writesavetxt << asctime(timeinfo) << " - " << numbertosave << endl; //from the compiler error i got, there is a const hidden somewhere...
    writesavetxt.close(); 
}

int main(){
    char useranswer;

    cout << "random number generator" << endl;
    cout << endl; 
    cout << "this program will generate textfiles, to avoid bugs, it should be put in a separate folder." << endl; 
    cout << "number_setup.txt is used to save the last maximum number you used, you can update it manually or follow the instructions" << endl; 
    cout << "save.txt is a save file used to find numbers generated and their time of birth." << endl; 
    cout << "you should always answer with one character to (y/n) questions" << endl; 
    cout << "start ? (y/n)"; 
    cin >> useranswer; 
    while (true){ //feels too convolutaed 
        if (useranswer == 'y' || useranswer == 'Y'){
            break;
        }
        else if (useranswer =='n' || useranswer == 'N'){
            exit(0); 
        }
        else {
            cout << "start ? (y/n)"; 
            cin >> useranswer; 
        }
    } 

    readingtxtfile(); 
    
    rng:
    {
        srand(time(NULL));
        int randomnumber = randomgenerator();
        cout << "your number is : " << randomnumber << endl; 
        savingtxtfile(randomnumber); 
    }
    cout << endl;
    ending :{
        cout << "want a new random number ? (y/n)"; 
        cin >> useranswer; 
        while (true){ //feels too convoluted
            if (useranswer == 'y' || useranswer == 'Y'){
                break;
            }
            else if (useranswer =='n' || useranswer == 'N'){
                cout << "want to quit ? (y/n)"; 
                cin >> useranswer;
                while (true){
                    if (useranswer == 'y' || useranswer == 'Y'){
                        exit(0); //used to safely exit the program (the value inside resemble the return 0 in int main())
                    }
                    else if (useranswer =='n' || useranswer == 'N'){
                        break;
                    }
                    else {
                    cout << "want to quit ? (y/n)";
                    cin >> useranswer; 
                    }
            }
            goto ending; 
            }
            else {
                cout << "want a new random number ? (y/n)"; 
                cin >> useranswer; 
            }
            
        }
    }
    
    goto rng; 
    
    // refreshmax -> goto  
     

}

