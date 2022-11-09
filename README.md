# michellundell/9a C++

## Understanding examples
If you find the examples and my explanation to hard to understand, 
raise your hand or say something so I can explain it in an alternative way.


## Agenda

1. Status 4a-ticket.c,  only 7 pull-requests so far.
2. Status C++ versionen ticket.cpp?
3. C++ Code organization.
4. C++ Compile a program using multiple source code files.
5. Finishing 4a-ticket.c version ....

## Lets start

3. Code organization.

C & C++ code is normally divided into two parts:
- a header file with definitions of functions, structures, classes and macros. 
  This is the file "other sources" includes when using your functions/classes.
- a file with code that implementation of functions and classes.

ExampleClass.hh
```
#include <iostream.h>

#ifndef EXAMPLE_CLASS_INCLUDED
#define EXAMPLE_CLASS_INCLUDED

class ExampleClass {
	int x;
	char y;
	double z;
public:
	ExampleClass();
	ExampleClass(int x,char y,double z);
	void run();
	void run(int what);
	friend ostream& operator<<(ostream &out, const ExampleClass &c);
	friend istream& operator>>(istream &out, const ExampleClass &c);
};

#endif
```

Here is the implementation of the ExampleClass ExampleClass.cpp

```
#include "ExampleClass.hh"

/**
* @brief constructor
*/

ExampleClass::ExampleClass() 
{ 
	x=3; 
	y='a'; 
	z=0.2; 
}

/**
* @brief constructor with three arguments
*/

ExampleClass::ExampleClass(int x,char y,double z) 
{
	this->x=3;
	this->y='a';
	this->z=0.2; 
}

/**
* @brief the doit method
*/

void ExampleClass::run() 
{ 
	std::cout << "ExampleClass::run()" << std::endl; 
}

/**
* @brief the doit(int) method
*/

void ExampleClass::run(int what) 
{
	std::cout << "ExampleClass::run( what=" << what << ")" << std::endl; 
}

/**
* @brief the output operator <<  method
*/
std::ostream& operator<<(std::ostream &out, const ExampleClass &c)
{
	out << "x=" << c.x;
	return out ;
}
```

Lets compile it !

```
c++ ExampleClass.cpp -o ExampleProgram
Undefined symbols for architecture x86_64:
  "_main", referenced from:
     implicit entry/start for main executable
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)

```

uuh what?

Ahaa no main() defined. This is normally declared in a separate file

main.cpp
```
#include "ExampleClass.hh"

int main(int argc, char **argv)
{
	ExampleClass myObject;
	myObject.run();
	return 0;
}
```

## 4. C++ Compile a program using multiple source code files.

Compiling two sources into one program is done like this

```
c++ ExampleClass.cpp main.cpp -o ExampleProgram
```

## 5. Finishing 4a-ticket.c version ....

```
You should create a program that takes two arguments.
The first argument is a file with flight information.
The second argument is a file with booking information.
Your program should create files with a ticket for each booking.
```

**Example running the program:**
```
4a-tickets.exe flights.csv booking.csv
```

**Will produce the files:**

```
ticket-1001.txt ticket-1002.txt ticket-1003.txt ticket-1004.txt
ticket-1005.txt ticket-1006.txt ticket-1007.txt ticket-1008.txt
....

## Each row in any flights contain 7 seats. There is an aisle between seat 2 and 3, and 5 and 6.

```
Row seating is 2-3-2 the all flights.

[Window] [seat 1][seat 2] aisle [seat 3][seat 4][seat 5] aisle [seat 6][seat 7] [window]

