package com.example.lab7;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class ThreadManager {

    TrackedExecutorService executorService;
    List<BankThread> threads;


    public List<BankThread> createThreads(Bank bank, int amount) throws NumberFormatException {
        if (amount < 0){
            throw new NumberFormatException("The number is less than 0");
        }
        Random random = new Random();

        bank.setBalance(new BigDecimal(amount * 250));
        System.out.println(bank.getBalance());
        threads = new ArrayList<>();
        for (int i = 0; i != amount; ++i) {
            Client client = new Client("Client " + i, new BigDecimal(250), bank);
            var thread = new BankThread(client);

            thread.setName(client.getName());
            thread.setPriority(random.nextInt(1,11));
            threads.add(thread);
        }
        return threads;
    }

    public TrackedExecutorService createExecutor(int corePoolSize, int keepAliveTime) throws NumberFormatException{
        if (corePoolSize < 0 || keepAliveTime < 0){
            throw new NumberFormatException("The number is less than 0");
        }
        executorService = new TrackedExecutorService(corePoolSize, keepAliveTime);
        return executorService;
    }

    public TrackedExecutorService getExecutorService() {
        return executorService;
    }

    public List<BankThread> getThreads() {
        return threads;
    }
}
