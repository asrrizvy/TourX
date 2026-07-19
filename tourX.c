#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_PACKAGES 50

// Structure for Multi-Level Authentication
typedef struct {
    char username[50];
    char password[50];
    int isAdmin; // 1 for Admin, 0 for Regular User
} User;

// Structure for Advanced Multi-Criteria Search (Rizvy's Module)
typedef struct {
    int id;
    char destination[100];
    char region[50];
    double budget;
    char transport[50];
    int duration;
} TourPackage;

// NEW: Structure for Group Member Details
typedef struct {
    char name[100];
    int age;
    char nid[20];
} Member;

// Global Arrays and Counters
User users[MAX_USERS];
int userCount = 0;
TourPackage packages[MAX_PACKAGES];
int packageCount = 0;

// Function Declarations
void loadUsers();
void loadPackages();
int authenticateUser(char *username, char *password, int *isAdmin);
void registerUser();
void runAdminPanel();
void runUserPanel();
void advancedSearch();
void bookTour(); // NEW: Booking Function
void trimNewline(char *str);

int main() {
    loadUsers();
    loadPackages();

    int choice;
    char username[50], password[50];
    int isAdmin = 0;

    while (1) {
        printf("\n==================================================\n");
        printf("       TOURX - TRAVEL MANAGEMENT SYSTEM         \n");
        printf("==================================================\n");
        printf(" [1] Login to Account\n");
        printf(" [2] Register New Account\n");
        printf(" [3] Exit System\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            getchar();
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("\n>>> LOGIN SCREEN <<<\n");
                printf("Enter Username: ");
                fgets(username, sizeof(username), stdin);
                trimNewline(username);

                printf("Enter Password: ");
                fgets(password, sizeof(password), stdin);
                trimNewline(password);

                if (authenticateUser(username, password, &isAdmin)) {
                    printf("\n[SUCCESS] Welcome back, %s!\n", username);
                    if (isAdmin) {
                        runAdminPanel();
                    } else {
                        runUserPanel();
                    }
                } else {
                    printf("\n[ERROR] Invalid username or password.\n");
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("\nExiting system. Thank you for using TourX!\n");
                exit(0);
            default:
                printf("\n[ERROR] Invalid option. Please choice between 1 and 3.\n");
        }
    }
    return 0;
}

void trimNewline(char *str) {
    unsigned long len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r' || str[len - 1] == ' ')) {
        str[len - 1] = '\0';
        len--;
    }
}

// --- FEATURE 1: MULTI-LEVEL AUTHENTICATION LOGIC ---
void loadUsers() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        file = fopen("users.txt", "w");
        if (file != NULL) {
            fprintf(file, "admin admin123 1\n");
            fprintf(file, "rizvy cse56 0\n");
            fclose(file);
        }
        userCount = 0;
        loadUsers();
        return;
    }

    userCount = 0;
    while (fscanf(file, "%s %s %d", users[userCount].username, users[userCount].password, &users[userCount].isAdmin) != EOF) {
        userCount++;
        if (userCount >= MAX_USERS) break;
    }
    fclose(file);
}

int authenticateUser(char *username, char *password, int *isAdmin) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            *isAdmin = users[i].isAdmin;
            return 1;
        }
    }
    return 0;
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("\n[ERROR] System storage full.\n");
        return;
    }

    User newUser;
    printf("\n>>> ACCOUNT REGISTRATION <<<\n");
    printf("Create Username: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    trimNewline(newUser.username);

    printf("Create Password: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    trimNewline(newUser.password);

    newUser.isAdmin = 0;

    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("\n[ERROR] File system error.\n");
        return;
    }
    fprintf(file, "%s %s %d\n", newUser.username, newUser.password, newUser.isAdmin);
    fclose(file);

    users[userCount++] = newUser;
    printf("\n[SUCCESS] Registration complete! You can now login.\n");
}

// --- FEATURE 2: ADVANCED MULTI-CRITERIA SEARCH (Rizvy's Module) ---
void loadPackages() {
    FILE *file = fopen("packages.txt", "r");
    if (file == NULL) {
        file = fopen("packages.txt", "w");
        if (file != NULL) {
            fprintf(file, "101 Coxs_Bazar Coastal 5000.00 Bus 3\n");
            fprintf(file, "102 Sreemangal Sylhet 4500.00 Train 4\n");
            fprintf(file, "103 Sajek_Valley Hill_Tracts 8000.00 Bus 3\n");
            fprintf(file, "104 Sundarbans Mangrove 12000.00 Ship 5\n");
            fprintf(file, "105 Saint_Martin Coastal 15000.00 Air 2\n");
            fprintf(file, "106 Jaflong Sylhet 3500.00 Bus 2\n");
            fprintf(file, "107 Rangamati Hill_Tracts 6000.00 Train 3\n");
            fclose(file);
        }
        packageCount = 0;
        loadPackages();
        return;
    }

    packageCount = 0;
    while (fscanf(file, "%d %s %s %lf %s %d",
                  &packages[packageCount].id,
                  packages[packageCount].destination,
                  packages[packageCount].region,
                  &packages[packageCount].budget,
                  packages[packageCount].transport,
                  &packages[packageCount].duration) != EOF) {
        packageCount++;
        if (packageCount >= MAX_PACKAGES) break;
    }
    fclose(file);
}

