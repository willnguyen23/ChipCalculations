#include <string>
#include <iostream>
using namespace std;

class Chip {
    private:
        char chipType; // Type of the chip (A: Addition, S: Subtraction, etc.)
        string id; // Unique identifier for the chip
        Chip* input1; // Pointer to the first input chip
        Chip* input2; // Pointer to the second input chip (can be NULL)
        Chip* output; // Ptr to the output chip (is NULL for output chips)
        double inputValue; //for the input chip

    public:
        // Constructor
        Chip(char type, const string& id);
        // overloaded assignment operator
        // Asked AI - "How can I copy an object to another object variable in C++?"
        Chip& operator=(const Chip& m) {
            if (this != &m) {
                id = m.id;
                chipType = m.chipType;
            }

            return *this;
        }

        // Method prototypes
        void setInput1(Chip* inputChip); // Sets the first input chip
        void setInput2(Chip* inputChip); // second input chip (can be NULL)
        void setOutput(Chip* outputChip); // Sets the output chip (can be NULL)
        void compute(); // Performs the operation based on the chip type
        void display() const; // Displays the chip's information
        
//example: I6, Output = S600 --- for the input Chip
//example: O50, Input 1 = S600 --- for the output Chip
//example: A100, Input 1 = I1, Input 2 = I2, Output = M300

//****** OTHER METHODS AS NECESSARY ************//
        char getChipType() const; // gets the chip type value of specific chip
        void setChipType(char type); // sets the chip type
        string getId() const; // gets the id value of a specific chip
        void setId(string num); // sets the id number
        double getInputValue() const; // gets the input value of chip
        void setInputValue(double value); // sets the input value of chip
        Chip* getInput1() const; // gets 1st input
        Chip* getInput2() const; // gets 2nd input
        Chip* getOutput() const; // gets output
};

// Constructor that sets the values of chipType and id, also set the input1, input2, and output as null
// so I check whether it is holding something when I am inserting input values into the variables
Chip::Chip(char type, const string& id) {
    chipType = type;
    (*this).id = id;
    inputValue = 0.0;
}

// Setter and getter methods for the Chip method
char Chip:: getChipType() const {
    return chipType;
}
void Chip:: setChipType(char type) {
    chipType = type;
}
string Chip:: getId() const {
    return id;
}
void Chip:: setId(string num) {
    id = num;
}
double Chip::getInputValue() const {
    return inputValue;
}
void Chip:: setInputValue(double value) {
    inputValue = value;
}
//On the input setters, I asked AI - "How to have a pointer variable point to another pointer variable?"
Chip* Chip:: getInput1() const {
    return input1;
}
void Chip:: setInput1(Chip* inputChip) {
    input1 = inputChip;
}
Chip* Chip:: getInput2() const {
    return input2;
}
void Chip:: setInput2(Chip* inputChip) {
    input2 = inputChip;
}
Chip* Chip:: getOutput() const {
    return output;
}
void Chip:: setOutput(Chip* outputChip) {
    output = outputChip;
}

