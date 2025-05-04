
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 // Structure for a menu item
 typedef struct MenuItem {
     int id;
     char name[50];
     float price;
     struct MenuItem *next;
 } MenuItem;
 
 // Structure for a cart item
 typedef struct CartItem {
     int id;
     char name[50];
     float price;
     int quantity;
     struct CartItem *next;
 } CartItem;
 
 // Function prototypes
 void addMenuItem(MenuItem **head, int id, const char *name, float price);
 void displayMenu(MenuItem *head);
 MenuItem* findMenuItem(MenuItem *head, int id);
 
 void addToCart(CartItem **cart, MenuItem *menu, int id, int quantity);
 void displayCart(CartItem *cart);
 void removeCartItem(CartItem **cart, int id);
 void clearCart(CartItem **cart);
 float calculateTotal(CartItem *cart);
 

 
 // Add a new menu item to the end of the list
 void addMenuItem(MenuItem **head, int id, const char *name, float price) {
     MenuItem *newNode = malloc(sizeof(MenuItem));
     newNode->id = id;
     strcpy(newNode->name, name);
     newNode->price = price;
     newNode->next = NULL;
 
     if (*head == NULL) {
         *head = newNode;
     } else {
         MenuItem *cur = *head;
         while (cur->next)
             cur = cur->next;
         cur->next = newNode;
     }
 }
 
 // Display the restaurant menu
 void displayMenu(MenuItem *head) {
     printf("\n--- MENU ---\n");
     printf("ID   Name                  Price\n");
     printf("-----------------------------------\n");
     MenuItem *cur = head;
     while (cur) {
         printf("%-4d %-20s $%.2f\n", cur->id, cur->name, cur->price);
         cur = cur->next;
     }
 }
 
 // Find a menu item by ID
 MenuItem* findMenuItem(MenuItem *head, int id) {
     MenuItem *cur = head;
     while (cur) {
         if (cur->id == id)
             return cur;
         cur = cur->next;
     }
     return NULL;
 }
 
 // Add an item to the shopping cart
 void addToCart(CartItem **cart, MenuItem *menu, int id, int quantity) {
     MenuItem *item = findMenuItem(menu, id);
     if (!item) {
         printf("Item ID %d not found in menu.\n", id);
         return;
     }
     CartItem *cur = *cart;
     while (cur) {
         if (cur->id == id) {
             cur->quantity += quantity;
             printf("Updated %s quantity to %d in cart.\n", cur->name, cur->quantity);
             return;
         }
         cur = cur->next;
     }
     CartItem *newNode = malloc(sizeof(CartItem));
     newNode->id = id;
     strcpy(newNode->name, item->name);
     newNode->price = item->price;
     newNode->quantity = quantity;
     newNode->next = *cart;
     *cart = newNode;
     printf("Added %d x %s to cart.\n", quantity, item->name);
 }
 
 // Display items in the cart
 void displayCart(CartItem *cart) {
     if (!cart) {
         printf("\nCart is empty.\n");
         return;
     }
     printf("\n--- YOUR CART ---\n");
     printf("ID   Name                  Qty   Subtotal\n");
     printf("----------------------------------------\n");
     CartItem *cur = cart;
     while (cur) {
         printf("%-4d %-20s %-5d $%.2f\n", cur->id, cur->name, cur->quantity, cur->price * cur->quantity);
         cur = cur->next;
     }
 }
 
 // Remove an item from the cart
 void removeCartItem(CartItem **cart, int id) {
     CartItem *cur = *cart, *prev = NULL;
     while (cur) {
         if (cur->id == id) {
             if (prev)
                 prev->next = cur->next;
             else
                 *cart = cur->next;
             printf("Removed %s from cart.\n", cur->name);
             free(cur);
             return;
         }
         prev = cur;
         cur = cur->next;
     }
     printf("Item ID %d not found in cart.\n", id);
 }
 
 // Calculate total amount
 float calculateTotal(CartItem *cart) {
     float total = 0.0;
     CartItem *cur = cart;
     while (cur) {
         total += cur->price * cur->quantity;
         cur = cur->next;
     }
     return total;
 }
 
 // Clear the cart and free memory
 void clearCart(CartItem **cart) {
     CartItem *cur = *cart;
     while (cur) {
         CartItem *tmp = cur;
         cur = cur->next;
         free(tmp);
     }
     *cart = NULL;
 }