```

## Flight data-file structure:

flights.csv:
```
flightnumber,departure,destination,date,time,f-rows,b-rows,e-rows
```

## Booking data-file structure:

bookings.csv:
```
bookingnumber,date,time,departure,destination,seatclass,firstname,surname
```

## Output:

The tickets should be written to files with the following filename format:

```
ticket-{bookingnumber}.txt
```

Each file should contain the following information in this format: 

```
BOOKING:{bookingnumber} 
FLIGHT:{flight} DEPARTURE:{dep} DESTINATION: {dest} {date} {time}
PASSENGER {firstname} {surname}
CLASS: {seatclass}
ROW {row} SEAT {seatnumber}
```

### Example of ticket filename:

```
ticket-2007.txt
```

### Example of ticket file content:
```
BOOKING:2007
FLIGHT:304 DEPARTURE:GOT DESTINATION:CPH 2022-10-27 06:30
PASSENGER: Kalle Kula
CLASS: first
ROW:4 SEAT:24
```

## Hint's for completing the assignment:

### Hint 1, use pseudo code:

A good tip is to always start writing high level pseudo code of what your program/function should do.
A short description that you can communicate with others without the C syntax knowledge.
Writing pseudo code is also a part of the process creating software, that prepares your brain for the task.
Breaking down the requirements into small defined tasks that your(and other) brains can easily read and understand.
When you get experienced with C, you might find that the C-code itself is so natural to you it is just as natural and easy to understand like the pseudo code itself.

#### Example
```
READ INDATA FLIGHTS FILE AND SAVE IT IN A FLIGHTS LIST.
READ INDATA BOOKING FILE AND SAVE IT IN A BOOKING LIST.
FOR EACH BOOKING IN THE BOOKING LIST
    FIND THE FLIGHT IN THE FLIGHTS LIST WHICH MATCH THE BOOKING
    THEN ALLOCATE A SEAT (FIND A FREE SEAT)
    MARK THE SEAT BOOKED
    THEN PRINT THE TICKET TO A TICKET FILE
```

### Hint 2, to save flights and bookings in lists, we need data structures that map the indata

Here are examples of datastructures that hold the information we read from the files.

```
typedef struct flight_list_node {
	int flightno;          /* !< The flight number */
	char dep[20];          /* !< Departure airport code */
	char des[20];          /* !< Destination airport code */
	char datestr[20];      /* !< Date departure*/
	char timestr[20];      /* !< Time departure */
	int nfs;               /* !< Number of First class rows */
	int *fs;	       /* !< An array with flags of if a seat is taken or not. 1==occupied, 0==not occupied */
	int nbs;               /* !< Number of Business class rows */
	int *bs;               /* !< An array with flags of if a seat is taken or not. 1==occupied, 0==not occupied */
	int nes;               /* !< Number of Economy class rows */
	int *es;               /* !< An array with flags of if a seat is taken or not. 1==occupied, 0==not occupied */
	struct flight_list_node *next; /* !< A pointer to the next flight information */
} FlightListNode;

typedef struct booking_list_node {
	int booking;          /* !< The booking number */
	char datestr[15];     /* !< The departure date */
	char timestr[15];     /* !< The departure time */
	char dep[10];         /* !< The departure airport */
	char des[10];         /* !< The destination airport */
	char class[20];       /* !< The seat class */
	char fname[25];       /* !< Firstname */
	char lname[25];       /* !< Lastname */
	struct booking_list_node *next; /* !< a pointer to the next booking */
} BookingListNode;

```

### Hint 3, example of realizing READ INDATA FLIGHTS FILE AND SAVE IT IN A FLIGHTS LIST
```
/**
* @brief Read flights from a file, return a linked list with the flights information.
*/
FlightListNode *read_flights(const char *filename)
{
	FlightListNode fln;              /* A variable to store a row read from the file */
	FlightListNode  *head=NULL;      /* A pointer to the first node in the linked list */
	FILE *fp = fopen(filename,"r");  /* Open the file where flight data is */
	while( fscanf(fp,"%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%d\n",&fln.flightno,fln.dep,fln.des,fln.datestr,fln.timestr,&fln.nfs,&fln.nbs,&fln.nes) == 8 ) {
		FlightListNode *nn = malloc(sizeof(FlightListNode)); /* Allocate space to save the read information */
		memcpy(nn,&fln,sizeof(FlightListNode));              /* Copy the read data into the allocated memory */
		nn->fs = malloc(fln.nfs*sizeof(int)*7);              /* Allocate a vector to keep track of seat booking in first class */
		memset(nn->fs,0,fln.nfs*7);                          /* Initiate the seats to free, e.g 0 */
		nn->bs = malloc(fln.nbs*sizeof(int)*7);              /* Allocate a vector to keep track of seat booking in business class */
		memset(nn->bs,0,fln.nbs*7);                          /* Initiate the seats to free, e.g 0 */
		nn->es = malloc(fln.nes*sizeof(int)*7);              /* Allocate a vector to keep track of seat booking in economy class */
		memset(nn->es,0,fln.nes*7);                          /* Initiate the seats to free, e.g 0 */
		nn->next =  head;                                    /* Set the next pointer to head .... */
		head = nn;                                           /* then set the head to the new node. */
	}
	return(head);                                                /* Return the pointer to the list with flights read from the file */
}
```

### Hint 4, example of realizing READ INDATA BOOKING FILE AND SAVE IT IN A BOOKING LIST.
```