// Calculates the answer for the linked computations
void Chip:: compute() { // recursive algorithm
    double value = 0.0; // a holder for calculated values

// this conditional is ran if the input1 object does not have a value, which is indicated by 0.0
// if it is called, then it will call compute again to the input1 object, so it will compute its inputs
// It will repeat, if it still does not have a value
    if ((*(*this).getInput1()).getInputValue() == 0.0) { 
        (*(*this).getInput1()).compute();
    }
    if ((*this).getChipType() != 'O' && (*this).getChipType() != 'N' && (*(*this).getInput2()).getInputValue() == 0.0) {
        (*(*this).getInput2()).compute();
    }
   
    if ((*this).getChipType() == 'A') {
        value += (*(*this).getInput1()).getInputValue() + (*(*this).getInput2()).getInputValue(); // makes calculation
        (*this).setInputValue(value); // sets the calculation to the input value of current object
    }
    else if ((*this).getChipType() == 'S') {
        value += (*(*this).getInput1()).getInputValue() - (*(*this).getInput2()).getInputValue(); // makes calculation
        (*this).setInputValue(value); // sets the calculation to the input value of current object
    }
    else if ((*this).getChipType() == 'M') {
        value += (*(*this).getInput1()).getInputValue() * (*(*this).getInput2()).getInputValue(); // makes calculation
        (*this).setInputValue(value); // sets the calculation to the input value of current object
    }
    else if ((*this).getChipType() == 'D') {
        value += (*(*this).getInput1()).getInputValue() / (*(*this).getInput2()).getInputValue(); // makes calculation
        (*this).setInputValue(value); // sets the calculation to the input value of current object
    } 
    else if ((*this).getChipType() == 'N') {
        value += (*(*this).getInput1()).getInputValue() * -1.0; // makes calculation
        (*this).setInputValue(value); // sets the calculation to the input value of current object
    }
    else if ((*this).getChipType() == 'O') {
        cout << "Computation Starts" << endl << "The output value from this circuit is " << (*(*this).getInput1()).getInputValue() << endl;
    } 
}

// Displays the links made
void Chip:: display() const {
    if ((*this).getChipType() == 'I') { // If chip type is I, then it just displays output
        cout << (*this).getChipType() << (*this).getId() << ", Output = " << (*(*this).getOutput()).getChipType() << (*(*this).getOutput()).getId() << endl;
    }
    else if ((*this).getChipType() == 'O') { // If chip type is O, then it just displays the only input
        cout << (*this).getChipType() << (*this).getId() << ", Input 1 = " << (*(*this).getInput1()).getChipType() << (*(*this).getInput1()).getId() << endl;
    }
    else if ((*this).getChipType() == 'N') { // If chip type is O, then it just displays the only input
        cout << (*this).getChipType() << (*this).getId() << ", Input 1 = " << (*(*this).getInput1()).getChipType() << (*(*this).getInput1()).getId() << ", Input 2 = None, Output = " << (*(*this).getOutput()).getChipType() << (*(*this).getOutput()).getId() << endl;
    }
    else { // If the computing chips such as 'A','N', 'S', 'M'
        cout << (*this).getChipType() << (*this).getId() << ", Input 1 = " << (*(*this).getInput1()).getChipType() << (*(*this).getInput1()).getId() << ", Input 2 = " << (*(*this).getInput2()).getChipType() << (*(*this).getInput2()).getId() << ", Output = " << (*(*this).getOutput()).getChipType() << (*(*this).getOutput()).getId() << endl;
    }
}

// This function finds the index of where an Id is in the array
int search(Chip** allChips, string id, int size) {
    int index;

    for (int a = 0; a < size; ++a) {
        if (id.substr(1, id.size() - 1) == (*allChips[a]).getId()) {
            index = a;
            break;
        }
    }

    return index;
}

// This function assigns the input values into the elements of the allChips array
void settingA(Chip** allChips, string input1, string input2, int size) {
    int indexOutput = search(allChips, input2, size); // finds index of the output element
    int indexInput1 = search(allChips, input1, size); // finds index of the input element, so that it can be pointed to when it is referred to during computation

    if ((*allChips[indexOutput]).getInput1() == NULL) { // if the input1 value is empty, then assign it to input1
        (*allChips[indexOutput]).setInput1(allChips[indexInput1]); 
        (*allChips[indexInput1]).setOutput(allChips[indexOutput]); // sets the output value in the input's element
    }
    else if ((*allChips[indexOutput]).getInput1() != NULL) { //if it isn't, then it assigns it to input2
        (*allChips[indexOutput]).setInput2(allChips[indexInput1]);
        (*allChips[indexInput1]).setOutput(allChips[indexOutput]); // sets the output value in the input's element
    } 
} 

// This function assigns the values into the input chips into the elements of the allChips array
void settingI(Chip** allChips, string input1, string input2, int size) {
    int index = search(allChips, input1, size); // finds index of input2 which is the chip in its array
    (*allChips[index]).setInputValue(stod(input2)); // puts the double version of input2 with "stod()" into the input value
}

