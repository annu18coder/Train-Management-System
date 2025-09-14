#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<conio.h>

struct train{
    long pnr;
    char train_name[200];
    char source[100];
    char departure_time[100];
    char arrival_time[100];
    char destination[100];
};

struct passenger_details{
    char pass_name[100];
    int age;
    char gender[50];
};

void train_list(struct train trains[15], int *n);
void displaymatchingTrains(struct train trains[], int n, char source[], char destination[]);
void displayTrains(struct train t);
void reserveTicket(struct train selectedTrain);

void train_list(struct train trains[15], int *n){
    *n = 5;
    trains[0].pnr = 101010;
    strcpy(trains[0].train_name, "Express A");
    strcpy(trains[0].source, "New Delhi");
    strcpy(trains[0].destination, "Mumbai");
    strcpy(trains[0].departure_time, "08:30");
    strcpy(trains[0].arrival_time, "21:09");

    trains[1].pnr = 101011;
    strcpy(trains[1].train_name, "Express B");
    strcpy(trains[1].source, "Mumbai");
    strcpy(trains[1].destination, "New Delhi");
    strcpy(trains[1].departure_time, "00:45");
    strcpy(trains[1].arrival_time, "14:45");
    
    trains[2].pnr = 101012;
    strcpy(trains[2].train_name, "Express C");
    strcpy(trains[2].source, "New Delhi");
    strcpy(trains[2].destination, "Patna");
    strcpy(trains[2].departure_time, "12:22");
    strcpy(trains[2].arrival_time, "17:23");
    
    trains[3].pnr = 101013;
    strcpy(trains[3].train_name, "Express D");
    strcpy(trains[3].source,"Patna");
    strcpy(trains[3].destination, "New Delhi");
    strcpy(trains[3].departure_time, "08:34");
    strcpy(trains[3].arrival_time, "18:45");
    
    trains[4].pnr = 101014;
    strcpy(trains[4].train_name, "Express E");
    strcpy(trains[4].source, "Chennai");
    strcpy(trains[4].destination, "New Delhi");
    strcpy(trains[4].departure_time, "10:56");
    strcpy(trains[4].arrival_time, "20:23");
};

void displaymatchingTrains(struct train trains[15], int n, char source[], char dest[]){
    int i; 
    int found = 0;
    printf("\nDisplaying the train details from %s to %s:\n", source, dest);
    for(i=0;i<n;i++){
        if((strcasecmp(trains[i].source, source) == 0) && (strcasecmp(trains[i].destination, dest) == 0))
        {
            displayTrains(trains[i]);       
            found = 1;
        }
    }
        if(found == 0){
            printf("\nNo trains found for the given source and destination");
        }
}

void displayTrains(struct train t){
    printf("\nTrain PNR NO. : %ld" ,t.pnr);
    printf("\nTrain Name. : %s" ,t.train_name);
    printf("\nSource Station : %s" ,t.source);
    printf("\nDestination Station : %s" ,t.destination);
    printf("\nTrain departure time : %s" ,t.departure_time);
    printf("\nTrain arrival time : %s" ,t.arrival_time);
}

// for reservation system
void reserveTicket(struct train selectedTrain){
    struct passenger_details passenger;
    
    printf("\n----------------- Enter Passenger Details --------------------");
    printf("\nPassenger Name: ");
    fgets(passenger.pass_name, sizeof(passenger.pass_name), stdin);
    passenger.pass_name[strcspn(passenger.pass_name, "\n")] = 0;

    
    printf("\nPassenger Age: ");
    scanf("%d", &passenger.age);
    getchar();
    
    printf("\nPassenger Gender: ");
    fgets(passenger.gender, sizeof(passenger.gender), stdin);
    passenger.gender[strcspn(passenger.gender, "\n")] = 0;

    printf("\nReservation Confirmed! \n");
    printf("\nPassenger Name: %s", passenger.pass_name);
    printf("\nPassenger Age: %d", passenger.age);
    printf("\nPassenger Gender: %s", passenger.gender);


    FILE*fp = fopen("reservation.txt", "a");
    if(fp == NULL){
        printf("Error opening file!\n");
    }
    else{
        fprintf(fp, "\n----------------------------------------------");
        fprintf(fp, "\n\t\t\t Reservation Confirmed! \n");
        fprintf(fp, "\n----------------------------------------------");
        fprintf(fp, "\n\t\tPassenger Name: %s", passenger.pass_name);
        fprintf(fp, "\n\t\tPassenger Age: %d", passenger.age);
        fprintf(fp, "\n\t\tPassenger Gender: %s", passenger.gender);
        fprintf(fp, "\n\t\tTrain Name: %s", selectedTrain.train_name);
        fprintf(fp, "\n\t\tFrom %s to %s", selectedTrain.source, selectedTrain.destination);
        fprintf(fp, "\n\t\tArrival Time: %s", selectedTrain.arrival_time);
        fprintf(fp, "\n\t\tDestination Time: %s", selectedTrain.departure_time);
        fprintf(fp, "\n----------------------------------------------");
        fclose(fp);
    }
}

int main(){
    struct train trains[15];
    int i, n;
    long selectedPNR;

    // function call to initialize predefined trains
    train_list(trains, &n);

    char source[100];
    char dest[100];


    printf(" \t\t\t\t\t\t  WELCOME TO \t\t\t\t\t\t\t ");
    printf("\n =========================================== TRAIN MANAGEMENT SYSTEM ============================================ \n");
    
    printf("Enter your destination Jourey:\n");
    printf("Enter ORIGIN/SOURCE STATION : ");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = 0;

    printf("\nEnter DESTINATION STATION : ");
    fgets(dest, sizeof(dest), stdin);
    dest[strcspn(dest, "\n")] = 0;

    // while(count>10){
    printf("\n ......../ ........../ ........... /.. SEARCHING FOR AVAILABLE TRAINS ../ ........./ ........../ ........");
        
    // train match karne ke lie 
    displaymatchingTrains(trains, n, source, dest);

    printf("\nEnter PNR No. of Train to confirm reservation: ");
    scanf("%ld", &selectedPNR);
    getchar();

    for(i=0;i<n;i++){
        if(trains[i].pnr == selectedPNR){
            reserveTicket(trains[i]);
            break;
        }
    }
    
    return 0;
}