void advancedSearch() {
    int regionChoice;
    char targetRegion[50] = "";
    double maxBudget;
    char prefTransport[50];
    int maxDuration;
    int matchesFound = 0;

    printf("\n==================================================\n");
    printf("         ADVANCED TOUR SEARCH ENGINE            \n");
    printf("==================================================\n");

    printf("Select Your Desired Destination Region:\n");
    printf(" [1] Coastal Zone (Cox's Bazar, Saint Martin)\n");
    printf(" [2] Sylhet Region (Sreemangal, Jaflong)\n");
    printf(" [3] Chittagong Hill Tracts (Sajek, Rangamati)\n");
    printf(" [4] Mangrove & Heritage (Sundarbans)\n");
    printf("--------------------------------------------------\n");
    printf("Enter Region Choice (1-4): ");
    if (scanf("%d", &regionChoice) != 1) {
        getchar();
        printf("[ERROR] Invalid choice.\n");
        return;
    }
    getchar();

    switch(regionChoice) {
        case 1: strcpy(targetRegion, "Coastal"); break;
        case 2: strcpy(targetRegion, "Sylhet"); break;
        case 3: strcpy(targetRegion, "Hill_Tracts"); break;
        case 4: strcpy(targetRegion, "Mangrove"); break;
        default:
            printf("[ERROR] Invalid region selection.\n");
            return;
    }

    printf("Enter Maximum Budget (BDT): ");
    if (scanf("%lf", &maxBudget) != 1) {
        getchar();
        printf("[ERROR] Invalid budget input.\n");
        return;
    }
    getchar();

    printf("Enter Preferred Transport (Bus/Train/Air/Ship): ");
    fgets(prefTransport, sizeof(prefTransport), stdin);
    trimNewline(prefTransport);

    printf("Enter Maximum Duration (Days): ");
    if (scanf("%d", &maxDuration) != 1) {
        getchar();
        printf("[ERROR] Invalid duration input.\n");
        return;
    }
    getchar();

    printf("\n==================== SEARCH RESULTS ====================\n");
    printf("| %-6s | %-15s | %-9s | %-9s | %-8s |\n", "ID", "Destination", "Budget", "Transport", "Duration");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < packageCount; i++) {
        if (strcmp(packages[i].region, targetRegion) == 0 &&
            packages[i].budget <= maxBudget &&
            strcasecmp(packages[i].transport, prefTransport) == 0 &&
            packages[i].duration <= maxDuration) {

            printf("| %-6d | %-15s | %-9.2f | %-9s | %-3d Days |\n",
                   packages[i].id,
                   packages[i].destination,
                   packages[i].budget,
                   packages[i].transport,
                   packages[i].duration);
            matchesFound++;
        }
    }
    printf("========================================================\n");

    if (matchesFound == 0) {
        printf(" [INFO] No available packages match your criteria in this region.\n");
    } else {
        printf(" Total matching packages found: %d\n", matchesFound);
    }
    printf("========================================================\n");
}

