//-------|---------|---------|---------|---------|---------|---------|---------|
//
// UW CSS 537 - Assignment 1 - eWallet
// eWallet.h
//
//-------|---------|---------|---------|---------|---------|---------|---------|

//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// c. University of Washington Bothell, 2018
//
// Student code portions by:
// Samantha Smith + Tim Lum
// twhlum@gmail.com
// Created:  2018.10.11
// Modified: 2018.--.--
// For the University of Washington Bothell, CSS 537
// Fall 2018, Masters in CyberSecurity Engineering (MCSE) program
//

//-----------------------------------------------------------------------------|
// File Description
//-----------------------------------------------------------------------------|
//
// This is the declaration file for the eWallet class.
//
// For program behavior, see README.txt
//

//-----------------------------------------------------------------------------|
// Package Files
//-----------------------------------------------------------------------------|
//
// See README.txt
//

//-----------------------------------------------------------------------------|
// Useage
//-----------------------------------------------------------------------------|
//
// Compile with:
// Not necessary - run.sh includes instructions to compile
//
// To run:
// $ chmod u+x run.sh
// $ ./run.sh
//



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       INCLUDE STATEMENTS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// For input/output operations
#include <iostream>

// For width-formatted outputs
#include <iomanip>

// For stringstream operations
#include <sstream>

// For string operations
#include <string>

// For holding IP data operations
#include <vector>

class ipRange {

public:
//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PUBLIC FIELDS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// None for this class



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       CONSTRUCTORS / DESTRUCTOR
//
//-------|---------|---------|---------|---------|---------|---------|---------|
   
// (+) --------------------------------|
// #ipRange( )
// ------------------------------------|
// Desc: Generates an empty eWallet object
   ipRange( );

// (+) --------------------------------|
// #eWallet( int )
// ------------------------------------|
// Desc: Generates an empty eWallet object using a provided ID
   eWallet( int ID );

// (+) --------------------------------|
// #eWallet( int, float )
// ------------------------------------|
// Desc: Generates an eWallet object using a provided ID and the provided amount
   eWallet( int ID, float amt );

// (+) --------------------------------|
// #eWallet( string )
// ------------------------------------|
// Desc: Generates an eWallet object using a provided filename
   eWallet( std::string filename );

// (+) --------------------------------|
// #~eWallet( )
// ------------------------------------|
// Desc: eWallet destructor
   ~eWallet( );



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PUBLIC METHODS (interface)
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// (+) --------------------------------|
// #debug( )
// ------------------------------------|
// Desc: Pushes the internal state of the wallet to std::cout
   void debug( );

// (+) --------------------------------|
// #deposit( string )
// ------------------------------------|
// Desc: Decrypts and deposits an AES (wallet) transaction into the wallet
// Note: Must resolve to a positive value
   void deposit( std::string cipher );

// (+) --------------------------------/
// #pay( int, int )
// ------------------------------------|
// Desc: Generates a transaction code and deducts the withdraw amount from the wallet
// Note: Must be a positive value and less than or equal to the wallet balance
   std::string pay( int amt, int tgtID );

// (+) --------------------------------|
// #sync( )
// ------------------------------------|
// Desc: Generates a synchronization AES encrypted string
   std::string sync( int tgtID );

// (+) --------------------------------|
// #toString( )
// ------------------------------------|
// Desc: Generates a string representation of the wallet's contents
   std::string toString( );

// (+) --------------------------------/
// #withdraw( string )
// ------------------------------------|
// Desc: Converts a bank RSA money order to an in-wallet amount
   void withdraw( std::string );



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       GETTERS / SETTERS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// (+) --------------------------------|
// #getBalance( )
// ------------------------------------|
// Desc: Returns the balance contained in this wallet
   int getBalance( );

// (+) --------------------------------|
// #getID( )
// ------------------------------------|
// Desc: Returns the ID number of this wallet
   int getID( );

// (+) --------------------------------|
// #getAESKey( )
// ------------------------------------|
// Desc: Returns the Key of this wallet
   int* getAESKey( );

// (+) --------------------------------|
// #getRSAKey( )
// ------------------------------------|
// Desc: Returns the Key of this wallet
   int* getRSAKey( );

// (+) --------------------------------|
// #getName( )
// ------------------------------------|
// Desc: Returns the Name of this wallet
   std::string getName( );

// (+) --------------------------------|
// #setBalance( )
// ------------------------------------|
// Desc: Sets the wallet balance
   void setBalance( int amt );

// (+) --------------------------------|
// #setID( )
// ------------------------------------|
// Desc: Sets the wallet ID
   void setID( int ID );

// (+) --------------------------------|
// #setAESKey( )
// ------------------------------------|
// Desc: Sets the key of this wallet
   void setAESKey( std::string key );

// (+) --------------------------------|
// #setKey( )
// ------------------------------------|
// Desc: Sets the key of this wallet
   void setRSAKey( std::string key );

// (+) --------------------------------|
// #setName( )
// ------------------------------------|
// Desc: Sets the name of this wallet
   void setName( std::string name );



private:
//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PRIVATE FIELDS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// (-) --------------------------------|
// #balance
// ------------------------------------|
// Desc: The amount of money in this wallet -in cents-
   int balance;

// (-) --------------------------------|
// #ID
// ------------------------------------|
// Desc: The identity of the wallet (valid range from 0 to 999)
   int ID;

// (-) --------------------------------|
// #RSAkey
// ------------------------------------|
// Desc: This wallet's private RSA encryption key
   int RSAkey[8]; // TODO - Change to int[8]

// (-) --------------------------------|
// #AESkey
// ------------------------------------|
// Desc: This wallet's private AES encryption key
   int AESkey[8]; // TODO - Change to int[8]

// (-) --------------------------------|
// #ledger
// ------------------------------------|
// Desc: The 999 possible parties to transact with and their transaction number
// Note: Making simultaneous payments may cause synchronizations to go out of sync
   int ledger[1000];

// (-) --------------------------------|
// #name
// ------------------------------------|
// Desc: The account name of the wallet holder
   std::string name;



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PRIVATE METHODS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// (-) --------------------------------|
// #AESEncrypt( vector<char>, string )
// ------------------------------------|
// Desc: AES encrypts a vector<char>
   std::vector<char> AESEncrypt( std::vector<char> plaintext, int* key);

// (-) --------------------------------|
// #decryptOrder( string, )
// ------------------------------------|
// Desc: Decrypts a 32-character encrypted transfer order
   std::string decryptOrder( std::string cipher );

// (-) --------------------------------|
// #encryptOrder( string, string, int )
// ------------------------------------|
// Desc: Encrypts a properly formatted transfer to a 32-char ciphertext
   std::string encryptOrder( int myID, int tgtID, int amt );

// (-) --------------------------------|
// #load( string )
// ------------------------------------|
// Desc: Loads a wallet from a state file
   void load( std::string filename );

// (-) --------------------------------|
// #parseAmt( string )
// ------------------------------------|
// Desc: NULL
   int parseAmt( std::string transfer );

// (-) --------------------------------|
// #parseRecipient( string )
// ------------------------------------|
// Desc: NULL
   int parseRecipient( std::string transfer );

// (-) --------------------------------|
// #parseSender( string )
// ------------------------------------|
// Desc: NULL
   int parseSender( std::string transfer );

// (-) --------------------------------|
// #parseSequence( string )
// ------------------------------------|
// Desc: NULL
   int parseSequence( std::string transfer );

// (-) --------------------------------|
// #RSAEncrypt( vector<char>, string )
// ------------------------------------|
// Desc: RSA encrypts a vector<char>
   std::vector<char> RSAEncrypt( std::vector<char> plaintext, std::string key);

// (-) --------------------------------|
// #save( string )
// ------------------------------------|
// Desc: Saves a wallet to a state file
   void save( std::string filename );

// (-) --------------------------------|
// #tare( )
// ------------------------------------|
// Desc: Zeroes out internal fields
   void tare( );

// (-) --------------------------------|
// #validate( string )
// ------------------------------------|
// Desc: Determines whether a plaintext transfer is legal or not
   bool validate( std::string transfer );



}; // Closing class eWallet{ }

