package com.example.lab7;

import java.math.BigDecimal;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicReference;

public class Bank {
    private final AtomicReference<BigDecimal> totalCash;
    private final Semaphore mutex;

    public Bank(BigDecimal totalCash) {
        mutex = new Semaphore(1);
        this.totalCash = new AtomicReference<>(totalCash);
    }

    public void withdrawCash(BigDecimal amount) throws IllegalArgumentException, InterruptedException {
        mutex.acquire();

        if (totalCash.get().compareTo(amount) >= 0) {
                totalCash.getAndUpdate(sum -> sum.subtract(amount));
        } else throw new IllegalArgumentException("Bank does not have such money!");

        mutex.release();
    }
    public void depositCash(BigDecimal amount) throws InterruptedException {
        mutex.acquire();

        totalCash.getAndUpdate(sum -> sum.add(amount));

        mutex.release();
    }

    public BigDecimal getBalance()  {
         return totalCash.get();
    }

    public void setBalance(BigDecimal totalCash) {
        this.totalCash.set(totalCash);
    }
}