// --- NEW FEATURE: GROUP TOUR BOOKING ENGINE ---
void bookTour() {
    char groupId[30];
    int numMembers;

    printf("\n========== BOOK TOUR ==========\n");
    printf("Enter Group ID : ");
    fgets(groupId, sizeof(groupId), stdin);
    trimNewline(groupId);

    printf("Number of Members : ");
    if (scanf("%d", &numMembers) != 1 || numMembers <= 0) {
        getchar();
        printf("[ERROR] Invalid number of members.\n");
        return;
    }
    getchar(); // Clear layout buffer

    // Memory Allocation for structural dynamic inputs
    Member *members = (Member *)malloc(numMembers * sizeof(Member));
    if (members == NULL) {
        printf("[ERROR] Memory allocation failed.\n");
        return;
    }

    // Dynamic Loop for capturing member inputs sequentially
    for (int i = 0; i < numMembers; i++) {
        printf("\nMember %d\n", i + 1);
        printf("Name : ");
        fgets(members[i].name, sizeof(members[i].name), stdin);
        trimNewline(members[i].name);

        printf("Age : ");
        if (scanf("%d", &members[i].age) != 1) {
            members[i].age = 0;
        }
        getchar();

        printf("NID : ");
        fgets(members[i].nid, sizeof(members[i].nid), stdin);
        trimNewline(members[i].nid);
    }

    // Back-end File Handling: Save records directly to bookings.txt
    FILE *file = fopen("bookings.txt", "a");
    if (file == NULL) {
        printf("\n[ERROR] Failed to open database file for booking.\n");
        free(members);
        return;
    }

    fprintf(file, "Group_ID: %s | Total_Members: %d\n", groupId, numMembers);
    for (int i = 0; i < numMembers; i++) {
        fprintf(file, "  -> Member %d: Name: %s, Age: %d, NID: %s\n",
                i + 1, members[i].name, members[i].age, members[i].nid);
    }
    fprintf(file, "--------------------------------------------------\n");
    fclose(file);

    free(members); // Deallocate structural buffer memory
    printf("\nBooking Successful.\n");
}

// --- NAVIGATION MENUS ---
void runAdminPanel() {
    int choice;
    while (1) {
        printf("\n---> ADMIN PANEL <---\n");
        printf("1. View Revenue Summary (Sprint 2)\n");
        printf("2. Manage Travel Packages (Sprint 2)\n");
        printf("3. Logout\n");
        printf("Enter option: ");
        if (scanf("%d", &choice) != 1) { getchar(); continue; }

        if (choice == 3) break;
        else printf("\n[INFO] Implemented in the next phase.\n");
    }
}

void runUserPanel() {
    int choice;
    while (1) {
        printf("\n---> USER DASHBOARD <---\n");
        printf("1. Search Tour Packages (Multi-Criteria)\n");
        printf("2. Book a Tour (New Feature!)\n");
        printf("3. Logout\n");
        printf("Enter option: ");
        if (scanf("%d", &choice) != 1) { getchar(); continue; }
        getchar(); // Clear buffer

        if (choice == 1) {
            advancedSearch();
        } else if (choice == 2) {
            bookTour(); // Call the newly added features block
        } else if (choice == 3) {
            break;
        } else {
            printf("\n[INFO] Implemented in the next phase.\n");
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_PACKAGES 50

// Structure for Multi-Level Authentication
typedef struct {
    char username[50];
    char password[50];
    int isAdmin; // 1 for Admin, 0 for Regular User
} User;

// Structure for Advanced Multi-Criteria Search (Rizvy's Module)
typedef struct {
    int id;
    char destination[100];
    char region[50];
    double budget;
    char transport[50];
    int duration;
} TourPackage;

// NEW: Structure for Group Member Details
typedef struct {
    char name[100];
    int age;
    char nid[20];
} Member;

// Global Arrays and Counters
User users[MAX_USERS];
int userCount = 0;
TourPackage packages[MAX_PACKAGES];
int packageCount = 0;

// Function Declarations
void loadUsers();
void loadPackages();
int authenticateUser(char *username, char *password, int *isAdmin);
void registerUser();
void runAdminPanel();
void runUserPanel();
void advancedSearch();
void bookTour(); // NEW: Booking Function
void trimNewline(char *str);

int main() {
    loadUsers();
    loadPackages();

    int choice;
    char username[50], password[50];
    int isAdmin = 0;

    while (1) {
        printf("\n==================================================\n");
        printf("       TOURX - TRAVEL MANAGEMENT SYSTEM         \n");
        printf("==================================================\n");
        printf(" [1] Login to Account\n");
        printf(" [2] Register New Account\n");
        printf(" [3] Exit System\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            getchar();
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("\n>>> LOGIN SCREEN <<<\n");
                printf("Enter Username: ");
                fgets(username, sizeof(username), stdin);
                trimNewline(username);

                printf("Enter Password: ");
                fgets(password, sizeof(password), stdin);
                trimNewline(password);

                if (authenticateUser(username, password, &isAdmin)) {
                    printf("\n[SUCCESS] Welcome back, %s!\n", username);
                    if (isAdmin) {
                        runAdminPanel();
                    } else {
                        runUserPanel();
                    }
                } else {
                    printf("\n[ERROR] Invalid username or password.\n");
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("\nExiting system. Thank you for using TourX!\n");
                exit(0);
            default:
                printf("\n[ERROR] Invalid option. Please choice between 1 and 3.\n");
        }
    }
    return 0;
}

void trimNewline(char *str) {
    unsigned long len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r' || str[len - 1] == ' ')) {
        str[len - 1] = '\0';
        len--;
    }
}

// --- FEATURE 1: MULTI-LEVEL AUTHENTICATION LOGIC ---
void loadUsers() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        file = fopen("users.txt", "w");
        if (file != NULL) {
            fprintf(file, "admin admin123 1\n");
            fprintf(file, "rizvy cse56 0\n");
            fclose(file);
        }
        userCount = 0;
        loadUsers();
        return;
    }

    userCount = 0;
    while (fscanf(file, "%s %s %d", users[userCount].username, users[userCount].password, &users[userCount].isAdmin) != EOF) {
        userCount++;
        if (userCount >= MAX_USERS) break;
    }
    fclose(file);
}

int authenticateUser(char *username, char *password, int *isAdmin) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            *isAdmin = users[i].isAdmin;
            return 1;
        }
    }
    return 0;
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("\n[ERROR] System storage full.\n");
        return;
    }

    User newUser;
    printf("\n>>> ACCOUNT REGISTRATION <<<\n");
    printf("Create Username: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    trimNewline(newUser.username);

    printf("Create Password: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    trimNewline(newUser.password);

    newUser.isAdmin = 0;

    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("\n[ERROR] File system error.\n");
        return;
    }
    fprintf(file, "%s %s %d\n", newUser.username, newUser.password, newUser.isAdmin);
    fclose(file);

    users[userCount++] = newUser;
    printf("\n[SUCCESS] Registration complete! You can now login.\n");
}

