package com.example.lab7;

import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

public class BankThreadPanel extends VBox {

    private static BankThreadPanel instance;
    private Bank bank;

    private BankThreadPanel() {
        // Singleton pattern
    }

    public static BankThreadPanel getInstance() {
        if (instance == null) {
            instance = new BankThreadPanel();
        }
        return instance;
    }

    public void setBank(Bank bank) {
        this.bank = bank;
    }

    public Bank getBank() {
        return bank;
    }

    public void addThreadPanel(String threadName) {
        ThreadPanel threadPanel = new ThreadPanel(threadName, bank);
        getChildren().add(threadPanel);
    }

    private static class ThreadPanel extends HBox {

        private final Label threadInfoLabel;

        public ThreadPanel(String threadName, Bank bank) {
            setSpacing(10);
            setAlignment(Pos.CENTER);

            // Create UI elements
            threadInfoLabel = new Label(threadName + ": Not Started");
            Button startButton = new Button("Start");
            Button pauseButton = new Button("Pause");

            // Event handlers for start and pause buttons
            startButton.setOnAction(event -> {
                threadInfoLabel.setText(threadName + ": Running");
                new ClientThread(threadName, bank).start();
            });

            pauseButton.setOnAction(event ->
                    threadInfoLabel.setText(threadName + ": Paused"));

            getChildren().addAll(threadInfoLabel, startButton, pauseButton);
        }
    }
}
