#include <stdio.h>
#include <stdlib.h>
#include "user_management.c"
#include "Menu.c"
#include "OT_PS.c"


void runOrderingSystem() {
    MenuItem *menu = NULL;
    CartItem *cart = NULL;
    int choice, id, qty;
    float total;

    // Initialize menu
    addMenuItem(&menu, 1, "Margherita Pizza", 8.99);
    addMenuItem(&menu, 2, "Veggie Burger", 6.49);
    addMenuItem(&menu, 3, "Caesar Salad", 5.99);
    addMenuItem(&menu, 4, "Spaghetti Bolognese", 9.49);
    addMenuItem(&menu, 5, "Grilled Chicken", 11.99);
    addMenuItem(&menu, 6, "Tandoori Chicken", 12.49);
    addMenuItem(&menu, 7, "Paneer Tikka", 7.99);
    addMenuItem(&menu, 8, "Chicken Biryani", 10.99);
    addMenuItem(&menu, 9, "Butter Naan", 1.49);
    addMenuItem(&menu, 10, "Mango Lassi", 2.99);

    do {
        printf("\n=== Food Ordering Menu ===\n");
        printf("1. View Menu\n");
        printf("2. Add to Cart\n");
        printf("3. View Cart\n");
        printf("4. Remove from Cart\n");
        printf("5. Checkout\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                displayMenu(menu);
                break;
            case 2:
                displayMenu(menu);
                printf("Enter item ID: ");
                scanf("%d", &id);
                printf("Enter quantity: ");
                scanf("%d", &qty);
                addToCart(&cart, menu, id, qty);
                break;
            case 3:
                displayCart(cart);
                break;
            case 4:
                displayCart(cart);
                printf("Enter item ID to remove: ");
                scanf("%d", &id);
                removeCartItem(&cart, id);
                break;
            case 5:
                displayCart(cart);
                total = calculateTotal(cart);
                printf("\nTotal: $%.2f\n", total);
                simulatePayment();
                trackOrder();
                clearCart(&cart);
                break;
            case 6:
                printf("Exiting order system.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 6);

    // Clean up memory
    MenuItem *tmp;
    while (menu) {
        tmp = menu;
        menu = menu->next;
        free(tmp);
    }
}

int main() {
    int authChoice, loginStatus = 0;
    do {
        printf("\n--- Welcome to Food Delivery System ---\n");
        printf("1. Register\n2. Login\n3. Forgot Password\n4. Change Password\n5. Exit\nEnter your choice: ");
        scanf("%d", &authChoice);
        getchar();

        switch(authChoice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginStatus = loginUser();
                if (loginStatus)
                    runOrderingSystem();
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                changePassword();
                break;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (authChoice != 5);

    return 0;
}