// --- FEATURE 2: ADVANCED MULTI-CRITERIA SEARCH (Rizvy's Module) ---
void loadPackages() {
    FILE *file = fopen("packages.txt", "r");
    if (file == NULL) {
        file = fopen("packages.txt", "w");
        if (file != NULL) {
            fprintf(file, "101 Coxs_Bazar Coastal 5000.00 Bus 3\n");
            fprintf(file, "102 Sreemangal Sylhet 4500.00 Train 4\n");
            fprintf(file, "103 Sajek_Valley Hill_Tracts 8000.00 Bus 3\n");
            fprintf(file, "104 Sundarbans Mangrove 12000.00 Ship 5\n");
            fprintf(file, "105 Saint_Martin Coastal 15000.00 Air 2\n");
            fprintf(file, "106 Jaflong Sylhet 3500.00 Bus 2\n");
            fprintf(file, "107 Rangamati Hill_Tracts 6000.00 Train 3\n");
            fclose(file);
        }
        packageCount = 0;
        loadPackages();
        return;
    }

    packageCount = 0;
    while (fscanf(file, "%d %s %s %lf %s %d",
                  &packages[packageCount].id,
                  packages[packageCount].destination,
                  packages[packageCount].region,
                  &packages[packageCount].budget,
                  packages[packageCount].transport,
                  &packages[packageCount].duration) != EOF) {
        packageCount++;
        if (packageCount >= MAX_PACKAGES) break;
    }
    fclose(file);
}

void advancedSearch() {
    int regionChoice;
    char targetRegion[50] = "";
    double maxBudget;
    char prefTransport[50];
    int maxDuration;
    int matchesFound = 0;

    printf("\n==================================================\n");
    printf("         ADVANCED TOUR SEARCH ENGINE            \n");
    printf("==================================================\n");

    printf("Select Your Desired Destination Region:\n");
    printf(" [1] Coastal Zone (Cox's Bazar, Saint Martin)\n");
    printf(" [2] Sylhet Region (Sreemangal, Jaflong)\n");
    printf(" [3] Chittagong Hill Tracts (Sajek, Rangamati)\n");
    printf(" [4] Mangrove & Heritage (Sundarbans)\n");
    printf("--------------------------------------------------\n");
    printf("Enter Region Choice (1-4): ");
    if (scanf("%d", &regionChoice) != 1) {
        getchar();
        printf("[ERROR] Invalid choice.\n");
        return;
    }
    getchar();

    switch(regionChoice) {
        case 1: strcpy(targetRegion, "Coastal"); break;
        case 2: strcpy(targetRegion, "Sylhet"); break;
        case 3: strcpy(targetRegion, "Hill_Tracts"); break;
        case 4: strcpy(targetRegion, "Mangrove"); break;
        default:
            printf("[ERROR] Invalid region selection.\n");
            return;
    }

    printf("Enter Maximum Budget (BDT): ");
    if (scanf("%lf", &maxBudget) != 1) {
        getchar();
        printf("[ERROR] Invalid budget input.\n");
        return;
    }
    getchar();

    printf("Enter Preferred Transport (Bus/Train/Air/Ship): ");
    fgets(prefTransport, sizeof(prefTransport), stdin);
    trimNewline(prefTransport);

    printf("Enter Maximum Duration (Days): ");
    if (scanf("%d", &maxDuration) != 1) {
        getchar();
        printf("[ERROR] Invalid duration input.\n");
        return;
    }
    getchar();

    printf("\n==================== SEARCH RESULTS ====================\n");
    printf("| %-6s | %-15s | %-9s | %-9s | %-8s |\n", "ID", "Destination", "Budget", "Transport", "Duration");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < packageCount; i++) {
        if (strcmp(packages[i].region, targetRegion) == 0 &&
            packages[i].budget <= maxBudget &&
            strcasecmp(packages[i].transport, prefTransport) == 0 &&
            packages[i].duration <= maxDuration) {

            printf("| %-6d | %-15s | %-9.2f | %-9s | %-3d Days |\n",
                   packages[i].id,
                   packages[i].destination,
                   packages[i].budget,
                   packages[i].transport,
                   packages[i].duration);
            matchesFound++;
        }
    }
    printf("========================================================\n");

    if (matchesFound == 0) {
        printf(" [INFO] No available packages match your criteria in this region.\n");
    } else {
        printf(" Total matching packages found: %d\n", matchesFound);
    }
    printf("========================================================\n");
}

