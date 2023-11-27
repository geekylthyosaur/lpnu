package com.example.lab7;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Thread Bank Simulation");

        // Create the main layout
        VBox root = new VBox();
        root.getChildren().add(new BankSimulation());

        Scene scene = new Scene(root, 600, 400);
        primaryStage.setScene(scene);

        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
