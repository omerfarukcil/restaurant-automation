#include <iostream>

using namespace std;

struct Menu {
protected:
    static const int menuSize = 5;
    int menuID[menuSize] = { 1, 2, 3, 4, 5 };
    string menuItems[menuSize] = { "Yaglama", "Manti", "Cola", "Water", "Salad" };
    int menuPrices[menuSize] = { 220, 180, 45, 15, 30 };
};

class Order : public Menu {
private:
    int* orderID;
    int* orderQuantity;
    int orderCount;

public:
    friend void showTotalAmount(const Order&);

    Order() {
        orderCount = 0;
        orderID = new int[99];
        orderQuantity = new int[99];

        for (int i = 0; i < 99; i++) {
            orderID[i] = 0;
            orderQuantity[i] = 0;
        }
        cout << "Constructor executed." << endl;
    }

    virtual ~Order() {}

    int getOrderID(int index) const {
        return orderID[index];
    }

    void setOrderID(int index, int id) {
        orderID[index] = id;
    }

    int getOrderQuantity(int index) const {
        return orderQuantity[index];
    }

    void setOrderQuantity(int index, int quantity) {
        orderQuantity[index] = quantity;
    }

    inline void addOrder() {
        char continueOrder;
        int productID, quantity;

        do {
            cout << "\n\tMenu\n" << endl;

            for (int i = 0; i < menuSize; i++) {
                cout << menuID[i] << ". " << menuItems[i] << " - " << menuPrices[i] << " TL" << endl;
            }

            cout << "\nEnter the product ID you want to order: ";
            cin >> productID;

            cout << "Enter quantity: ";
            cin >> quantity;

            if (productID <= menuSize) {
                orderID[orderCount] = productID;
                orderQuantity[orderCount] = quantity;
                orderCount++;

                cout << "Order received!" << endl;
            }
            else {
                cout << "Please enter a valid ID!" << endl;
            }

            cout << "\nDo you want to add another order? (y/n): ";
            cin >> continueOrder;

        } while (continueOrder == 'y' || continueOrder == 'Y');

        if (continueOrder == 'n') {
            cout << "\n\tReturning to main menu...\n";
        }
        else {
            cout << "Invalid input\n";
        }
    }

    void showOrders() {

        if (orderCount == 0) {
            cout << "No orders yet." << endl;
        }

        cout << "\n\tOrders\n " << endl;

        int total = 0;

        for (int i = 0; i < orderCount; i++) {

            int id = orderID[i];
            int quantity = orderQuantity[i];

            for (int j = 0; j < menuSize; j++) {

                if (menuID[j] == id) {

                    int price = menuPrices[j] * quantity;

                    cout << quantity << " " << menuItems[j] << " = " << price << " TL" << endl;

                    total += price;
                }
            }
        }
    }
};

void showTotalAmount(const Order& order) {

    int total = 0;

    for (int i = 0; i < order.orderCount; i++) {

        int id = order.orderID[i];
        int quantity = order.orderQuantity[i];

        for (int j = 0; j < Menu::menuSize; j++) {

            if (order.menuID[j] == id) {

                total += order.menuPrices[j] * quantity;
            }
        }
    }

    cout << "\n\tTotal Amount\n "
        << "\t   " << total << " TL" << endl;
}

int main() {

    setlocale(LC_ALL, "turkish");

    Order order;

    int choice;

    do {

        cout << "\nRestaurant Automation" << endl;
        cout << "1. Add Order" << endl;
        cout << "2. Show Orders" << endl;
        cout << "3. Show Total Amount" << endl;
        cout << "4. Exit" << endl;
        cout << "Your choice: ";

        cin >> choice;

        switch (choice) {

        case 1:
            order.addOrder();
            break;

        case 2:
            order.showOrders();
            break;

        case 3:
            showTotalAmount(order);
            break;

        case 4:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice, try again." << endl;
        }

    } while (choice != 4);

    return 0;
}