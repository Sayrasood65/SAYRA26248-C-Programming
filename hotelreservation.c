#include <stdio.h>

#include <string.h>

int main() {
    int rooms[30];
    char names[30][50];
    int members[30];
    int kingBed[30] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };
    int extraBedding[30];
    int acType[30];
    char checkinDate[30][15];
    char checkoutDate[30][15];
    char checkinTime[30][10];
    char checkoutTime[30][10];
    char aadhaar[30][25];
    char payment[30][20];
    int facilitiesBreakfast[30];
    int facilitiesWifi[30];
    int facilitiesParking[30];
    int confirmed[30];
    char waiting_names[30][50];
    int waiting_count = 0;

    int base_normal = 3000;
    int base_king = 5500;
    int ac_extra = 800;
    int extra_bedding_charge = 700;
    int breakfast_charge = 800;
    int wifi_charge = 500;
    int parking_charge = 80;

    int i, choice, room;

    for (i = 0; i < 30; i++) {
        rooms[i] = 0;
        strcpy(names[i], "");
        members[i] = 0;
        extraBedding[i] = 0;
        acType[i] = 0;
        strcpy(checkinDate[i], "");
        strcpy(checkoutDate[i], "");
        strcpy(checkinTime[i], "");
        strcpy(checkoutTime[i], "");
        strcpy(aadhaar[i], "");
        strcpy(payment[i], "");
        facilitiesBreakfast[i] = 0;
        facilitiesWifi[i] = 0;
        facilitiesParking[i] = 0;
        confirmed[i] = 0;
    }

    while (1) {
        printf("\n1.Display Rooms\n2.Book Room\n3.Cancel Booking\n4.View All Bookings\n5.View Waiting List\n6.Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            for (i = 0; i < 30; i++) {
                printf("Room %d : %s, Bed: %s, Type: %s, Confirmed: %s\n",
                       i+1,
                       rooms[i] ? "Booked" : "Available",
                       kingBed[i] ? "King" : "Normal",
                       acType[i] ? "AC" : "Non-AC",
                       confirmed[i] ? "Yes" : "No");
            }
        }

        else if (choice == 2) {
            printf("Enter room number to book (1-30): ");
            if (scanf("%d", &room) != 1) continue;
            if (room < 1 || room > 30) continue;

            if (rooms[room-1]) {
                int w;
                printf("Room booked. Add to waiting list? (1=Yes 0=No): ");
                if (scanf("%d", &w) != 1) continue;
                if (w == 1 && waiting_count < 30) {
                    printf("Enter name for waiting list: ");
                    scanf("%s", waiting_names[waiting_count]);
                    waiting_count++;
                    printf("Added to waiting list.\n");
                } else if (w == 1) {
                    printf("Waiting list full.\n");
                }
                continue;
            }

            printf("Enter customer name: ");
            scanf("%s", names[room-1]);

            printf("Enter number of members: ");
            scanf("%d", &members[room-1]);

            printf("This room has a %s bed.\n", kingBed[room-1] ? "KING" : "NORMAL");

            printf("Extra bedding? (1=Yes 0=No): ");
            scanf("%d", &extraBedding[room-1]);

            printf("Room type (1=AC 0=Non-AC): ");
            scanf("%d", &acType[room-1]);

            printf("Enter Check-In Date (DD/MM/YYYY): ");
            scanf("%s", checkinDate[room-1]);

            printf("Enter Check-In Time (HH:MM): ");
            scanf("%s", checkinTime[room-1]);

            printf("Enter Check-Out Date (DD/MM/YYYY): ");
            scanf("%s", checkoutDate[room-1]);

            printf("Enter Check-Out Time (HH:MM): ");
            scanf("%s", checkoutTime[room-1]);

            printf("Enter Aadhaar Number: ");
            scanf("%s", aadhaar[room-1]);

            printf("Select Payment Method (UPI/Cash/Card): ");
            scanf("%s", payment[room-1]);

            printf("Do you want Breakfast? (1 = Yes, 0 = No): ");
            scanf("%d", &facilitiesBreakfast[room-1]);

            printf("Do you want WiFi? (1 = Yes, 0 = No): ");
            scanf("%d", &facilitiesWifi[room-1]);

            printf("Do you need Parking? (1 = Yes, 0 = No): ");
            scanf("%d", &facilitiesParking[room-1]);

            printf("Confirm Booking? (1 = Yes, 0 = No): ");
            scanf("%d", &confirmed[room-1]);

            if (confirmed[room-1] == 1) {
                rooms[room-1] = 1;

                int charge = kingBed[room-1] ? base_king : base_normal;
                if (acType[room-1]) charge += ac_extra;
                if (extraBedding[room-1]) charge += extra_bedding_charge;
                if (facilitiesBreakfast[room-1]) charge += breakfast_charge;
                if (facilitiesWifi[room-1]) charge += wifi_charge;
                if (facilitiesParking[room-1]) charge += parking_charge;

                printf("Booking confirmed for %s. Total charge: %d\n", names[room-1], charge);
            } else {
                printf("Booking not confirmed.\n");
            }
        }

        else if (choice == 3) {
            printf("Enter room number to cancel (1-30): ");
            if (scanf("%d", &room) != 1) continue;
            if (room < 1 || room > 30) continue;

            if (!rooms[room-1]) {
                printf("Room not booked.\n");
                continue;
            }

            rooms[room-1] = 0;
            strcpy(names[room-1], "");
            members[room-1] = 0;
            extraBedding[room-1] = 0;
            acType[room-1] = 0;
            strcpy(checkinDate[room-1], "");
            strcpy(checkinTime[room-1], "");
            strcpy(checkoutDate[room-1], "");
            strcpy(checkoutTime[room-1], "");
            strcpy(aadhaar[room-1], "");
            strcpy(payment[room-1], "");
            facilitiesBreakfast[room-1] = 0;
            facilitiesWifi[room-1] = 0;
            facilitiesParking[room-1] = 0;
            confirmed[room-1] = 0;

            printf("Booking canceled for room %d.\n", room);
        }

        else if (choice == 4) {
            int found = 0;
            for (i = 0; i < 30; i++) {
                if (rooms[i]) {
                    found = 1;
                    printf("\nRoom %d: %s, Members: %d, Bed: %s, ExtraBedding: %s, Type: %s\nCheck-in: %s %s  Check-out: %s %s\nAadhaar: %s Payment: %s\nFacilities: Breakfast:%s Wifi:%s Parking:%s Confirmed:%s\n",
                        i+1,
                        names[i],
                        members[i],
                        kingBed[i] ? "King" : "Normal",
                        extraBedding[i] ? "Yes" : "No",
                        acType[i] ? "AC" : "Non-AC",
                        checkinDate[i], checkinTime[i],
                        checkoutDate[i], checkoutTime[i],
                        aadhaar[i], payment[i],
                        facilitiesBreakfast[i] ? "Yes" : "No",
                        facilitiesWifi[i] ? "Yes" : "No",
                        facilitiesParking[i] ? "Yes" : "No",
                        confirmed[i] ? "Yes" : "No");
                }
            }
            if (!found) printf("No bookings.\n");
        }

        else if (choice == 5) {
            printf("Waiting List (%d):\n", waiting_count);
            for (i = 0; i < waiting_count; i++) {
                printf("%d. %s\n", i+1, waiting_names[i]);
            }
            if (waiting_count == 0) printf("Waiting list is empty.\n");
        }

        else if (choice == 6) {
            break;
        }
    }

    return 0;
}
