package com.example.lab7;

public class Bank {

    private int totalCash;

    public Bank(int totalCash) {
        this.totalCash = totalCash;
    }

    public synchronized void withdrawCash(int amount, String threadName) {
        if (totalCash >= amount) {
            totalCash -= amount;
            System.out.println(threadName + " withdrew $" + amount + ". Remaining cash: $" + totalCash);
        } else {
            System.out.println(threadName + " tried to withdraw $" + amount + " but insufficient funds.");
        }
    }

    public synchronized void depositCash(int amount, String threadName) {
        totalCash += amount;
        System.out.println(threadName + " deposited $" + amount + ". Total cash: $" + totalCash);
    }
}