/**
* @brief Read bookings from a file, return a linked list with the booking information.
*/
BookingListNode *read_bookings(const char *filename) 
{
	/* code the same way as when reading the flights and create a list, see hint 3 */
}
```

### Hint 5, example of realizing FOR EACH BOOKING IN THE BOOKING LIST
```
/**
* @brief create the ticket for each booking in the booking list
* To create a ticket we need which row and seat in the booked class that
* the passenger have. Therefore we need to find the flight and search
* for free seat, then mark the seat as booked.
*/
int create_tickets(BookingListNode *bookings, FlightListNode *flights)
{
	int num_tickets = 0;
	fprintf(stdout,"Writing tickets: ");

	/* Loop through the booking list */

	for(BookingListNode *blnp = bookings; blnp != NULL; blnp=blnp->next) {

            /* find the flight for this booking, see hint 6 */

	}
	fprintf(stdout,"Created  %d tickets\n\n",num_tickets);
	return(num_tickets);
}
```

### Hint 6, example of realizing FIND THE FLIGHT THE BOOKING IS ON
```
                /* Loop through the flights list ... */
		for(FlightListNode *flnp = flights; flnp != NULL; flnp=flnp->next) {

			/* Check if this flight have the same departure, destination, 
                           date and time as the booking have */
			if( !strcmp(blnp->dep,flnp->dep) &&  
			    !strcmp(blnp->des,flnp->des) &&  
                            !strcmp(blnp->datestr,flnp->datestr) &&  
                            !strcmp(blnp->timestr,flnp->timestr) ) {
                             /* allocate seat and mark it booked */
                             /* see hint 7 */
			}
		}
```


### Hint 7, example of realizing THEN ALLOCATE A SEAT AND PRINT THE TICKET
```
				int row=0, seat=0;

				/* have booking and flight, now find a seat, mark it booked 
                                   and print the ticket */

				if(allocate_seat(flnp,blnp,&row,&seat)){ /* hint 8 */
					fprintf(stdout,"[ticket-%d.txt]",blnp->booking);
					print_ticket(blnp,flnp,seat,row); /* hint 9 */
					num_tickets++;
				}
```


### Hint 8, example of realizing THEN ALLOCATE A SEAT && MARK THE SEAT BOOKED
```
int allocate_seat(FlightListNode *flight,BookingListNode *booking,int *row, int *seat)
{
	int sn = 0;
	int rn = 0;
	/* is the booking in first class ? */
	if( strcmp("first",booking->class) == 0 ) {
                /* Yes, now find a free seat in first class */
		for(int p=0;p<flight->nfs*7;p++) {
			if( flight->fs[p] == 0 ) {      /* seat is free */
				flight->fs[p] = 1;      /* set it booked */
				sn = p+1;               /* calculate seat number */
				rn = (int)p/7+1;        /* calculate row number */
				break;                  /* no need to look for more */
			}
		}
	}
	/* is the booking in business class ? */
	if( strcmp("business",booking->class) == 0 ) {
                /* Yes, now find a free seat in business class */
		for(int p=0;p<flight->nbs*7;p++) {
			if( flight->bs[p] == 0 ) {            /* seat is free */
				flight->bs[p] = 1;            /* set it booked */
				sn = p+flight->nfs*7+1;       /* calculate seat number */
				rn = flight->nfs+(int)p/7+1;  /* calculate row number */
				break;                        /* no need to look for more */
			}
		}
	}
	/* is the booking in economy class ? */
	if( strcmp("economy",booking->class) == 0 ) {
                /* Yes, now find a free seat in economy class */
		for(int p=0;p<flight->nes*7;p++) {
			if( flight->es[p] == 0 ) {                       /* seat is free */
				flight->es[p] = 1;                       /* set it booked */
				sn = p+flight->nfs*7+flight->nbs*7+1;    /* calculate seat number */
				rn = flight->nfs+flight->nbs+(int)p/7+1; /* calculate row number */
				break;                                   /* no need to look for more */
			}
		}
	}
	if( rn ==0 || sn == 0 ) {
		fprintf(stdout,"did not find class \"%s\" for booking on this plane\n",booking->class);
		return(0);
	}
	*row = rn;
	*seat = sn;
	return(1);
}
```

### Hint 9, example of realizing PRINT THE TICKET TO A TICKET FILE
```
void print_ticket(BookingListNode *blnp, FlightListNode *flnp,int seat,int row)
{
	char filename[255];
	sprintf(filename,"ticket-%d.txt",blnp->booking);
	FILE *fp = fopen(filename,"w");
	if( fp ) {
		fprintf(fp,"BOOKING:%d\n",blnp->booking);
		fprintf(fp,"FLIGHT:%d DEPARTURE:%s DESTINATION: %s %s %s\n",flnp->flightno,flnp->dep,flnp->des,flnp->datestr,flnp->timestr);
		fprintf(fp,"PASSENGER %s %s\n",blnp->fname,blnp->lname);
		fprintf(fp,"CLASS: %s\n",blnp->class);
		fprintf(fp,"ROW %d SEAT %d\n\n",row,seat);
		fclose(fp);
	}
}
```

## Enhance your system with the following features (optional, just in case you have time).

### 1. Cancel all flights that does not have any passengers.
It is not good for the business to run planes without passengers. These flights must be cancelled.
Create a function that checks all flights seatings. If there is no occupied seats on a flight it should
be cancelled.

### 2. Create a report-file of cancelled flights named cancelled-flights.txt .
The management want's to see a report of how many and which flights are cancelled.
(Hmm, maybe create this report when cancelling the flight?)

### 3. Create a seating map for each flight and save these into a seating-report.txt file.
Booking staff want's to know where there are free seatings on the flights.
The seating map should show each section and rows in the section.
A '1' will indicate a seat is taken. '0' indicates it is free.

```
Example:

