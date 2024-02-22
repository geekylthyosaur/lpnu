package com.example.lab7;

import java.math.BigDecimal;
import java.util.Random;

public class BankThread extends Thread {
    private boolean paused, stopped;
    private final Client client;
    private final Random random;

    public BankThread(Client client) {
        paused = false;
        this.client = client;
        random = new Random();
    }

    public Client getClient() {
        return client;
    }

    @Override
    public void run() {
        while (!currentThread().isInterrupted()) {
            synchronized (this) {
                if(stopped){
                    currentThread().interrupt();
                }
                if (paused) {
                    try {
                        this.wait();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
                try {
                    var amount = new BigDecimal(random.nextInt(0, 10));
                    if (random.nextInt(0, 2) == 0) {
                        client.depositCash(amount);
                        System.out.println(client.getName() + " deposited " + amount + ". Current balance is " + client.getBalance());
                    } else {
                        client.withdrawCash(amount);
                        System.out.println(client.getName() + " withdrew " + amount + ". Current balance is " + client.getBalance());
                    }
                } catch (IllegalArgumentException | InterruptedException e) {

                }
            }
        }
    }

    public boolean isPaused() {
        return paused;
    }

    public void togglePause() {
        paused = !paused;
        if (!paused) {
            synchronized (this) {
                this.notifyAll();
            }
        }
    }

    public void stopThread(){
        stopped = true;
    }
}
