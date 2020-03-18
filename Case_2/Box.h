#include <iostream>

class Box {
    private:
        int myInt;
        char myChar;
    public:
        ~Box() {}

        Box(int myInt = 0, char myChar = 0) {
            this->myInt = myInt;
            this->myChar = myChar;
        }

        int getInt() {
            return myInt;
        }
        
        void setInt(int myInt) {
            this->myInt = myInt;
        } 
        
        char getChar() {
            return myChar;
        }
        
        void setChar(char myChar) {
            this->myChar = myChar;
        } 

        void show() {
            std::cout << "<" << myInt << " / " << myChar << ">" << std::endl; 
        }
};



