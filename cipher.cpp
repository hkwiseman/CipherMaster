#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include<bitset>

using namespace std;

string caesarShift(string message, int shift);
void textToBinary(string message);

int main ()
{
   int menuControl = -1, menuOptions = 0, shiftVal;
   char fileControl = 'y', contProg;
   string message, newMessage;
   ofstream outfile;

   // Looping until user is finished encoding
   // or decoding messages
   while(menuControl == -1)
   {
      // Displaying menu
      cout << endl << endl;
      cout << "Cipher Menu" << endl;
      cout << "-----------" << endl;
      cout << "1) Encode " << endl;
      cout << "2) Decode " << endl;
      cout << "Enter the number corresponding to the option";
      cout << " you want: " << endl;
      cin >> menuControl;

      // Checking value for encode or decode menu
      if (menuControl == 1)
      {
         // Displaying encoding menu and accepting input
         cout << endl;
         cout << "Encoding Menu" << endl;
         cout << "-------------" << endl;
         cout << "1) Caesar Shift" << endl;
         cout << "2) Text to Binary" << endl;
         cout << "Enter number: " << endl;
         cin >> menuOptions;

         // File control
         cout << "Would you like to save your encoded";
         cout << " message to a file? (y/n)" << endl;
         cin >> fileControl;
         cin.ignore();

         // Opens output file to write to if input is 'y'
         if (fileControl == 'y')
         {
            string filename;
            cout << endl << "Enter the filename you want your";
            cout << " message saved to: " << endl;
            getline(cin, filename);
            outfile.open(filename);
         }

         cout << endl << "Enter your message: " << endl;
         getline(cin, message);

         switch (menuOptions)
         {  case 1:
            {
               // Taking plaintext input and encoding it using caesarShift
               // with user defined shift value
               cout << endl << "Enter shift value: " << endl;
               cin >> shiftVal;

               newMessage = caesarShift(message, shiftVal);

               // Outputting to terminal if fileControl is no
               if (fileControl == 'n')
               {
                  cout << endl << "Message: " << endl;
                  cout << newMessage << endl << endl;
               }
               // Writing to file specified by user
               else
               {
                  cout << endl << "Your message has been saved";
                  cout << " in the file." << endl;
                  outfile << newMessage;
                  outfile.close();
               }
               break;
            }
            case 2:
            {
               // Calling function to output binary conversion
               // to terminal window
               textToBinary(message);
               break;
            }
         }
      }

      else if (menuControl == 2)
      {
         // Displaying decoding menu and taking input
         cout << endl;
         cout << "Decoding Menu" << endl;
         cout << "-------------" << endl;
         cout << "1) Caesar Shift (Key Known)" << endl;
         cout << "2) Caesar Shift (Brute Force)" << endl;
         cout << "3) Binary to Text" << endl;
         cout << "Enter number: " << endl;
         cin >> menuOptions;

         // File control
         cout << "Would you like to save your decoded";
         cout << " message to a file? (y/n)" << endl;
         cin >> fileControl;
         cin.ignore();

         if (fileControl == 'y')
         {
            string filename;
            cout << endl << "Enter the filename you want the";
            cout << " message saved to: " << endl;
            getline(cin, filename);
            outfile.open(filename);
         }

         switch(menuOptions)
         {
            case 1:
            {
               // Takes encoded input and passes it to caesarShift function
               // with negative shift value to reverse original encoding
               cout << endl << "Enter the message: " << endl;
               getline(cin, message);
               cout << endl << "Enter the original shift value: " << endl;
               cin >> shiftVal;
               shiftVal = 26 - shiftVal;

               newMessage = caesarShift(message, shiftVal);

               // Outputs decoded message to terminal if fileControl is no
               if (fileControl == 'n')
               {
                  cout << endl << "Message: " << endl;
                  cout << newMessage << endl << endl;
               }
               else
               {
                  cout << endl << "Your message has been saved";
                  cout << " in the file." << endl;
                  outfile << newMessage;
                  outfile.close();
               }
               break;
            }
            case 2:
            {
               // Takes encoded input and brute forces shift
               cout <<"Enter the message: " << endl;
               getline(cin, message);

               for (int i = 1; i < 26; i++)
               {
                  newMessage = caesarShift(message, i);
                  if (fileControl != 'y')
                  {
                     cout << "Message with shift " << i << ":";
                     cout << newMessage << endl;
                  }
                  else
                  {
                     outfile << "Message with shift " << i << ":";
                     outfile << newMessage << endl;
                  }
               }
               cout << "The data has been saved to the file." << endl;
               break;
            }
         }
      }
      cout << endl << endl;
      cout << "Would you like to encode or decode another message? (y/n)" << endl;
      cin >> contProg;

      // Allows user to restart program from menu easily
      if (contProg == 'y')
      {
         cout << endl << endl << endl << endl;
         cout << endl << endl;
         menuControl = -1;
      }
   }
   return 0;

}


// Inputs: Message to encode or decode and value to shift by
// Output: The encoded or decoded message
string caesarShift(string shiftMessage, int shift)
{
   int i = 0;

   while (i < shiftMessage.size())
   {
      // Checking for upper case characters using ASCII values
      if(shiftMessage[i] > 65 && shiftMessage[i] < 91)
      {
         shiftMessage[i] += shift;
         // If value goes past 'Z' then rolls back to 'A'
         if(shiftMessage[i] > 90)
            shiftMessage[i] = 'A' + (shiftMessage[i] % 91);
      }

      // Checking for lower case characters
      else if(shiftMessage[i] > 96 && shiftMessage[i] < (123 - shift))
         shiftMessage[i] = shiftMessage[i] + shift;

      // If value goes past 'z' then rolls back to 'a'
      // and adds shift
      else if(shiftMessage[i] > (122 - shift))
      {
         int dif = 123 - shiftMessage[i];
         shiftMessage[i] = 'a' - dif + shift;
      }
      // Loop control
      i++;
   }
   return shiftMessage;
}

void textToBinary(string message)
{
   cout << endl << "Your encoded message: ";
   cout << endl;

   for (int i = 1; i <= message.size(); i++)
   {
      cout << bitset<8>(message[i-1]) << " ";
      
      // Breaking up lines for every 5 bytes
      if (i % 5 == 0)
         cout << endl;
   }
}
