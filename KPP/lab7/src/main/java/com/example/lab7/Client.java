package com.example.lab7;

import java.math.BigDecimal;

public class Client {
    private BigDecimal balance;
    private final Bank bank;
    private String name;

    public Client(String name, BigDecimal balance, Bank bank) {
        this.balance = balance;
        this.bank = bank;
        this.name = name;
    }

    public void withdrawCash(BigDecimal amount) throws IllegalArgumentException, InterruptedException {
        if (balance.compareTo(amount) >= 0) {
            bank.withdrawCash(amount);
            balance = balance.subtract(amount);
        } else throw new IllegalArgumentException(name + " does not have such money!");
    }
    public void depositCash(BigDecimal amount) throws InterruptedException {
        balance = balance.add(amount);
        bank.depositCash(amount);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public BigDecimal getBalance() {
            return balance;
    }

    public void setBalance(BigDecimal balance) {
        this.balance = balance;
    }
}
