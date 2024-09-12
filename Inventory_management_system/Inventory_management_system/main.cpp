#include <iostream>         //  input/output stream (standard library)
#include <fstream>          // file stream library for file operation
#include <string>           // string library
#include <sstream>          // string stream library
using namespace std;        // standard namespace


// Defining the product class
class Product{
private:
    string product_num;                // Private variable for product number
protected:
    string category, product_name;     // Protected variables for category and product name
    int quantity;                      // Protected variable for quantity
public:
    void input_product();              // Public function for inputting product information
    void display_product();            // Public function for displaying product information
    void writeRecord();                // Public function for writing product information to a file
    void modifyProduct(string search);    // Public function for editing product information
    virtual void display();            // Virtual function for displaying information of product
};


// inheritance and polymorphism
class Electronics : public Product {               // Electronics class inherited from Product class

    void display(){                               // Override display function
        cout << endl << "Electronics";
    }
};

class Household : public Product {               // Household class inherited from Product class
    void display(){
        cout << endl << "Household";
    }
};

class Furniture : public Product {              // Furniture class inherited from Product class
    void display(){
        cout << endl << "Furniture" << endl;
    }
};


void showCategories(char category) {                            // this function shows available products based on the selected category
    string product_name;
    switch (category) {
        case 'e':
            cout << "-----------------------------------------------------------------"<<endl;
            cout << "Electronics category selected. Available products:" << endl;
            cout << "-----------------------------------------------------------------"<<endl;
            
            break;
            
        case 'h':
            cout << "-----------------------------------------------------------------"<<endl;
            cout << "Household category selected. Available products:" << endl;
            cout << "-----------------------------------------------------------------"<<endl;
            
            break;
            
        case 'f':
            cout << "-----------------------------------------------------------------"<<endl;
            cout << "Furniture category selected. Available products:" << endl;
            cout << "-----------------------------------------------------------------"<<endl;
            
            
            break;
        default:
            cout << "Invalid category" << endl;
            return;
    }
    // Open the file "myfile" and read its contents
    ifstream myfile("product.txt");
    // check if the file is opened
    if (myfile.is_open()) {
        // declare an array to hold contents of each file
        string temp[4];
        // if the end of file is reached, exit the loop
        while (true) {
                    
                    for (int i = 0; i < 4; i++) {
                        myfile >> temp[i];
                    }
                    
                    if(myfile.eof()){
                        break;
                    }
                    
                    if (toupper(temp[2][0]) == toupper(category)) {
                        cout << "- " << temp[0] << endl;
                    }
                }
            
        myfile.close();                                      // close the file
    } else {
        cout << "Unable to open file" << endl;
    }

}
    


void Product::display(){                                      // display a welcome message to the user
    cout << "-----------------------------------------------------------------"<<endl;
    cout << "Welcome to our Product shop. "<<endl;
    
    cout << "-----------------------------------------------------------------"<<endl;
    cout << "These are the available categories: " <<endl;

}


// asking the user to input product information
void Product::input_product(){
    cout << "Product Name: ";
    cin >> product_name;
    
    cout << "Product ID: ";
    cin >> product_num;
    
    cout << "Product Type:";
    cin >> category;
    
    cout << "The number of products: ";
    cin >> quantity;
    
}

// diplaying the product information
void Product::display_product(){
    cout << "-------------------------------------------------------"<<endl;
    cout << "Product Name: " << product_name << endl;
    cout << "Product ID: " << product_num << endl;
    cout << "Product Category: " << category << endl;
    cout << "There are " << quantity << " products left."<< endl << endl;

}

void Product::writeRecord(){                            //  Definition of the writeRecord() function, which writes product information to a file

    ofstream myfile ("product.txt", ios::app);          //  Creating an output file stream object to write data to a file
    
    if(myfile.is_open()){                               //  Checks if the file is successfully opened
        myfile <<product_name << " " << product_num << " " << category << " " << quantity<<endl;
        myfile.close();
        cout << "Successfully imported the data to the product.txt file!"<<endl;          // output success message
        cout << "*******************************************************"<<endl;

    }else {
        cout << "Unable to import file";        // an error message
    }
}