Flight 234, Departure ARN, Destination GOT, Date 2022-02-03, Time 07:20
first class
[1][1] [1][1][1] [1][1]
[1][1] [1][1][1] [1][1]
[1][1] [1][0][0] [0][0]
[0][0] [0][0][0] [0][0]
[0][0] [0][0][0] [0][0]
business class
[1][1] [1][1][1] [1][1]
[1][1] [1][1][1] [1][1]
[1][1] [1][1][1] [1][1]
[0][0] [0][0][0] [0][0]
[0][0] [0][0][0] [0][0]
economy class
[1][1] [1][1][1] [1][1]
[1][1] [1][1][1] [1][1]
[1][1] [1][1][1] [1][1]
[1][1] [1][1][1] [1][1]
[1][1] [1][1][1] [1][1]
[1][1] [1][1][1] [1][1]
[1][1] [1][0][0] [0][0]
[0][0] [0][0][0] [0][0]
```

### 4. Read about the getopt() function and make a small example of using it.
Getting directions input to a program is a standard way of telling the program how to operate.

### 5. Create a program that creates "fake flights" into a .csv file
Create some options for the fake flight program to use when creating fake flights.
Example is to set a range of dates, minimum, maximum seats for each class .... etc

Useful standard functions to use could be strtok, and the functions that manipulates time in C.
```
fake-flights.exe -?
 -s {start date}
 -e {end date}
 -n {number of flights per day}
 -t {list of departure times that can be used}
 -f {list of possible number of rows in first class}
 -b {list of possible number of rows in business class}
 -e {list of possible number of rows in economy class}
 -c {list seating configurations}
 -o {output filename}
```

### 6. Create a program that creates "fake bookings" to the flights in flights.csv file
Let the fake bookings generator know which flights file to read and create bookings for by specifying a filename argument option.
Create arguments that tells the fake bookings generator how many fake bookings it should create.
Be creative and add other options to the program.
Also be creative and make random names!

### 7. Use the fake-flights-generator to create a new flights.csv file
```
fake-flights.exe -s "2022-01-01" -e "2022-01-31" -n 5 -t "06:00,07:00,10:00,13:00,18:00" -f "5,10,15" -b "10,15,20" -e "20,30,40" -c "2-3-2,2-2-2,3-3-3" -o fake-flights.csv
```

### 8. Use the fake-booking-generator to create a new bookings.csv file from the new flights.csv
```
fake-bookings.exe -f fake-flights.csv -o fake-bookings.csv
```

### 9. Run your create tickets program with the new flights.csv and bookings.csv and verify the output.
```
tickets -f flights.csv -b bookings.csv
```

# Final assignment for this class

## The ticket generator you made in C should be turned into a C++ version.
You should create a repository named ticket-system.
The code should be commented in a way that doxygen could produce a nice output for your software (html, pdf is a bonus).
Your software should use C++ features where appropriate.
