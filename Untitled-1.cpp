#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Product {
public:
    int productID;
    string name;
    double price;
    int stock;

    Product(int id, string n, double p, int s) : productID(id), name(n), price(p), stock(s) {}

    void display() const {
        cout << setw(10) << productID << setw(20) << name << setw(10) << price << endl;
    }
};

class OrderDetail {
public:
    Product product;
    int quantity;

    OrderDetail(const Product& p, int qty) : product(p), quantity(qty) {}
};

class Order {
public:
    int orderID;
    double totalAmount;
    vector<OrderDetail> orderDetails;

    Order(int id, double amount, const vector<OrderDetail>& details) : orderID(id), totalAmount(amount), orderDetails(details) {}

    void display() const {
        cout << "Order ID: " << orderID << endl;
        cout << "Total Amount: " << totalAmount << endl;
        cout << "Order Details:" << endl;
        cout << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (const auto& detail : orderDetails) {
            cout << setw(10) << detail.product.productID << setw(20) << detail.product.name << setw(10) << detail.product.price << setw(10) << detail.quantity << endl;
        }
        cout << endl;
    }
};

class ShoppingCart {
public:
    vector<pair<Product, int>> items;

    void addItem(const Product& product, int quantity) {
        items.push_back(make_pair(product, quantity));
        cout << "Product added successfully!" << endl;
    }

    void display() const {
        cout << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (const auto& item : items) {
            cout << setw(10) << item.first.productID << setw(20) << item.first.name << setw(10) << item.first.price << setw(10) << item.second << endl;
        }
    }

    double getTotalAmount() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.first.price * item.second;
        }
        return total;
    }

    vector<OrderDetail> getOrderDetails() const {
        vector<OrderDetail> details;
        for (const auto& item : items) {
            details.push_back(OrderDetail(item.first, item.second));
        }
        return details;
    }

    void checkout(vector<Order>& orders, int& orderIDCounter) {
        if (items.empty()) {
            cout << "Your shopping cart is empty. Nothing to checkout!" << endl;
            return;
        }

        double totalAmount = getTotalAmount();
        cout << "Total amount: $" << totalAmount << endl;

        cout << "Order Details:" << endl;
        cout << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (const auto& item : items) {
            cout << setw(10) << item.first.productID << setw(20) << item.first.name << setw(10) << item.first.price << setw(10) << item.second << endl;
        }

        vector<OrderDetail> orderDetails = getOrderDetails();
        orders.push_back(Order(orderIDCounter++, totalAmount, orderDetails));
        items.clear();

        cout << "You have successfully checked out the products!" << endl;
    }
};

void displayMenu() {
    cout << "1. View Products" << endl;
    cout << "2. View Shopping Cart" << endl;
    cout << "3. View Orders" << endl;
    cout << "4. Exit" << endl;
}

void viewProducts(const vector<Product>& products, ShoppingCart& cart) {
    cout << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << endl;
    for (const auto& product : products) {
        product.display();
    }

    char choice;
    do {
        int productID;
        cout << "Enter the ID of the product you want to add to the shopping cart: ";
        while (!(cin >> productID)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Invalid input. Please enter a valid product ID: ";
        }

        bool found = false;
        for (const auto& product : products) {
            if (product.productID == productID) {
                int quantity;
                cout << "Enter the quantity: ";
                while (!(cin >> quantity)) {
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "Invalid input. Please enter a valid quantity: ";
                }
                cart.addItem(product, quantity);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Product ID not found!" << endl;
        }

        cout << "Do you want to add another product? (Y/N): ";
        cin >> choice;
        while (cin.get() != '\n');
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
            cout << "Invalid input. Please enter a valid choice (Y/N): ";
            cin >> choice;
            while (cin.get() != '\n');
        }
    } while (choice == 'Y' || choice == 'y');
}

void viewShoppingCart(ShoppingCart& cart, vector<Order>& orders, int& orderIDCounter) {
    cart.display();

    char choice;
    cout << "Do you want to check out all the products? (Y/N): ";
    cin >> choice;
    while (cin.get() != '\n');

    if (choice == 'Y' || choice == 'y') {
        cart.checkout(orders, orderIDCounter);
    }
}

void viewOrders(const vector<Order>& orders) {
    if (orders.empty()) {
        cout << "No orders found!" << endl;
        return;
    }

    for (const auto& order : orders) {
        order.display();
    }
}

int main() {
    vector<Product> products = {
        {1, "Paper", 20.0, 100},
        {2, "Pencil", 10.0, 200}
    };

    ShoppingCart cart;
    vector<Order> orders;
    int orderIDCounter = 1;

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Invalid input. Please enter a valid choice: ";
        }

        switch (choice) {
            case 1:
                viewProducts(products, cart);
                break;
            case 2:
                viewShoppingCart(cart, orders, orderIDCounter);
                break;
            case 3:
                viewOrders(orders);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}