int main () {
    //**** ALL THE VARIABLES YOU NEED FOR THIS MAIN FUNCTION *****//
    int numChips;
    Chip** allChips;
    int numCommands;
    
    string nextChip; //stores the chip as a string, allowing the ability to break it down into its chipType and id
    std::cin >> numChips;

    //create an array Chip objects pointers
    allChips = new Chip*[numChips];  

    //each array location is a pointer to a Chip Object
    for (int i = 0; i < numChips; i++) {
        std::cin >> nextChip; //reads the next chip into the variable nextChip

    //read the chip ID based on the first letter to determine its type
    //create the chip object and initialize it appropriately
    // nextChip[0] - asked AI "In C++, how do I get a specific character from a string?"
    //     This gets the first letter of the chip, which is the type
    // nextChip.substr(1, nextChip.length() - 1) - asked AI "In C++, how can I get a substring of characters from a string?", 1 is starting
    //     This gives the rest of the chip excluding the first letter, which is the chip's ID
    // index of id, nextChip.length() - 1 is the entire string length of the chip minus the first letter
        Chip* chip = new Chip(nextChip[0], nextChip.substr(1, nextChip.length() - 1));

    //store the chip object in the allChips array
        allChips[i] = (chip); // stores the chip into an index of the array
    }

    cin >> numCommands; // reads in the amount of commands that will be done

    char behavior; // stores whether the data need to be linked or assigned
    string chip1; // stores the first chip on the line
    string chip2; // stores the second chip on the line

// I am using this for loop to store the input/output values of each element in the array. 
// The letter will determine the action that will be done.
// I want to make shallow copies of Chip objects, so that variables can point to other Chip objects and get their information.
// This will create a "link" and make calculating and retreiving easier.
    for (int j = 0; j < numCommands; j++) {
    // read from input the links and make the appropriate connections. 
        cin >> behavior; // determines what action is done
        cin >> chip1; // reads in next chip for input1, or what chip to put inputValue to
        cin >> chip2; // reads in next chip for input2/output, 
    // You may need to search the array allChips to find the chip that is referred and connect.
    // Conditionals determines if input storage or calculating is done
        if (behavior == 'A') { // This will store the input1 or input2, and the output
            settingA(allChips, chip1, chip2, numChips); 
        }
        else if (behavior == 'I') { // This will store the inputValue into its respected variable
            settingI(allChips, chip1, chip2, numChips);
        }
        else if (behavior == 'O') { // If the first letter is an O, then execute the compute method on the object referred.
            int index = search(allChips, chip1, numChips);
            (*allChips[index]).compute();
        } 
    }

    //for each component created call the display () method
    std:: cout << "***** Showing the connections that were established" << endl;

    int ind; // holds the index of the O chip
    for (int d = 0; d < numChips; ++d) {
        if ((*allChips[d]).getChipType() == 'O') {
            ind = d; // assigns the index that O chip is in
        }
        else {
            (*allChips[d]).display();
        }
    }

    (*allChips[ind]).display(); // displays the O chip last 

    return 0;
};

