package com.example.lab7;

public class ClientThread extends Thread {

    private final Bank bank;

    public ClientThread(String name, Bank bank) {
        super(name);
        this.bank = bank;
    }

    @Override
    public void run() {
        // Simulate client operations
        for (int i = 0; i < 5; i++) {
            int amount = (int) (Math.random() * 500) + 1;
            bank.withdrawCash(amount, getName());

            amount = (int) (Math.random() * 500) + 1;
            bank.depositCash(amount, getName());

            try {
                Thread.sleep(1000); // Simulate some delay between operations
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
