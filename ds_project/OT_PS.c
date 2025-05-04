#include <stdio.h>
#include <string.h>

// Enum for order statuses
typedef enum {
    PREPARING,
    ON_THE_WAY,
    DELIVERED
} OrderStatus;

// Function to get status as a string
const char* getStatusText(OrderStatus status) {
    switch(status) {
        case PREPARING: return "Preparing";
        case ON_THE_WAY: return "On the way";
        case DELIVERED: return "Delivered";
        default: return "Unknown";
    }
}

// Function to simulate payment process
void simulatePayment() {
    int paymentMethod;
    printf("\nChoose Payment Method:\n");
    printf("1. Cash on Delivery\n");
    printf("2. Card Payment\n");
    printf("Enter your choice: ");
    scanf("%d", &paymentMethod);

    if (paymentMethod == 1) {
        printf("You selected: Cash on Delivery.\n");
        printf("Payment will be collected upon delivery.\n");
    } else if (paymentMethod == 2) {
        char cardNumber[20];
        char cardHolder[50];
        int cvv;

        printf("You selected: Card Payment.\n");
        printf("Enter Card Holder Name: ");
        scanf(" %[^\n]", cardHolder);
        printf("Enter Card Number: ");
        scanf("%s", cardNumber);
        printf("Enter CVV: ");
        scanf("%d", &cvv);

        printf("Processing payment...\n");
        printf("Payment successful! Thank you, %s.\n", cardHolder);
    } else {
        printf("Invalid payment option.\n");
        return;
    }

    printf("Order placed successfully!\n");
}

// Function to simulate order tracking
void trackOrder() {
    OrderStatus status = PREPARING;
    int choice;

    while (status != DELIVERED) {
        printf("\nCurrent Order Status: %s\n", getStatusText(status));
        printf("1. Update Status\n");
        printf("2. Exit Tracking\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (status < DELIVERED) {
                status++;
                printf("Status updated to: %s\n", getStatusText(status));
            } else {
                printf("Order already delivered.\n");
            }
        } else if (choice == 2) {
            break;
        } else {
            printf("Invalid input. Try again.\n");
        }
    }

    if (status == DELIVERED) {
        printf("Your order has been delivered. Enjoy your meal!\n");
    }
}


