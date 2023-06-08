import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.*;

public class FeatureFileGenerator {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USERNAME = "username";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        // Fetch data from the database
        String accountName = fetchDataFromDatabase("SELECT name FROM accounts WHERE id = 1");
        String accountNumber = fetchDataFromDatabase("SELECT number FROM accounts WHERE id = 1");
        String cycleDetails = fetchDataFromDatabase("SELECT details FROM cycles WHERE id = 1");

        // Generate the feature file content based on fetched data
        String featureFileContent = generateFeatureFileContent(accountName, accountNumber, cycleDetails);

        // Save the generated feature file
        saveFeatureFile("GeneratedFeature.feature", featureFileContent);

        System.out.println("Feature file generated successfully!");
    }

    private static String fetchDataFromDatabase(String query) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USERNAME, DB_PASSWORD);
             Statement statement = connection.createStatement();
             ResultSet resultSet = statement.executeQuery(query)) {

            if (resultSet.next()) {
                return resultSet.getString(1);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    private static String generateFeatureFileContent(String accountName, String accountNumber, String cycleDetails) {
        StringBuilder content = new StringBuilder();

        content.append("Feature: Account Management\n")
                .append("\n")
                .append("  Scenario: Account Creation\n")
                .append("    Given I have the following account details:\n")
                .append("      | Name   | ").append(accountName).append(" |\n")
                .append("      | Number | ").append(accountNumber).append(" |\n")
                .append("    When I initiate the account creation\n")
                .append("    Then the account should be created successfully\n")
                .append("\n")
                .append("  Scenario: Cycle Details\n")
                .append("    Given I have the following cycle details:\n")
                .append("      | Details | ").append(cycleDetails).append(" |\n")
                .append("    When I perform the cycle operation\n")
                .append("    Then the operation should be successful\n");

        return content.toString();
    }

    private static void saveFeatureFile(String fileName, String content) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
