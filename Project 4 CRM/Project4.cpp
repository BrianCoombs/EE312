/* 
 * EE312 Simple CRM Project
 * Nandakumar
 * Brian Coombs
 * bjc2975
 * 10/9/2017
 */

#include <stdio.h>
#include "MyString.h"
#include "Invent.h"
#include <stddef.h>
#include <stdint.h>

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;
Customer store;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */


//clear the inventory and reset the customer database to empty
void reset(void) {
    store.bottles = 0;
    store.diapers = 0;
    store.rattles = 0;
    for(uint32_t i = 0; i < num_customers; i++){
        customers[i].rattles = 0;
        customers[i].bottles = 0;
        customers[i].diapers = 0;
        StringDestroy(&customers[i].name);
    }
    num_customers = 0;
}

Customer* getCust(String name) {
    for(uint32_t i = 0; i < num_customers; i++){
        if (StringIsEqualTo(&name, &customers[i].name)) {
            return customers+i;
        }
    }
    if (num_customers < MAX_CUSTOMERS) {
        Customer* newCust = customers+num_customers;
        String newName = StringDup(&name);
        (*newCust).name = newName;
        (*newCust).bottles = 0;
        (*newCust).diapers = 0;
        (*newCust).rattles = 0;
        num_customers++;
        return newCust;
    } else {
        return 0; // nullptr
    }
}

uint64_t getInv(String type) {
    String bottles = StringCreate("Bottles");
    String diapers = StringCreate("Diapers");
    String rattles = StringCreate("Rattles");
    uint64_t offset;
    if (StringIsEqualTo(&type, &bottles)) {
        offset = offsetof(Customer, bottles);
    }
    else if(StringIsEqualTo(&type, &diapers)){
        offset = offsetof(Customer, diapers);
    }
    else if(StringIsEqualTo(&type, &rattles)){
        offset = offsetof(Customer, rattles);
    }
    else{
        offset = -1; //If item not in inventory, return -1
    }
    StringDestroy(&bottles);
    StringDestroy(&diapers);
    StringDestroy(&rattles);
    return (offset+3)/4;
}

void processSummarize() {
    printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", store.bottles,
           store.diapers, store.rattles);
    printf("we have had a total of %d different customers\n", num_customers);
    Customer bCust = customers[0];          //Defined as customers to make respective values accessible like name later
    Customer dCust = customers[0];
    Customer rCust = customers[0];
    int i;
    for(i = 1; i < num_customers; i++){
        if(customers[i].bottles > bCust.bottles){
            bCust = customers[i];
        }
        if(customers[i].diapers > dCust.diapers){
            dCust = customers[i];
        }
        if(customers[i].rattles > rCust.rattles){
            rCust = customers[i];
        }

    }

    if(bCust.bottles > 0){
        StringPrint(&(bCust.name));
        printf(" has purchased the most Bottles (%d)\n", bCust.bottles);
    }
    else{
        printf("no one has purchased any Bottles\n");
    }
    if(dCust.diapers > 0){
        StringPrint(&(dCust.name));
        printf(" has purchased the most Diapers (%d)\n", dCust.diapers);
    }
    else{
        printf("no one has purchased any Diapers\n");
    }
    if(rCust.rattles > 0){
        StringPrint(&(rCust.name));
        printf(" has purchased the most Rattles (%d)\n", rCust.rattles);
    }
    else{
        printf("no one has purchased any Rattles\n");
    }
}

void processPurchase() {
    String cust, prod;
    int num;
    readString(&cust);
    readString(&prod);
    readNum(&num);

    uint64_t offset = getInv(prod);
    if (offset != -1) { //Check that item requested is in inventory
        if (num > 0) { //Check if customer actually providing any items at all
            int* inv = (int *)(&store)+offset;
            if (num <= *inv) {
                Customer* custPtr = getCust(cust);
                if (custPtr != 0) { //Make sure not exceeding max customers
                    int* customer = (int *)(custPtr)+offset;
                    *inv -= num;
                    *customer += num;
                }
            } else {
                printf("Sorry ");
                StringPrint(&cust);
                printf(", we only have %d ", *inv);
                StringPrint(&prod);
                printf("\n");
            }
        }
    }
    StringDestroy(&cust);
    StringDestroy(&prod);
}


void processInventory() {
    String prod;
    int num;
    readString(&prod);
    readNum(&num);

    uint64_t offset = getInv(prod);
    if (offset != -1) {
        int* inv = (int *)(&store)+offset;
        *inv += num;
    }
    StringDestroy(&prod);
}
