//-------|---------|---------|---------|---------|---------|---------|---------|
//
// IP Range Checker
// driver.cpp
//
//-------|---------|---------|---------|---------|---------|---------|---------|

//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum
// twhlum@gmail.com
// Created:  2018.10.18
// Modified: 2018.10.18
//

//-----------------------------------------------------------------------------|
// File Description
//-----------------------------------------------------------------------------|
//
// This is the driver file for an IP range checker.
//
// Program Behavior:
// This program generates a range of IP addresses, as well as an associated
// range of IP address ranges, then reports whether the IP addresses may be
// found in -any- of the IP address ranges.
//
// It explores the most general case, in which IP ranges may overlap and both
// ranges and single addresses are generated in a randomized order.
//
// The output can be provided in the most general case (set VERBOSE_MATCH == True),
// in which a matching IP address will report all matches. Toggling
// VERBOSE_MATCH to false improves the worst-case time complexity substantially,
// but will only report the first matching range.
//

//-----------------------------------------------------------------------------|
// Package Files
//-----------------------------------------------------------------------------|
//
// None, this is a standalone file
//

//-----------------------------------------------------------------------------|
// Useage
//-----------------------------------------------------------------------------|
//
// Compile with:
// $ g++ --std=c++11 driver.cpp
//
// To run:
// $ chmod u+x run.sh
// $ ./run.sh
//



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       GLOBAL VARIABLES
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// Controls whether 
bool VERBOSE_MATCH = false;

// The number of ranges to generate
int RANGE_COUNT = 100;

// The range density in percent.
// 100 == Sum of ranges equals the number of possible IP addresses (2^32)
// 50  == Sum of ranges equals half the number of possible IP addresses (2^31)
int DENSITY = 150;

// The number of IP addresses to generate
int IP_COUNT = 100;


//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       INCLUDE STATEMENTS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// For input/output operations
#include <iostream>

// For width-formatted outputs
#include <iomanip>

// For string operations
#include <string>

// For stringstream operations
#include <sstream>

// For vector operations
#include <vector>

// For random number generation
#include <cstdlib>

// For INT_MAX
#include <climits>

// For exponentiation
#include <cmath>

// For sort()
#include <algorithm>

// For bitshifting
#include <bitset>

//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       HELPER METHODS (DECLARATIONS)
//
//-------|---------|---------|---------|---------|---------|---------|---------|

