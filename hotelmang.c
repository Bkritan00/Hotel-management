#include <stdio.h>
#include <string.h>

// Structure for storing guest details
struct guest {   
int guest_id;
char name[20];
int room_no;
char in_date[20];
char out_date[20];
};

// Function to add a record
void addRecord() {
struct guest g;
FILE *fp;
fp = fopen("guest.dat", "a+");
if (fp == NULL) {
printf("Error in opening file\n");
return;
}

printf("Enter guest id: ");
scanf("%d", &g.guest_id);
printf("Enter your name: ");
scanf("%s", g.name);
printf("Enter your room id: ");
scanf("%d", &g.room_no);
printf("Enter Check-in date (YYYY-MM-DD): ");
scanf("%s", g.in_date);
printf("Enter Check-out date (YYYY-MM-DD): ");
scanf("%s", g.out_date);

fwrite(&g, sizeof(struct guest), 1, fp);
fclose(fp);

printf("Guest record added successfully!\n");
}

// Function to view records
void viewRecords() {
struct guest g;
FILE *fp;
fp = fopen("guest.dat", "r");
if (fp == NULL) {
printf("No records found.\n");
return;
}

printf("\nGuest Records:\n");
printf("ID\tName\t\tRoom\tCheck-in\tCheck-out\n");
printf("--------------------------------------------------\n");

while (fread(&g, sizeof(struct guest), 1, fp)) {
printf("%d\t%s\t%d\t%s\t%s\n", g.guest_id, g.name, g.room_no, g.in_date, g.out_date);
}

fclose(fp);
}

// Function to search a record
void searchRecord() {
FILE *fp;
struct guest g;
int id, found = 0;

fp = fopen("guest.dat", "r");
if (fp == NULL) {
printf("Error in opening file\n");
return;
}

printf("Enter guest id to search: ");
scanf("%d", &id);

while (fread(&g, sizeof(struct guest), 1, fp)) {
if (g.guest_id == id) {
printf("ID: %d\nName: %s\nRoom No: %d\nCheck-in: %s\nCheck-out: %s\n", g.guest_id, g.name, g.room_no, g.in_date, g.out_date);
found = 1;
}
}

if (!found) {
printf("Guest ID not found.\n");
}

fclose(fp);
}

// Function to update a record
void updateRecord() {
FILE *fp = fopen("guest.dat", "r");
FILE *tf = fopen("temp.dat", "w");

if (fp == NULL || tf == NULL) {
printf("Error opening file\n");
return;
}

struct guest g;
int id, found = 0;

printf("Enter guest id to update: ");
scanf("%d", &id);

while (fread(&g, sizeof(struct guest), 1, fp)) {
if (g.guest_id == id) {
found = 1;
printf("\nExisting Record:\n");
printf("ID: %d\nName: %s\nRoom No: %d\nCheck-in: %s\nCheck-out: %s\n",g.guest_id, g.name, g.room_no, g.in_date, g.out_date);

printf("\nEnter new name: ");
scanf("%s", g.name);
printf("Enter new Room Number: ");
scanf("%d", &g.room_no);
printf("Enter new Check-in Date: ");
scanf("%s", g.in_date);
printf("Enter new Check-out Date: ");
scanf("%s", g.out_date);
}
fwrite(&g, sizeof(struct guest), 1, tf);
}

fclose(fp);
fclose(tf);

remove("guest.dat");
rename("temp.dat", "guest.dat");

if (found) {
printf("Guest record updated successfully!\n");
} else {
printf("Guest ID not found.\n");
    }
}


// Function to delete a record
void deleteRecord() {
FILE *fp = fopen("guest.dat", "r");
FILE *tf = fopen("temp.dat", "w");

if (fp == NULL || tf == NULL) {
printf("Error opening file\n");
return;
}

struct guest g;
int id, found = 0;

printf("Enter Guest ID to delete: ");
scanf("%d", &id);

while (fread(&g, sizeof(struct guest), 1, fp)) {
if (g.guest_id != id) {
fwrite(&g, sizeof(struct guest), 1, tf);
} else {
found = 1;
}
}

fclose(fp);
fclose(tf);

remove("guest.dat");
rename("temp.dat", "guest.dat");

if (found) {
printf("Guest record deleted successfully!\n");
} else {
printf("Guest ID not found.\n");
}
}

// Main Menu Function
void menu() {
int choice;
do {
printf("\nHotel Management System\n");
printf("1. Add Record\n");
printf("2. View Records\n");
printf("3. Search Record\n");
printf("4. Update Record\n");
printf("5. Delete Record\n");
printf("6. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);

switch (choice) {
case 1: addRecord(); break;
case 2: viewRecords(); break;
case 3: searchRecord(); break;
case 4: updateRecord(); break;
case 5: deleteRecord(); break;
case 6: printf("Exiting...\n"); break;
default: printf("Invalid choice!\n");
}
} while (choice != 6);
}

// Main Function
int main() {
    menu();
    return 0;
}
