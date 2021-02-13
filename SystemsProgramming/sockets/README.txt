1.
The socket API - socket(AF_INET, SOCK_STREAM, 0);

AF_INET = IPv4, 
SOCK_STREAM = stream socket or TCP, for UDP it is SOCK_DGRAM
Last argument is 0 means single protocol to be used in protocol family

2. 
struct sockaddr_in
Socket = IP address + port number, and this is what this structure is all about.
In addition it just specifies which address family - IPv4 or IPv6.

The port number needs to be in network byte ordering. Network byte ordering is always big-endian which can differ from host byte ordering. Hence the conversion. Use htons( ) - Host byte to network byte short.

The internet address in this structure is always the address of server.
If you are providing this address as a dotted decimal (like 10.45.89.30), then this is a string and it needs to be converted to actual internet address. For that use inet_addr( ) or inet_pton( ). 
inet_addr( ) - Converts string to network IP for only IPv4
inet_pton( ) - Converts string to network IP for IPv4 and IPv6

The s_addr (sin_addr.s_addr) as specified above is the address of server o

struct sockaddr_in {
    sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address - Convert dotted decimal to IP using inet_addr or inet_pton */
 };

 /* Internet address. */
 struct in_addr {
      uint32_t       s_addr;     /* address in network byte order */
  };
  
  NOTE: If we give, "sin_addr.s_addr = INADDR_ANY;" This means it can bind to any address of the m/c (A m/c can have different NICs so different IP addresses of same host)
  INADDR_ANY is used when you don't need to bind a socket to a specific IP. When you use this value as the address when calling bind() , the socket accepts connections to all the IPs of the machine (Ref: https://stackoverflow.com/questions/16508685/understanding-inaddr-any-for-socket-programming)
  
 3. Important UNIX networking structures (Ref: https://www.tutorialspoint.com/unix_sockets/socket_structures.htm)
 
 sockaddr -This is a generic socket address structure, which will be passed in most of the socket function calls. 
 struct sockaddr {
   unsigned short   sa_family;
   char             sa_data[14];
 };
  
  sockaddr_in - Standard structure which stores most of information. This is often typecasted to sockaddr.
  struct sockaddr_in {
   short int            sin_family;
   unsigned short int   sin_port;
   struct in_addr       sin_addr;
   unsigned char        sin_zero[8];
};

Used only in sockaddr_in to store the server address.
struct in_addr {
   unsigned long s_addr;
};

This structure is used to keep information related to host.
struct hostent {
   char *h_name; 
   char **h_aliases; 
   int h_addrtype;  
   int h_length;    
   char **h_addr_list
	
#define h_addr  h_addr_list[0]
};

servent -This particular structure is used to keep information related to service and associated ports.
struct servent {
   char  *s_name; 
   char  **s_aliases; 
   int   s_port;  
   char  *s_proto;
};


References:
https://www.tutorialspoint.com/unix_sockets/socket_structures.htm
https://stackoverflow.com/questions/26974179/calling-accept-gives-errorno-14-bad-address
https://www.lixu.ca/2014/09/c-implicit-declaration-of-function.html
http://man7.org/linux/man-pages/man2/accept.2.html
https://stackoverflow.com/questions/16508685/understanding-inaddr-any-for-socket-programming
