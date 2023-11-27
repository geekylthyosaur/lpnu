package com.example.lab7;

import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;

public class BankSimulation extends VBox {

    public BankSimulation() {
        setupUI();
    }

    private void setupUI() {
        // Create UI elements
        TextField threadCountField = new TextField("5");
        TextField resourceLimitField = new TextField("1000");
        Button startButton = getStartButton(threadCountField, resourceLimitField);

        // Layout
        HBox inputBox = new HBox(10, new Label("Thread Count:"), threadCountField,
                new Label("Resource Limit:"), resourceLimitField, startButton);
        inputBox.setAlignment(Pos.CENTER);

        getChildren().addAll(inputBox, BankThreadPanel.getInstance());
    }

    private static Button getStartButton(TextField threadCountField, TextField resourceLimitField) {
        Button startButton = new Button("Start Simulation");

        // Event handler for the start button
        startButton.setOnAction(event -> {
            int threadCount = Integer.parseInt(threadCountField.getText());
            int resourceLimit = Integer.parseInt(resourceLimitField.getText());

            // Start the bank simulation
            Bank bank = new Bank(resourceLimit);
            for (int i = 0; i < threadCount; i++) {
                ClientThread clientThread = new ClientThread("Thread " + (i + 1), bank);
                clientThread.start();
            }
        });
        return startButton;
    }
}
