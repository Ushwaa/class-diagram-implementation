#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class Product {
public:
    int productID;
    std::string name;
    double price;
    int stock;

    Product(int id, std::string n, double p, int s) : productID(id), name(n), price(p), stock(s) {}

    void display() const {
        std::cout << std::setw(10) << productID << std::setw(20) << name << std::setw(10) << price << std::endl;
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
    std::vector<OrderDetail> orderDetails;

    Order(int id, double amount, const std::vector<OrderDetail>& details) : orderID(id), totalAmount(amount), orderDetails(details) {}

    void display() const {
        std::cout << "Order ID: " << orderID << std::endl;
        std::cout << "Total Amount: " << totalAmount << std::endl;
        std::cout << "Order Details:" << std::endl;
        std::cout << std::setw(10) << "Product ID" << std::setw(20) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Quantity" << std::endl;
        for (const auto& detail : orderDetails) {
            std::cout << std::setw(10) << detail.product.productID << std::setw(20) << detail.product.name << std::setw(10) << detail.product.price << std::setw(10) << detail.quantity << std::endl;
        }
        std::cout << std::endl;
    }
};

class ShoppingCart {
public:
    std::vector<std::pair<Product, int>> items;

    void addItem(const Product& product, int quantity) {
        items.push_back(std::make_pair(product, quantity));
        std::cout << "Product added successfully!" << std::endl;
    }

    void display() const {
        std::cout << std::setw(10) << "Product ID" << std::setw(20) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Quantity" << std::endl;
        for (const auto& item : items) {
            std::cout << std::setw(10) << item.first.productID << std::setw(20) << item.first.name << std::setw(10) << item.first.price << std::setw(10) << item.second << std::endl;
        }
    }

    double getTotalAmount() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.first.price * item.second;
        }
        return total;
    }

    std::vector<OrderDetail> getOrderDetails() const {
        std::vector<OrderDetail> details;
        for (const auto& item : items) {
            details.push_back(OrderDetail(item.first, item.second));
        }
        return details;
    }

    void checkout(std::vector<Order>& orders, int& orderIDCounter) {
        if (items.empty()) {
            std::cout << "Your shopping cart is empty. Nothing to checkout!" << std::endl;
            return;
        }

        double totalAmount = getTotalAmount();
        std::cout << "Total amount: $" << totalAmount << std::endl;

        std::cout << "Order Details:" << std::endl;
        std::cout << std::setw(10) << "Product ID" << std::setw(20) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Quantity" << std::endl;
        for (const auto& item : items) {
            std::cout << std::setw(10) << item.first.productID << std::setw(20) << item.first.name << std::setw(10) << item.first.price << std::setw(10) << item.second << std::endl;
        }

        std::vector<OrderDetail> orderDetails = getOrderDetails();
        orders.push_back(Order(orderIDCounter++, totalAmount, orderDetails));
        items.clear();

        std::cout << "You have successfully checked out the products!" << std::endl;
    }
};

void displayMenu() {
    std::cout << "1. View Products" << std::endl;
    std::cout << "2. View Shopping Cart" << std::endl;
    std::cout << "3. View Orders" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void viewProducts(const std::vector<Product>& products, ShoppingCart& cart) {
    std::cout << std::setw(10) << "Product ID" << std::setw(20) << "Name" << std::setw(10) << "Price" << std::endl;
    for (const auto& product : products) {
        product.display();
    }

    char choice;
    do {
        int productID;
        std::cout << "Enter the ID of the product you want to add to the shopping cart: ";
        std::cin >> productID;

        bool found = false;
        for (const auto& product : products) {
            if (product.productID == productID) {
                int quantity;
                std::cout << "Enter the quantity: ";
                std::cin >> quantity;
                cart.addItem(product, quantity);
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Product ID not found!" << std::endl;
        }

        std::cout << "Do you want to add another product? (Y/N): ";
        std::cin >> choice;
    } while (choice == 'Y' || choice == 'y');
}

void viewShoppingCart(ShoppingCart& cart, std::vector<Order>& orders, int& orderIDCounter) {
    cart.display();

    char choice;
    std::cout << "Do you want to check out all the products? (Y/N): ";
    std::cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        cart.checkout(orders, orderIDCounter);
    }
}

void viewOrders(const std::vector<Order>& orders) {
    if (orders.empty()) {
        std::cout << "No orders found!" << std::endl;
        return;
    }

    for (const auto& order : orders) {
        order.display();
    }
}

int main() {
    std::vector<Product> products = {
        {1, "Paper", 20.0, 100},
        {2, "Pencil", 10.0, 200}
    };

    ShoppingCart cart;
    std::vector<Order> orders;
    int orderIDCounter = 1;

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}