unsigned int     CIDRLoInt( std::string CIDRRange );
unsigned int     CIDRHiInt( std::string CIDRRange );
std::vector<int> findClosest( std::string tgtIP, std::vector<std::vector<int>> rangeTable );
bool             isGreaterThan( const std::vector<int>& vec1, const std::vector<int>& vec2);
std::string      intToIP( unsigned int IPval );
unsigned int     IPtoInt( std::string IPaddy );
std::vector<int> IPtoRange( std::string IPRange );
void             isInAnyRange( std::vector<std::string> IPtable, std::vector<std::vector<int>> rangeTable, std::vector<bool> &truthTable );
bool             isInRange( std::string IPaddy, std::string range );
int              isValid( std::string IPaddy );
unsigned int     parseLow( std::string IPRange );
unsigned int     parseHighDash( std::string IPRange );
std::string      randIP( );
std::string      randRange( );
void             reportAddyTable( std::vector<std::string> table );
void             reportRangeTable( std::vector<std::string> table );
void             reportRangeTableInt( std::vector<std::vector<int>> table );
void             reportTruthTable( std::vector<bool> table );
void             sortIPRanges( std::vector<std::vector<int>> &table);
void             testAlert( std::string title );



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       DRIVER
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// (+) --------------------------------|
// #main(int arg1, char* arg2[])
// ------------------------------------|
// Desc:    The driver of the program
// Params:  None
// PreCons: None
// PosCons: None
// RetVal:  Integer exit code
int main( int argc, char *argv[] ) {

   // Declare and initialize the truth table
   std::vector<bool> truthTable;
   for( int i = 0 ; i < IP_COUNT ; i++ ) {
      truthTable.push_back( false );
   }

   testAlert("00 - Generate and report IP addresses");
   // Declare and initialize the address tables
   std::vector<std::string> addyTable;
   for( int i = 0 ; i < IP_COUNT ; i++ ) {
      addyTable.push_back( randIP( ) );
   }
   reportAddyTable( addyTable );
   std::cout << std::endl;

   testAlert("01 - Generate and report IP ranges");
   std::vector<std::string> rangeTable;
   for( int i = 0 ; i < RANGE_COUNT ; i++ ) {
      rangeTable.push_back( randRange( ) );
   }
   reportRangeTable( rangeTable );
   std::cout << std::endl;

   testAlert("02 - Convert CIDR range to int ranges");
   std::string CIDRRange = "123.123.123.123/27";
   unsigned int CIDRLo = CIDRLoInt( CIDRRange );
   unsigned int CIDRHi = CIDRHiInt( CIDRRange );
   std::cout << CIDRLo << " - " << CIDRHi << std::endl;

   testAlert("03 - Convert all ranges to integers");
   std::vector<std::vector<int>> rangeTableInts;
   for( int i = 0 ; i < RANGE_COUNT ; i++ ) {
      std::vector<int> pair;
      pair.push_back( parseLow(  rangeTable.at(i) ) );
      pair.push_back( parseHighDash( rangeTable.at(i) ) );
      rangeTableInts.push_back( pair );
   }
   reportRangeTableInt( rangeTableInts );

   testAlert("04 - Validate if an address is within range");
   std::string testIP = "127.0.0.1";
   std::cout << "In range 83.159.127.18-85.139.4.48   : " << isInRange( "127.0.0.1", "83.159.127.18-85.139.4.48") << std::endl;
   std::cout << "In range 106.55.40.138-108.34.173.168: " << isInRange( "127.0.0.1", "106.55.40.138-108.34.173.168") << std::endl;
   std::cout << "In range 126.2.2.1-128.4.17.18       : " << isInRange( "127.0.0.1", "126.2.2.1-128.4.17.18") << std::endl;

   testAlert("05 - Sort the ranges");
   sortIPRanges( rangeTableInts );
   reportRangeTableInt( rangeTableInts );

   testAlert("06 - Compare all ranges");
   isInAnyRange( addyTable, rangeTableInts, truthTable );
   std::cout << std::endl;
   std::cout << "Truth table state:" << std::endl;
   reportTruthTable( truthTable );

   return( 0 );
} // Closing main( )



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       HELPER METHODS (IMPLEMENTATIONS)
//
//-------|---------|---------|---------|---------|---------|---------|---------|

unsigned int CIDRLoInt( std::string CIDRRange ) {
   std::cout << "CIDRLo() called: " << CIDRRange << std::endl;
   unsigned int IPAsInt = IPtoInt( CIDRRange );
   std::bitset<32> IPBinary(IPAsInt);
   std::cout << "IPBinary: " << IPBinary << std::endl;
   unsigned int hostID = 0;
   std::stringstream parser( CIDRRange );
   char wasteChar;
   for( int i = 0 ; i < 5 ; i++ ) {
      parser >> hostID;
      parser >> wasteChar;
   }
   // hostID == 25
   hostID = 32 - hostID;
   // hostID == 7
   std::cout << "hostID: " << hostID << std::endl;
   IPBinary >>= hostID;
   IPBinary <<= hostID;
   std::cout << "IP Low: " << IPBinary << std::endl;
   std::cout << "               .       .       ." << std::endl;
   return( IPBinary.to_ulong( ) );
}

unsigned int CIDRHiInt( std::string CIDRRange ) {
   std::cout << "CIDRHi() called: " << CIDRRange << std::endl;
   unsigned int IPAsInt = IPtoInt( CIDRRange );
   std::bitset<32> IPBinary(IPAsInt);
   std::cout << "IPBinary: " << IPBinary << std::endl;
   unsigned int hostID = 0;
   std::stringstream parser( CIDRRange );
   char wasteChar;
   for( int i = 0 ; i < 5 ; i++ ) {
      parser >> hostID;
      parser >> wasteChar;
   }
   // hostID == 25
   hostID = 32 - hostID;
   // hostID == 7
   std::cout << "hostID: " << hostID << std::endl;
   // Shift right, then left to clear the hostID bits
   IPBinary >>= hostID;
   for( int i = 0 ; i < hostID ; i++ ) {
      IPBinary <<= 1; // TODO: Find arithmetic left shift?
      IPBinary.set( 0, 1 );
   }

   std::cout << "IP High: " << IPBinary << std::endl;
   unsigned int retInt = IPBinary.to_ulong( );
   std::cout << "Returning( " << retInt << " : " << intToIP(retInt) << " )" << std::endl;
   return( retInt );
}

