package com.example.lab7;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Duration;
import javafx.util.Pair;
import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.HashMap;

public class BankController {
    private ObservableList<BankThread> threads;
    private TrackedExecutorService executor;
    private ThreadManager threadManager;
    @FXML
    private TableView<BankThread> threadsTable;
    @FXML
    private TableColumn<BankThread, String> nameColumn, stateColumn;
    @FXML
    private TableColumn<BankThread, Integer> priorityColumn;
    @FXML
    private TableColumn<BankThread, LocalDateTime> statusChangeTimeColumn;
    @FXML
    private TableColumn<BankThread, Void> toggleActivenessButton;
    @FXML
    private TableColumn<BankThread, BigDecimal> balanceColumn;
    @FXML
    private Label balance;
    @FXML
    private TextField threadsAmount, keepAliveTime;
    private Bank bank;

    @FXML
    public void initialize() {
        bank = new Bank(new BigDecimal(0));
        threadManager = new ThreadManager();

        HashMap<Long, Pair<Thread.State, LocalDateTime>> threadsStatusChange = new HashMap<>();
        threads = FXCollections.observableArrayList();

        nameColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getName()));
        priorityColumn.setCellValueFactory(cellData -> new SimpleObjectProperty<>(cellData.getValue().getPriority()));
        stateColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().isPaused() ? "PAUSED" : cellData.getValue().getState().toString()));
        statusChangeTimeColumn.setCellValueFactory(cellData -> {
            var thread = threadsStatusChange.getOrDefault(cellData.getValue().threadId(), null);
            LocalDateTime datetime = thread == null || !thread.getKey().equals(cellData.getValue().getState())
                    ? LocalDateTime.now()
                    : thread.getValue();
            threadsStatusChange.put(cellData.getValue().threadId(), new Pair<>(cellData.getValue().getState(), datetime));
            return new SimpleObjectProperty<>(datetime);
        });
        balanceColumn.setCellValueFactory(cellData -> new SimpleObjectProperty<>(cellData.getValue().getClient().getBalance()));
        toggleActivenessButton.setCellFactory(col -> new TableCell<>() {
            private final Button clearButton;
            {
                clearButton = new Button("Toggle Activeness");
                clearButton.setOnAction(event ->  {
                    BankThread thread = getTableView().getItems().get(getIndex());
                    if(!thread.isInterrupted())
                        thread.togglePauseness();
                });
            }
            @Override
            public void updateItem(Void item, boolean empty) {
                clearButton.disableProperty().unbind();
                super.updateItem(item, empty);
                setGraphic(empty ? null : clearButton);
            }
        });
        threadsTable.setItems(threads);
    }

    @FXML
    protected void onCreateButtonClick() {
        try {
            this.onTerminateAllThreadsClick();
            threads.addAll(threadManager.createThreads(bank, Integer.parseInt(threadsAmount.getText())));

            executor = threadManager.createExecutor(Integer.parseInt(threadsAmount.getText()), Integer.parseInt(keepAliveTime.getText()));
            threads.forEach(t->executor.submitTask(t));

            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(0.5), e -> update()));
            timeline.setCycleCount(Animation.INDEFINITE);
            timeline.playFromStart();
        } catch (NumberFormatException e) {
            this.onTerminateAllThreadsClick();
            balance.setText("Error : " + e.getMessage());
        }
    }

    @FXML
    protected void onTerminateAllThreadsClick(){
        if(executor!=null)
            executor.shutdown();
        threads.clear();
        balance.setText("");
    }

    public void update() {
        threadsTable.refresh();
        balance.setText("Bank balance: " + bank.getBalance());
    }
}