#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1. DEFINITIONS AND DATA STRUCTURES ---

// Constants for maximum field lengths
#define MAX_NAME_LEN 50
#define MAX_SPECIALTY_LEN 30
#define MAX_ID_LEN 10

// 1. Doctor Structure (Node for Linked List)
typedef struct Doctor {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    char specialty[MAX_SPECIALTY_LEN];
    struct Doctor *next; // Pointer to the next Doctor record
} Doctor;

// 2. Patient Structure (Node for Linked List)
typedef struct Patient {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    int age;
    struct Patient *next; // Pointer to the next Patient record
} Patient;

// 3. Appointment Structure (Node for Linked List)
typedef struct Appointment {
    char appointment_id[MAX_ID_LEN];
    char patient_id[MAX_ID_LEN];  // Foreign key link to Patient
    char doctor_id[MAX_ID_LEN];    // Foreign key link to Doctor
    char date[15]; // YYYY-MM-DD
    char time[10]; // HH:MM
    struct Appointment *next; // Pointer to the next Appointment record
} Appointment;

// Global Head Pointers for the Linked Lists (entry points to our data)
Doctor *doctorList = NULL;
Patient *patientList = NULL;
Appointment *appointmentList = NULL;

// --- UTILITY FUNCTIONS (SEARCH AND ID GENERATION) ---

