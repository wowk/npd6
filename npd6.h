/*
*   This software is Copyright 2011 by Sean Groarke <sgroarke@gmail.com>
*   All rights reserved.
*
*   This file is part of npd6.
*
*   npd6 is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   npd6 is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with npd6.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NPD6_H

#define NPD6_H
#include "includes.h"

#ifndef NPD6_CONF
#define NPD6_CONF "/etc/npd6.conf"
#endif

#ifndef NPD6_LOG
#define NPD6_LOG "/var/log/npd6.log"
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE    1
#endif

// Misc bits and bobs
#define HWADDR_MAX          16
#define MAX_PKT_BUFF        1500
#define LOGTIMEFORMAT       "%b %d %H:%M:%S"
#define INTERFACE_STRLEN    12
#define NULLSTR             "null"
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define MAXMAXHOPS          255
#define HWADDR_MAX          16
#define MAX_PKT_BUFF        1500
#define DISPATCH_TIMEOUT    300000          // milliseconds 300000 = 5 mins
#define flog(pri, ...)      npd6log(__FUNCTION__, pri, __VA_ARGS__)
#define LOG_DEBUG2          8

//*****************************************************************************
// Globals
//
char            *pname;
char            *configfile;
char            *paramName;
int             sockicmp;
int             sockpkt;
int             debug;
int             daemonize;
FILE            *logFileFD;
FILE            *configFileFD;
int             initialIFFlags;

// Interface we're interested in
char            interfacestr[INTERFACE_STRLEN];
unsigned int    interfaceIdx;
unsigned char   linkAddr[6];

// Regarding the target prefix being matched
char            prefixaddrstr[INET6_ADDRSTRLEN];
struct          in6_addr prefixaddr;
unsigned int    prefixaddrlen;

// Key behaviour
int             naLinkOptFlag;      // From config file NPD6OPTFLAG
int             nsIgnoreLocal;      // From config file NPD6LOCALIG
int             naRouter;           // From config file NPD6ROUTERNA
int             maxHops;            // From config file NPD6MAXHOPS


//*****************************************************************************
// Prototypes
//
// main.c
void    dispatcher(void);
void    showUsage(void);

// config.c
int     readConfig(char *);

// util.c
int     npd6log(const char *, int , char *, ...);
void    usersignal(int );
void    print_addr(struct in6_addr *, char *);
void    print_addr16(const struct in6_addr * , char * );
void    build_addr(char *, struct in6_addr *);
int     prefixset(char []);
void    stripwhitespace(char *);
void    dumpHex(unsigned char *, unsigned int);
int     getLinkaddress( char *, unsigned char *);
void    showVersion(void);
int     openLog(char *);
void    dropdead(void);

// icmp6.c
int     open_packet_socket(void);
int     open_icmpv6_socket(void);
int     get_rx(unsigned char *);
void    if_allmulti(char *, unsigned int);
int     sockets_open(int);

// ip6.c
void    processNS( unsigned char *, unsigned int);
int     addr6match( struct in6_addr *, struct in6_addr *, int);


#endif