// Desc: Converts an IP address to its integer equivalent
unsigned int CIDRtoInt( std::string addy ) {
   std::stringstream parser( addy );
   unsigned int retInt = 0;
   for( int i = 3 ; i >= 0 ; i-- ) {
      int temp;
      parser >> temp;
      retInt += temp * ( std::pow( 2., ( 8 * i ) ) );
   }
   return( retInt );
} // Closing IPtoInt( )

bool isGreaterThan( const std::vector<int>& vec1, const std::vector<int>& vec2) {
   return( vec1[0] < vec2[0] );
}

// Desc: Converts an integer to its IP equivalent
std::string intToIP( unsigned int addy ) {
   int octets[4];

   // Capture the octets from least to greatest
   for( int i = 3 ; i >= 0 ; i-- ) {
      octets[i] = addy % 256;
      addy = addy / 256;
   }

   std::stringstream concat;

   // Append octets 0, 1, and 2 back to the stream
   for( int i = 0 ; i < 3 ; i++ ) {
      concat << octets[i] << '.';
   }
   concat << octets[3];

   std::string retIP = concat.str( );
   return( retIP );
} // Closing intToIP( )

// Desc: Converts an IP address to its integer equivalent
unsigned int IPtoInt( std::string addy ) {
   std::stringstream parser( addy );
   unsigned int retInt = 0;
   for( int i = 3 ; i >= 0 ; i-- ) {
      int temp;
      char waste;
      parser >> temp;
      parser >> waste;
      retInt += temp * ( std::pow( 2., ( 8 * i ) ) );
   }
   return( retInt );
} // Closing IPtoInt( )

// Returns if the address is within range
bool isInRange( std::string IPaddy, std::string range ) {
   unsigned int hi = parseHighDash( range );
   unsigned int lo = parseLow( range );
   unsigned int addy = IPtoInt( IPaddy );
   // Perform the in-range evaluation
   return( (hi >= addy) && (addy >= lo) );
} // Closing isInRange( )

// Returns if the address is within range
bool isInRangeInt( std::string IPaddy, std::vector<int> range ) {
   unsigned int hi = range[1];
   unsigned int lo = range[0];
   unsigned int addy = IPtoInt( IPaddy );
   // Perform the in-range evaluation
   bool didHit = ( (hi >= addy) && (addy >= lo) );
   if (didHit) {
      std::cout << std::left << std::setw(16) << IPaddy << "is in range " << std::setw(16) << std::left << intToIP( lo ) << "- " << intToIP( hi ) << std::endl;
   }
   return( didHit );
} // Closing isInRange( )

// Records which addresses are within any range
void isInAnyRange( std::vector<std::string> IPtable, std::vector<std::vector<int>> rangeTable, std::vector<bool> &truthTable ) {
   for( int i = 0 ; i < IP_COUNT ; i++ ) {
      std::vector<int> compareRange = findClosest( IPtable[i], rangeTable );
      truthTable[i] = isInRangeInt( IPtable[i], compareRange );
   }
} // Closing isInAnyRange( )

// Finds the closest range such that the range low bound is less than or equal to the target IP
std::vector<int> findClosest( std::string tgtIP, std::vector<std::vector<int>> rangeTable ) {
   int addy = IPtoInt( tgtIP );
   // Binary search
   int curr = rangeTable.size( ) - 1; // Be sure to subtract 1, otherwise segfault
   while( (rangeTable[curr][0] > addy) && (curr > 0) ) {
      curr--;
   }
   return( rangeTable[curr] );
   // TODO: Swap with binary search at some point
}


// Desc: Isolates the low value of a given range
unsigned int parseLow( std::string range ) {
   std::stringstream parser( range );
   unsigned int retInt = 0;
   for( int i = 3 ; i >= 0 ; i-- ) {
      unsigned int temp;
      char waste;
      parser >> temp;
      parser >> waste;
      retInt += temp * std::pow( 2., ( 8 * i ) );
   }
   return( retInt );
} // Closing parseLow( )