// Sequential Search: Finds a doctor by ID
Doctor* findDoctor(const char* id) {
    Doctor *current = doctorList;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Sequential Search: Finds a patient by ID
Patient* findPatient(const char* id) {
    Patient *current = patientList;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Generates a simple ID (e.g., D001, P002)
char* generateId(char prefix, int count, char* buffer) {
    sprintf(buffer, "%c%03d", prefix, count);
    return buffer;
}


// --- 2. CORE SYSTEM FUNCTIONS (LINKED LIST OPERATIONS) ---

// --- A. Doctor Management ---

void addDoctor() {
    // Dynamic Memory Allocation: Request memory for a new doctor node
    Doctor *newDoctor = (Doctor *)malloc(sizeof(Doctor));
    if (newDoctor == NULL) {
        printf("\nError: Could not allocate memory.\n");
        return;
    }

    static int doctor_count = 0;
    char id_buffer[MAX_ID_LEN];
    doctor_count++;
    generateId('D', doctor_count, id_buffer);
    strcpy(newDoctor->id, id_buffer);

    printf("\n--- Register New Doctor (ID: %s) ---\n", newDoctor->id);
    printf("Enter Name: ");
    scanf("%s", newDoctor->name);
    printf("Enter Specialty: ");
    scanf("%s", newDoctor->specialty);
    
    // Linked List Insertion (at the head/beginning)
    newDoctor->next = doctorList;
    doctorList = newDoctor;
    
    printf("\n✅ Doctor %s registered successfully.\n", newDoctor->name);
}

void displayDoctors() {
    Doctor *current = doctorList;
    if (current == NULL) {
        printf("\n🛑 No doctors registered.\n");
        return;
    }

    printf("\n--- Registered Doctors ---\n");
    printf("%-10s %-30s %-20s\n", "ID", "Name", "Specialty");
    printf("---------------------------------------------------\n");

    // Linked List Traversal: Walk from the start until the end (NULL)
    while (current != NULL) {
        printf("%-10s %-30s %-20s\n", current->id, current->name, current->specialty);
        current = current->next;
    }
    printf("---------------------------------------------------\n");
}


// --- B. Patient Management ---

void registerPatient() {
    Patient *newPatient = (Patient *)malloc(sizeof(Patient));
    if (newPatient == NULL) {
        printf("\nError: Could not allocate memory.\n");
        return;
    }

    static int patient_count = 0;
    char id_buffer[MAX_ID_LEN];
    patient_count++;
    generateId('P', patient_count, id_buffer);
    strcpy(newPatient->id, id_buffer);

    printf("\n--- Register New Patient (ID: %s) ---\n", newPatient->id);
    printf("Enter Name: ");
    scanf("%s", newPatient->name);
    printf("Enter Age: ");
    scanf("%d", &newPatient->age);
    
    // Linked List Insertion
    newPatient->next = patientList;
    patientList = newPatient;
    
    printf("\n✅ Patient %s registered successfully.\n", newPatient->name);
}

void displayPatients() {
    Patient *current = patientList;
    if (current == NULL) {
        printf("\n🛑 No patients registered.\n");
        return;
    }

    printf("\n--- Registered Patients ---\n");
    printf("%-10s %-30s %-5s\n", "ID", "Name", "Age");
    printf("--------------------------------------------\n");

    // Linked List Traversal
    while (current != NULL) {
        printf("%-10s %-30s %-5d\n", current->id, current->name, current->age);
        current = current->next;
    }
    printf("--------------------------------------------\n");
}

// --- C. Appointment Management ---

void bookAppointment() {
    Appointment *newAppt = (Appointment *)malloc(sizeof(Appointment));
    if (newAppt == NULL) {
        printf("\nError: Could not allocate memory.\n");
        return;
    }

    char pat_id[MAX_ID_LEN], doc_id[MAX_ID_LEN];
    static int appt_count = 0;
    char id_buffer[MAX_ID_LEN];
    appt_count++;
    generateId('A', appt_count, id_buffer);
    strcpy(newAppt->appointment_id, id_buffer);

    printf("\n--- Book New Appointment (ID: %s) ---\n", newAppt->appointment_id);

    // 1. Get and Validate Patient ID (Using Sequential Search)
    printf("Enter Patient ID (e.g., P001): ");
    scanf("%s", pat_id);
    if (findPatient(pat_id) == NULL) {
        printf("❌ Error: Patient ID '%s' not found. Please register first.\n", pat_id);
        free(newAppt); // Cleanup allocated memory
        return;
    }
    strcpy(newAppt->patient_id, pat_id);


    // 2. Get and Validate Doctor ID (Using Sequential Search)
    printf("Enter Doctor ID (e.g., D001): ");
    scanf("%s", doc_id);
    if (findDoctor(doc_id) == NULL) {
        printf("❌ Error: Doctor ID '%s' not found.\n", doc_id);
        free(newAppt); // Cleanup allocated memory
        return;
    }
    strcpy(newAppt->doctor_id, doc_id);


    // 3. Get Date and Time
    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", newAppt->date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", newAppt->time);

    // Linked List Insertion
    newAppt->next = appointmentList;
    appointmentList = newAppt;
    
    printf("\n✅ Appointment booked successfully on %s at %s.\n", newAppt->date, newAppt->time);
}

void displayDoctorSchedule() {
    char doc_id[MAX_ID_LEN];
    printf("\n--- Display Doctor Schedule ---\n");
    printf("Enter Doctor ID to view schedule (e.g., D001): ");
    scanf("%s", doc_id);

    Doctor *doctor = findDoctor(doc_id);
    if (doctor == NULL) {
        printf("❌ Error: Doctor ID '%s' not found.\n", doc_id);
        return;
    }
    
    printf("\nSchedule for Dr. %s (%s):\n", doctor->name, doctor->specialty);
    printf("%-15s %-15s %-15s %-10s\n", "Appt ID", "Patient ID", "Date", "Time");
    printf("--------------------------------------------------------\n");

    Appointment *current = appointmentList;
    int found = 0;

    // Linked List Traversal (Filtering)
    // We traverse the appointment list, but only print nodes matching the Doctor ID.
    while (current != NULL) {
        if (strcmp(current->doctor_id, doc_id) == 0) {
            printf("%-15s %-15s %-15s %-10s\n", 
                   current->appointment_id, 
                   current->patient_id, 
                   current->date, 
                   current->time);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No appointments found for this doctor.\n");
    }
    printf("--------------------------------------------------------\n");
}


// --- 3. MENU AND MEMORY CLEANUP ---

// Function to display the main navigation menu
void displayMenu() {
    printf("\n============================================\n");
    printf("🏥 Hospital Management System (HMS) Console\n");
    printf("============================================\n");
    printf("1. Register Patient\n");
    printf("2. Add Doctor\n");
    printf("3. Book Appointment\n");
    printf("4. Display All Patients\n");
    printf("5. Display All Doctors\n");
    printf("6. Display Doctor Schedule\n");
    printf("0. Exit System\n");
    printf("--------------------------------------------\n");
    printf("Enter your choice: ");
}

// Cleans up all dynamically allocated memory before program exit
void freeAllMemory() {
    // Standard Linked List Deletion: Freeing each node one by one
    
    Doctor *currentDoc = doctorList;
    Doctor *nextDoc;
    while (currentDoc != NULL) {
        nextDoc = currentDoc->next;
        free(currentDoc);
        currentDoc = nextDoc;
    }

    Patient *currentPat = patientList;
    Patient *nextPat;
    while (currentPat != NULL) {
        nextPat = currentPat->next;
        free(currentPat);
        currentPat = nextPat;
    }

    Appointment *currentAppt = appointmentList;
    Appointment *nextAppt;
    while (currentAppt != NULL) {
        nextAppt = currentAppt->next;
        free(currentAppt);
        currentAppt = nextAppt;
    }

    printf("\nMemory cleanup complete. Exiting system.\n");
}


// --- 4. MAIN PROGRAM ENTRY POINT ---

int main() {
    int choice;

    // The main loop that drives the menu
    do {
        displayMenu();
        // Input validation loop
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear the input buffer to prevent infinite loop on bad input
            while (getchar() != '\n'); 
            choice = -1; 
        } else {
            switch (choice) {
                case 1: registerPatient(); break;
                case 2: addDoctor(); break;
                case 3: bookAppointment(); break;
                case 4: displayPatients(); break;
                case 5: displayDoctors(); break;
                case 6: displayDoctorSchedule(); break;
                case 0: freeAllMemory(); break;
                default: printf("\nInvalid choice. Please try again.\n");
            }
        }
    } while (choice != 0);

    return 0;
}