void Product::modifyProduct(string search){
    fstream inFile("product.txt", ios::in | ios::out);
    string myArray[4], testStr, line;                               // Declare variables

    size_t pos;                                                     // size of objects in the memory
    bool control=false;
    // inFile.iss_open();
    if(!inFile){
        cout << "Unable to open the file" << endl;
        exit(1);
    }
    while (inFile.good()) {
        getline(inFile,line);                 // Read a line from the file

        pos=line.find(search);                // Search for the specified text in the line
        

        /*
         returns the position of the first occurance of a substring within a string, or string::npos if the substring is not found
         */
        if(pos!=string::npos){ // maximum value of the size_t type
            control=true;
            cout << "We found the following data!" << endl;
            cout << "=======================================" << endl;
            cout<<   "Data keywords =======>  "      << line << "\n" ;
            
            cout << "=======================================" << endl;
            
            stringstream ss(line);               // Creates a string stream object to read the line
            // that provides a way to read and write strings as if they were input/output streams
            int i=0;
            while(getline(ss, testStr, ' ')){
                myArray[i]=testStr;
                i++;
            }
            
        
            /*
             for(int i=0; i<4; i++){
             cout << endl << myArray[i] << endl;
             }
             */
            char control;                                               // defining character "control" to store user input
            cout << "Enter 1 to modify Product Name" << endl;
            cout << "Enter 2 to modify Product ID" << endl;
            cout << "Enter 3 to modify Product category" << endl;
            cout << "Enter 4 to modify the quantity of products" << endl;
            
            cin >> control;                                     // store the user input in control variable
            switch (control) {                                  // using switch statement to find out which product information to edit
                case '1':
                    cout << "Modify the name to :" << endl;
                    cin >> myArray[0];
                    break;
                case '2':
                    cout << "Modify the ID to :"<< endl;
                    cin >> myArray[1];
                    break;
                case '3':
                    cout << "Modify the category name to : " << endl;
                    cin >> myArray[2];
                    break;
                case '4':
                    cout << "Modify the quantity to : " << endl;
                    cin >> myArray[3];
                    break;
                default:
                    break;
            }
            inFile.close();                                 // close the file

            break;                                          // stop editing products by exiting the loop
        }
    }
    if(control==false){
        cout << "The entered data is not found" << endl;
    }
    
    
    // declaring ifstream,ofstream and string datatypes to store a line of text
    ifstream file;
    ofstream outfile;
    string lineN;
    
    file.open("product.txt");
    outfile.open("newP.txt", ios::app);
    
    
// using while loop to read lines from input file and write to the output file
    while(getline(file, lineN)){
        if((lineN.find(search)==string::npos)){
            outfile << lineN << endl;
        }else{
            outfile << myArray[0] << " " << myArray[1] << " " << myArray[2] << " " << myArray[3] << endl;
        }
    }
    outfile.close();                // closing output file
    file.close();                   //closing input file
    remove("product.txt");          // removing the original product file
    rename("newP.txt", "product.txt");      // renaming the output file "newP.txt" to "product.txt"
}

int main(){
    // defining functions to use later
    void addProduct();
    void displayProduct();
    void modifyProduct();

    // defining variables to use later
    char choice = '\0';
    Product pd, *ppointer;
    Electronics e;
    Household h;
    Furniture f;
    
// showing menu options and asking the user to enter a choice
    
    do{
        cout << endl
        << "Choose 1 to add a new product.\n"
        << "Choose 2 to modify the product info.\n"
        << "Choose 3 to display product details.\n"
        << "Choose 4 to display categories.\n"
        << "Choose 5 to exit this program.\n"
        << "Choose any number and press Return on your keyboard: \n"
        << "=> ";
        cin >> choice;

        
        
        //  call the function that matches the user's choice
        switch (choice) {
            case '1':
                addProduct();
                break;
            case '2':
                modifyProduct();
                break;
            case '3':
                displayProduct();
                break;
            case '4':
                ppointer=&pd;                           // displaying product categories
                ppointer->display();
                ppointer=&e;                            // display electronic category
                ppointer->display();
                ppointer=&h;
                ppointer->display();                    // display household category
                ppointer= &f;
                ppointer->display();                    // display furniture category
                cout << "      "  <<endl;
                    char category;
                cout << "Enter a category letter: "<<endl;                          // telling user to enter category
             cout << "(e for electronics, h for household, f for furniture): ";
                    cin >> category;
                     showCategories(category);
                break;
            case '5':
                cout << endl << "End of the Program" << endl<< endl;
                break;
            default:
                cout << "Not a valid choice.\n" << "Choose again.\n";
                break;
        }
        
    }while(choice != '5');
    return 0;
}



void addProduct(){
    Product pd;
    cout << "Input data(Note: When entering the data, use underscores instead of spaces.)" << endl;
    pd.input_product();
    cout << endl << "Ok. Here is your inputted data" << endl;
    pd.display_product();
    pd.writeRecord();
}

void displayProduct(){
    string data, temp[4];
    ifstream myfile;
    myfile.open("product.txt");
    
    cout << "Displaying all Products data:" << endl << endl;
    
    
    
    
    // Display table header
       cout << setfill('-') << setw(100) << "-" << endl;
       cout << setfill(' ') << setw(25) << left << "| Product Name"
            << setw(25) << left << "| Product ID"
            << setw(25) << left << "| Product Category"
            << setw(25) << left << "| Quantity of Products" << "|" << endl;
       cout << setfill('-') << setw(100) << "-" << endl;


    // read data from the file and display in a table
    while(true){
        for(int i=0; i<4; i++){
            myfile >> temp[i];
        }
            if(myfile.eof()){
                break;
            }

        // Display the product data in a table row
           cout << setfill(' ') << setw(25) << left << "| " + temp[0]
                << setw(25) << left << "| " + temp[1]
                << setw(25) << left << "| " + temp[2]
                << setw (25) << left << "| " + temp[3] << "|" << endl;

           cout << setfill('-') << setw(100) << "-" << endl;
     

        if(myfile.eof()){
            break;
        }
    }
    
    myfile.close();
}

void modifyProduct(){                   // allow users to edit information of the product
    Product pd;                         // to access member functions
    string search;                      // users can search for the data with keywords
    cout << "Enter word to search for: ";
    cin >> search;
    
    pd.modifyProduct(search);               // to edit product information
}
 