// --- NEW FEATURE: GROUP TOUR BOOKING ENGINE ---
void bookTour() {
    char groupId[30];
    int numMembers;

    printf("\n========== BOOK TOUR ==========\n");
    printf("Enter Group ID : ");
    fgets(groupId, sizeof(groupId), stdin);
    trimNewline(groupId);

    printf("Number of Members : ");
    if (scanf("%d", &numMembers) != 1 || numMembers <= 0) {
        getchar();
        printf("[ERROR] Invalid number of members.\n");
        return;
    }
    getchar(); // Clear layout buffer

    // Memory Allocation for structural dynamic inputs
    Member *members = (Member *)malloc(numMembers * sizeof(Member));
    if (members == NULL) {
        printf("[ERROR] Memory allocation failed.\n");
        return;
    }

    // Dynamic Loop for capturing member inputs sequentially
    for (int i = 0; i < numMembers; i++) {
        printf("\nMember %d\n", i + 1);
        printf("Name : ");
        fgets(members[i].name, sizeof(members[i].name), stdin);
        trimNewline(members[i].name);

        printf("Age : ");
        if (scanf("%d", &members[i].age) != 1) {
            members[i].age = 0;
        }
        getchar();

        printf("NID : ");
        fgets(members[i].nid, sizeof(members[i].nid), stdin);
        trimNewline(members[i].nid);
    }

    // Back-end File Handling: Save records directly to bookings.txt
    FILE *file = fopen("bookings.txt", "a");
    if (file == NULL) {
        printf("\n[ERROR] Failed to open database file for booking.\n");
        free(members);
        return;
    }

    fprintf(file, "Group_ID: %s | Total_Members: %d\n", groupId, numMembers);
    for (int i = 0; i < numMembers; i++) {
        fprintf(file, "  -> Member %d: Name: %s, Age: %d, NID: %s\n",
                i + 1, members[i].name, members[i].age, members[i].nid);
    }
    fprintf(file, "--------------------------------------------------\n");
    fclose(file);

    free(members); // Deallocate structural buffer memory
    printf("\nBooking Successful.\n");
}

// --- NAVIGATION MENUS ---
void runAdminPanel() {
    int choice;
    while (1) {
        printf("\n---> ADMIN PANEL <---\n");
        printf("1. View Revenue Summary (Sprint 2)\n");
        printf("2. Manage Travel Packages (Sprint 2)\n");
        printf("3. Logout\n");
        printf("Enter option: ");
        if (scanf("%d", &choice) != 1) { getchar(); continue; }

        if (choice == 3) break;
        else printf("\n[INFO] Implemented in the next phase.\n");
    }
}

void runUserPanel() {
    int choice;
    while (1) {
        printf("\n---> USER DASHBOARD <---\n");
        printf("1. Search Tour Packages (Multi-Criteria)\n");
        printf("2. Book a Tour (New Feature!)\n");
        printf("3. Logout\n");
        printf("Enter option: ");
        if (scanf("%d", &choice) != 1) { getchar(); continue; }
        getchar(); // Clear buffer

        if (choice == 1) {
            advancedSearch();
        } else if (choice == 2) {
            bookTour(); // Call the newly added features block
        } else if (choice == 3) {
            break;
        } else {
            printf("\n[INFO] Implemented in the next phase.\n");
        }
    }
}
