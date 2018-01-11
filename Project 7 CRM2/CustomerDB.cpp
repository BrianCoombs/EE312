/*
 * Name: Brian Coombs
 * EID: bjc2975
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
    Customer* c = new Customer("name");
}

int CustomerDB::size(void) {
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

//Returns a customer object
Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}
/*
 * Returns a customer based on an input name, and creates the customer if they're not already in the DB
 * Uses amortized doubling with a new array to resize
 * @param name The name of the customer to be found or created
 * @return The location of the of the customer
*/
Customer& CustomerDB::operator[](String name) {
    if (isMember(name)) {
        // Find cust with name
        for (int k = 0; k < this->length; k++) {
            if (this->data[k].name == name) {
                return this->data[k];
            }
        }
    } else {
        // Reached max capacity, then double size of data array
        if (this->length + 1 == this->capacity) {
            // New array
            Customer* newData = new Customer[capacity * 2];
            for (int k = 0; k < this->length; k++) {
                newData[k] = this->data[k];
            }
            // Clear out old array after transfered
            delete[] this->data;
            // Add customer to new array
            newData[length] = Customer(name);
            // Transfer new array into database
            this->data = newData;
            this->capacity *= 2;
        } else {
            // If no need to amortized double then just add the customer
            this->data[length] = Customer(name);
        }
        this->length++;
        return this->data[length - 1];
    }
}



bool CustomerDB::isMember(String name) {
    // Iterate through data
    for (int i = 0; i < this->length; i++) {
        // If name is same then return
        if (this->data[i].name == name) {
            return true;
        }
    }
    return false;
}