// Desc: Isolates the high value of a given range
unsigned int parseHighDash( std::string range ) {
   std::stringstream parser( range );

   // Chew through the first four octets
   int wasteInt;
   char wasteChar;
   for( int i = 0 ; i < 4 ; i++ ) {
      parser >> wasteInt;
      parser >> wasteChar;
   }

   unsigned int retInt = 0;
   for( int i = 3 ; i >= 0 ; i-- ) {
      unsigned int temp = 0;
      parser >> temp;
      parser >> wasteChar;
      retInt += temp * std::pow( 2., ( 8 * i ) );
   }
   return( retInt );
} // Closing parseHighDash( )

// Desc: Generates a randomized IP as a string in format "###.###.###.###"
std::string randIP( ) {
   std::stringstream concat;
   concat << ( rand( ) % 256 ) << "." << ( rand( ) % 256 ) << "."<< ( rand( ) % 256 ) << "."<< ( rand( ) % 256 );
   std::string retIP = concat.str( );
   return( retIP );
} // Closing randIP( )

// Desc: Generates a randomized IP range as a string
std::string randRange( ) {
   std::stringstream concat;
   // Establish a random IP start point (as integer)
   int rangeLo = rand( );
   concat << intToIP( rangeLo );

   // Determine the range format (0 == direct range, 1 == CIDR, 2 == subnet mask)
   int choice = 0;
   // int choice = ( rand( ) % 3 );

   // Dash format <LOW IP>-<HIGH IP>
   if( choice == 0 ) {
      int delta = (INT_MAX / RANGE_COUNT) * (float)( DENSITY / 100.0 );
      int rangeHi = 0;
      if( INT_MAX - delta <= rangeLo ) {
         rangeHi = INT_MAX;
      }
      else {
         rangeHi = rangeLo + delta;
      }
      std::string terminus = intToIP( rangeHi );
      concat << "-" << terminus;
   }

   else if ( choice == 1 ) { // TODO
      return( "" );
   }

   else if ( choice == 2 ) { // TODO
      return( "" );
   }

   std::string retRange = concat.str( );
   return( retRange );
} // Closing randRange( )

// Desc: Writes the contents of an address table to STD out
void reportAddyTable( std::vector<std::string> table ) {
   for( int i = 0 ; i < IP_COUNT ; i++ ) {
      std::cout << std::left << std::setw(20) << table.at( i );
      if( i % 5 == 4 ) {
         std::cout << std::endl;
      }
   }
} // Closing reportAddyTable( vector<string> )

// Desc: Writes the contents of a range table to STD out
void reportRangeTable( std::vector<std::string> table ) {
   for( int i = 0 ; i < RANGE_COUNT ; i++ ) {
      std::cout << std::left << std::setw(32) << table.at( i );
      if( i % 3 == 2 ) {
         std::cout << std::endl;
      }
   }
} // Closing reportRangeTable( vector<string> )

// Desc: Writes the contents of a range table to STD out
void reportRangeTableInt( std::vector<std::vector<int>> table ) {
   for( int i = 0 ; i < RANGE_COUNT ; i++ ) {
      std::stringstream concat;
      concat << std::right << std::setw(10) << table.at(i).at(0) << " : " << std::right << std::setw(10) << table.at(i).at(1);
      std::cout << std::left << std::setw(30) << concat.str( );
      if( i % 5 == 4 ) {
         std::cout << std::endl;
      }
   }
} // Closing reportRangeTable( vector<string> )

void reportTruthTable( std::vector<bool> table ) {
   for( int i = 0 ; i < IP_COUNT ; i++ ) {
      std::cout << table[i] << " ";
      if( i % 10 == 9 ) {
         std::cout << std::endl;
      }
   }
}

// Desc: Sorts a table of vector ranges
void sortIPRanges( std::vector<std::vector<int>> &table ) {
   std::sort ( table.begin( ), table.end( ), isGreaterThan );
} // Closing sortIPRanges( vector<vector<int>> )

void testAlert( std::string title ) {
   std::cout << std::endl;
   std::cout << "//-------|---------|---------|---------|---------|---------|---------|---------|" << std::endl;
   std::cout << "//       TEST " << title << std::endl;
   std::cout << "//-------|---------|---------|---------|---------|---------|---------|---------|" << std::endl;
   std::cout << std::endl;
} // Closing testAlert( string )

// End of file - driver.cpp
