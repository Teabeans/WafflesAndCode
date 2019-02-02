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
bool[] are_ip_addresses_in_any_range(string[] ip_addresses, string[] ip_ranges) {
   bool truthTable[1MM+];
   for (1MM+) {
      sort(ipranges[]); // We get sorted, non overlapping IP ranges
      int rangetoCheck(iprange); // The low value
      int lowIP = isolate_lowIP(iprange) // 123-256
      comparisonRange = find(iprange[], lowIP); //Binary search goes here
      truthTable[i] = is_ip_in_range( comparisonRange[], ip_ranges[i] )
   }
}