// End of file - ipRange.h



// Testing Hello

// Problem 1:
// IPv4: 192.168.0.10
// Ip range: 
//   * 192.168.0.0/24
//   * 192.168.0.0-192.168.0.255

is_ip_in_range("192.168.0.10", "192.168.0.0/24") -> true
is_ip_in_range("192.168.0.10", "192.168.0.0-192.168.0.255") -> true
is_ip_in_range("192.168.1.10", "192.168.0.0-192.168.0.255") -> false

is_ip_in_range("10.0.1.10", "10.0.0.0/8") -> true
is_ip_in_range("10.0.1.9", "10.0.0.0/8") -> true
is_ip_in_range("9.0.1.10", "10.0.0.0/8") -> false
//              10.0.1.9

"192.168.0.0-192.168.0.255"
long ip_address_to_decimal(string ip_address) {
    return ...
}

bool is_ip_in_range(string ip_address, string ip_range) {
    stringstream parser1(ip_adress);
    stringstream parser2(ip_range);
    bool retValue = true;
    for( int i = 0 ; i < 3 ; i++ ) {
        // 0.10
        retValue = (parser1.delimit('.') == parser2.delimit('.'))
        if (retValue == false) {
            return (false)
        }
    }
    // "10" vs "10-192.1...."
    // "10" vs "10/24"
    
    
    
    // Step 1 would be to define the valid range range of IP addresses (as an int range)
    string IPaddyLo = parser2.delimit('-');
    string IPaddyHi << parser2;
    
    // Low range of the IP range (as int) && High range of the IP range (as int)
    int IPLo = ip_address_to_decimal(IPaddyLo);
    int IPHi = ip_address_to_decimal(IPaddyHi);
    
    // Step 2 is to determine the int representation of the 2nd ip address
    int IP1 = ip_address_to_decimal(parser1.str())
    
    // Step 3, figure out if the int of the 2nd IP is greater than or equal the low bound and less than the high bound
    
    return( IP1 >= IPLo && IP1 <= IPHi );

    
    // 192.168.0.0/24
    -
}

// Problem 2:
// 1MM+ Ip addresses
// 1MM+ Ip ranges
//


// ip_ranges = [
//    "10.0.0.0-10.0.0.255",
//    "10.0.8.0-10.0.8.255",
//    "192.168.0.0-192.168.0.10"
//]
// ip_addresses = [
//       "192.168.0.10",          -> true
//       "10.0.0.5",              -> true
//       "10.1.0.5",              -> false
//       "192.168.0.6",           -> true
// ]

// output = [true, true, false, true]

// R1   R2   R3   R4
// ^

Tim Sort

// IP1  IP2  IP3  IP4
// ^

// is_ip_in_range() <- Assuming we have this working...
vector<bool> anyInRange(vector<std::string> addies, vector<std::string> ranges) {
   vector<bool> truthTable;

   ranges.sort(); // We get sorted, non overlapping IP ranges
   // For all IP addresses to check...
   for (1MM+) {
      // Find the appropriate range for the value we hold
      range comparisonRange = find(ipranges[], addy[i]); //Binary search goes here
      truthTable[i] = is_ip_in_range( comparisonRange, ip_addy[i] )
   }
}


