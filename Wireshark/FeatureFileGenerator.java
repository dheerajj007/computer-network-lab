import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FeatureFileGenerator {
    public static void main(String[] args) {
        // Capture inputs from developers
        List<Account> accounts = captureAccountDetails();

        // Generate feature content based on inputs
        String featureContent = generateFeatureContent(accounts);

        // Save the generated feature content to a file
        saveFeatureFile("AccountManagement.feature", featureContent);
    }

    private static List<Account> captureAccountDetails() {
        List<Account> accounts = new ArrayList<>();

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of accounts: ");
        int numAccounts = scanner.nextInt();
        scanner.nextLine(); // Consume the newline character

        for (int i = 1; i <= numAccounts; i++) {
            System.out.println("\nEnter details for Account " + i);
            System.out.print("Account ID: ");
            String accountId = scanner.nextLine();

            System.out.print("Account Name: ");
            String accountName = scanner.nextLine();

            System.out.print("Account Branch: ");
            String accountBranch = scanner.nextLine();

            // Gather any additional attributes you require

            Account account = new Account(accountId, accountName, accountBranch);
            accounts.add(account);
        }

        return accounts;
    }

    private static String generateFeatureContent(List<Account> accounts) {
    StringBuilder content = new StringBuilder();

    content.append("Feature: Account Management\n\n");

    for (Account account : accounts) {
        content.append("  Scenario: Create Account - ").append(account.getId()).append("\n")
                .append("    Given I am a developer\n")
                .append("    When I provide the following account details:\n")
                .append(String.format("      | ID     | %s |\n", account.getId()))
                .append(String.format("      | Name   | %s |\n", account.getName()))
                .append(String.format("      | Branch | %s |\n", account.getBranch()))
                // Add other attributes as needed
                .append("    Then the account creation should be successful\n\n");
    }

    return content.toString();
}


    private static void saveFeatureFile(String fileName, String featureContent) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(featureContent);
            System.out.println("Feature file saved successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static class Account {
        private final String id;
        private final String name;
        private final String branch;

        public Account(String id, String name, String branch) {
            this.id = id;
            this.name = name;
            this.branch = branch;
        }

        public String getId() {
            return id;
        }

        public String getName() {
            return name;
        }

        public String getBranch() {
            return branch;
        }
    }
}