/* Debugging Plan (Based off of input1-1.txt)
        The first thing I worked on was the method implementation for the Chip class. Most of it was setting the arguments from parameters into the
    instance varaibles of the class. Afterwards, I worked on the for loop to read in the chips and store it into the array. I wanted to check if it actually
    read and stored the values, so I made a for loop to check. If it prints out the input, then the chip functions were implemented correctly and I properly
    stored and read in the input. The for loop I made was...

        for (int j = 0; j < numChips; ++j) {
            cout << "Type: " << (*allChips[j]).getChipType() << " ID: " << (*allChips[j]).getId() << endl;
        }

    It ended up working as it printed out...

        Type: I ID: 1
        Type: I ID: 2
        Type: I ID: 3
        Type: A ID: 100
        Type: M ID: 200
        Type: O ID: 50
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Additionally, I made a search function that receives an id and gives the index of where that id is. It serves to make the code more readable. I
    tested this by creating a test. 

        int hello = search(allChips, "100", numChips);
        cout << hello << endl;

    By testing with input1-1.txt, we know that the output should be 3. When I implemented it, it printed out 3. Therefore, the search method works.
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        Next, I want to implement a function for the behaviors: "A", and "I" of the commands. I started with the "A" commands. I wanted to check this
    function, so I implemented a for loop. It goes through each element and prints out the input values. If there is something there, then it is correct.
    The code I made was...

        cout << (*allChips[indexOutput]).getInput1() -> getId() << " " << (*allChips[indexOutput]).getInput2() -> getId() << " " << (*allChips[indexOutput]).getOutput() -> getId() << endl;
    
    So every time that the function is called, it will call the test. It should print out the input id of all of the A behaviors. However, it kept saying "zsh:
    segmentation fail." I used AI to learn what that mean, which is that it is trying to get something that is not there. Therefore, I tweawked my setter for my 
    input and outputs. After backtracking, the issue was with the search. Instead of giving an int, it was returning a memory address. I think that the reason was
    because I did not initialize it, but when I assigned it to 0, all it returns is 0. Finally, I noticed that I did not find the substring of id, which led to the 
    conditional never being reached. Now, I have it working. I tested it by...

        cout << index << endl;

    This prints out the index, and all of them were corect. Next, I wanted to test the settingA function, so I tried the first test on this debugging section, and
    it is saying "zsh: segmentation fault" again. To find the issue, I first checked if I was getting the right indices, which I was. Thus, I think it is from
    mistakes in assigning the pointer object into variables. Then, I noticed that maybe it was not printing because there was not an input2 to access. Thus, I
    made a for loop that went outside the second main for loop...

        for (int c = 0; c < numChips; ++c) {
            if ((*allChips[c]).getChipType() != 'I') {
                cout << (*(*allChips[c]).getInput1()).getId() << " " << (*(*allChips[c]).getInput2()).getId() << " " << (*(*allChips[c]).getOutput()).getId() << endl;
            }
        }

    And it works.
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        After, I worked on implementing the settingI function. I wanted to check this by using this for loop...

        for (int f = 0; f < numChips; ++f) {
            if ((*allChips[f]).getChipType() == 'I') {
                cout << (*allChips[f]).getInputValue() << endl;
            }
        }

    And it works. The numbers printed out matches with the numbers in the input text fiel.
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        A way I can check if the input and output variables are right is by implementing the display function. If it matches with the output file, then we did it correctly
    and we can start working computating. I did this by simply using this for loop...

        for (int d = 0; d < numChips; ++d) {
            (*allChips[d]).display();
        }

    It iterates through every element, calling the display function. It works with input file 1 because it matches the output file. However, the other files do not work, so
    I have to change it to make it work. Looking at input2-1.txt, it does not print the chips after M120. It gives zsh: segmentation failed, which means that the compiler is
    trying to access something that it can't. It stops once it tries to show the chip that is a 'N' type. I figured out that it only takes one input, so I made its own conditional
    so that it shows that there is not an input2 or output. In inpu3-1.txt, the O chip was not printed last, so I altered the for loop so that when it goes on the O chip that is in the middle, it stores the index of the variable and skips over it.
    After the for loop is done, it will then print the O chip.
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        The final thing to work on is the compute function. I am going to make it a recursive algorithm that breaks the links down into the first plug-ins, then it puts everything together.
    At first, it would not print as it kept saying "zsh: segmentation fault". I noticed the issue was that I did not mark the getInputValue function as const, therefore when I called it in compute,
    it would not access anything. Next, the issue was that instead of intiially calling the output Chip for compute, it was calling the first element. I figured it out it was from a flaw of the
    search function. There was nothing wrong with the function. I called it wrong. It works with input1-1.txt. However, the other test do not work. This is because when the N chip is read,
    it cannot access a input2 object so it cannot work. When it checks the input2, I added as long as chipType is not 'N' as well.
*/